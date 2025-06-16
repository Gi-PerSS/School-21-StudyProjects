
/* ex05

Please write a SQL statement which returns all possible combinations between person and pizzeria tables and please set ordering by person identifier and then by pizzeria identifier columns. Please take a look at the result sample below. Please be aware column's names can be different for you.

person.id	person.name	age	gender	address	pizzeria.id	pizzeria.name	rating
1	Anna	16	female	Moscow	1	Pizza Hut	4.6
1	Anna	16	female	Moscow	2	Dominos	4.3
...	...	...	...	...	...	...	...

*/
-- вариант 1
SELECT  *
FROM person, pizzeria
ORDER BY person.id, pizzeria.id;

-- вариант 2
SELECT  *
FROM person
CROSS JOIN pizzeria
ORDER BY person.id, pizzeria.id;
