# Piscine SQL - Day 08

## Transactions and Isolation Levels

### Exercise 00
**Task:** Demonstrate transaction behavior. Update "Pizza Hut" rating to 5 in session #1, show changes aren't visible in session #2 until COMMIT.

### Exercise 01
**Task:** Reproduce "Lost Update" anomaly at READ COMMITTED level. Update rating to 4 in session #1 and 3.6 in session #2.

### Exercise 02
**Task:** Reproduce "Lost Update" at REPEATABLE READ level. Update rating to 4 in session #1 and 3.6 in session #2.

### Exercise 03
**Task:** Reproduce "Non-Repeatable Reads" at READ COMMITTED level. Check rating in session #1, update to 3.6 in session #2.

### Exercise 04
**Task:** Reproduce "Non-Repeatable Reads" at SERIALIZABLE level. Check rating in session #1, update to 3.0 in session #2.

### Exercise 05
**Task:** Reproduce "Phantom Reads" at READ COMMITTED level. Sum ratings in session #1, update "Pizza Hut" to 1 in session #2.

### Exercise 06
**Task:** Reproduce "Phantom Reads" at REPEATABLE READ level. Sum ratings in session #1, update "Pizza Hut" to 5 in session #2.

### Exercise 07
**Task:** Create a deadlock situation between two sessions.

[Русская версия](README_RUS.md)