using System;
using System.Runtime.InteropServices;

using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Newtonsoft.Json.Converters; // StringEnumConverter

namespace json_test
{
	// https://stackoverflow.com/questions/14427596/convert-an-int-to-bool-with-json-net?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
	public class BoolConverter : JsonConverter
	{
		public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
		{
			writer.WriteValue(((bool)value) ? 1 : 0);
		}
		public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
		{
			return reader.Value.ToString() == "1";
		}
		public override bool CanConvert(Type objectType)
		{
			return objectType == typeof(bool);
		}
	}

	/*
		jobj: {
		  "recordType": "Disc",
		  "existentCheck": "IfNotExist",
		  "record": {
			"id": 0,
			"message": null,
			"subject": null,
			"flagInt": 0,
			"flagBool": false,
			"flagConvertedFromBool": 0,
			"flagConvertedToBool": false,
			"data": null
		  }
		}
	*/
	[JsonObject]
	[StructLayout(LayoutKind.Sequential)]
	public struct Record
	{
		public UInt32 id;

		[MarshalAs(UnmanagedType.LPStr)]
		public string message;

		[MarshalAs(UnmanagedType.LPStr)]
		public string subject;

		public UInt32 flagInt;
		public bool flagBool;
		public UInt32 flagConvertedFromBool;
		public bool flagConvertedToBool;

		[JsonConverter(typeof(BoolConverter))]
		public UInt32 flagIntC;
		public bool flagBoolC;

		[MarshalAs(UnmanagedType.LPStr)]
		public string data;
	};

	enum RecordType
	{
		Unknown,
		Item,
		Disc,
	}
	enum Condition
	{
		Unknown,
		Anyway,
		IfNotExist,
		IfExist,
	}
	class MetaRecord
	{
		[JsonConverter(typeof(StringEnumConverter))]
		[JsonProperty("recordType")]
		public RecordType RecordType = RecordType.Unknown;

		[JsonConverter(typeof(StringEnumConverter))]
		[JsonProperty("existentCheck")]
		public Condition Condition = Condition.IfNotExist;

		[JsonProperty("record")]
		public JToken Record = null;
	}

	public class RecordUtil
	{
		public static void Test()
		{
			Record rec = new Record();
			MetaRecord param = new MetaRecord();
			param.RecordType = RecordType.Disc;
			param.Record = JToken.FromObject(rec);
			Console.WriteLine("param: " + JsonConvert.SerializeObject(param));

			//JObject jobj = new JObject(param); // XXX exception
			JObject jobj = JObject.FromObject(param);
			Console.WriteLine("jobj: " + jobj.ToString());

			string input = @"
				{'recordType':'disc',
				 'condition':'IfNotExist',
				 'record':{
					'id':0,
					'message':null,
					'subject':null,
					'flagInt':1,
					'flagBool':true,
					'flagConvertedFromBool':true,
					'flagConvertedToBool':1,
					'flagIntC':1,
					'flagBoolC':true,
					'data':null,
				},
				}";
			param = JsonConvert.DeserializeObject<MetaRecord>(input);
			rec = param.Record.ToObject<Record>();

			MetaRecord param2 = jobj.ToObject<MetaRecord>();
			Insert(param2);

//			Insert(new InsertParam()); // exception!
		}

		static int Insert(MetaRecord insertParam)
		{
			switch (insertParam.RecordType)
			{
				case RecordType.Disc:
					Record recDisc = insertParam.Record.ToObject<Record>();
					if (CheckExistentCondition(insertParam.Condition, recDisc.id, recDisc.message))
					{
						Insert(ref recDisc);
					}
					else
					{
						insertParam.Record = null;
					}
					return 0;
				default:
					throw new Exception();
			}
		}
		static bool CheckExistentCondition(Condition condition, uint userId, string message)
		{
			switch (condition)
			{
				case Condition.Anyway:
					return true;
				case Condition.IfNotExist:
					return !IsRecordExist(userId, message);
				case Condition.IfExist:
					return IsRecordExist(userId, message);
				default: // Unknown
					throw new Exception();
			}
		}
		static public bool IsRecordExist(uint user_id, string message) { return false; }
		public static int Insert(ref Record rec)
		{
			return 0;
		}
	}
}
