/*
names (based on internal query in SELECT clause) who made orders for the menu with identifiers 13 , 14 and 18 and date of orders should be equal 7th of January 2022
*/

SELECT 
    (SELECT name FROM person WHERE id = person_order.person_id) AS name
FROM 
    person_order
WHERE 
    (menu_id = 13 OR menu_id = 14 OR menu_id = 18)
    AND order_date = '2022-01-07';


