using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace json_test
{
    class ArrayTest
    {
        public static void getArrayFromJToken(JToken token)
        {
            //JArray arr = (JArray)token; // XXX: exception!
            //JArray arr = token.ToObject<JArray>(); // XXX: exception
            JTokenType type = token.Type;
            if (type != JTokenType.Array) {
                Console.WriteLine("not array: " + token);
                return;
            }
            foreach (var item in /*arr*/(JArray)token)
            {
                Console.WriteLine("item: " + item);
            }
        }
        public static void test()
        {
            JObject obj = JObject.Parse(@"{ ""firstname"" : ""xxx"", ""surname"" : ""yyy"" }");
            Console.WriteLine($"My family name is {obj["surname"]}.");

            JArray arr = JArray.Parse(@"[ { ""surname"" : ""xxx"" }, { ""surname"" : ""yyy"" } ]");
            foreach (var item in arr)
            {
                Console.WriteLine(item["surname"]);
                string s = (string)item["surname"];
                Console.WriteLine("string: " + s);
                getArrayFromJToken(item["surname"]);
            }
            getArrayFromJToken(arr); // OK

            return;
        }
    }
}

