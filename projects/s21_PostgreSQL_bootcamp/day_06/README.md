# Piscine SQL - Day 06

## Extending Data Model for Discount System

### Exercise 00
**Task:** Create `person_discounts` table to store personal discounts with:
- id (primary key)
- person_id (foreign key)
- pizzeria_id (foreign key)
- discount (numeric value)

### Exercise 01
**Task:** Populate `person_discounts` based on order history:
- 10.5% discount for 1 order
- 22% for 2 orders
- 30% for 3+ orders
- Use ROW_NUMBER() for id generation

### Exercise 02
**Task:** Write query showing orders with original and discounted prices, sorted by name and pizza.

### Exercise 03
**Task:** Create unique index `idx_person_discounts_unique` to prevent (person_id, pizzeria_id) duplicates.

### Exercise 04
**Task:** Add constraints to `person_discounts`:
- NOT NULL for all columns
- Default 0 for discount
- Discount range (0-100)

### Exercise 05
**Task:** Add comments to `person_discounts` table and columns.

### Exercise 06
**Task:** Create sequence `seq_person_discounts` and setup auto-increment for id.

[Русская версия](README_RUS.md)