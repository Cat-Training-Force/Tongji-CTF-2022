
using System;
using System.Security.Cryptography;
using System.IO;
using System.Text;
namespace HelloWorldApplication
{
    public class Main1
    {
        byte[] t = { 65, 85, 135, 14, 130, 191, 4, 47, 184, 184, 116, 133, 192, 173, 142, 52, 124, 56, 252, 0, 2, 66, 15, 228, 9, 204, 85, 137, 119, 113, 169, 223, 212, 27, 218, 62, 187, 69, 15, 214, 230, 156, 202, 143, 189, 187, 157, 96 };
        bool c(string s)
        {
            // flag{A_ma1war3_w1ll_g3t_ur_s3cr3t_f1le}
            byte[] key = Encoding.UTF8.GetBytes("not important k~");
            byte[] iv = { 222, 173, 190, 239, 1, 1, 4, 5, 1, 4, 1, 9, 1, 9, 130, 130 };
            byte[] data = System.Text.Encoding.UTF8.GetBytes(s);
            using (RijndaelManaged rdel = new RijndaelManaged())
            {
                rdel.Key = key;
                rdel.Mode = CipherMode.CBC;
                rdel.Padding = PaddingMode.PKCS7;
                rdel.IV = iv;
                ICryptoTransform ctrans = rdel.CreateEncryptor();
                byte[] res = ctrans.TransformFinalBlock(data, 0, data.Length);
                for(int i = 0; i < t.Length; i++)
                {
                    if (t[i] != res[i]) return false;
                }
                return true;
            }
            return false;
        }
        public bool d(string path)
        {
            try
            {
                using (StreamReader sr = new StreamReader(path + "\\.ssh\\id_rsa"))
                {
                    string s = sr.ReadLine();
                    if (s != null)
                    {
                        return c(s);
                    }
                    return false;
                }
            }
            catch (Exception e)
            {

            }
            return false;
        }
        static void Main(string[] args)
        {
            Console.WriteLine("flag{Another fake flag~~~}");
        }
    }
}