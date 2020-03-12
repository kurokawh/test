SELECT *
  FROM (VALUES (1, 2, 3),
               (4, 5, 6),
	       (NULL, NULL, NULL)
       );


SELECT COUNT(*)
  FROM (VALUES (1, 2, 3),
               (4, 5, 6),
	       (NULL, NULL, NULL)
       );
