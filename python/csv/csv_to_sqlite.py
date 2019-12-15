import csv
import sqlite3


conn = sqlite3.connect('./a.db')
c = conn.cursor()
c.execute('create table tbl_towns(town_name , city_id, country_code, city_name)')
insert_sql = 'insert into tbl_towns(town_name , city_id, country_code, city_name) values (?,?,?,?)'

csv_file = open("./input.csv", "r")

reader = csv.reader(csv_file, delimiter=",", doublequote=True, lineterminator="\r", quotechar='"', skipinitialspace=True)
header = next(reader)
print(header)
for row in reader:
    # row is List
    # row[0] can refer each column
    print(row)
    c.execute(insert_sql, (row[3], row[0], row[1], row[2]))


conn.commit()
conn.close()
