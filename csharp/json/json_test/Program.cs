using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Converters; // StringEnumConverter


// <<memo to build>>
// create git repository under $HOME/tool directory and build dll in it.
// % cd ~/tool
// % git clone git@github.com:JamesNK/Newtonsoft.Json.git

namespace json_test
{
    class Program
    {
        [JsonObject]
        class Test
        {
            public int id = 0;
            [JsonProperty("xxx")]
            public string name = null;
        };

		enum Type
		{
			None,
			Test,
			Test2,
			Test3,
		};
		[JsonObject]
		struct MetaClass
		{
			[JsonConverter(typeof(StringEnumConverter))]
			public Type type;
			public JToken jtoken;
		}
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

			test.id = -1;
			test.name = "no-name";
			Console.WriteLine("test: " + JsonConvert.SerializeObject(test));


			MetaClass meta = new MetaClass();
			meta.type = Type.Test;
			meta.jtoken = JToken.FromObject(test);
			Console.WriteLine("meta: " + JsonConvert.SerializeObject(meta));
			Console.WriteLine("done");
        }

		static void showInputAndResult(string input, Test test)
		{
			Console.WriteLine("== result ==");
			Console.WriteLine("\tinput: " + input);
			Console.WriteLine("\ttest: " + test);
			Console.WriteLine("\tserialize: " + JsonConvert.SerializeObject(test));
		}
        static void testDeserializeClasses()
        {
			string input = null;
			Test test = new Test();

			// "" => null
			input = "";
			test = JsonConvert.DeserializeObject<Test>(input);
			showInputAndResult(input, test);

			// normal: OK
			input = "{\"id\": -1, \"xxx\": \"no-name\" }";
			test = JsonConvert.DeserializeObject<Test>(input);
			showInputAndResult(input, test);

			// missing element: OK (initial value)
			input = "{ \"id\": 100 }";
			test = JsonConvert.DeserializeObject<Test>(input);
			showInputAndResult(input, test);
			input = "{ \"xxx\": \"name2\" }";
			test = JsonConvert.DeserializeObject<Test>(input);
			showInputAndResult(input, test);

			// additional element: OK (ignored)
			input = "{\"unknownKey\": \"OK?\", \"id\": -1, \"xxx\": \"no-name\" }";
			test = JsonConvert.DeserializeObject<Test>(input);
			showInputAndResult(input, test);

			// meta: OK
			input = "{\"type\": \"Test\",\"jtoken\":{\"id\":2,\"xxx\":\"with-name\"}}";
			MetaClass meta = JsonConvert.DeserializeObject<MetaClass>(input);
			test = meta.jtoken.ToObject<Test>();
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
			RecordUtil.Test();

            testSerializeClasses();
            testSerializeDouble();
            testDeserializeClasses();
        }
    }
}
