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
MAX_RETRY = 5
  
file_ok = open(DEST_CSV_FILE_NAME, 'w')
file_skip = open(DEST_SKIP_FILE_NAME, 'w')
file_err = open(DEST_ERR_FILE_NAME, 'w')

def http_get(base, tid, retry):
    if (retry >= MAX_RETRY):
        return

    url = base + tid + "/concept"
    # print("url: " + url)

    callAgain = False
    try:
        # sending get request and saving the response as response object 
        r = requests.get(url, verify = False) 
    except requests.exceptions.ConnectionError as e:
        line = "exception (retry: {0}): {1}".format(retry, tid)
        print(line)
        file_err.write(line + "\n")
        file_err.write(str(e) + "\n")
        callAgain = True

    if callAgain:
        http_get(base, tid, retry + 1)
        return
    
    if (r.status_code == 200):
        # extracting data in json format 
        data = r.json() 
        concept_id = data['id']
        name = data.get('nameEn', tid) # use get() because `nameEn` may does not exist
        type = data['type']
        # print to OK file in csv file format
        line = "{0},\"{1}\",{2},{3},".format(concept_id, name, type, tid)
        print("OK: " + line) 
        file_ok.write(line + "\n")
    elif (r.status_code == 404):
        # server does not have this entry.
        line = "404: {0}".format(tid)
        print(line) 
        file_skip.write(line + "\n")
    else:
        # other unexpected error. need retry
        line = "{0} (retry: {1}): {2}".format(str(r.status_code), retry, tid)
        print(line)
        file_err.write(line + "\n")
        #file_err.write(str(r) + "\n")
        http_get(base, tid, retry + 1)
        return
    return


for i in range (0, 5):
#for i in range (0, 100000):
    tid = "CUSA" + str(i).zfill(5) + "_00"
    http_get("https://" + fqdn + "/api/catalog/v2/titles/", tid, 0)


file_ok.close()
file_skip.close()
file_err.close()
