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
