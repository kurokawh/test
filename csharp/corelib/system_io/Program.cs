using System;
using System.IO;
using System.Linq;

namespace array_test
{
    class Program
    {
        static string TargetStringFilePath = @".\TargetString.txt";
        static string TargetBinaryFilePath = @".\TargetBinary.txt";

        static void Main(string[] args)
        {
            string str_data = "書き込みます。\r\nあいうえお。\r\nabc\r\n";
            WriteStringToFile(TargetStringFilePath, str_data);
            Console.WriteLine(ReadStringFromFile(TargetStringFilePath));

            var bin_in = Enumerable.Range(1, 10).Select(x => (byte)x).ToArray();
//            WriteBinaryToFile(TargetBinaryFilePath, bin_in);
            WriteBinaryToFile(TargetBinaryFilePath, str_data);
            var bin_out = ReadBinaryFromFile(TargetBinaryFilePath);

            Console.ReadLine();
        }

        // 文字列をファイルに書き込み
        public static void WriteStringToFile(string path, string data)
        {
            var dir = Path.GetDirectoryName(path);
            if (!Directory.Exists(dir))
            {
                Directory.CreateDirectory(dir);
            }

            using (var fs = new FileStream(path, FileMode.Create))
            using (var sw = new StreamWriter(fs))
            {
                sw.Write(data);
            }
        }

        // 文字列をファイルに書き込み2
        public static void WriteStringToFile2(string path, string data)
        {
            var dir = Path.GetDirectoryName(path);
            if (!Directory.Exists(dir))
            {
                Directory.CreateDirectory(dir);
            }
            // 簡素なやり方。第二引数をtrueにすると、同じファイルに追記できる)
            using (var sw = new StreamWriter(path, true))
            {
                sw.Write(data);
            }
        }


        // 文字列をファイルから読み込み
        public static string ReadStringFromFile(string path)
        {
            string data = string.Empty;

            if (File.Exists(path))
            {
                using (var fs = new FileStream(path, FileMode.Open))
                using (var sr = new StreamReader(fs))
                {
                    data = sr.ReadToEnd();
                }
            }
            return data;
        }

        // バイナリデータをファイルに書き込み(書き込み先のフォルダがない場合は作成する)
//        public static void WriteBinaryToFile(string path, byte[] data)
        public static void WriteBinaryToFile(string path, string data)
        {
            var dir = Path.GetDirectoryName(path);
            if (!Directory.Exists(dir))
            {
                Directory.CreateDirectory(dir);
            }

            using (var fs = new FileStream(path, FileMode.Create))
            using (var sw = new BinaryWriter(fs))
            {
//                sw.Write(data);
//                char[] ca = data.ToCharArray();
//                sw.Write(ca);
                byte[] ba = System.Text.Encoding.Unicode.GetBytes(data);
                sw.Write(ba);
            }
        }

        // バイナリデータをファイルから読み込み
        public static byte[] ReadBinaryFromFile(string path)
        {
            if (File.Exists(path))
            {
                using (var fs = new FileStream(path, FileMode.Open))
                using (var sr = new BinaryReader(fs))
                {
                    int len = (int)fs.Length;
                    byte[] data = new byte[len];
                    sr.Read(data, 0, len);

                    return data;
                }
            }

            return null;
        }
    }
}
