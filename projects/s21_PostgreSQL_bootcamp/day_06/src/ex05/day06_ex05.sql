
/* ex05
To satisfy Data Governance Policies need to add comments for the table and table's columns. Let’s apply this policy for the person_discounts table. Please add English or Russian comments (it's up to you) that explain what is a business goal of a table and all included attributes.
*/

comment
ON TABLE person_discounts is 'Это таблица персональных скидок, чья настоящая бизнес цель - научить нас программировать на sql.';

-- регкласс - приведение типа к годному для функции obj_description, извлекающей комметарии к вещам.
SELECT  obj_description('person_discounts'::regclass) AS table_comment; 

comment
ON column person_discounts.id is 'Это id.'; 
comment
ON column person_discounts.person_id is 'А это уже person_id...'; 
comment
ON column person_discounts.pizzeria_id is 'pizzeria_id.'; 
comment
ON column person_discounts.discount is 'А это скидка для человека под id';

SELECT description
FROM pg_description
WHERE objoid = 'person_discounts'::regclass
  AND objsubid = 1 or  objsubid =  2 or  objsubid =  3 or  objsubid =  4;