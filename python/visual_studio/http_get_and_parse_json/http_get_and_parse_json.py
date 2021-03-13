# importing the requests library 
import sys
import requests 
import urllib3

# disable InsecureRequestWarning warning for unknown cert.
urllib3.disable_warnings(urllib3.exceptions.InsecureRequestWarning)

if (len(sys.argv) < 1):
    print("FQDN must be specified")
    exit(-1)

print("fqdn : " + sys.argv[1])
fqdn = sys.argv[1]

DEST_CSV_FILE_NAME = "ok.txt"
DEST_SKIP_FILE_NAME = "skip.txt"
DEST_ERR_FILE_NAME = "err.txt"
  
file_ok = open(DEST_CSV_FILE_NAME, 'w')
file_skip = open(DEST_SKIP_FILE_NAME, 'w')
file_err = open(DEST_ERR_FILE_NAME, 'w')

def http_get(base, tid) :  
    url = base + tid + "/concept"
    # print("url: " + url)

    try:
        # sending get request and saving the response as response object 
        r = requests.get(url, verify = False) 
    except requests.exceptions.ConnectionError as e:
        line = "exception: {0}".format(tid)
        print(line)
        file_err.write(line + "\n")
        file_err.write(str(e) + "\n")
        return
    

    if (r.status_code == 200):
        # extracting data in json format 
        data = r.json() 
        # extracting latitude, longitude and formatted address  
        # of the first matching location 
        concept_id = data['id']
        name = data['nameEn']
        type = data['type']
        # printing the output 
        line = "OK: {0},\"{1}\",{2},{3},".format(concept_id, name, type, tid)
        print(line) 
        file_ok.write(line + "\n")
    elif (r.status_code == 404):
        line = "404: {0}".format(tid)
        print(line) 
        file_skip.write(line + "\n")
    else:
        line = "{0}: {1}".format(str(r.status_code), tid)
        print(line)
        file_err.write(line + "\n")
        file_err.write(str(r) + "\n")



# for i in range (0, 10):
for i in range (11456, 11500):
    tid = "CUSA" + str(i).zfill(5) + "_00"
    http_get("https://" + fqdn + "/api/catalog/v2/titles/", tid)


file_ok.close()
file_skip.close()
file_err.close()
