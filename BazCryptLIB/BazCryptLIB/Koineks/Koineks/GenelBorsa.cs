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
using System.IO;

namespace Koineks
{
    public partial class GenelBorsa : UserControl
    {
        public Dictionary<string, Dictionary<string, dynamic>> prices = new Dictionary<string, Dictionary<string, dynamic>>();
        public Dictionary<string, dynamic> dict = new Dictionary<string, dynamic>();
        private string[] koinekstrings = { "name", "short_code", "change_percentage", "current", "ask", "bid", "low", "high", "volume" };
        private string[] poloniexstrings = { "percentChange", "last", "lowestAsk", "highestBid", "low24hr", "high24hr","baseVolume" };
        public GenelBorsa()
        {
            InitializeComponent();

            UpdatePriceList();

        }
        public void UpdatePriceList()
        {
            BorsaData.Columns.Add("Isim", "Isim");
            BorsaData.Columns.Add("Kod", "Kod");
            BorsaData.Columns.Add("Degisim", "Degisim");
            BorsaData.Columns.Add("Fiyat", "Fiyat");
            BorsaData.Columns.Add("Satis", "Satis");
            BorsaData.Columns.Add("Alis", "Alis");
            BorsaData.Columns.Add("24 Low", "24 Low");
            BorsaData.Columns.Add("24 High", "24 High");
            BorsaData.Columns.Add("Hacim", "Hacim");
            var client = new WebClient();
            var json = client.DownloadString("https://koineks.com/ticker");
            var jss = new JavaScriptSerializer();
            dict = jss.Deserialize<Dictionary<string, dynamic>>(json);
            List<string> list = new List<string>(dict.Keys);
            DataGridViewRow row = new DataGridViewRow();
            for (int i = 0; i < list.Count - 1; ++i)
            {
                BorsaData.Rows.Add();
                for (int j = 0; j < koinekstrings.Length - 1; j++)
                {

                    BorsaData.Rows[i].Cells[j].Value = Convert.ToString(dict[list[i]][koinekstrings[j]]);

                }

            }



        }
        public void UpdatePriceList1()
        {
            BorsaData.Columns.Add("Kod", "Kod");
            BorsaData.Columns.Add("Degisim", "Degisim");
            BorsaData.Columns.Add("Fiyat", "Fiyat");
            BorsaData.Columns.Add("Satis", "Satis");
            BorsaData.Columns.Add("Alis", "Alis");
            BorsaData.Columns.Add("24 Low", "24 Low");
            BorsaData.Columns.Add("24 High", "24 High");
            BorsaData.Columns.Add("Hacim", "Hacim");

            ServicePointManager.Expect100Continue = true;
            ServicePointManager.SecurityProtocol = SecurityProtocolType.Tls12;

            ServicePointManager.ServerCertificateValidationCallback = delegate { return true; };

            var client = new WebClient();
            var json = client.DownloadString("https://poloniex.com/public?command=returnTicker");
            var jss = new JavaScriptSerializer();
            dict = jss.Deserialize<Dictionary<string, dynamic>>(json);
            double tmp = 0;
            List<string> list = new List<string>(dict.Keys);
            DataGridViewRow row = new DataGridViewRow();
            for (int i = 0; i < list.Count - 1; ++i)
            {
                BorsaData.Rows.Add();
                BorsaData.Rows[i].Cells[0].Value = list[i].ToString();
                double.TryParse(dict[list[i]][poloniexstrings[1]], out tmp); // yanlis sonuc
                BorsaData.Rows[i].Cells[1].Value = (tmp*100);
                for (int j = 2; j <= poloniexstrings.Length; j++)
                {

                    BorsaData.Rows[i].Cells[j].Value = Convert.ToString(dict[list[i]][poloniexstrings[j-1]]);

                }

            }



        }
        public string Get(string uri)
        {
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(uri);
            request.AutomaticDecompression = DecompressionMethods.GZip | DecompressionMethods.Deflate;

            using (HttpWebResponse response = (HttpWebResponse)request.GetResponse())
            using (Stream stream = response.GetResponseStream())
            using (StreamReader reader = new StreamReader(stream))
            {
                return reader.ReadToEnd();
            }
        }
        public string Post(string uri, string data, string contentType, string method = "POST")
        {
            byte[] dataBytes = Encoding.UTF8.GetBytes(data);

            HttpWebRequest request = (HttpWebRequest)WebRequest.Create(uri);
            request.AutomaticDecompression = DecompressionMethods.GZip | DecompressionMethods.Deflate;
            request.ContentLength = dataBytes.Length;
            request.ContentType = contentType;
            request.Method = method;

            using (Stream requestBody = request.GetRequestStream())
            {
                requestBody.Write(dataBytes, 0, dataBytes.Length);
            }

            using (HttpWebResponse response = (HttpWebResponse)request.GetResponse())
            using (Stream stream = response.GetResponseStream())
            using (StreamReader reader = new StreamReader(stream))
            {
                return reader.ReadToEnd();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            BorsaData.Rows.Clear();
            BorsaData.Columns.Clear();
            UpdatePriceList1();

        }

        private void button1_Click(object sender, EventArgs e)
        {
            BorsaData.Rows.Clear();
            BorsaData.Columns.Clear();
            UpdatePriceList();
        }

        private void BorsaData_CellContentDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            int index = e.RowIndex;
            string pair = BorsaData.Rows[index].Cells[0].Value.ToString();
            Charts grafik = new Koineks.Charts();
            grafik.Show();
            grafik.OrderDataCekPolo(pair, "10");


        }
    }
}
