using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

// <<memo to build>>
// create git repository under $HOME/tool directory and build dll in it.
// % cd ~/tool
// % git clone git@github.com:JamesNK/Newtonsoft.Json.git

namespace json
{
    class Program
    {
        [JsonObject]
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
                        { "item", JToken.FromObject(item) },
                    };
            Console.WriteLine("jobj: " + jobj.ToString());
        }
    }
}
