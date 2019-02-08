using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace Koineks
{
    class Sistem
    {

        public Kullanici user = new Kullanici();
        private const string userfile = "user.dat";
        public Girdi girdiler = new Girdi();
        public Borsa brs = new Koineks.Borsa();
        public YatirimControl yatirimlar = new YatirimControl();
        public GecmisKontrol gecmisler = new GecmisKontrol();
        public GenelBorsa gbrs = new GenelBorsa();
        public Sistem()
        {
            try
            {
                user.YerAyir();
                user = ReadFromBinaryFile<Kullanici>(userfile);
            }
            catch (FileNotFoundException)
            {
                user.BTC = 0;
                user.ETH = 0;
                user.LTC = 0;
                user.TL = 0;
                user.XLM = 0;
                user.XRP = 0;
                
                WriteToBinaryFile<Kullanici>(userfile, user);
            }
        }
        public void Yatir()
        {
            user = ReadFromBinaryFile<Kullanici>(userfile);

            try
            {
                user.XLMHistory[0, 0] = user.XLMHistory[0, 0];
                user.BTCHistory[0, 0] = user.BTCHistory[0, 0];
                user.LTCHistory[0, 0] = user.LTCHistory[0, 0];
                user.XRPHistory[0, 0] = user.XRPHistory[0, 0];
                user.ETHHistory[0, 0] = user.ETHHistory[0, 0];
                user.TLHistory[0, 0] = user.TLHistory[0, 0];
            }
            catch (NullReferenceException)
            {
                user.YerAyir();
            }
            user.BTC += girdiler.BTC;
            user.ETH += girdiler.ETH;
            user.LTC += girdiler.LTC;
            user.TL += girdiler.TL;
            user.XLM += girdiler.XLM;
            user.XRP += girdiler.XRP;
            if(girdiler.BTC != 0)
            {
                
                user.BTCHistory[user.BTCtxcount, 0] = girdiler.BTC;
                user.BTCHistory[user.BTCtxcount, 1] = girdiler.BTCat;
                user.BTCHistory[user.BTCtxcount, 2] = DateTime.Now.Hour;
                user.BTCHistory[user.BTCtxcount, 3] = DateTime.Now.Minute;
                user.BTCHistory[user.BTCtxcount, 4] = DateTime.Now.Day;
                user.BTCHistory[user.BTCtxcount, 5] = DateTime.Now.Month;
                user.BTCHistory[user.BTCtxcount, 6] = DateTime.Now.Year;
                user.BTCtxcount += 1;
                user.CommandHistory[user.CommandWindowCount] = Convert.ToString(girdiler.BTC)+" BTC @ "+ Convert.ToString(girdiler.BTCat) + "        Time = " + Convert.ToString(DateTime.Now.Hour) +
       ":" + Convert.ToString(DateTime.Now.Minute) + " " + Convert.ToString(DateTime.Now.Day)+"/" + Convert.ToString(DateTime.Now.Month)+ "/" + Convert.ToString(DateTime.Now.Year);
                user.CommandWindowCount += 1;
            }
            if (girdiler.LTC != 0)
            {

                user.LTCHistory[user.LTCtxcount, 0] = girdiler.LTC;
                user.LTCHistory[user.LTCtxcount, 1] = girdiler.LTCat;
                user.LTCHistory[user.LTCtxcount, 2] = DateTime.Now.Hour;
                user.LTCHistory[user.LTCtxcount, 3] = DateTime.Now.Minute;
                user.LTCHistory[user.LTCtxcount, 4] = DateTime.Now.Day;
                user.LTCHistory[user.LTCtxcount, 5] = DateTime.Now.Month;
                user.LTCHistory[user.LTCtxcount, 6] = DateTime.Now.Year;
                user.LTCtxcount += 1;
                user.CommandHistory[user.CommandWindowCount] = Convert.ToString(girdiler.LTC) + " LTC @ " + Convert.ToString(girdiler.LTCat) + "        Time = " + Convert.ToString(DateTime.Now.Hour) +
":" + Convert.ToString(DateTime.Now.Minute) + " " + Convert.ToString(DateTime.Now.Day) + "/" + Convert.ToString(DateTime.Now.Month) + "/" + Convert.ToString(DateTime.Now.Year);
                user.CommandWindowCount += 1;
            }
            if (girdiler.ETH != 0)
            {

                user.ETHHistory[user.ETHtxcount, 0] = girdiler.ETH;
                user.ETHHistory[user.ETHtxcount, 1] = girdiler.ETHat;
                user.ETHHistory[user.ETHtxcount, 2] = DateTime.Now.Hour;
                user.ETHHistory[user.ETHtxcount, 3] = DateTime.Now.Minute;
                user.ETHHistory[user.ETHtxcount, 4] = DateTime.Now.Day;
                user.ETHHistory[user.ETHtxcount, 5] = DateTime.Now.Month;
                user.ETHHistory[user.ETHtxcount, 6] = DateTime.Now.Year;
                user.ETHtxcount += 1;
                user.CommandHistory[user.CommandWindowCount] = Convert.ToString(girdiler.ETH) + " ETH @ " + Convert.ToString(girdiler.ETHat) + "        Time = " + Convert.ToString(DateTime.Now.Hour) +
":" + Convert.ToString(DateTime.Now.Minute) + " " + Convert.ToString(DateTime.Now.Day) + "/" + Convert.ToString(DateTime.Now.Month) + "/" + Convert.ToString(DateTime.Now.Year);
                user.CommandWindowCount += 1;
            }
            if (girdiler.XRP != 0)
            {

                user.XRPHistory[user.XRPtxcount, 0] = girdiler.XRP;
                user.XRPHistory[user.XRPtxcount, 1] = girdiler.XRPat;
                user.XRPHistory[user.XRPtxcount, 2] = DateTime.Now.Hour;
                user.XRPHistory[user.XRPtxcount, 3] = DateTime.Now.Minute;
                user.XRPHistory[user.XRPtxcount, 4] = DateTime.Now.Day;
                user.XRPHistory[user.XRPtxcount, 5] = DateTime.Now.Month;
                user.XRPHistory[user.XRPtxcount, 6] = DateTime.Now.Year;
                user.XRPtxcount += 1;
                user.CommandHistory[user.CommandWindowCount] = Convert.ToString(girdiler.XRP) + " XRP @ " + Convert.ToString(girdiler.XRPat) + "        Time = " + Convert.ToString(DateTime.Now.Hour) +
":" + Convert.ToString(DateTime.Now.Minute) + " " + Convert.ToString(DateTime.Now.Day) + "/" + Convert.ToString(DateTime.Now.Month) + "/" + Convert.ToString(DateTime.Now.Year);
                user.CommandWindowCount += 1;
            }
            if (girdiler.XLM != 0)
            {

                user.XLMHistory[user.XLMtxcount, 0] = girdiler.XLM;
                user.XLMHistory[user.XLMtxcount, 1] = girdiler.XLMat;
                user.XLMHistory[user.XLMtxcount, 2] = DateTime.Now.Hour;
                user.XLMHistory[user.XLMtxcount, 3] = DateTime.Now.Minute;
                user.XLMHistory[user.XLMtxcount, 4] = DateTime.Now.Day;
                user.XLMHistory[user.XLMtxcount, 5] = DateTime.Now.Month;
                user.XLMHistory[user.XLMtxcount, 6] = DateTime.Now.Year;
                user.XLMtxcount += 1;
                user.CommandHistory[user.CommandWindowCount] = Convert.ToString(girdiler.XLM) + " XLM @ " + Convert.ToString(girdiler.XLMat) + "        Time = " + Convert.ToString(DateTime.Now.Hour) +
":" + Convert.ToString(DateTime.Now.Minute) + " " + Convert.ToString(DateTime.Now.Day) + "/" + Convert.ToString(DateTime.Now.Month) + "/" + Convert.ToString(DateTime.Now.Year);
                user.CommandWindowCount += 1;
            }
            if (girdiler.TL != 0)
            {

                user.TLHistory[user.TLtxcount, 0] = girdiler.TL;
                user.TLHistory[user.TLtxcount, 1] = DateTime.Now.Hour;
                user.TLHistory[user.TLtxcount, 2] = DateTime.Now.Minute;
                user.TLHistory[user.TLtxcount, 3] = DateTime.Now.Day;
                user.TLHistory[user.TLtxcount, 4] = DateTime.Now.Month;
                user.TLHistory[user.TLtxcount, 5] = DateTime.Now.Year;
                user.TLtxcount += 1;
                user.CommandHistory[user.CommandWindowCount] = Convert.ToString(girdiler.TL)  + " TL        Time = " + Convert.ToString(DateTime.Now.Hour) +
":" + Convert.ToString(DateTime.Now.Minute) + " " + Convert.ToString(DateTime.Now.Day) + "/" + Convert.ToString(DateTime.Now.Month) + "/" + Convert.ToString(DateTime.Now.Year);
                user.CommandWindowCount += 1;
            }
            KullaniciUpdate();
        }
        public void GirdiFiyatYukle()
        {
            girdiler.BTCat = brs.BTCprice;
            girdiler.LTCat = brs.LTCprice;
            girdiler.ETHat = brs.ETHprice;
            girdiler.XRPat = brs.XRPprice;
            girdiler.XLMat = brs.XLMprice;
        }
        void KullaniciUpdate()
        {
            WriteToBinaryFile<Kullanici>(userfile, user);
        }
        public void YatirimlariHesapla()
        {
            yatirimlar.TL = user.TL;
            yatirimlar.BTC = user.BTC;
            yatirimlar.ETH = user.ETH;
            yatirimlar.LTC = user.LTC;
            yatirimlar.XLM = user.XLM;
            yatirimlar.XRP = user.XRP;

            yatirimlar.BTCTL = user.BTC*brs.BTCprice;
            yatirimlar.ETHTL = user.ETH*brs.ETHprice;
            yatirimlar.LTCTL = user.LTC*brs.LTCprice;
            yatirimlar.XLMTL = user.XLM*brs.XLMprice;
            yatirimlar.XRPTL = user.XRP*brs.XRPprice;

            for(int i = 0; i < user.BTCtxcount; ++i)
            {
                yatirimlar.BTCkar += user.BTCHistory[i, 0] * user.BTCHistory[i, 1];
            }
            yatirimlar.BTCkarp = (((user.BTC * brs.BTCprice) - yatirimlar.BTCkar)/ (user.BTC * brs.BTCprice))*100;
            yatirimlar.BTCkar =  (user.BTC * brs.BTCprice)- yatirimlar.BTCkar;
            

            for (int i = 0; i < user.LTCtxcount; ++i)
            {
                yatirimlar.LTCkar += user.LTCHistory[i, 0] * user.LTCHistory[i, 1];
            }
            yatirimlar.LTCkarp = (((user.LTC * brs.LTCprice) - yatirimlar.LTCkar) / (user.LTC * brs.LTCprice)) * 100;
            yatirimlar.LTCkar =  (user.LTC * brs.LTCprice) - yatirimlar.LTCkar;

            for (int i = 0; i < user.ETHtxcount; ++i)
            {
                yatirimlar.ETHkar += user.ETHHistory[i, 0] * user.ETHHistory[i, 1];
            }
            yatirimlar.ETHkarp = (((user.ETH * brs.ETHprice) - yatirimlar.ETHkar) / (user.ETH * brs.ETHprice)) * 100;
            yatirimlar.ETHkar = (user.ETH * brs.ETHprice)- yatirimlar.ETHkar ;

            for (int i = 0; i < user.XRPtxcount; ++i)
            {
                yatirimlar.XRPkar += user.XRPHistory[i, 0] * user.XRPHistory[i, 1];
            }
            yatirimlar.XRPkarp = (((user.XRP * brs.XRPprice) - yatirimlar.XRPkar) / (user.XRP * brs.XRPprice)) * 100;
            yatirimlar.XRPkar =  (user.XRP * brs.XRPprice)- yatirimlar.XRPkar;

            for (int i = 0; i < user.XLMtxcount; ++i)
            {
                yatirimlar.XLMkar += user.XLMHistory[i, 0] * user.XLMHistory[i, 1];
            }
            yatirimlar.XLMkarp = (((user.XLM * brs.XLMprice) - yatirimlar.XLMkar) / (user.XLM * brs.XLMprice)) * 100;
            yatirimlar.XLMkar = (user.XLM * brs.XLMprice)- yatirimlar.XLMkar ;

            yatirimlar.BTCav = user.BTC;
            yatirimlar.ETHav = user.ETH;
            yatirimlar.LTCav = user.LTC;
            yatirimlar.XLMav = user.XLM;
            yatirimlar.XRPav = user.XRP;
        }
        public double TotalinTL()
        {
            return user.BTC * brs.BTCprice + user.ETH * brs.ETHprice + user.LTC * brs.LTCprice + user.XRP * brs.XRPprice + user.XLM * brs.XLMprice;
        }
        /// <summary>
        /// Writes the given object instance to a binary file.
        /// <para>Object type (and all child types) must be decorated with the [Serializable] attribute.</para>
        /// <para>To prevent a variable from being serialized, decorate it with the [NonSerialized] attribute; cannot be applied to properties.</para>
        /// </summary>
        /// <typeparam name="T">The type of object being written to the XML file.</typeparam>
        /// <param name="filePath">The file path to write the object instance to.</param>
        /// <param name="objectToWrite">The object instance to write to the XML file.</param>
        /// <param name="append">If false the file will be overwritten if it already exists. If true the contents will be appended to the file.</param>
        public static void WriteToBinaryFile<T>(string filePath, T objectToWrite, bool append = false)
        {
            using (Stream stream = File.Open(filePath, append ? FileMode.Append : FileMode.Create))
            {
                var binaryFormatter = new System.Runtime.Serialization.Formatters.Binary.BinaryFormatter();
                binaryFormatter.Serialize(stream, objectToWrite);
            }
        }

        /// <summary>
        /// Reads an object instance from a binary file.
        /// </summary>
        /// <typeparam name="T">The type of object to read from the XML.</typeparam>
        /// <param name="filePath">The file path to read the object instance from.</param>
        /// <returns>Returns a new instance of the object read from the binary file.</returns>
        public static T ReadFromBinaryFile<T>(string filePath)
        {
            using (Stream stream = File.Open(filePath, FileMode.Open))
            {
                var binaryFormatter = new System.Runtime.Serialization.Formatters.Binary.BinaryFormatter();
                return (T)binaryFormatter.Deserialize(stream);
            }
        }
    }
}
