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
//			Type t = value.GetType();
			bool boolValue = false;
			if (value is bool)
			{
				boolValue = (bool)value;
			}
			else if (value is int)
			{
				int intValue = (int)value;
				boolValue = intValue != 0;
			}
			else if (value is uint)
			{
				boolValue = (uint)value != 0;
			}
			else if (value is long)
			{
				boolValue = (long)value != 0;
			}
			else if (value is ulong)
			{
				boolValue = (ulong)value != 0;
			}
			else if (value is string)
			{
				string strValue = (string)value;
				boolValue = strValue.ToLower() == "true";
			}
			writer.WriteValue(boolValue);
		}
		public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
		{
			return serializer.Deserialize(reader, objectType);
#if XXX
			int intValue = 0;
			if (value is bool)
			{
				bool boolValue = (bool)value;
				if (boolValue)
				{
					intValue = 1;
				}
				else
				{
					intValue = 0;
				}
			}
			else if (value is int)
			{
				int intValue = (int)value;
			}
			else if (value is string)
			{
				string strValue = (string)value;
				if (strValue.ToLower() == "true")
				{
					intValue = 1;
				}
				else if (strValue.ToLower() == "false")
				{
					intValue = 0;
				}
				else
				{
					Int32.TryParse(strValue, out intValue);
				}
			}
			return intValue;
#endif
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
		public Int32 flagIntC;
		[JsonConverter(typeof(BoolConverter))]
		public UInt32 flagUintC;
		[JsonConverter(typeof(BoolConverter))]
		public Int64 flagLongC;
		[JsonConverter(typeof(BoolConverter))]
		public UInt64 flagUlongC;
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

			rec.flagLongC = 1;
			rec.flagUlongC = 1;
			rec.flagIntC = 1;
			rec.flagUintC = 1;
			param.Record = JToken.FromObject(rec);
			Console.WriteLine("param-1: " + JsonConvert.SerializeObject(param));


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
					'flagIntC':0,
					'flagUintC':false,
					'flagLongC':0,
					'flagUlongC':false,
					'flagBoolC':true,
					'data':null,
				},
				}";
			param = JsonConvert.DeserializeObject<MetaRecord>(input);
			rec = param.Record.ToObject<Record>();

			input = @"
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
					'flagUintC':true,
					'flagLongC':1,
					'flagUlongC':true,
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
