
/* ex02

Please create a Database View (with name v_generated_dates) which should be “store” generated dates from 1st to 31th of January 2022 in DATE type. Don’t forget about order for the generated_date column.

generated_date
2022-01-01
2022-01-02
...

*/

DROP VIEW IF EXISTS v_generated_dates;

CREATE VIEW v_generated_dates AS(
SELECT  generate_series::DATE AS generated_date
FROM generate_series
('2022-01-01'::DATE, '2022-01-31'::DATE, '1 day'
) AS generate_series);

select * from v_generated_dates;