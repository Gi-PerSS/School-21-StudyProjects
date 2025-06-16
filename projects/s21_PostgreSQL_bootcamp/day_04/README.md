# Piscine SQL - Day 04

## Virtual Tables and Materialized Views

### Exercise 00
**Task:** Create 2 views (v_persons_female and v_persons_male) filtered by gender from person table.

### Exercise 01
**Task:** Using views from exercise 00, return combined list of male and female names sorted by name.

### Exercise 02
**Task:** Create view v_generated_dates containing dates from Jan 1-31, 2022.

### Exercise 03
**Task:** Find days in Jan 2022 when no one visited pizzerias using v_generated_dates view. Sort by date.

### Exercise 04
**Task:** Create view v_symmetric_union implementing formula (R - S)∪(S - R), where R - visits on Jan 2, S - visits on Jan 6, 2022.

### Exercise 05
**Task:** Create view v_price_with_discount showing orders with 10% discounted prices (rounded to integer).

### Exercise 06
**Task:** Create materialized view mv_dmitriy_visits_and_eats with data about Dmitriy's Jan 8, 2022 visit where he could eat pizza under 800 rub.

### Exercise 07
**Task:** Add new Dmitriy visit (excluding pizzeria from ex.06) and refresh materialized view.

### Exercise 08
**Task:** Drop all created views and materialized views.

[Русская версия](README_RUS.md)