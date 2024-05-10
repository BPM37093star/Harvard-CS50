-- Keep a log of any SQL queries you execute as you solve the mystery.
-- crime id: 295
-- date: 2023 7 28
--description: Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
--Interviews were conducted today with three witnesses who were present at the time - each of their interview transcript mentions the bakery.
SELECT * FROM crime_scene_reports WHERE year = 2023 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

--interview transcript
--1st(id 161 name:Ruth): Sometime within 10 minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
--2nd(id:162 name:Eugene): I don't know the thief's name, but it was someone I recognised. Earlier this morning,
--before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
--3rd(id:163 name:Raymond): As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call,
--I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
SELECT * FROM interviews WHERE year = 2023 AND month = 7 AND day = 28 AND transcript LIKE '%bakery%';

--atm_transactions
SELECT * FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

--fiftyville airport id:8, abbreviation: CSF, full_name: Fiftyville Regional Airport
SELECT id FROM airports WHERE city = 'Fiftyville';

SELECT * FROM airports WHERE id = 8;

--earliest flights: id:36 origin:8 destination:4 hour:8 minute 20
SELECT * FROM flights WHERE year = 2023 AND month = 7 AND day = 29 AND origin_airport_id = 8;

--destination id:4, abbreviation:LGA, full_name: LaGuardia Airport, city: New York City
SELECT * FROM airports WHERE id = 4;

--license plate:
SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND minute > 15 AND activity = 'exit';

--accoring license plate find the passengers
--(name: Sofia Bruce Kelsey Luca)
SELECT * FROM passengers JOIN people ON passengers.passport_number = people.passport_number
WHERE flight_id = 36 AND license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND minute > 15 AND activity = 'exit');

--phone call

SELECT * FROM phone_calls WHERE year = 2023 AND month =7 AND day = 28;

SELECT * FROM phone_calls WHERE caller IN
(
    SELECT phone_number FROM passengers JOIN people ON passengers.passport_number = people.passport_number
WHERE flight_id = 36 AND license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND minute > 15 AND activity = 'exit')

)
AND year = 2023 AND month = 7 AND day = 28 AND duration < 60;

-- suspect bank account, person_id
SELECT person_id FROM bank_accounts WHERE account_number IN (
SELECT account_number FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw');

--当天在atm取钱的人的名字 according the suspect bank transaction found the person name(Kenny, Iman, Benista, Taylor, Brooke, Luca, Diana, Bruce)
SELECT name FROM people WHERE id IN
(
    SELECT person_id FROM bank_accounts WHERE account_number IN (
SELECT account_number FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw')

--Sofia, Bruce, Kelsey(Bruce phone_number (367) 555-5533 passport_number:1695452385
SELECT * FROM passengers JOIN people WHERE passengers.passport_number = people.passport_number AND
license_plate IN
(
    SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND minute > 15 AND activity = 'exit'

)
AND flight_id = 36
AND phone_number IN
(
    SELECT caller FROM phone_calls WHERE caller IN
(
    SELECT phone_number FROM passengers JOIN people ON passengers.passport_number = people.passport_number
WHERE flight_id = 36 AND license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute <= 25 AND minute > 15 AND activity = 'exit')

)
AND year = 2023 AND month = 7 AND day = 28 AND duration < 60
);

--receiver number (375) 555-8161
SELECT receiver FROM phone_calls WHERE caller = '(367) 555-5533' AND year = 2023 AND month = 7 AND day = 28 AND duration < 60;

--complice name: Robin
SELECT name FROM people WHERE phone_number = '(375) 555-8161';
