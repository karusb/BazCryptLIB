using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Koineks
{
    [Serializable]
    class Kullanici
    {
        public double TL { get; set; }
        public double[,] TLHistory { get; set; } = new double[1000, 9];
        public double XRP { get; set; }
        public double[,] XRPHistory { get; set; } = new double[1000, 9];
        public double XLM { get; set; }
        public double[,] XLMHistory { get; set; } = new double[1000, 9];
        public double BTC { get; set; }
        public double[,] BTCHistory { get; set; } = new double[1000, 9];
        public double LTC { get; set; }
        public double[,] LTCHistory { get; set; } = new double[1000, 9];
        public double ETH { get; set; }
        public double[,] ETHHistory { get; set; } = new double[1000, 9];
        public int TLtxcount { get; set; } = 0;
        public int BTCtxcount { get; set; } = 0;
        public int ETHtxcount { get; set; } = 0;
        public int XLMtxcount { get; set; } = 0;
        public int LTCtxcount { get; set; } = 0;
        public int XRPtxcount { get; set; } = 0;
        public string[] CommandHistory;

        public Dictionary<string, Dictionary<string, dynamic>> txinfo = new Dictionary<string, Dictionary<string, dynamic>>();
        public int CommandWindowCount { get; set; } = 0;

        public void YerAyir()
        {
            TLHistory = new double[1000, 9];
            BTCHistory = new double[1000, 9];
            LTCHistory = new double[1000, 9];
            ETHHistory = new double[1000, 9];
            XRPHistory = new double[1000, 9];
            XLMHistory = new double[1000, 9];
            CommandHistory = new string[50];
        }


    }
}
