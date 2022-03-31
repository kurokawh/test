using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;

namespace ConsoleApp
{

	public struct Point
	{
		public int x;
		public int y;
	}

	[StructLayout(LayoutKind.Sequential)]
	public class StaticPoint
	{
		public static int x;
		public static int y;
		protected const string sqlSelectColumn = "cicon.localConceptId AS LocalConceptId, "
										+ "cicon.lastAccessIndex AS LastAccessIndex, "
										+ "cicon.lastAccessTime AS LastAccessTime, "
										+ "cicon.lastPlayedDate AS LastPlayedDateDtm, ";
	}

[StructLayout(LayoutKind.Sequential)]
	public class StringPair
	{
		public string x;
		public string y;
	}

	[StructLayout(LayoutKind.Sequential)]
	public class StringPair2
	{
		public enum Test : ulong
		{
			A,
			B,
		}
		public string x;
		public string y;

		static string RNPS_ACTION = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
		static string RNPS_ADULT = "yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy";
		internal static readonly Dictionary<string, int> TABLE = new Dictionary<string, int>()
		{
			{ RNPS_ACTION,  0 },
			{ RNPS_ADULT,  0 },
		};
	}


	class Program
	{
		static void Main(string[] args)
		{
			Point p;
			p.x = 1;
			p.y = 1;

			Console.WriteLine("TotalMemory: {0}", GC.GetTotalMemory(false));
			StaticPoint p2 = new StaticPoint();
			Console.WriteLine("TotalMemory: {0}", GC.GetTotalMemory(false));
			StringPair s = new StringPair();
			StringPair2 s2 = new StringPair2();
			Console.WriteLine("TotalMemory: {0}", GC.GetTotalMemory(false));

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
