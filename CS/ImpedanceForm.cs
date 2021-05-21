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

namespace GarantEEG_Viewer
{
    public partial class ImpedanceForm : Form
    {
        private static Timer m_Timer = new Timer();

        public ImpedanceForm()
        {
            InitializeComponent();

            m_Timer.Tick += OnTimer;

            m_Timer.Interval = 500;
            m_Timer.Start();
            pictureBox1.Update();
        }

        public static List<string> Channels()
        {
            return new List<string>{ "Po7", "O1", "Oz", "P3", "Pz", "P4", "O2", "Po8", "Ref", "Gnd" };
        }

        public void OnTimer(object sender, EventArgs e)
        {
            pictureBox1.Refresh();
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            int x1 = 200;
            int x2 = 600;
            int y1 = 300;
            int y2 = 500;


            int c = 15;
            //бока
            Pen pen = new Pen(Color.Black);
            e.Graphics.DrawLine(pen, new Point(x1, y1), new Point(x1, y2));
            e.Graphics.DrawLine(pen, new Point(x2, y1), new Point(x2, y2));

            //верхняя дуга
            Rectangle rect = new Rectangle(200, 150, 400, 300);
            e.Graphics.DrawArc(pen, rect, 0, -180);

            //нижняя дуга
            Rectangle rect2 = new Rectangle(200, 350, 400, 300);
            e.Graphics.DrawArc(pen, rect2, 0, 180);

            //левое ухо
            Rectangle rect3 = new Rectangle(175, 350, 50, 100);
            e.Graphics.DrawArc(pen, rect3, 90, 180);

            //правое ухо
            Rectangle rect4 = new Rectangle(575, 350, 50, 100);
            e.Graphics.DrawArc(pen, rect4, -90, 180);

            //нос
            Rectangle rect5 = new Rectangle(380, 125, 40, 50);
            e.Graphics.DrawArc(pen, rect5, 0, -180);



            List<string> channels = Channels();
            List<Point> positions = new List<Point>
                {
                    new Point(230, 490), //Po7
                    new Point(300, 550), //O1
                    new Point(385, 600), //Oz
                    new Point(300, 440), //P3
                    new Point(385, 400), //Pz
                    new Point(470, 440), //P4
                    new Point(470, 550), //O2
                    new Point(540, 490), //Po8
                    new Point(585, 385), //Ref
                    new Point(385, 180) //Gnd
        };

            StringFormat stringFormat = new StringFormat();
            stringFormat.Alignment = StringAlignment.Center;
            stringFormat.LineAlignment = StringAlignment.Center;

            listBox1.Items.Clear();

            for (int i = 0; i < channels.Count; i++)
            {
                int x = positions[i].X;
                int y = positions[i].Y;

                //круги заливка
                SolidBrush redBrush = new SolidBrush(Color.Red);
                e.Graphics.FillEllipse(redBrush, x, y, 30, 30);

                //круги контур
                Rectangle rect6 = new Rectangle(x, y, 30, 30);
                e.Graphics.DrawArc(pen, rect6, 0, 360);

                //фон текста
                SolidBrush solidBrush = new SolidBrush(Color.LightGray);
                e.Graphics.FillRectangle(solidBrush, x - 10, y + 33, 50, 28);

                //текст к кругам
                e.Graphics.DrawString(channels[i], Font, Brushes.Black, x + c, y + c, stringFormat);

                e.Graphics.DrawString(string.Format("{0}\n{1}", channels[i], MainWindow.m_RX[i]), Font, Brushes.Black, x + c, y + 48, stringFormat);

                listBox1.Items.Add(string.Format("{0} = {1} kOhm", channels[i], MainWindow.m_RX[i]));
            }
        }

        private void pictureBox1_LoadCompleted(object sender, AsyncCompletedEventArgs e)
        {
            this.pictureBox1.SizeMode = PictureBoxSizeMode.Zoom;
        }
    }
}
