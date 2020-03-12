-- https://stackoverflow.com/questions/43913457/how-do-i-name-the-output-column-in-a-sqlite-values-clause

with cte(my_column_alias) as 
  (select * from (values (1),(2),(3),(4),(5)))
select * from cte;


---
WITH tbl(a, b, c) AS
     (SELECT *
     	     FROM (VALUES (1, 2, 3),
             	  	  (4, 5, 6),
			  (NULL, NULL, NULL)))
SELECT * FROM tbl;

