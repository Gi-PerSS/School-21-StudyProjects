/*

Denied	
SQL Syntax Construction	NOT IN, IN, NOT EXISTS, EXISTS, UNION, EXCEPT, INTERSECT
Please write a SQL statement which returns the missing days from 1st to 10th of January 2022 (including all days) for visits of persons with identifiers 1 or 2. Please order by visiting days in ascending mode. The sample of data with column name is presented below.

missing_date
2022-01-03
2022-01-04
2022-01-05
...
*/


SELECT  all_days::DATE AS missing_date
FROM generate_series
('2022-01-01', '2022-01-10', interval '1 day'
) all_days
LEFT JOIN
(
	SELECT  visit_date
	FROM person_visits
	WHERE (person_id = 1 OR person_id = 2)
	AND visit_date BETWEEN '2022-01-01' AND '2022-01-10'
) AS filtered
ON all_days = filtered.visit_date
WHERE filtered.visit_date IS NULL
ORDER BY missing_date ASC;
