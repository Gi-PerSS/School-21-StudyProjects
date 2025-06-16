
/* ex08

After all our exercises were born a few Virtual Tables and one Materialized View. Let’s drop them!

-- Список материализованных представлений
SELECT matviewname FROM pg_matviews;

-- Список обычных представлений
SELECT table_name FROM information_schema.views WHERE table_schema = 'public'; 

*/

DROP MATERIALIZED VIEW IF EXISTS mv_dmitriy_visits_and_eats;

DROP VIEW IF EXISTS  v_persons_female, v_persons_male, v_from_1_to_31_january_dates, v_generated_dates, v_symmetric_union, v_price_with_discount;