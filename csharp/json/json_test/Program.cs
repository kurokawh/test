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
        class Test
        {
            public int id = -1;
            [JsonProperty("xxx")]
            public string name = "no-name";
        };

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            int id = 111;
            Test test = new Test();
            Config config = new Config();

            JObject jobj = new JObject()
                    {
                        { "id", id },
                        { "test", JToken.FromObject(test) },
                        { "config", JToken.FromObject(config) },
                    };
            Console.WriteLine("jobj: " + jobj.ToString());
            Console.WriteLine("done");
        }
    }
}
