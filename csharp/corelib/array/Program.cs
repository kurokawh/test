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
			int[] ary1 = new int[] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			int[] ary2 = ary1.Skip(2).Take(5).ToArray();
			Console.WriteLine(ary2.Length);
			int[] ary3 = ary1.Skip(8).Take(5).ToArray();
			Console.WriteLine(ary3.Length);
			int[] ary4 = ary1.Skip(20).Take(5).ToArray();
			Console.WriteLine(ary4.Length);
		}
	}
}
