namespace GarantEEG_Viewer
{
    partial class SettingsForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel3 = new System.Windows.Forms.TableLayoutPanel();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.tableLayoutPanel5 = new System.Windows.Forms.TableLayoutPanel();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel4 = new System.Windows.Forms.TableLayoutPanel();
            this.cb_UsePo8 = new System.Windows.Forms.CheckBox();
            this.cb_UseO2 = new System.Windows.Forms.CheckBox();
            this.cb_UseP4 = new System.Windows.Forms.CheckBox();
            this.cb_UsePz = new System.Windows.Forms.CheckBox();
            this.cb_UseP3 = new System.Windows.Forms.CheckBox();
            this.cb_UseOz = new System.Windows.Forms.CheckBox();
            this.cb_UseO1 = new System.Windows.Forms.CheckBox();
            this.cb_UsePo7 = new System.Windows.Forms.CheckBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.bt_ColorPo7 = new System.Windows.Forms.Button();
            this.bt_ColorO1 = new System.Windows.Forms.Button();
            this.bt_ColorOz = new System.Windows.Forms.Button();
            this.bt_ColorP3 = new System.Windows.Forms.Button();
            this.bt_ColorPz = new System.Windows.Forms.Button();
            this.bt_ColorP4 = new System.Windows.Forms.Button();
            this.bt_ColorO2 = new System.Windows.Forms.Button();
            this.bt_ColorPo8 = new System.Windows.Forms.Button();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.button15 = new System.Windows.Forms.Button();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.tableLayoutPanel6 = new System.Windows.Forms.TableLayoutPanel();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.bt_RemoveAllFilters = new System.Windows.Forms.Button();
            this.bt_AddFilter = new System.Windows.Forms.Button();
            this.bt_RemoveFilter = new System.Windows.Forms.Button();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.checkBox9 = new System.Windows.Forms.CheckBox();
            this.colorDialog1 = new System.Windows.Forms.ColorDialog();
            this.groupBox1.SuspendLayout();
            this.tableLayoutPanel3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            this.tableLayoutPanel1.SuspendLayout();
            this.tableLayoutPanel5.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.tableLayoutPanel4.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.tableLayoutPanel6.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.tableLayoutPanel3);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.Location = new System.Drawing.Point(3, 273);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(437, 144);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "EEG handling";
            // 
            // tableLayoutPanel3
            // 
            this.tableLayoutPanel3.ColumnCount = 2;
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 250F));
            this.tableLayoutPanel3.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel3.Controls.Add(this.groupBox2, 0, 0);
            this.tableLayoutPanel3.Controls.Add(this.button3, 1, 0);
            this.tableLayoutPanel3.Location = new System.Drawing.Point(5, 13);
            this.tableLayoutPanel3.Name = "tableLayoutPanel3";
            this.tableLayoutPanel3.RowCount = 1;
            this.tableLayoutPanel3.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel3.Size = new System.Drawing.Size(452, 125);
            this.tableLayoutPanel3.TabIndex = 0;
            // 
            // groupBox2
            // 
            this.groupBox2.AutoSize = true;
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.numericUpDown1);
            this.groupBox2.Controls.Add(this.button2);
            this.groupBox2.Controls.Add(this.button1);
            this.groupBox2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox2.Location = new System.Drawing.Point(3, 3);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(244, 119);
            this.groupBox2.TabIndex = 0;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Indication test";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(62, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Value, kOm";
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.AutoSize = true;
            this.numericUpDown1.Location = new System.Drawing.Point(106, 20);
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(88, 20);
            this.numericUpDown1.TabIndex = 1;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(6, 46);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(188, 24);
            this.button2.TabIndex = 0;
            this.button2.Text = "Start";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(6, 76);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(188, 24);
            this.button1.TabIndex = 0;
            this.button1.Text = "Stop";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(265, 15);
            this.button3.Margin = new System.Windows.Forms.Padding(15, 15, 3, 3);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(84, 24);
            this.button3.TabIndex = 0;
            this.button3.Text = "Power off";
            this.button3.UseVisualStyleBackColor = true;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel5, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 1, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 1;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(898, 489);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // tableLayoutPanel5
            // 
            this.tableLayoutPanel5.ColumnCount = 1;
            this.tableLayoutPanel5.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel5.Controls.Add(this.groupBox1, 0, 1);
            this.tableLayoutPanel5.Controls.Add(this.groupBox3, 0, 0);
            this.tableLayoutPanel5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel5.Location = new System.Drawing.Point(3, 3);
            this.tableLayoutPanel5.Name = "tableLayoutPanel5";
            this.tableLayoutPanel5.RowCount = 3;
            this.tableLayoutPanel5.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 270F));
            this.tableLayoutPanel5.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 150F));
            this.tableLayoutPanel5.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel5.Size = new System.Drawing.Size(443, 483);
            this.tableLayoutPanel5.TabIndex = 1;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.tableLayoutPanel4);
            this.groupBox3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox3.Location = new System.Drawing.Point(3, 3);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(437, 264);
            this.groupBox3.TabIndex = 3;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Chart settings";
            // 
            // tableLayoutPanel4
            // 
            this.tableLayoutPanel4.CellBorderStyle = System.Windows.Forms.TableLayoutPanelCellBorderStyle.Single;
            this.tableLayoutPanel4.ColumnCount = 2;
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 20F));
            this.tableLayoutPanel4.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 80F));
            this.tableLayoutPanel4.Controls.Add(this.cb_UsePo8, 0, 8);
            this.tableLayoutPanel4.Controls.Add(this.cb_UseO2, 0, 7);
            this.tableLayoutPanel4.Controls.Add(this.cb_UseP4, 0, 6);
            this.tableLayoutPanel4.Controls.Add(this.cb_UsePz, 0, 5);
            this.tableLayoutPanel4.Controls.Add(this.cb_UseP3, 0, 4);
            this.tableLayoutPanel4.Controls.Add(this.cb_UseOz, 0, 3);
            this.tableLayoutPanel4.Controls.Add(this.cb_UseO1, 0, 2);
            this.tableLayoutPanel4.Controls.Add(this.cb_UsePo7, 0, 1);
            this.tableLayoutPanel4.Controls.Add(this.label2, 0, 0);
            this.tableLayoutPanel4.Controls.Add(this.label3, 1, 0);
            this.tableLayoutPanel4.Controls.Add(this.bt_ColorPo7, 1, 1);
            this.tableLayoutPanel4.Controls.Add(this.bt_ColorO1, 1, 2);
            this.tableLayoutPanel4.Controls.Add(this.bt_ColorOz, 1, 3);
            this.tableLayoutPanel4.Controls.Add(this.bt_ColorP3, 1, 4);
            this.tableLayoutPanel4.Controls.Add(this.bt_ColorPz, 1, 5);
            this.tableLayoutPanel4.Controls.Add(this.bt_ColorP4, 1, 6);
            this.tableLayoutPanel4.Controls.Add(this.bt_ColorO2, 1, 7);
            this.tableLayoutPanel4.Controls.Add(this.bt_ColorPo8, 1, 8);
            this.tableLayoutPanel4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel4.Location = new System.Drawing.Point(3, 16);
            this.tableLayoutPanel4.Name = "tableLayoutPanel4";
            this.tableLayoutPanel4.RowCount = 9;
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 11.11111F));
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 11.11111F));
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 11.11111F));
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 11.11111F));
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 11.11111F));
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 11.11111F));
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 11.11111F));
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 11.11111F));
            this.tableLayoutPanel4.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 11.11111F));
            this.tableLayoutPanel4.Size = new System.Drawing.Size(431, 245);
            this.tableLayoutPanel4.TabIndex = 1;
            // 
            // cb_UsePo8
            // 
            this.cb_UsePo8.AutoSize = true;
            this.cb_UsePo8.Location = new System.Drawing.Point(11, 222);
            this.cb_UsePo8.Margin = new System.Windows.Forms.Padding(10, 5, 3, 3);
            this.cb_UsePo8.Name = "cb_UsePo8";
            this.cb_UsePo8.Size = new System.Drawing.Size(45, 17);
            this.cb_UsePo8.TabIndex = 0;
            this.cb_UsePo8.Text = "Po8";
            this.cb_UsePo8.UseVisualStyleBackColor = true;
            this.cb_UsePo8.CheckedChanged += new System.EventHandler(this.cb_UsePo8_CheckedChanged);
            // 
            // cb_UseO2
            // 
            this.cb_UseO2.AutoSize = true;
            this.cb_UseO2.Location = new System.Drawing.Point(11, 195);
            this.cb_UseO2.Margin = new System.Windows.Forms.Padding(10, 5, 3, 3);
            this.cb_UseO2.Name = "cb_UseO2";
            this.cb_UseO2.Size = new System.Drawing.Size(40, 17);
            this.cb_UseO2.TabIndex = 0;
            this.cb_UseO2.Text = "O2";
            this.cb_UseO2.UseVisualStyleBackColor = true;
            this.cb_UseO2.CheckedChanged += new System.EventHandler(this.cb_UseO2_CheckedChanged);
            // 
            // cb_UseP4
            // 
            this.cb_UseP4.AutoSize = true;
            this.cb_UseP4.Location = new System.Drawing.Point(11, 168);
            this.cb_UseP4.Margin = new System.Windows.Forms.Padding(10, 5, 3, 3);
            this.cb_UseP4.Name = "cb_UseP4";
            this.cb_UseP4.Size = new System.Drawing.Size(39, 17);
            this.cb_UseP4.TabIndex = 0;
            this.cb_UseP4.Text = "P4";
            this.cb_UseP4.UseVisualStyleBackColor = true;
            this.cb_UseP4.CheckedChanged += new System.EventHandler(this.cb_UseP4_CheckedChanged);
            // 
            // cb_UsePz
            // 
            this.cb_UsePz.AutoSize = true;
            this.cb_UsePz.Location = new System.Drawing.Point(11, 141);
            this.cb_UsePz.Margin = new System.Windows.Forms.Padding(10, 5, 3, 3);
            this.cb_UsePz.Name = "cb_UsePz";
            this.cb_UsePz.Size = new System.Drawing.Size(38, 17);
            this.cb_UsePz.TabIndex = 0;
            this.cb_UsePz.Text = "Pz";
            this.cb_UsePz.UseVisualStyleBackColor = true;
            this.cb_UsePz.CheckedChanged += new System.EventHandler(this.cb_UsePz_CheckedChanged);
            // 
            // cb_UseP3
            // 
            this.cb_UseP3.AutoSize = true;
            this.cb_UseP3.Location = new System.Drawing.Point(11, 114);
            this.cb_UseP3.Margin = new System.Windows.Forms.Padding(10, 5, 3, 3);
            this.cb_UseP3.Name = "cb_UseP3";
            this.cb_UseP3.Size = new System.Drawing.Size(39, 17);
            this.cb_UseP3.TabIndex = 0;
            this.cb_UseP3.Text = "P3";
            this.cb_UseP3.UseVisualStyleBackColor = true;
            this.cb_UseP3.CheckedChanged += new System.EventHandler(this.cb_UseP3_CheckedChanged);
            // 
            // cb_UseOz
            // 
            this.cb_UseOz.AutoSize = true;
            this.cb_UseOz.Location = new System.Drawing.Point(11, 87);
            this.cb_UseOz.Margin = new System.Windows.Forms.Padding(10, 5, 3, 3);
            this.cb_UseOz.Name = "cb_UseOz";
            this.cb_UseOz.Size = new System.Drawing.Size(39, 17);
            this.cb_UseOz.TabIndex = 0;
            this.cb_UseOz.Text = "Oz";
            this.cb_UseOz.UseVisualStyleBackColor = true;
            this.cb_UseOz.CheckedChanged += new System.EventHandler(this.cb_UseOz_CheckedChanged);
            // 
            // cb_UseO1
            // 
            this.cb_UseO1.AutoSize = true;
            this.cb_UseO1.Location = new System.Drawing.Point(11, 60);
            this.cb_UseO1.Margin = new System.Windows.Forms.Padding(10, 5, 3, 3);
            this.cb_UseO1.Name = "cb_UseO1";
            this.cb_UseO1.Size = new System.Drawing.Size(40, 17);
            this.cb_UseO1.TabIndex = 0;
            this.cb_UseO1.Text = "O1";
            this.cb_UseO1.UseVisualStyleBackColor = true;
            this.cb_UseO1.CheckedChanged += new System.EventHandler(this.cb_UseO1_CheckedChanged);
            // 
            // cb_UsePo7
            // 
            this.cb_UsePo7.AutoSize = true;
            this.cb_UsePo7.Location = new System.Drawing.Point(11, 33);
            this.cb_UsePo7.Margin = new System.Windows.Forms.Padding(10, 5, 3, 3);
            this.cb_UsePo7.Name = "cb_UsePo7";
            this.cb_UsePo7.Size = new System.Drawing.Size(45, 17);
            this.cb_UsePo7.TabIndex = 0;
            this.cb_UsePo7.Text = "Po7";
            this.cb_UsePo7.UseVisualStyleBackColor = true;
            this.cb_UsePo7.CheckedChanged += new System.EventHandler(this.cb_UsePo7_CheckedChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(11, 6);
            this.label2.Margin = new System.Windows.Forms.Padding(10, 5, 3, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Name";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(97, 6);
            this.label3.Margin = new System.Windows.Forms.Padding(10, 5, 3, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(31, 13);
            this.label3.TabIndex = 1;
            this.label3.Text = "Color";
            // 
            // bt_ColorPo7
            // 
            this.bt_ColorPo7.Dock = System.Windows.Forms.DockStyle.Fill;
            this.bt_ColorPo7.Location = new System.Drawing.Point(87, 28);
            this.bt_ColorPo7.Margin = new System.Windows.Forms.Padding(0);
            this.bt_ColorPo7.Name = "bt_ColorPo7";
            this.bt_ColorPo7.Size = new System.Drawing.Size(343, 26);
            this.bt_ColorPo7.TabIndex = 2;
            this.bt_ColorPo7.UseVisualStyleBackColor = true;
            this.bt_ColorPo7.Click += new System.EventHandler(this.button4_Click);
            // 
            // bt_ColorO1
            // 
            this.bt_ColorO1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.bt_ColorO1.Location = new System.Drawing.Point(87, 55);
            this.bt_ColorO1.Margin = new System.Windows.Forms.Padding(0);
            this.bt_ColorO1.Name = "bt_ColorO1";
            this.bt_ColorO1.Size = new System.Drawing.Size(343, 26);
            this.bt_ColorO1.TabIndex = 2;
            this.bt_ColorO1.UseVisualStyleBackColor = true;
            this.bt_ColorO1.Click += new System.EventHandler(this.button5_Click);
            // 
            // bt_ColorOz
            // 
            this.bt_ColorOz.Dock = System.Windows.Forms.DockStyle.Fill;
            this.bt_ColorOz.Location = new System.Drawing.Point(87, 82);
            this.bt_ColorOz.Margin = new System.Windows.Forms.Padding(0);
            this.bt_ColorOz.Name = "bt_ColorOz";
            this.bt_ColorOz.Size = new System.Drawing.Size(343, 26);
            this.bt_ColorOz.TabIndex = 2;
            this.bt_ColorOz.UseVisualStyleBackColor = true;
            this.bt_ColorOz.Click += new System.EventHandler(this.button6_Click);
            // 
            // bt_ColorP3
            // 
            this.bt_ColorP3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.bt_ColorP3.Location = new System.Drawing.Point(87, 109);
            this.bt_ColorP3.Margin = new System.Windows.Forms.Padding(0);
            this.bt_ColorP3.Name = "bt_ColorP3";
            this.bt_ColorP3.Size = new System.Drawing.Size(343, 26);
            this.bt_ColorP3.TabIndex = 2;
            this.bt_ColorP3.UseVisualStyleBackColor = true;
            this.bt_ColorP3.Click += new System.EventHandler(this.button7_Click);
            // 
            // bt_ColorPz
            // 
            this.bt_ColorPz.Dock = System.Windows.Forms.DockStyle.Fill;
            this.bt_ColorPz.Location = new System.Drawing.Point(87, 136);
            this.bt_ColorPz.Margin = new System.Windows.Forms.Padding(0);
            this.bt_ColorPz.Name = "bt_ColorPz";
            this.bt_ColorPz.Size = new System.Drawing.Size(343, 26);
            this.bt_ColorPz.TabIndex = 2;
            this.bt_ColorPz.UseVisualStyleBackColor = true;
            this.bt_ColorPz.Click += new System.EventHandler(this.button8_Click);
            // 
            // bt_ColorP4
            // 
            this.bt_ColorP4.Dock = System.Windows.Forms.DockStyle.Fill;
            this.bt_ColorP4.Location = new System.Drawing.Point(87, 163);
            this.bt_ColorP4.Margin = new System.Windows.Forms.Padding(0);
            this.bt_ColorP4.Name = "bt_ColorP4";
            this.bt_ColorP4.Size = new System.Drawing.Size(343, 26);
            this.bt_ColorP4.TabIndex = 2;
            this.bt_ColorP4.UseVisualStyleBackColor = true;
            this.bt_ColorP4.Click += new System.EventHandler(this.button9_Click);
            // 
            // bt_ColorO2
            // 
            this.bt_ColorO2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.bt_ColorO2.Location = new System.Drawing.Point(87, 190);
            this.bt_ColorO2.Margin = new System.Windows.Forms.Padding(0);
            this.bt_ColorO2.Name = "bt_ColorO2";
            this.bt_ColorO2.Size = new System.Drawing.Size(343, 26);
            this.bt_ColorO2.TabIndex = 2;
            this.bt_ColorO2.UseVisualStyleBackColor = true;
            this.bt_ColorO2.Click += new System.EventHandler(this.button10_Click);
            // 
            // bt_ColorPo8
            // 
            this.bt_ColorPo8.Dock = System.Windows.Forms.DockStyle.Fill;
            this.bt_ColorPo8.Location = new System.Drawing.Point(87, 217);
            this.bt_ColorPo8.Margin = new System.Windows.Forms.Padding(0);
            this.bt_ColorPo8.Name = "bt_ColorPo8";
            this.bt_ColorPo8.Size = new System.Drawing.Size(343, 27);
            this.bt_ColorPo8.TabIndex = 2;
            this.bt_ColorPo8.UseVisualStyleBackColor = true;
            this.bt_ColorPo8.Click += new System.EventHandler(this.button11_Click);
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 1;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Controls.Add(this.button15, 0, 1);
            this.tableLayoutPanel2.Controls.Add(this.groupBox5, 0, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(452, 3);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 2;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 50F));
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(443, 483);
            this.tableLayoutPanel2.TabIndex = 2;
            // 
            // button15
            // 
            this.button15.Anchor = System.Windows.Forms.AnchorStyles.Right;
            this.button15.Location = new System.Drawing.Point(363, 446);
            this.button15.Margin = new System.Windows.Forms.Padding(3, 3, 5, 3);
            this.button15.Name = "button15";
            this.button15.Size = new System.Drawing.Size(75, 23);
            this.button15.TabIndex = 1;
            this.button15.Text = "Close";
            this.button15.UseVisualStyleBackColor = true;
            this.button15.Click += new System.EventHandler(this.button15_Click);
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.tableLayoutPanel6);
            this.groupBox5.Controls.Add(this.checkBox9);
            this.groupBox5.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox5.Location = new System.Drawing.Point(3, 3);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(437, 427);
            this.groupBox5.TabIndex = 2;
            this.groupBox5.TabStop = false;
            // 
            // tableLayoutPanel6
            // 
            this.tableLayoutPanel6.ColumnCount = 1;
            this.tableLayoutPanel6.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel6.Controls.Add(this.groupBox6, 0, 0);
            this.tableLayoutPanel6.Controls.Add(this.listBox1, 0, 1);
            this.tableLayoutPanel6.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel6.Location = new System.Drawing.Point(3, 16);
            this.tableLayoutPanel6.Name = "tableLayoutPanel6";
            this.tableLayoutPanel6.RowCount = 2;
            this.tableLayoutPanel6.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 50F));
            this.tableLayoutPanel6.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel6.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel6.Size = new System.Drawing.Size(431, 408);
            this.tableLayoutPanel6.TabIndex = 0;
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.bt_RemoveAllFilters);
            this.groupBox6.Controls.Add(this.bt_AddFilter);
            this.groupBox6.Controls.Add(this.bt_RemoveFilter);
            this.groupBox6.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox6.Location = new System.Drawing.Point(3, 3);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(425, 44);
            this.groupBox6.TabIndex = 0;
            this.groupBox6.TabStop = false;
            // 
            // bt_RemoveAllFilters
            // 
            this.bt_RemoveAllFilters.Location = new System.Drawing.Point(323, 15);
            this.bt_RemoveAllFilters.Name = "bt_RemoveAllFilters";
            this.bt_RemoveAllFilters.Size = new System.Drawing.Size(96, 23);
            this.bt_RemoveAllFilters.TabIndex = 1;
            this.bt_RemoveAllFilters.Text = "Remove all filters";
            this.bt_RemoveAllFilters.UseVisualStyleBackColor = true;
            this.bt_RemoveAllFilters.Click += new System.EventHandler(this.button14_Click);
            // 
            // bt_AddFilter
            // 
            this.bt_AddFilter.Location = new System.Drawing.Point(6, 15);
            this.bt_AddFilter.Name = "bt_AddFilter";
            this.bt_AddFilter.Size = new System.Drawing.Size(99, 23);
            this.bt_AddFilter.TabIndex = 1;
            this.bt_AddFilter.Text = "Add new filters";
            this.bt_AddFilter.UseVisualStyleBackColor = true;
            this.bt_AddFilter.Click += new System.EventHandler(this.button12_Click);
            // 
            // bt_RemoveFilter
            // 
            this.bt_RemoveFilter.Location = new System.Drawing.Point(111, 15);
            this.bt_RemoveFilter.Name = "bt_RemoveFilter";
            this.bt_RemoveFilter.Size = new System.Drawing.Size(121, 23);
            this.bt_RemoveFilter.TabIndex = 1;
            this.bt_RemoveFilter.Text = "Remove selected filter";
            this.bt_RemoveFilter.UseVisualStyleBackColor = true;
            this.bt_RemoveFilter.Click += new System.EventHandler(this.button13_Click);
            // 
            // listBox1
            // 
            this.listBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(3, 53);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(425, 342);
            this.listBox1.TabIndex = 1;
            // 
            // checkBox9
            // 
            this.checkBox9.AutoSize = true;
            this.checkBox9.Location = new System.Drawing.Point(6, 0);
            this.checkBox9.Name = "checkBox9";
            this.checkBox9.Size = new System.Drawing.Size(72, 17);
            this.checkBox9.TabIndex = 0;
            this.checkBox9.Text = "Use filters";
            this.checkBox9.UseVisualStyleBackColor = true;
            this.checkBox9.CheckedChanged += new System.EventHandler(this.checkBox9_CheckedChanged);
            // 
            // SettingsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(898, 489);
            this.Controls.Add(this.tableLayoutPanel1);
            this.MinimumSize = new System.Drawing.Size(914, 486);
            this.Name = "SettingsForm";
            this.Text = "Form2";
            this.groupBox1.ResumeLayout(false);
            this.tableLayoutPanel3.ResumeLayout(false);
            this.tableLayoutPanel3.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel5.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.tableLayoutPanel4.ResumeLayout(false);
            this.tableLayoutPanel4.PerformLayout();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.tableLayoutPanel6.ResumeLayout(false);
            this.groupBox6.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel3;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel5;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel4;
        private System.Windows.Forms.CheckBox cb_UsePo8;
        private System.Windows.Forms.CheckBox cb_UseO2;
        private System.Windows.Forms.CheckBox cb_UseP4;
        private System.Windows.Forms.CheckBox cb_UsePz;
        private System.Windows.Forms.CheckBox cb_UseP3;
        private System.Windows.Forms.CheckBox cb_UseOz;
        private System.Windows.Forms.CheckBox cb_UseO1;
        private System.Windows.Forms.CheckBox cb_UsePo7;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button bt_ColorPo7;
        private System.Windows.Forms.Button bt_ColorO1;
        private System.Windows.Forms.Button bt_ColorOz;
        private System.Windows.Forms.Button bt_ColorP3;
        private System.Windows.Forms.Button bt_ColorPz;
        private System.Windows.Forms.Button bt_ColorP4;
        private System.Windows.Forms.Button bt_ColorO2;
        private System.Windows.Forms.Button bt_ColorPo8;
        private System.Windows.Forms.ColorDialog colorDialog1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Button bt_RemoveAllFilters;
        private System.Windows.Forms.Button bt_RemoveFilter;
        private System.Windows.Forms.Button bt_AddFilter;
        private System.Windows.Forms.CheckBox checkBox9;
        private System.Windows.Forms.Button button15;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel6;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.ListBox listBox1;
    }
}