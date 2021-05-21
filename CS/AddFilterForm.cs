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
    public partial class Form5 : Form
    {
        public Form5()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (MainWindow.m_GarantEEG != null)
            {
                GarantEEG.GARANT_EEG_FILTER_TYPE type = GarantEEG.GARANT_EEG_FILTER_TYPE.FT_BUTTERWORTH;

                GarantEEG.IFilter filter = MainWindow.m_GarantEEG.AddFilter((int)type, MainWindow.m_GarantEEG.GetRate(), (int)numericUpDown2.Value);

                if (filter == null)
                {
                    MessageBox.Show(
                        "An error occurred while creating the filter!",
                        "Create filter error",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error);

                    return;
                }
            }

            Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
