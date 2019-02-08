using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using LiveCharts;
using System.Net;
using System.Web.Script.Serialization;
using System.IO;
namespace Koineks
{
    public partial class Charts : Form
    {

        Int32 unixTimestamp = (Int32)(DateTime.UtcNow.Subtract(new DateTime(1970, 1, 1))).TotalSeconds;
        private string[] poloChartstrings = { "high", "low", "open", "close" };
        
        public string[] poloOrderstrings = { "asks","bids" };
        public Dictionary<string, dynamic> dict = new Dictionary<string, dynamic>();
        public Dictionary<string, dynamic> dictorder = new Dictionary<string, dynamic>();
        public Charts()
        {
            InitializeComponent();
        }
        public void ChartDataCekPolo(string pair,string startTime,string period)
        {
            var client = new WebClient();
            var json = client.DownloadString("https://poloniex.com/public?command=returnChartData&currencyPair="+pair+"&start="+startTime+"&end=9999999999&period="+period);
            var jss = new JavaScriptSerializer();
            dict = jss.Deserialize<Dictionary<string, dynamic>>(json);
            List<string> list = new List<string>(dict.Keys);
            DataGridViewRow row = new DataGridViewRow();
            chart1.Series.Add("data");
        }
        public void OrderDataCekPolo(string pair, string depth)
        {
            var client = new WebClient();
            var json = client.DownloadString("https://poloniex.com/public?command=returnOrderBook&currencyPair=" + pair + "&depth=" + depth );
            var jss = new JavaScriptSerializer();
            dictorder = jss.Deserialize<Dictionary<string, dynamic>>(json);
            List<string> list = new List<string>(dict.Keys);
            
            dataGridView1.Columns.Add("Fiyat", "Fiyat");
            dataGridView1.Columns.Add("Miktar", "Miktar");
            backgroundWorker1.RunWorkerAsync(dictorder);
            string kelebek = dictorder["asks"][0][0];
            string kelebek2 = dictorder["asks"][1][0];
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            DataGridViewRow[] row = new DataGridViewRow[10];
           
            for(int i = 0; i <10; ++i) row[i] = new DataGridViewRow();
            Dictionary<string, dynamic> argument = e.Argument as Dictionary<string, dynamic>;
            for (int i = 0; i < 10;++i)
            {
                backgroundWorker1.ReportProgress((i+1)*10);
                decimal tmp = argument["asks"][i][1];
                
                row[i].SetValues((argument["asks"][i][0].ToString()), tmp.ToString());
                //row[i].Cells.Add((DataGridViewCell)(argument["asks"][i][0].ToString()));
                //row[i].Cells.Add((DataGridViewCell)tmp.ToString());
                //row[i].Cells[0].Value = ((argument["asks"][i][0].ToString()));
                //row[i].Cells[1].Value = (tmp.ToString());
                //row[i].Cells[0] = argument["asks"][i][0].ToString() ;
                //row[i].Cells[1] = tmp.ToString();
                

            }
            e.Result =row;
           

        }

        private void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            progressBarOrder.Value = e.ProgressPercentage;
            if (e.ProgressPercentage >= 100) progressBarOrder.Visible = false;

        }

        private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Error != null)
            {
                // handle the error
            }
            else if (e.Cancelled)
            {
                // handle cancellation
            }
            else
            {
                DataGridViewRow[] row = new DataGridViewRow[10];
                row = (DataGridViewRow[])e.Result;

                for(int i=0 ; i < 10; ++i)
                {
                    dataGridView1.Rows.Add(row[i]);
                }
                dataGridView1.Refresh();
                // use it on the UI thread
                this.Refresh();
            }
        }
    }
}
