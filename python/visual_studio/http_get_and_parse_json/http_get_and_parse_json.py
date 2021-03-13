# importing the requests library 
import requests 

title_id = "CUSA11456"
  
# api-endpoint 
#URL = "http://maps.googleapis.com/maps/api/geocode/json"
URL = "https://ps5.np.playstation.net/api/catalog/v2/titles/CUSA11456_00/concept"
  
  
# sending get request and saving the response as response object 
r = requests.get(url = URL, verify = False) 
  
# extracting data in json format 
data = r.json() 
  
  
# extracting latitude, longitude and formatted address  
# of the first matching location 
concept_id = data['id']
name = data['nameEn']
type = data['type']

# printing the output 
print("%s,%s,%s,%s"
      %(title_id, concept_id, name, type)) 
