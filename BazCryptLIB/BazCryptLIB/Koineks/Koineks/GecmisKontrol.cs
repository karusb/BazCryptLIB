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
    public partial class GecmisKontrol : UserControl
    {
        double[,] btcC;
        int btctxC;
        double[,] ltcC;
        int ltctxC;
        double[,] ethC;
        int ethtxC;
        double[,] xrpC;
        int xrptxC;
        double[,] xlmC;
        int xlmtxC;
        double[,] tlC;
        int tltxC;

        public GecmisKontrol()
        {
            InitializeComponent();
            dataGridView1.Columns.Add("Coin", "Coin");
            dataGridView1.Columns.Add("Miktar", "Miktar");
            dataGridView1.Columns.Add("Fiyat", "Fiyat");
            dataGridView1.Columns.Add("TL", "TL");
            dataGridView1.Columns.Add("Zaman", "Zaman");
        }
        public void HepsiniCalistir()
        {
            dataGridView1.Rows.Clear();

            for (int i = 0; i < btctxC; ++i)
            {
                dataGridView1.Rows.Add("BTC", btcC[i,0], btcC[i, 1], btcC[i, 0]* btcC[i, 1], Convert.ToString(btcC[i, 2])+":"+ Convert.ToString(btcC[i, 3])+" " + Convert.ToString(btcC[i, 4]+"/"+ Convert.ToString(btcC[i, 5]+"/"+ Convert.ToString(btcC[i, 6]))));
            }
            for (int i = 0; i < xrptxC; ++i)
            {
                dataGridView1.Rows.Add("XRP",xrpC[i, 0], xrpC[i, 1], xrpC[i, 0] * xrpC[i, 1], Convert.ToString(xrpC[i, 2]) + ":" + Convert.ToString(xrpC[i, 3]) + " " + Convert.ToString(xrpC[i, 4] + "/" + Convert.ToString(xrpC[i, 5] + "/" + Convert.ToString(xrpC[i, 6]))));
            }
            for (int i = 0; i < xlmtxC; ++i)
            {
                dataGridView1.Rows.Add("XLM", xlmC[i, 0], xlmC[i, 1], xlmC[i, 0] * xlmC[i, 1], Convert.ToString(xlmC[i, 2]) + ":" + Convert.ToString(xlmC[i, 3]) + " " + Convert.ToString(xlmC[i, 4] + "/" + Convert.ToString(xlmC[i, 5] + "/" + Convert.ToString(xlmC[i, 6]))));
            }
            for (int i = 0; i < ltctxC; ++i)
            {
                dataGridView1.Rows.Add("LTC", ltcC[i, 0], ltcC[i, 1], ltcC[i, 0] * ltcC[i, 1], Convert.ToString(ltcC[i, 2]) + ":" + Convert.ToString(ltcC[i, 3]) + " " + Convert.ToString(ltcC[i, 4] + "/" + Convert.ToString(ltcC[i, 5] + "/" + Convert.ToString(ltcC[i, 6]))));
            }
            for (int i = 0; i < ethtxC; ++i)
            {
                dataGridView1.Rows.Add("ETH", ethC[i, 0], ethC[i, 1], ethC[i, 0] * ethC[i, 1], Convert.ToString(ethC[i, 2]) + ":" + Convert.ToString(ethC[i, 3]) + " " + Convert.ToString(ethC[i, 4] + "/" + Convert.ToString(ethC[i, 5] + "/" + Convert.ToString(ethC[i, 6]))));
            }
            for (int i = 0; i < tltxC; ++i)
            {
                dataGridView1.Rows.Add("TL", tlC[i, 0], tlC[i, 1], tlC[i, 0] * tlC[i, 1], Convert.ToString(tlC[i, 2]) + ":" + Convert.ToString(tlC[i, 3]) + " " + Convert.ToString(tlC[i, 4] + "/" + Convert.ToString(tlC[i, 5] + "/" + Convert.ToString(tlC[i, 6]))));
            }

            dataGridView1.Sort(dataGridView1.Columns["Zaman"], ListSortDirection.Ascending);
        }
        public void DegerYukle(double[,] btc, int btctx, double[,] ltc, int ltctx, double[,] eth, int ethtx, double[,] xrp, int xrptx, double[,] xlm, int xlmtx, double[,] tl, int tltx)
        {
            btcC = btc;
            btctxC = btctx;
            ltcC = ltc;
            ltctxC = ltctx;
            ethC = eth;
            ethtxC = ethtx;
            xrpC = xrp;
            xrptxC = xrptx;
            xlmC = xlm;
            xlmtxC = xlmtx;
            tlC = tl;
            tltxC = tltx;
        }
        private void button2_Click(object sender, EventArgs e)
        {
            dataGridView1.Rows.Clear();

            for (int i = 0; i < btctxC; ++i)
            {
                dataGridView1.Rows.Add("BTC", btcC[i, 0], btcC[i, 1], btcC[i, 0] * btcC[i, 1], Convert.ToString(btcC[i, 2]) + ":" + Convert.ToString(btcC[i, 3]) + " " + Convert.ToString(btcC[i, 4] + "/" + Convert.ToString(btcC[i, 5] + "/" + Convert.ToString(btcC[i, 6]))));
            }
            dataGridView1.Sort(dataGridView1.Columns["Zaman"], ListSortDirection.Ascending);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            HepsiniCalistir();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            dataGridView1.Rows.Clear();
            for (int i = 0; i < ethtxC; ++i)
            {
                dataGridView1.Rows.Add("ETH", ethC[i, 0], ethC[i, 1], ethC[i, 0] * ethC[i, 1], Convert.ToString(ethC[i, 2]) + ":" + Convert.ToString(ethC[i, 3]) + " " + Convert.ToString(ethC[i, 4] + "/" + Convert.ToString(ethC[i, 5] + "/" + Convert.ToString(ethC[i, 6]))));
            }
            dataGridView1.Sort(dataGridView1.Columns["Zaman"], ListSortDirection.Ascending);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            dataGridView1.Rows.Clear();
            for (int i = 0; i < xrptxC; ++i)
            {
                dataGridView1.Rows.Add("XRP", xrpC[i, 0], xrpC[i, 1], xrpC[i, 0] * xrpC[i, 1], Convert.ToString(xrpC[i, 2]) + ":" + Convert.ToString(xrpC[i, 3]) + " " + Convert.ToString(xrpC[i, 4] + "/" + Convert.ToString(xrpC[i, 5] + "/" + Convert.ToString(xrpC[i, 6]))));
            }
            dataGridView1.Sort(dataGridView1.Columns["Zaman"], ListSortDirection.Ascending);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            dataGridView1.Rows.Clear();
            for (int i = 0; i < xlmtxC; ++i)
            {
                dataGridView1.Rows.Add("XLM", xlmC[i, 0], xlmC[i, 1], xlmC[i, 0] * xlmC[i, 1], Convert.ToString(xlmC[i, 2]) + ":" + Convert.ToString(xlmC[i, 3]) + " " + Convert.ToString(xlmC[i, 4] + "/" + Convert.ToString(xlmC[i, 5] + "/" + Convert.ToString(xlmC[i, 6]))));
            }
            dataGridView1.Sort(dataGridView1.Columns["Zaman"], ListSortDirection.Ascending);
            

        }

        private void button6_Click(object sender, EventArgs e)
        {
            dataGridView1.Rows.Clear();
            for (int i = 0; i < ltctxC; ++i)
            {
                dataGridView1.Rows.Add("LTC", ltcC[i, 0], ltcC[i, 1], ltcC[i, 0] * ltcC[i, 1], Convert.ToString(ltcC[i, 2]) + ":" + Convert.ToString(ltcC[i, 3]) + " " + Convert.ToString(ltcC[i, 4] + "/" + Convert.ToString(ltcC[i, 5] + "/" + Convert.ToString(ltcC[i, 6]))));
            }
            dataGridView1.Sort(dataGridView1.Columns["Zaman"], ListSortDirection.Ascending);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            dataGridView1.Rows.Clear();
            for (int i = 0; i < tltxC; ++i)
            {
                dataGridView1.Rows.Add("TL", tlC[i, 0], tlC[i, 1], tlC[i, 0] * tlC[i, 1], Convert.ToString(tlC[i, 2]) + ":" + Convert.ToString(tlC[i, 3]) + " " + Convert.ToString(tlC[i, 4] + "/" + Convert.ToString(tlC[i, 5] + "/" + Convert.ToString(tlC[i, 6]))));
            }
            dataGridView1.Sort(dataGridView1.Columns["Zaman"], ListSortDirection.Ascending);
        }
    }
}
