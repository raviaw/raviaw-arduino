namespace readArduino
{
    partial class ReadArduinoForm
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
            this.components = new System.ComponentModel.Container();
            this.arduinoPort = new System.IO.Ports.SerialPort(this.components);
            this.container1 = new System.Windows.Forms.Panel();
            this.graph1 = new System.Windows.Forms.Panel();
            this.byteLabel1 = new System.Windows.Forms.Label();
            this.dialogUpdateTimer = new System.Windows.Forms.Timer(this.components);
            this.container2 = new System.Windows.Forms.Panel();
            this.graph2 = new System.Windows.Forms.Panel();
            this.byteLabel2 = new System.Windows.Forms.Label();
            this.container3 = new System.Windows.Forms.Panel();
            this.graph3 = new System.Windows.Forms.Panel();
            this.byteLabel3 = new System.Windows.Forms.Label();
            this.container1.SuspendLayout();
            this.graph1.SuspendLayout();
            this.container2.SuspendLayout();
            this.graph2.SuspendLayout();
            this.container3.SuspendLayout();
            this.graph3.SuspendLayout();
            this.SuspendLayout();
            // 
            // arduinoPort
            // 
            this.arduinoPort.PortName = "COM5";
            this.arduinoPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.arduinoPort_DataReceived);
            // 
            // container1
            // 
            this.container1.BackColor = System.Drawing.Color.White;
            this.container1.Controls.Add(this.graph1);
            this.container1.Location = new System.Drawing.Point(12, 12);
            this.container1.Name = "container1";
            this.container1.Size = new System.Drawing.Size(882, 63);
            this.container1.TabIndex = 0;
            // 
            // graph1
            // 
            this.graph1.BackColor = System.Drawing.Color.Black;
            this.graph1.Controls.Add(this.byteLabel1);
            this.graph1.Location = new System.Drawing.Point(0, 0);
            this.graph1.Name = "graph1";
            this.graph1.Size = new System.Drawing.Size(882, 63);
            this.graph1.TabIndex = 1;
            // 
            // byteLabel1
            // 
            this.byteLabel1.AutoSize = true;
            this.byteLabel1.ForeColor = System.Drawing.Color.Red;
            this.byteLabel1.Location = new System.Drawing.Point(3, 0);
            this.byteLabel1.Name = "byteLabel1";
            this.byteLabel1.Size = new System.Drawing.Size(52, 13);
            this.byteLabel1.TabIndex = 1;
            this.byteLabel1.Text = "Wait for it";
            // 
            // dialogUpdateTimer
            // 
            this.dialogUpdateTimer.Tick += new System.EventHandler(this.dialogUpdateTimer_Tick);
            // 
            // container2
            // 
            this.container2.BackColor = System.Drawing.Color.White;
            this.container2.Controls.Add(this.graph2);
            this.container2.Location = new System.Drawing.Point(12, 81);
            this.container2.Name = "container2";
            this.container2.Size = new System.Drawing.Size(882, 63);
            this.container2.TabIndex = 1;
            // 
            // graph2
            // 
            this.graph2.BackColor = System.Drawing.Color.Black;
            this.graph2.Controls.Add(this.byteLabel2);
            this.graph2.Location = new System.Drawing.Point(0, 0);
            this.graph2.Name = "graph2";
            this.graph2.Size = new System.Drawing.Size(882, 63);
            this.graph2.TabIndex = 1;
            // 
            // byteLabel2
            // 
            this.byteLabel2.AutoSize = true;
            this.byteLabel2.ForeColor = System.Drawing.Color.Red;
            this.byteLabel2.Location = new System.Drawing.Point(3, 0);
            this.byteLabel2.Name = "byteLabel2";
            this.byteLabel2.Size = new System.Drawing.Size(52, 13);
            this.byteLabel2.TabIndex = 1;
            this.byteLabel2.Text = "Wait for it";
            // 
            // container3
            // 
            this.container3.BackColor = System.Drawing.Color.White;
            this.container3.Controls.Add(this.graph3);
            this.container3.Location = new System.Drawing.Point(12, 154);
            this.container3.Name = "container3";
            this.container3.Size = new System.Drawing.Size(882, 63);
            this.container3.TabIndex = 2;
            // 
            // graph3
            // 
            this.graph3.BackColor = System.Drawing.Color.Black;
            this.graph3.Controls.Add(this.byteLabel3);
            this.graph3.Location = new System.Drawing.Point(0, 0);
            this.graph3.Name = "graph3";
            this.graph3.Size = new System.Drawing.Size(882, 63);
            this.graph3.TabIndex = 1;
            // 
            // byteLabel3
            // 
            this.byteLabel3.AutoSize = true;
            this.byteLabel3.ForeColor = System.Drawing.Color.Red;
            this.byteLabel3.Location = new System.Drawing.Point(3, 0);
            this.byteLabel3.Name = "byteLabel3";
            this.byteLabel3.Size = new System.Drawing.Size(52, 13);
            this.byteLabel3.TabIndex = 1;
            this.byteLabel3.Text = "Wait for it";
            // 
            // ReadArduinoForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(906, 231);
            this.Controls.Add(this.container3);
            this.Controls.Add(this.container2);
            this.Controls.Add(this.container1);
            this.Name = "ReadArduinoForm";
            this.Text = "Show Me The Data";
            this.Load += new System.EventHandler(this.ReadArduinoForm_Load);
            this.container1.ResumeLayout(false);
            this.graph1.ResumeLayout(false);
            this.graph1.PerformLayout();
            this.container2.ResumeLayout(false);
            this.graph2.ResumeLayout(false);
            this.graph2.PerformLayout();
            this.container3.ResumeLayout(false);
            this.graph3.ResumeLayout(false);
            this.graph3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.IO.Ports.SerialPort arduinoPort;
        private System.Windows.Forms.Panel container1;
        private System.Windows.Forms.Label byteLabel1;
        private System.Windows.Forms.Panel graph1;
        private System.Windows.Forms.Timer dialogUpdateTimer;
        private System.Windows.Forms.Panel container2;
        private System.Windows.Forms.Panel graph2;
        private System.Windows.Forms.Label byteLabel2;
        private System.Windows.Forms.Panel container3;
        private System.Windows.Forms.Panel graph3;
        private System.Windows.Forms.Label byteLabel3;
    }
}

