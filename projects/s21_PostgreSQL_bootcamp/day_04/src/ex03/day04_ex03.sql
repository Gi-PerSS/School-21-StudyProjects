
/* ex03

Please write a SQL statement which returns missing days for persons’ visits in January of 2022. Use v_generated_dates view for that task and sort the result by missing_date column. The sample of data is presented below.

missing_date
2022-01-11
2022-01-12
...

*/

SELECT  v_generated_dates.generated_date AS missing_date
FROM v_generated_dates
LEFT JOIN
(
	SELECT  distinct visit_date
	FROM person_visits
) unique_visit_dates
ON v_generated_dates.generated_date = unique_visit_dates.visit_date
WHERE unique_visit_dates.visit_date IS NULL
ORDER by 1;