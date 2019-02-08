using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Web.Script.Serialization;

namespace Koineks
{
    public partial class Borsa : UserControl
    {
        public double XRPprice { get; set; }
        public double XLMprice { get; set; }
        public double BTCprice { get; set; }
        public double LTCprice { get; set; }
        public double ETHprice { get; set; }
        public Dictionary<string,Dictionary<string, dynamic>> prices = new Dictionary<string,Dictionary<string, dynamic>>();
        public  Dictionary<string, dynamic> dict = new  Dictionary<string, dynamic>();
        public Borsa()
        {
            InitializeComponent();
            UpdatePriceList();
        }
        private void UpdatePriceList()
        {
            var client = new WebClient();
            var json = client.DownloadString("https://koineks.com/ticker");
            var jss = new JavaScriptSerializer();
            dict = jss.Deserialize<Dictionary<string, dynamic>>(json);
            //prices = dict;
            
            double XRPpricel;
            double XLMpricel;
            double BTCpricel;
            double LTCpricel;
            double ETHpricel;


        // XRP
        label1.Text = Convert.ToString(dict["XRP"]["name"]);
            label2.Text = Convert.ToString(dict["XRP"]["change_percentage"]) + " %";
            if (dict["XRP"]["change_percentage"] < 0)
            {
                label2.ForeColor = Color.Red;
                pictureBox4.Image = Koineks.Properties.Resources.arrow_Down_16xLG;
            }
            if (dict["XRP"]["change_percentage"] > 0)
            {
                label2.ForeColor = Color.LightGreen;
                pictureBox4.Image = Koineks.Properties.Resources.arrow_Up_16xLG;
            }
            if (dict["XRP"]["change_percentage"] == 0)
            {
                label2.ForeColor = Color.Yellow;
                pictureBox4.Image = Koineks.Properties.Resources.Symbols_Blocked_16xLG;
            }
            label6.Text = Convert.ToString(dict["XRP"]["high"]) + " TL";
            label5.Text = Convert.ToString(dict["XRP"]["low"]) + " TL";
            label22.Text = Convert.ToString(dict["XRP"]["volume"]);
            label4.Text = Convert.ToString(dict["XRP"]["ask"]) + " TL";
            label3.Text = Convert.ToString(dict["XRP"]["bid"]) + " TL";
            label23.Text = Convert.ToString(dict["XRP"]["short_code"]);
            label48.Text = Convert.ToString(dict["XRP"]["current"]) + " TL";

            // XLM
            label7.Text = Convert.ToString(dict["XLM"]["name"]);
            label10.Text = Convert.ToString(dict["XLM"]["change_percentage"]) + " %";
            label24.Text = Convert.ToString(dict["XLM"]["short_code"]);
            label49.Text = Convert.ToString(dict["XLM"]["current"]) + " TL";
            if (dict["XLM"]["change_percentage"] < 0)
            {
                label10.ForeColor = Color.Red;
                pictureBox5.Image = Koineks.Properties.Resources.arrow_Down_16xLG;
            }
            if (dict["XLM"]["change_percentage"] > 0)
            {
                label10.ForeColor = Color.LightGreen;
                pictureBox5.Image = Koineks.Properties.Resources.arrow_Up_16xLG;
            }
            if (dict["XLM"]["change_percentage"] == 0)
            {
                label10.ForeColor = Color.Yellow;
                pictureBox5.Image = Koineks.Properties.Resources.Symbols_Blocked_16xLG;
            }
            label32.Text = Convert.ToString(dict["XLM"]["bid"]) + " TL";
            label31.Text = Convert.ToString(dict["XLM"]["ask"]) + " TL";
            label30.Text = Convert.ToString(dict["XLM"]["low"]) + " TL";
            label29.Text = Convert.ToString(dict["XLM"]["high"]) + " TL";
            label28.Text = Convert.ToString(dict["XLM"]["volume"]);

            // ETH
            label8.Text = Convert.ToString(dict["ETH"]["name"]);
            label11.Text = Convert.ToString(dict["ETH"]["change_percentage"]) + " %";
            label25.Text = Convert.ToString(dict["ETH"]["short_code"]);
            label50.Text = Convert.ToString(dict["ETH"]["current"]) + " TL";
            if (dict["ETH"]["change_percentage"] < 0)
            {
                label11.ForeColor = Color.Red;
                pictureBox6.Image = Koineks.Properties.Resources.arrow_Down_16xLG;
            }
            if (dict["ETH"]["change_percentage"] > 0)
            {
                label11.ForeColor = Color.LightGreen;
                pictureBox6.Image = Koineks.Properties.Resources.arrow_Up_16xLG;
            }
            if (dict["ETH"]["change_percentage"] == 0)
            {
                label11.ForeColor = Color.Yellow;
                pictureBox6.Image = Koineks.Properties.Resources.Symbols_Blocked_16xLG;
            }
            label37.Text = Convert.ToString(dict["ETH"]["bid"]) + " TL";
            label36.Text = Convert.ToString(dict["ETH"]["ask"]) + " TL";
            label35.Text = Convert.ToString(dict["ETH"]["low"]) + " TL";
            label34.Text = Convert.ToString(dict["ETH"]["high"]) + " TL";
            label33.Text = Convert.ToString(dict["ETH"]["volume"]);

            // BTC
            label9.Text = Convert.ToString(dict["BTC"]["name"]);
            label12.Text = Convert.ToString(dict["BTC"]["change_percentage"]) + " %";
            label26.Text = Convert.ToString(dict["BTC"]["short_code"]);
            label51.Text = Convert.ToString(dict["BTC"]["current"]) + " TL";
            if (dict["BTC"]["change_percentage"] < 0)
            {
                label12.ForeColor = Color.Red;
                pictureBox7.Image = Koineks.Properties.Resources.arrow_Down_16xLG;
            }
            if (dict["BTC"]["change_percentage"] > 0)
            {
                label12.ForeColor = Color.LightGreen;
                pictureBox7.Image = Koineks.Properties.Resources.arrow_Up_16xLG;
            }
            if (dict["BTC"]["change_percentage"] == 0)
            {
                label12.ForeColor = Color.Yellow;
                pictureBox7.Image = Koineks.Properties.Resources.Symbols_Blocked_16xLG;
            }
            label42.Text = Convert.ToString(dict["BTC"]["bid"]) + " TL";
            label41.Text = Convert.ToString(dict["BTC"]["ask"]) + " TL";
            label40.Text = Convert.ToString(dict["BTC"]["low"]) + " TL";
            label39.Text = Convert.ToString(dict["BTC"]["high"]) + " TL";
            label38.Text = Convert.ToString(dict["BTC"]["volume"]);

            // LTC
            label14.Text = Convert.ToString(dict["LTC"]["name"]);
            label13.Text = Convert.ToString(dict["LTC"]["change_percentage"]) + " %";
            label27.Text = Convert.ToString(dict["LTC"]["short_code"]);
            label52.Text = Convert.ToString(dict["LTC"]["current"]) + " TL";
            if (dict["LTC"]["change_percentage"] < 0)
            {
                label13.ForeColor = Color.Red;
                pictureBox8.Image = Koineks.Properties.Resources.arrow_Down_16xLG;
            }
            if (dict["LTC"]["change_percentage"] > 0)
            {
                label13.ForeColor = Color.LightGreen;
                pictureBox8.Image = Koineks.Properties.Resources.arrow_Up_16xLG;
            }
            if (dict["LTC"]["change_percentage"] == 0)
            {
                label13.ForeColor = Color.Yellow;
                pictureBox8.Image = Koineks.Properties.Resources.Symbols_Blocked_16xLG;
            }
            label47.Text = Convert.ToString(dict["LTC"]["bid"]) + " TL";
            label46.Text = Convert.ToString(dict["LTC"]["ask"]) + " TL";
            label45.Text = Convert.ToString(dict["LTC"]["low"]) + " TL";
            label44.Text = Convert.ToString(dict["LTC"]["high"]) + " TL";
            label43.Text = Convert.ToString(dict["LTC"]["volume"]);

            double.TryParse(dict["XRP"]["ask"], out XRPpricel);
            double.TryParse(dict["XLM"]["ask"], out XLMpricel);
            double.TryParse(dict["BTC"]["ask"], out BTCpricel);
            double.TryParse(dict["LTC"]["ask"], out LTCpricel);
            double.TryParse(dict["ETH"]["ask"], out ETHpricel);

            XRPprice = XRPpricel;
            XLMprice = XLMpricel;
            BTCprice = BTCpricel;
            LTCprice = LTCpricel;
            ETHprice = ETHpricel;
        }

        private void button6_Click(object sender, EventArgs e)
        {
            ALMACA alacakli = new ALMACA(XRPprice, "XRP", "AL");
            if (alacakli.ShowDialog() == DialogResult.OK)
            {
                MessageBox.Show(alacakli.amount.ToString() + "  @ " + alacakli.price.ToString() + " Total of: " + alacakli.total.ToString());
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            ALMACA alacakli = new ALMACA(XRPprice, "XRP", "SAT");
            if (alacakli.ShowDialog() == DialogResult.OK)
            {
                MessageBox.Show(alacakli.amount.ToString() + "  @ " + alacakli.price.ToString() + " Total of: " + alacakli.total.ToString());
            }
        }
    }
}
