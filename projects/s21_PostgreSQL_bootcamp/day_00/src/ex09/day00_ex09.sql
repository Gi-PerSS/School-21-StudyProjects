/*
Please make a select statement that returns person names and pizzeria names based on the person_visits table with date of visit in a period from 07th of January to 09th of January 2022 (including all days) (based on internal query in FROM clause) .

Please take a look at the pattern of the final query.

SELECT (...) AS person_name ,  -- this is an internal query in a main SELECT clause
        (...) AS pizzeria_name  -- this is an internal query in a main SELECT clause
FROM (SELECT … FROM person_visits WHERE …) AS pv -- this is an internal query in a main FROM clause
ORDER BY ...
Please add a ordering clause by person name in ascending mode and by pizzeria name in descending mode
*/

SELECT
    (
        SELECT name
        FROM person
        WHERE id = pv.person_id
    ) AS person_name,
    (
        SELECT name
        FROM pizzeria
        WHERE id = pv.pizzeria_id
    ) AS pizzeria_name
FROM
    person_visits pv
WHERE
    pv.visit_date BETWEEN '2022-01-07' AND '2022-01-09'
ORDER BY
    person_name ASC,
    pizzeria_name DESC;
