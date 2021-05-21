using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using GarantEEG;
using TinyJson;
using System.Windows.Forms.DataVisualization.Charting;

namespace GarantEEG_Viewer
{
    public partial class MainWindow : Form
    {
        public static IGarantEEG m_GarantEEG { get; set; }

        private static System.Threading.Mutex m_Mutex = new System.Threading.Mutex();

        private static Timer m_DataTimer = new Timer();

        private static Timer m_RecordTimer = new Timer();

        private static DateTime m_RecordStartTime;

        private List<GARANT_EEG_DATA> m_BufferData;

        public static double[] m_RX = new double[10];

        public MainWindow()
        {
            ConfigManager.Config = ConfigManager.Load("garant_eeg.json");

            InitializeComponent();

            le_IP.Text = ConfigManager.Config.IP;
            le_Port.Text = ConfigManager.Config.Port.ToString();
            cb_AutoReconnection.Checked = ConfigManager.Config.Autoreconnect;

            m_BufferData = new List<GARANT_EEG_DATA>();

            m_GarantEEG = new CGarantEEG();

            chart1.ChartAreas.Clear();
            chart1.ChartAreas.Add(new ChartArea("area"));

            UpdateChartSeries();

            List<FilterInfo> filters = ConfigManager.Config.Filters;

            foreach (FilterInfo filter in filters)
            {
                m_GarantEEG.AddFilter(filter.Type, m_GarantEEG.GetRate(), filter.Frequency);
            }

            m_GarantEEG.ConnectionStateChanged += OnConnectionStateChanged;
            m_GarantEEG.RecordingStateChanged += OnRecordingStateChanged;
            m_GarantEEG.ReceivedData += OnReceivedData;
            m_DataTimer.Tick += OnUpdateDataTimer;
            m_RecordTimer.Tick += OnUpdateRecordTimer;

            m_DataTimer.Interval = 100;
            m_DataTimer.Start();

            m_RecordTimer.Interval = 100;
        }

        public void OnConnectionStateChanged(object sender, int code)
        {
        }

        public void OnRecordingStateChanged(object sender, int code)
        {
        }

        public void OnReceivedData(object sender, GARANT_EEG_DATA eegData)
        {
            if (m_GarantEEG == null || !m_GarantEEG.IsStarted())
                return;

            if (eegData.DataRecordsCount > 0)
            {
                m_Mutex.WaitOne();

                m_BufferData.Add(eegData);

                m_Mutex.ReleaseMutex();
            }
        }

        public void OnUpdateDataTimer(object sender, EventArgs e)
        {
            m_Mutex.WaitOne();

            //Debug.WriteLine("OnUpdateDataTimer {0}", m_BufferData.Count);

            if (m_BufferData.Count > 0)
            {
                for (int di = 0; di < m_BufferData.Count; di++)
                {
                    GARANT_EEG_DATA eegData = m_BufferData[di];

                    bool useFilters = (ConfigManager.Config.UseFilters && m_GarantEEG.GetFiltersCount() != 0);
                    int seriesIndex = 0;

                    for (int i = 0; i < 8; i++)
                    {
                        if (!ConfigManager.Config.CurveIsChecked[i] || chart1.Series.Count <= seriesIndex)
                            continue;

                        List<double> points = new List<double>();

                        for (int ci = 0; ci < chart1.Series[seriesIndex].Points.Count; ci++)
                            points.AddRange(chart1.Series[seriesIndex].Points[ci].YValues.ToList<double>()); //.Add(chart1.Series[i].Points[ci].YValues.ToList<double>());

                        chart1.Series[seriesIndex].Points.Clear();

                        for (int j = 0; j < eegData.DataRecordsCount; j++)
                        {
                            double value = (useFilters ? eegData.FilteredChannelsData[j].Value[i] : eegData.RawChannelsData[j].Value[i]) * 1000.0;
                            //double value = eegData.RawChannelsData[j].Value[i] + ((i - 4.0) * 1.0);
                            //double value = eegData.RawChannelsData[j].Value[i] + ((i - 4) * 0.001);

                            points.Add(value);
                            //chart1.Series[i].Points.Add(value);
                        }

                        while (points.Count > 2000)
                            points.RemoveAt(0);

                        for (int ci = 0; ci < points.Count; ci++)
                            chart1.Series[seriesIndex].Points.Add(points[ci]);

                        seriesIndex++;
                    }

                    for (int i = 0; i < 8; i++)
                    {
                        m_RX[i] = eegData.ResistanceData.Value[i];
                    }

                    m_RX[8] = eegData.ResistanceData.Ref;
                    m_RX[9] = eegData.ResistanceData.Ground;
                }
                //FIXME
                /*for (int i = 0; i < 8; i++)
                {
                    std::vector<float> y;

                    for (int j = 0; j < eegData.DataRecordsCount; j++)
                    {
                        double value = (useFilters ? eegData.FilteredChannelsData[j].Value[i] : eegData.RawChannelsData[j].Value[i]) * 1000.0;
                        //double value = eegData.RawChannelsData[j].Value[i] + ((i - 4.0) * 1.0);
                        //double value = eegData.RawChannelsData[j].Value[i] + ((i - 4) * 0.001);

                        y.push_back(value);
                    }

                    ui->qwt_Chart->appendPoints(QString("EEG%1").arg(i + 1), y);
                }

                ui->qwt_Chart->updateView();

                ui->pb_Battery->setValue(m_Eeg->GetBatteryStatus());*/

                m_BufferData.Clear();
            }

            if (m_GarantEEG != null)
            {
                pb_Progress.Value = m_GarantEEG.GetBatteryStatus();
                label1.Text = string.Format("{0}% battery", m_GarantEEG.GetBatteryStatus());
            }

            m_Mutex.ReleaseMutex();
        }

