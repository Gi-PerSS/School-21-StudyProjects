/*
Please use SQL construction from Exercise 05 and add a new calculated column (use column's name ‘check_name’) with a check statement (a pseudo code for this check is presented below) in the SELECT clause.

if (person_name == 'Denis') then return true
    else return false
*/

SELECT 
    (SELECT name FROM person WHERE id = person_order.person_id) AS name,
    (SELECT name FROM person WHERE id = person_order.person_id) = 'Denis' AS check_name
FROM 
    person_order
WHERE 
    (menu_id = 13 OR menu_id = 14 OR menu_id = 18)
    AND order_date = '2022-01-07';
