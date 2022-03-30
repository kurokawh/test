using System;
using System.Runtime.InteropServices;

namespace ConsoleApp
{

	public struct Point
	{
		public int x;
		public int y;
	}
	public struct StaticPoint
	{
		public static int x;
		public static int y;
	}

	public struct StringPair
	{
		public string x;
		public string y;
	}

	public struct StringPair2
	{
		enum Test {
			A,
			B,
		}
		public string x;
		public string y;
	}


	class Program
	{
		static void Main(string[] args)
		{
			Point p;
			p.x = 1;
			p.y = 1;

			StaticPoint p2;

			StringPair s = new StringPair();
			StringPair2 s2 = new StringPair2();

			Console.WriteLine("Marshal.SizeOf(p): " + Marshal.SizeOf(p));
			Console.WriteLine("Marshal.SizeOf(typeof(Point)): " + Marshal.SizeOf(typeof(Point)));
			Console.WriteLine("Marshal.SizeOf(p2): " + Marshal.SizeOf(p2));
			Console.WriteLine("Marshal.SizeOf(typeof(StaticPoint)): " + Marshal.SizeOf(typeof(StaticPoint)));

			Console.WriteLine("Marshal.SizeOf(s): " + Marshal.SizeOf(s));
			Console.WriteLine("Marshal.SizeOf(typeof(StringPair)): " + Marshal.SizeOf(typeof(StringPair)));
			Console.WriteLine("Marshal.SizeOf(s2): " + Marshal.SizeOf(s2));
			Console.WriteLine("Marshal.SizeOf(typeof(StringPair2)): " + Marshal.SizeOf(typeof(StringPair2)));
		}
	}
}
