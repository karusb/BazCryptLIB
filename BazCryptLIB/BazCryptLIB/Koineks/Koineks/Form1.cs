using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Web.Script.Serialization;
namespace Koineks
{
    public partial class Form1 : Form
    {


        Sistem sis;
        private string aktifpencere = "borsa";

        public Form1()
        {
            InitializeComponent();
            sis =  new Sistem();
            CommandWindow.Lines = new String[50];
            label8.Text = Convert.ToString(sis.user.BTC);
            label9.Text = Convert.ToString(sis.user.XRP);
            label10.Text = Convert.ToString(sis.user.ETH);
            label11.Text = Convert.ToString(sis.user.XLM);
            label12.Text = Convert.ToString(sis.user.LTC);
            label13.Text = Convert.ToString(sis.user.TL);
            label15.Text = Convert.ToString(sis.TotalinTL()) + " TL";
            sis.brs.Dock = DockStyle.Fill;
            panel4.Controls.Add(sis.brs);
            RefreshCommandWindow();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            aktifpencere = "borsa";
            panel4.Controls.Clear();
            sis.Yatir();
            sis.girdiler.Sifirla();
            sis.brs.Dock = DockStyle.Fill;
            panel4.Controls.Add(sis.brs);
            RefreshCommandWindow();
        }
        private void RefreshCommandWindow()
        {
            CommandWindow.Text = "";
            int lines = 0;

            if (sis.user.CommandWindowCount >= (int)50)
            {
                lines = sis.user.CommandWindowCount - 50;

                for (int i = lines; i < 50; ++i)
                {
                    CommandWindow.AppendText( sis.user.CommandHistory[i] + "/n");
                }
            }
            else
            {
                for (int i = 0; i < sis.user.CommandWindowCount; ++i)
                {
                    CommandWindow.AppendText( sis.user.CommandHistory[i] + "\r\n");
                }
            }
            CommandWindow.SelectionStart = CommandWindow.Text.Length;
            CommandWindow.ScrollToCaret();
        }

        private void button1_MouseHover(object sender, EventArgs e)
        {
            button1.BackColor = Color.YellowGreen;
        }

        private void panel4_MouseHover(object sender, EventArgs e)
        {
            button1.BackColor = Color.MidnightBlue;
        }
      

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            if (this.WindowState == FormWindowState.Normal)
            {
                this.WindowState = FormWindowState.Maximized;
            }
            else
            {
                this.WindowState = FormWindowState.Normal;
            }
        }

        private void pictureBox3_Click(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Minimized;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            aktifpencere = "girdiler";
            panel4.Controls.Clear();
            sis.GirdiFiyatYukle();
            sis.girdiler.initcurprice();
            sis.girdiler.Refresh();
            sis.girdiler.Dock = DockStyle.Fill;
            panel4.Controls.Add(sis.girdiler);
            RefreshCommandWindow();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            aktifpencere = "yatirimlar";
            sis.YatirimlariHesapla();
            sis.yatirimlar.Yukle();
            sis.yatirimlar.Refresh();
            sis.yatirimlar.Dock = DockStyle.Fill;
            panel4.Controls.Clear();
            panel4.Controls.Add(sis.yatirimlar);
            RefreshCommandWindow();
        }

        private void button16_Click(object sender, EventArgs e)
        {
            aktifpencere = "gecmisler";
            panel4.Controls.Clear();
            sis.gecmisler.DegerYukle(sis.user.BTCHistory,sis.user.BTCtxcount,sis.user.LTCHistory,sis.user.LTCtxcount,sis.user.ETHHistory,sis.user.ETHtxcount,sis.user.XRPHistory,sis.user.XRPtxcount,sis.user.XLMHistory,sis.user.XLMtxcount,sis.user.TLHistory,sis.user.TLtxcount);
            sis.gecmisler.HepsiniCalistir();
            sis.gecmisler.Refresh();
            sis.gecmisler.Dock = DockStyle.Fill;
            panel4.Controls.Add(sis.gecmisler);
            RefreshCommandWindow();
        }

        private void button1_MouseLeave(object sender, EventArgs e)
        {
            if (aktifpencere == "borsa")
            {
                button1.BackColor = Color.DarkSlateGray;
            }
            else
            {
                button1.BackColor = Color.DarkCyan;
            }
        }

        private void button2_MouseEnter(object sender, EventArgs e)
        {
            button2.BackColor = Color.YellowGreen;
        }

        private void button2_MouseHover(object sender, EventArgs e)
        {

        }

        private void button3_MouseEnter(object sender, EventArgs e)
        {
            button3.BackColor = Color.YellowGreen;
        }

        private void button3_MouseLeave(object sender, EventArgs e)
        {
            if (aktifpencere == "girdiler")
            {
                button3.BackColor = Color.DarkSlateGray;
            }
            else
            {
                button3.BackColor = Color.DarkCyan;
            }
        }

        private void button2_MouseLeave(object sender, EventArgs e)
        {
            if (aktifpencere == "yatirimlar")
            {
                button2.BackColor = Color.DarkSlateGray;
            }
            else
            {
                button2.BackColor = Color.DarkCyan;
            }
        }

        private void button4_MouseEnter(object sender, EventArgs e)
        {

        }

        private void button4_MouseLeave(object sender, EventArgs e)
        {

        }

        private void button5_MouseEnter(object sender, EventArgs e)
        {

        }

        private void button5_MouseLeave(object sender, EventArgs e)
        {

        }

        private void button16_MouseEnter(object sender, EventArgs e)
        {
            button16.BackColor = Color.YellowGreen;
        }

        private void button16_MouseLeave(object sender, EventArgs e)
        {
            if (aktifpencere == "gecmisler")
            {
                button16.BackColor = Color.DarkSlateGray;
            }
            else
            {
                button16.BackColor = Color.DarkCyan;
            }
        }

        private void button6_MouseEnter(object sender, EventArgs e)
        {

        }

        private void button6_MouseLeave(object sender, EventArgs e)
        {

        }

        private void button6_Click(object sender, EventArgs e)
        {
            aktifpencere = "genelborsa";
            panel4.Controls.Clear();
            sis.gbrs.Refresh();
            sis.gbrs.Dock = DockStyle.Fill;
            panel4.Controls.Add(sis.gbrs);
            RefreshCommandWindow();
        }
    }
}
