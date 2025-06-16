/*
Denied	
SQL Syntax Construction	NOT IN, IN, NOT EXISTS, EXISTS, UNION, EXCEPT, INTERSECT
Let’s return back to Exercise #01, please rewrite your SQL by using the CTE (Common Table Expression) pattern. Please move into the CTE part of your "day generator". The result should be similar like in Exercise #01

missing_date
2022-01-03
2022-01-04
2022-01-05
*/

WITH all_days AS (
SELECT generate_series('2022-01-01', '2022-01-10', interval '1 day')::DATE AS day
)
SELECT all_days.day AS missing_date
FROM all_days
LEFT JOIN (
SELECT visit_date
FROM person_visits
WHERE (person_id = 1 OR person_id = 2)
AND visit_date BETWEEN '2022-01-01' AND '2022-01-10'
) AS filtered ON all_days.day = filtered.visit_date
WHERE filtered.visit_date IS NULL
ORDER BY missing_date ASC;