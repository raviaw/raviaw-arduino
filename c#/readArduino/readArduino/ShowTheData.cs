using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;

namespace readArduino
{
    public partial class ReadArduinoForm : Form
    {
        delegate void SetTextCallback(string text);

        public ReadArduinoForm()
        {
            InitializeComponent();
        }

        private void ReadArduinoForm_Load(object sender, EventArgs e)
        {
            arduinoPort.Open();
            dialogUpdateTimer.Start();
        }

        private volatile String lastNumberA0;
        private volatile String lastNumberA1;
        private volatile String lastNumberA2;

        private void arduinoPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            String lastVal = arduinoPort.ReadLine();
            System.Console.WriteLine(lastVal);
            String id = lastVal.Substring(0, 2);
            String number = lastVal.Substring(2);
            if (id == "A0")
                lastNumberA0 = number;
            else if (id == "A1")
                lastNumberA1 = number;
            else if (id == "A2")
                lastNumberA2 = number;
        }

        private void dialogUpdateTimer_Tick(object sender, EventArgs e)
        {
            updateControls(lastNumberA0, byteLabel1, container1, graph1);
            updateControls(lastNumberA1, byteLabel2, container2, graph2);
            updateControls(lastNumberA2, byteLabel3, container3, graph3);
        }

        private void updateControls(String lastNumber, Label numberDisplay, Panel container, Panel graph)
        {
            numberDisplay.Text = lastNumber;
            double percentage;
            if (Convert.ToInt32(lastNumber) != 0)
                percentage = Convert.ToDouble(lastNumber) / 1023;
            else
                percentage = 0;
            double width = container.Width * percentage;
            graph.Width = (int)width;
        }
    }
}
