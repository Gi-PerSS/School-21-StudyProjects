
/* ex09
Please write a SQL statement that returns aggregated information by person’s address , the result of “Maximal Age - (Minimal Age / Maximal Age)” that is presented as a formula column, next one is average age per address and the result of comparison between formula and average columns (other words, if formula is greater than average then True, otherwise False value).

The result should be sorted by address column. Please take a look at the sample of output data below.

address	formula	average	comparison
Kazan	44.71	30.33	true
Moscow	20.24	18.5	true
...	...	...	...
*/

WITH person_age_numeric AS (
  SELECT *,
         age::numeric AS age_numeric
  FROM person
)

SELECT  address
       ,round(MAX(age_numeric) - ((MIN(age_numeric)/MAX(age_numeric))),2)                     AS formula
       ,round(AVG(age_numeric),2)                                             AS average
       ,round(MAX(age_numeric) - ((MIN(age_numeric)/MAX(age_numeric))),2) > round(AVG(age_numeric),2) AS comparison
FROM person_age_numeric
GROUP BY  address
ORDER BY 1;