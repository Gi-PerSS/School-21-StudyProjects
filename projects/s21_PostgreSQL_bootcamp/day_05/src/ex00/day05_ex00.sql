/* ex00
Please create a simple BTree index for every foreign key in our database. The name pattern should satisfy the next rule “idx_{table_name}_{column_name}”. For example, the name BTree index for the pizzeria_id column in the menu table is idx_menu_pizzeria_id.
*/

DROP INDEX IF EXISTS idx_person_order_person_id,
                 idx_person_order_menu_id,
                 idx_person_visits_person_id,
                 idx_person_visits_pizzeria_id,
                 idx_menu_pizzeria_id;


CREATE INDEX idx_person_order_person_id ON person_order (person_id);
CREATE INDEX idx_person_order_menu_id ON person_order (menu_id);
CREATE INDEX idx_person_visits_person_id ON person_visits (person_id);
CREATE INDEX idx_person_visits_pizzeria_id ON person_visits (pizzeria_id);CREATE INDEX idx_menu_pizzeria_id ON menu (pizzeria_id);