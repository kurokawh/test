using System;
using Newtonsoft.Json.Linq;

namespace json_test
{
    class Program
    {
        class Item
        {
            public int id = -1;
            public string name = "no-name";
        };

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            int id = 111;
            Item item = new Item();

            JObject jobj = new JObject()
                    {
                        { "id", id },
                        { "item", item },
                    };
            Console.WriteLine("jobj: " + jobj.ToString());
        }
    }
}
