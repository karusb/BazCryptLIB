using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Koineks
{
    public partial class ALMACA : Form
    {
        public double price;
        public double amount;
        public double total;
        public string isim;
        public string aksiyon;
        public ALMACA(double priceof, string name, string aksiyonz)
        {
            price = priceof;
            isim = name;
            aksiyon = aksiyonz;
            InitializeComponent();
            label4.Text = isim + " " + aksiyon;
            textBox1.Text = price.ToString();
        }
        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            double.TryParse(textBox3.Text, out total);
            textBox2.Text = (total / price).ToString();

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            double.TryParse(textBox2.Text, out amount);
            textBox3.Text = (amount * price).ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.OK;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            double.TryParse(textBox1.Text, out price);
            textBox1.Text = price.ToString();
            textBox2.Text = (total / price).ToString();
            textBox3.Text = (amount * price).ToString();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            DialogResult = DialogResult.No;
        }
    }
}
