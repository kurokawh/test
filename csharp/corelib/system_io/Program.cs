using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace array_test
{
	class Program
	{
		protected int p = 0;

		static void Main(string[] args)
		{
            Test t = new Test();
            t.test();
            show(t);

            t.aaa = "a";
            t.bbb = "b";
            t.ccc = "c"; // ignored
            show(t);
        }

        static void show(Test t)
        {
            string a = t.aaa;
            string b = t.bbb;
            string c = t.ccc;
            string x = a + b + c;
            Console.WriteLine(x);
        }
    }
	class Test
	{
		public string aaa = "";
		public String bbb { get; set; } // get value is null.
        public String ccc { get {return "";} set {} } // set value is ignored
        public void test()
		{
			Console.WriteLine("aaa: " + aaa);
            Console.WriteLine("bbb: " + bbb);
		}
	}
}
