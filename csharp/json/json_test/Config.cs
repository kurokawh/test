using System;
using System.Collections.Generic;
using System.Text;

using Newtonsoft.Json;
using Newtonsoft.Json.Linq;


namespace json
{
	public class ConfigMin
	{
		public String ApplicationId { get; set; }

		public override string ToString()
		{
			return ApplicationId;
		}

	}
	public class ConfigBase : ConfigMin
	{
		public long Active { get; set; }
		protected String _ApplicationName { get; set; }
		public String ApplicationName
		{
			get
			{
				return "test" + _ApplicationName;
			}
			set
			{
				_ApplicationName = value;
			}
		}
	}

	[JsonObject]
	public class Config : ConfigBase
	{

		public DateTime InstallDate { get; set; }
        [JsonIgnore]
        public long ContentStatus { get; set; }
		public bool CanRemove { get; set; }
		public String Category { get; set; }
		public Int64 ContentType { get; set; }

		private long _appType = 0;
		public long AppType { 
			get{
				if (IsInstalled() == true &&
					IsDownloadApp == 1 )
				{
					return 1;
				}
				return _appType;
			}
			set{
				_appType = value;
			} 
		}

		private String _appUri = "";
		public String AppUri
		{
			get {
				if (IsInstalled() == true &&
					IsDownloadApp == 1 )
				{
					return "http://test.org/xxx/yyy";
				}
				return _appUri;
			}
			set { _appUri = value; }
		}

		public bool IsInstalled(){
			if( String.IsNullOrEmpty(this.Category)){
				return false;
			}
			return true;
		}
		
		public Int64 Priv { get; set; }
		
		public bool IsPriv {
			get{
				if( this.Priv != 0 ){
					if( (this.Priv & 0x01) != 0 ){
						return true;
					}
					
					if( (this.Priv & 0x01<<1) != 0 ){
						return true;
					}
					return false;
				}
				return false;
			}
		}
		public enum PrivType : int 
		{
			TypeNone = 0,
			TypeApp,
			TypeAttachment,
		};

		public struct PrivInfo
		{
			public PrivType type;
			public string thumbnail_url;
			public string priv_id;
			[JsonIgnore]
			public long priv_active_flag;
			public void reset(){
				type = Config.PrivType.TypeNone;
				thumbnail_url = "";
				priv_id = "";
				priv_active_flag = 0;
			}
		}

		public PrivInfo GetPrivInfo(){
			PrivInfo info = new PrivInfo();
			info.reset();
			
			if( (this.Priv & 0x01) != 0 ){
				info.type = PrivType.TypeApp;}
			else 
				info.type = PrivType.TypeAttachment;
	
			info.thumbnail_url = this.ThumbnailUrl;

			if( this.Priv != 0 ){
				info.priv_id = this.PrivId;
			}
			info.priv_active_flag = this.PrivActiveFlag;
			return info;
		}
		public PrivInfo PropPrivInfo { 
			get {
				return GetPrivInfo();
			} 
		}
		
		public String ThumbnailUrl { get; set; }
		public String PrivId { get; set; }
		public Int64 PrivActiveFlag { get; set; }

//		[JsonProperty("IsReq")] // compile error
		public bool IsRequiredUpdate(){
			bool result = false;
			return result;
		}
				
		
		public long IsDownloadApp
		{
			get
			{
				return this.ContentType != 0 ? 1 : 0;
			}
		}
		public Int64 DirType { get; set; }
		public String DirInfo { get; set; }
		public bool IsDir
		{
			get{
				return (this.DirType == 1 ? true : false);
			}
		}

	}
}
