/*
Let’s apply data intervals for the person table. Please make a SQL statement which returns a person's identifiers, person's names and interval of person’s ages (set a name of a new calculated column as ‘interval_info’) based on pseudo code below.

if (age >= 10 and age <= 20) then return 'interval #1'
else if (age > 20 and age < 24) then return 'interval #2'
else return 'interval #3'
and yes...please sort a result by ‘interval_info’ column in ascending mode.
*/

SELECT id, name,
    CASE 
        WHEN age BETWEEN 10 AND 20 THEN 'interval #1'
        WHEN age > 10 AND age < 20 THEN 'interval #2'        
        ELSE 'interval #3'
    END as interval_info
FROM person
ORDER BY interval_info ASC;