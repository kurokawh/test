
import os
import glob
import hashlib

# return a list of hash target files under given directories.
# assume that *.csproj and Program.cs is placed in same directory.
def find_target_files(targetPath):
    found_list = list()
    csproj_list = glob.glob(targetPath)
    for csproj in csproj_list:
        programCsName = os.path.dirname(csproj) + r"\Program.cs"
        if (os.path.exists(programCsName)):
            found_list.append(programCsName)
    return found_list


def generate_hash(path):
    f = open(path,'rb')
    binary_data = f.read()
    f.close()
    hex_sha1 = hashlib.sha1(binary_data).hexdigest()
    return hex_sha1


def xor_strings(xs, ys):
    xb = xs.decode("hex")
    yb = ys.decode("hex")
    rb = "".join(chr(ord(x) ^ ord(y)) for x, y in zip(xb, yb))
    return rb.encode("hex")


DEST_FILE_NAME = "a.txt"
if (os.path.exists(DEST_FILE_NAME)):
    print("no need calc hash.")
else:
    programCsList = find_target_files(r"..\..\..\csharp\*\*\*.csproj")
    print programCsList
    hashList = map(generate_hash, programCsList)
    print hashList
    hash = reduce(xor_strings, hashList)
    print hash

    f = open(DEST_FILE_NAME, 'w')
    f.write("#define PROGRAM_CS_HASH 0x" + hash + "L")
    f.close()
    print("hash header is generated.")
