using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Koineks
{
    public partial class Girdi : UserControl
    {
        public double TL { get; set; }
        public double XRP { get; set; }
        public double XLM { get; set; }
        public double BTC { get; set; }
        public double LTC { get; set; }
        public double ETH { get; set; }

        public double XRPat { get; set; }
        public double XLMat { get; set; }
        public double BTCat { get; set; }
        public double LTCat { get; set; }
        public double ETHat { get; set; }
        public Girdi()
        {
            InitializeComponent();
            initcurprice();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            double TLl;
            double XRPl;
            double XLMl;
            double BTCl;
            double LTCl;
            double ETHl;
            double.TryParse(textBox1.Text, out XRPl);
            double.TryParse(textBox1.Text, out XRPl);
            double.TryParse(textBox2.Text, out BTCl);
            double.TryParse(textBox3.Text, out ETHl);
            double.TryParse(textBox4.Text, out XLMl);
            double.TryParse(textBox5.Text, out LTCl);
            double.TryParse(textBox6.Text, out TLl);
            TL= TLl;
            XRP = XRPl;
            XLM =  XLMl;
            BTC =  BTCl;
            LTC =  LTCl;
            ETH =  ETHl;
            double.TryParse(textBox12.Text, out XRPl);
            double.TryParse(textBox11.Text, out BTCl);
            double.TryParse(textBox10.Text, out ETHl);
            double.TryParse(textBox9.Text, out XLMl);
            double.TryParse(textBox8.Text, out LTCl);
            XRPat = XRPl;
            XLMat = XLMl;
            BTCat = BTCl;
            LTCat = LTCl;
            ETHat = ETHl;

        }
        public void Sifirla()
        {
            TL = 0;
            XRP = 0;
            XLM = 0;
            BTC = 0;
            LTC = 0;
            ETH = 0;
            textBox1.Text = Convert.ToString(XRP);
            textBox2.Text = Convert.ToString(BTC);
            textBox3.Text = Convert.ToString(ETH);
            textBox4.Text = Convert.ToString(XLM);
            textBox5.Text = Convert.ToString(LTC);
            textBox6.Text = Convert.ToString(TL);
        }
        public void initcurprice()
        {
            textBox12.Text = Convert.ToString(XRPat);
            textBox11.Text = Convert.ToString(BTCat);
            textBox10.Text = Convert.ToString(ETHat);
            textBox9.Text = Convert.ToString(XLMat);
            textBox8.Text = Convert.ToString(LTCat);
        }
    }
}