        public void OnUpdateRecordTimer(object sender, EventArgs e)
        {
            TimeSpan delta = DateTime.Now - m_RecordStartTime;
            label2.Text = "Recording time: " + delta.ToString(@"hh\:mm\:ss\.fff");
        }

        private void le_IP_TextChanged(object sender, EventArgs e)
        {
            TextBox control = (TextBox)sender;
            ConfigManager.Config.IP = control.Text;
        }

        private void le_Port_ValueChanged(object sender, EventArgs e)
        {
            NumericUpDown control = (NumericUpDown)sender;
            ConfigManager.Config.Port = (int)control.Value;
        }

        private void UpdateChartSeries()
        {
            chart1.Series.Clear();

            List<string> channels = ImpedanceForm.Channels();

            for (int i = 0; i < 8; i++)
            {
                if (!ConfigManager.Config.CurveIsChecked[i])
                    continue;

                Series series = new Series(channels[i])
                {
                    ChartType = SeriesChartType.Line,
                    IsValueShownAsLabel = false
                };

                series.SmartLabelStyle.Enabled = false;
                series.Color = Color.FromArgb(ConfigManager.Config.CurveColors[i]);

                chart1.Series.Add(series);
            }
        }

        private void bt_Settings_Click(object sender, EventArgs e)
        {
            SettingsForm f = new SettingsForm();
            f.ShowDialog();

            UpdateChartSeries();
        }

        private void bt_CheckImpedance_Click(object sender, EventArgs e)
        {
            ImpedanceForm f = new ImpedanceForm();
            f.ShowDialog();
        }

        private void cb_AutoReconnection_Click(object sender, EventArgs e)
        {
            CheckBox control = (CheckBox)sender;
            ConfigManager.Config.Autoreconnect = control.Checked;

            if (m_GarantEEG != null)
                m_GarantEEG.SetAutoReconnection(ConfigManager.Config.Autoreconnect);
        }

        private void bt_Start_Click(object sender, EventArgs e)
        {
            if (m_GarantEEG == null)
                return;

            int port = (int)le_Port.Value;

            if (m_GarantEEG.Start(true, 500, le_IP.Text, port))
            {
                Debug.WriteLine("started ok");
            }
            else
            {
                Debug.WriteLine("started ne ok");
            }
        }

        private void bt_Stop_Click(object sender, EventArgs e)
        {
            if (m_GarantEEG == null)
                return;

            m_GarantEEG.Stop();
        }

        private void bt_Pause_Click(object sender, EventArgs e)
        {
            if (m_GarantEEG == null || !m_GarantEEG.IsStarted() || m_GarantEEG.IsRecording() || m_GarantEEG.IsPaused())
                return;

            m_GarantEEG.StopDataTranslation();
        }

        private void bt_Resume_Click(object sender, EventArgs e)
        {
            if (m_GarantEEG == null || !m_GarantEEG.IsStarted() || m_GarantEEG.IsRecording() || !m_GarantEEG.IsPaused())
                return;

            m_GarantEEG.StartDataTranslation();
        }

        private void bt_RecordStart_Click(object sender, EventArgs e)
        {
            if (m_GarantEEG == null || !m_GarantEEG.IsStarted() || m_GarantEEG.IsRecording() || m_GarantEEG.IsPaused())
                return;

            if (m_GarantEEG.StartRecord("user"))
            {
                m_RecordStartTime = DateTime.Now;
                m_RecordTimer.Start();
                Debug.WriteLine("record started");
            }
            else
            {
                Debug.WriteLine("record start failed");
            }
        }

        private void bt_RecordStop_Click(object sender, EventArgs e)
        {
            if (m_GarantEEG == null || !m_GarantEEG.IsStarted() || !m_GarantEEG.IsRecording() || m_GarantEEG.IsPaused())
                return;

            m_RecordTimer.Stop();
            m_GarantEEG.StopRecord();
        }

        private void bt_RecordPause_Click(object sender, EventArgs e)
        {
            if (m_GarantEEG == null || !m_GarantEEG.IsStarted() || !m_GarantEEG.IsRecording() || m_GarantEEG.IsRecordPaused())
                return;

            m_GarantEEG.PauseRecord();
        }

        private void bt_RecordResume_Click(object sender, EventArgs e)
        {
            if (m_GarantEEG == null || !m_GarantEEG.IsStarted() || !m_GarantEEG.IsRecording() || !m_GarantEEG.IsRecordPaused())
                return;

            m_GarantEEG.ResumeRecord();
        }

        private void MainWindow_FormClosing(object sender, FormClosingEventArgs e)
        {
            ConfigManager.Config.Save("garant_eeg.json");

            //FIXME
            //Close impedance form
        }
    }
}
