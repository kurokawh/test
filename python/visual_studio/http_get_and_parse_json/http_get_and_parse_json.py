# importing the requests library 
import requests 
import urllib3

# disable InsecureRequestWarning warning for unknown cert.
urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)




  

def http_get(base, tid) :  
    url = base + tid + "_00/concept"
    print("url: " + url)

    # sending get request and saving the response as response object 
    r = requests.get(url, verify = False) 
  
    # extracting data in json format 
    data = r.json() 
  
  
    # extracting latitude, longitude and formatted address  
    # of the first matching location 
    concept_id = data['id']
    name = data['nameEn']
    type = data['type']

    # printing the output 
    print("%s,%s,%s,%s" %(title_id, concept_id, name, type)) 



http_get("https://ps5.np.playstation.net/api/catalog/v2/titles/", "CUSA11456")

