# Piscine SQL - Day 05

## Query Optimization with Indexes

### Exercise 00
**Task:** Create B-tree indexes for all foreign keys. Names should follow `idx_{table_name}_{column_name}` pattern.

### Exercise 01
**Task:** Write query returning pizza and pizzeria names. Prove indexes work using `EXPLAIN ANALYZE`.

### Exercise 02
**Task:** Create functional index `idx_person_name` for uppercase names. Provide proof of work with `EXPLAIN ANALYZE`.

### Exercise 03
**Task:** Create multicolumn index `idx_person_order_multi` for query filtering by `person_id` and `menu_id`. Show "Index Only Scan".

### Exercise 04
**Task:** Create unique index `idx_menu_unique` for `pizzeria_id` and `pizza_name` combination. Prove it works.

### Exercise 05
**Task:** Create partial unique index `idx_person_order_order_date` for `person_id` and `menu_id` with date condition '2022-01-01'.

### Exercise 06
**Task:** Create index `idx_1` to optimize window function. Show execution time improvement.

[Русская версия](README_RUS.md)