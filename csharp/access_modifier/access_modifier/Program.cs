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
			SubA a = new SubA();
			SubB b = new SubB();
			a.test();
			b.test(a);
		}
	}
	class SubA : Program
	{
		public void test()
		{
			Console.WriteLine("SubA");
			Console.WriteLine(p);
		}
	}
	class SubB : Program
	{
		public void test(SubA a)
		{
			Console.WriteLine("SubB");
			Console.WriteLine(p);
			// error CS1540: Cannot access protected member 'Program.p' via a qualifier of type 'SubA'; the qualifier must be of type 'SubB' (or derived from it)
			// Console.WriteLine(a.p); // NG: 
		}
	}
}
