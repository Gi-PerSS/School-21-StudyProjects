/*
Please write a SQL statement that returns the total volume (sum of all money) of transactions from user balance aggregated by user and balance type. Please be aware, all data should be processed including data with anomalies. Below presented a table of result columns and corresponding calculation formula.

Output Column	Formula (pseudocode)

name	source: user.name if user.name is NULL then return not defined value

lastname	source: user.lastname if user.lastname is NULL then return not defined value

type	source: balance.type

volume	source: balance.money need to summarize all money “movements”

currency_name	source: currency.name if currency.name is NULL then return not defined value

last_rate_to_usd	source: currency.rate_to_usd. take a last currency.rate_to_usd for corresponding currency if currency.rate_to_usd is NULL then return 1

total_volume_in_usd	source: volume , last_rate_to_usd. make a multiplication between volume and last_rate_to_usd

Please take a look at a sample of output data below. Sort the result by user name in descending mode and then by user lastname and balance type in ascending mode.

name	lastname	type	volume	currency_name	last_rate_to_usd	total_volume_in_usd
Петр	not defined	2	203	not defined	1	203
Иван	Иванов	1	410	EUR	0.9	369
...	...	...	...	...	...	...

*/

WITH first_part AS (
  SELECT 
    COALESCE(public.user.name, 'not defined') AS full_name,
    COALESCE(public.user.lastname, 'not defined') AS last_name,
    balance.type AS balance_type,
    SUM(balance.money) AS volume,
    ARRAY_AGG(balance.currency_id) AS currency_id_array
  FROM 
    public.user
    FULL JOIN balance ON balance.user_id = public.user.id
  GROUP BY 
    public.user.id, public.user.name, public.user.lastname, balance.type
), 
currency_last AS (
  SELECT 
    currency.id,
    currency.rate_to_usd AS last_rate_to_usd,
    ROW_NUMBER() OVER (PARTITION BY currency.id ORDER BY currency.updated DESC) AS row_number
  FROM 
    currency
)

-- select * from currency_last;

SELECT distinct
  first_part.full_name,
  first_part.last_name,
  first_part.balance_type,
  first_part.volume,
  COALESCE(currency.name, 'not defined') AS currency_name,
  COALESCE(currency_last.last_rate_to_usd, 1) AS last_rate_to_usd,
  first_part.volume * COALESCE(currency_last.last_rate_to_usd, 1) AS total_volume_in_usd
FROM 
  first_part
  LEFT JOIN currency ON currency.id = ANY(first_part.currency_id_array)
  LEFT JOIN currency_last ON currency_last.id = currency.id AND currency_last.row_number = 1
ORDER BY 
  first_part.full_name DESC, first_part.last_name ASC, first_part.balance_type ASC;
