import csv

csv_file = open("./input.csv", "r")

reader = csv.reader(csv_file, delimiter=",", doublequote=True, lineterminator="\r", quotechar='"', skipinitialspace=True)
header = next(reader)
print(header)
for row in reader:
    # row is List
    # row[0] can refer each column
    print(row)
