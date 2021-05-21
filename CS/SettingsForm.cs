using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GarantEEG_Viewer
{
    public partial class SettingsForm : Form
    {
        public SettingsForm()
        {
            InitializeComponent();

            colorDialog1.FullOpen = true;

            bt_ColorPo7.BackColor = Color.FromArgb(ConfigManager.Config.CurveColors[0]);
            bt_ColorO1.BackColor = Color.FromArgb(ConfigManager.Config.CurveColors[1]);
            bt_ColorOz.BackColor = Color.FromArgb(ConfigManager.Config.CurveColors[2]);
            bt_ColorP3.BackColor = Color.FromArgb(ConfigManager.Config.CurveColors[3]);
            bt_ColorPz.BackColor = Color.FromArgb(ConfigManager.Config.CurveColors[4]);
            bt_ColorP4.BackColor = Color.FromArgb(ConfigManager.Config.CurveColors[5]);
            bt_ColorO2.BackColor = Color.FromArgb(ConfigManager.Config.CurveColors[6]);
            bt_ColorPo8.BackColor = Color.FromArgb(ConfigManager.Config.CurveColors[7]);

            cb_UsePo7.Checked = ConfigManager.Config.CurveIsChecked[0];
            cb_UseO1.Checked = ConfigManager.Config.CurveIsChecked[1];
            cb_UseOz.Checked = ConfigManager.Config.CurveIsChecked[2];
            cb_UseP3.Checked = ConfigManager.Config.CurveIsChecked[3];
            cb_UsePz.Checked = ConfigManager.Config.CurveIsChecked[4];
            cb_UseP4.Checked = ConfigManager.Config.CurveIsChecked[5];
            cb_UseO2.Checked = ConfigManager.Config.CurveIsChecked[6];
            cb_UsePo8.Checked = ConfigManager.Config.CurveIsChecked[7];

            checkBox9.Checked = ConfigManager.Config.UseFilters;

            listBox1.Items.Clear();

            if (MainWindow.m_GarantEEG != null)
            {
                var filters = MainWindow.m_GarantEEG.GetFilters();

                foreach (var filter in filters)
                {
                    listBox1.Items.Add(string.Format("Butterworth: {0} Hz", filter.Frequency()));
                }
            }
        }

        private void SelectColor(Button button, ref int configColor)
        {
            colorDialog1.Color = button.BackColor;

            if (colorDialog1.ShowDialog() == DialogResult.Cancel)
                return;

            button.BackColor = colorDialog1.Color;
            configColor = button.BackColor.ToArgb();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            SelectColor(bt_ColorPo7, ref ConfigManager.Config.CurveColors[0]);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            SelectColor(bt_ColorO1, ref ConfigManager.Config.CurveColors[1]);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            SelectColor(bt_ColorOz, ref ConfigManager.Config.CurveColors[2]);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            SelectColor(bt_ColorP3, ref ConfigManager.Config.CurveColors[3]);
        }

        private void button8_Click(object sender, EventArgs e)
        {
            SelectColor(bt_ColorPz, ref ConfigManager.Config.CurveColors[4]);
        }

        private void button9_Click(object sender, EventArgs e)
        {
            SelectColor(bt_ColorP4, ref ConfigManager.Config.CurveColors[5]);
        }

        private void button10_Click(object sender, EventArgs e)
        {
            SelectColor(bt_ColorO2, ref ConfigManager.Config.CurveColors[6]);
        }

        private void button11_Click(object sender, EventArgs e)
        {
            SelectColor(bt_ColorPo8, ref ConfigManager.Config.CurveColors[7]);
        }

        private void button12_Click(object sender, EventArgs e)
        {
            Form5 f = new Form5();
            f.ShowDialog();

            listBox1.Items.Clear();
            ConfigManager.Config.Filters.Clear();

            var filters = MainWindow.m_GarantEEG.GetFilters();

            foreach (var filter in filters)
            {
                listBox1.Items.Add(string.Format("Butterworth: {0} Hz", filter.Frequency()));
                ConfigManager.Config.Filters.Add(new FilterInfo(filter.Type(), filter.Frequency()));
            }
        }

        private void button13_Click(object sender, EventArgs e)
        {
            DialogResult res = MessageBox.Show(
                "Are you shure you want to delete the selected filter?",
                "Remove filter?",
                MessageBoxButtons.YesNo,
                MessageBoxIcon.Question);

            if (res == DialogResult.Yes)
            {
                int index = listBox1.SelectedIndex;

                if (index >= 0 && index < listBox1.Items.Count)
                {
                    listBox1.Items.RemoveAt(index);

                    if (index < ConfigManager.Config.Filters.Count)
                        ConfigManager.Config.Filters.RemoveAt(index);

                    if (MainWindow.m_GarantEEG != null)
                    {
                        var filters = MainWindow.m_GarantEEG.GetFilters();

                        if (index < filters.Count)
                            MainWindow.m_GarantEEG.RemoveFilter(filters[index]);
                    }
                }
            }
        }

        private void button14_Click(object sender, EventArgs e)
        {
            DialogResult res = MessageBox.Show(
                "Are you shure you want to delete the all filters?",
                "Remove filters",
                MessageBoxButtons.YesNo,
                MessageBoxIcon.Question);

            if (res == DialogResult.Yes)
            {
                listBox1.Items.Clear();
                ConfigManager.Config.Filters.Clear();

                if (MainWindow.m_GarantEEG != null)
                    MainWindow.m_GarantEEG.RemoveAllFilters();
            }
        }

        private void cb_UsePo7_CheckedChanged(object sender, EventArgs e)
        {
            ConfigManager.Config.CurveIsChecked[0] = cb_UsePo7.Checked;
        }

        private void cb_UseO1_CheckedChanged(object sender, EventArgs e)
        {
            ConfigManager.Config.CurveIsChecked[1] = cb_UseO1.Checked;
        }

        private void cb_UseOz_CheckedChanged(object sender, EventArgs e)
        {
            ConfigManager.Config.CurveIsChecked[2] = cb_UseOz.Checked;
        }

        private void cb_UseP3_CheckedChanged(object sender, EventArgs e)
        {
            ConfigManager.Config.CurveIsChecked[3] = cb_UseP3.Checked;
        }

        private void cb_UsePz_CheckedChanged(object sender, EventArgs e)
        {
            ConfigManager.Config.CurveIsChecked[4] = cb_UsePz.Checked;
        }

        private void cb_UseP4_CheckedChanged(object sender, EventArgs e)
        {
            ConfigManager.Config.CurveIsChecked[5] = cb_UseP4.Checked;
        }

        private void cb_UseO2_CheckedChanged(object sender, EventArgs e)
        {
            ConfigManager.Config.CurveIsChecked[6] = cb_UseO2.Checked;
        }

        private void cb_UsePo8_CheckedChanged(object sender, EventArgs e)
        {
            ConfigManager.Config.CurveIsChecked[7] = cb_UsePo8.Checked;
        }

        private void button15_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void checkBox9_CheckedChanged(object sender, EventArgs e)
        {
            ConfigManager.Config.UseFilters = checkBox9.Checked;
        }
    }
}
