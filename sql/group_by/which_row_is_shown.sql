WITH tbl(dup, str, b) AS
     (SELECT *
     	     FROM (VALUES (1, 'a', true),
             	  	  (1, 'b', true),
             	  	  (1, 'a', false),
             	  	  (1, 'b', false),
             	  	  (1, 'b', NULL),
			  (2, 'a', true),
             	  	  (2, 'b', true),
             	  	  (2, 'a', false),
             	  	  (2, 'b', false),
             	  	  (2, 'b', NULL),
			  (NULL, NULL, NULL)))
SELECT * FROM tbl GROUP BY dup;
--> first row for each distinction is shown



SELECT * FROM 
(
WITH tbl(dup, str, b) AS
     (SELECT *
     	     FROM (VALUES (1, 'a', true),
             	  	  (1, 'b', true),
             	  	  (1, 'a', false),
             	  	  (1, 'b', false),
             	  	  (1, 'b', NULL),
			  (2, 'a', true),
             	  	  (2, 'b', true),
             	  	  (2, 'a', false),
             	  	  (2, 'b', false),
             	  	  (2, 'c', NULL),
			  (NULL, NULL, NULL)))
SELECT * FROM tbl ORDER BY str DESC
) 
GROUP BY dup;
--> first row for each distinction is shown



--SELECT dup, str, MIN(num) FROM 
SELECT dup, str, MAX(num) FROM 
(
WITH tbl(dup, str, num) AS
     (SELECT *
     	     FROM (VALUES (1, 'a', 100),
             	  	  (1, 'b', 101),
             	  	  (1, 'a', 102),
             	  	  (1, 'b',  99),
             	  	  (1, 'b', 104),
			  (2, 'a', 105),
             	  	  (2, 'b', 106),
             	  	  (2, 'a',  98),
             	  	  (2, 'b', 108),
             	  	  (2, 'c', 109),
             	  	  (1, 'c', 110),
			  (NULL, NULL, NULL)))
SELECT * FROM tbl ORDER BY str DESC
) 
GROUP BY dup;
-- if MAX/MIN is set, correct row which has MAX/MIN num is returned.
