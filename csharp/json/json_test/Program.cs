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

        static void testSerializeClasses()
        {
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


        // https://stackoverflow.com/questions/7814247/serialize-nan-values-into-json-as-nulls-in-json-net?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
        static void testSerializeDouble()
        {
            string json;
            IList<double> d = new List<double> { 1.1, double.NaN, double.PositiveInfinity };

            json = JsonConvert.SerializeObject(d);
            Console.WriteLine(json);

            // [1.1,"NaN","Infinity"]

            json = JsonConvert.SerializeObject(d, new JsonSerializerSettings { FloatFormatHandling = FloatFormatHandling.Symbol });
            Console.WriteLine(json);

            // [1.1,NaN,Infinity]

            json = JsonConvert.SerializeObject(d, new JsonSerializerSettings { FloatFormatHandling = FloatFormatHandling.DefaultValue });
            Console.WriteLine(json);

            // [1.1,0.0,0.0]
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            testSerializeClasses();
            testSerializeDouble();
        }
    }
}
