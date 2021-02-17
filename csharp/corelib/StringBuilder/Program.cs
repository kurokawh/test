using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace array_test
{
	class Program
	{
		static void Main(string[] args)
		{
            StringBuilder sb8 = new StringBuilder(8);
            StringBuilder sb4 = new StringBuilder(4);
            StringBuilder sb2 = new StringBuilder(2);

            sb8.Append("12345");
            string s5 = sb8.ToString();
            sb4.Append(sb8);
            Console.WriteLine(sb4.ToString());

        }
    }
}
