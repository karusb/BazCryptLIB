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
    public partial class YatirimControl : UserControl
    {
        public double TL { get; set; }
        public double XRP { get; set; }
        public double XLM { get; set; }
        public double BTC { get; set; }
        public double LTC { get; set; }
        public double ETH { get; set; }
        public double XRPav { get; set; }
        public double XLMav { get; set; }
        public double BTCav { get; set; }
        public double LTCav { get; set; }
        public double ETHav { get; set; }
        public double XRPkar { get; set; }
        public double XLMkar { get; set; }
        public double BTCkar { get; set; }
        public double LTCkar { get; set; }
        public double ETHkar { get; set; }
        public double XRPkarp { get; set; }
        public double XLMkarp { get; set; }
        public double BTCkarp { get; set; }
        public double LTCkarp { get; set; }
        public double ETHkarp { get; set; }
        public double XRPTL { get; set; }
        public double XLMTL { get; set; }
        public double BTCTL { get; set; }
        public double LTCTL { get; set; }
        public double ETHTL { get; set; }

        public YatirimControl()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
        public void Yukle()
        {
            label12.Text = Convert.ToString(BTC);
            label13.Text = Convert.ToString(BTCTL);
            label14.Text = Convert.ToString(BTCav);
            label15.Text = Convert.ToString(BTCkar.ToString("0.000"));
            label16.Text = Convert.ToString(BTCkarp.ToString("0.000"));

            label17.Text = Convert.ToString(XRP);
            label18.Text = Convert.ToString(XRPTL);
            label19.Text = Convert.ToString(XRPav);
            label20.Text = Convert.ToString(XRPkar.ToString("0.000"));
            label21.Text = Convert.ToString(XRPkarp.ToString("0.000"));

            label22.Text = Convert.ToString(ETH);
            label23.Text = Convert.ToString(ETHTL);
            label24.Text = Convert.ToString(ETHav);
            label25.Text = Convert.ToString(ETHkar.ToString("0.000"));
            label26.Text = Convert.ToString(ETHkarp.ToString("0.000"));

            label27.Text = Convert.ToString(XLM);
            label28.Text = Convert.ToString(XLMTL);
            label29.Text = Convert.ToString(XLMav);
            label30.Text = Convert.ToString(XLMkar.ToString("0.000"));
            label31.Text = Convert.ToString(XLMkarp.ToString("0.000"));

            label32.Text = Convert.ToString(LTC);
            label33.Text = Convert.ToString(LTCTL);
            label34.Text = Convert.ToString(LTCav);
            label35.Text = Convert.ToString(LTCkar.ToString("0.000"));
            label36.Text = Convert.ToString(LTCkarp.ToString("0.000"));
        }
    }
}
