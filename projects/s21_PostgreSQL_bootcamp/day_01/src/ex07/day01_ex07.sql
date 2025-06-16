/*

Please write a SQL statement which returns the date of order from the person_order table and corresponding person name (name and age are formatted as in the data sample below) which made an order from the person table. Add a sort by both columns in ascending mode.

order_date	person_information
2022-01-01	Andrey (age:21)
2022-01-01	Andrey (age:21)
2022-01-01	Anna (age:16)
...	...

*/
SELECT  order_date
       ,(person.name || ' (' || 'age:' || person.age || ')' ) AS person_information
FROM person_order
JOIN person
ON person.id = person_order.person_id
ORDER BY 1;