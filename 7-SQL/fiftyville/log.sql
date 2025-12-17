-- Keep a log of any SQL queries you execute as you solve the mystery.

-- #1 Finding who is the thief:

-- the theft took place on July 28, 2024 
-- on Humphrey Street

-- Belleow are the descripton of the crime that happend at that time at that location:
SELECT description
FROM crime_scene_reports
WHERE day = 28
AND month = 7
AND year = 2024
AND street = 'Humphrey Street';

-- took place at 10:15am 
-- at the Humphrey Street bakery.
-- three witnesses who were present at the time
-- each of their interview transcripts mentions the bakery.

-- Bellow are the transcripts of the three interviews:
SELECT name, transcript
FROM interviews
WHERE year = 2024
AND month = 7
AND day = 28
AND transcript like '%bakery%';

-- Interviews
-- Ruth Said: Sometime within "ten minutes of the theft", I saw the thief get into a "car in the bakery parking lot" and drive away

-- Bellow are the license plates of the cars that were in that parking sometime within ten minutes of the theft:
SELECT license_plate
FROM bakery_security_logs
WHERE year = 2024
AND month = 7
AND day = 28
AND hour = 10
AND minute > 15 AND minute <= 25
AND activity = 'exit';

-- Eugene Said:	I saw the thief "withdrawing money from ATM on Leggett Street".

-- Bellow are all the accounts that withdraw money from ATM on Leggett Street at that day:
SELECT account_number
FROM atm_transactions
WHERE year = 2024
AND month = 7
AND day = 28
AND atm_location = 'Leggett Street'
And transaction_type = 'withdraw';

-- Bellow is the people's id who are associated with these accounts
SELECT person_id
FROM bank_accounts
WHERE account_number in (
    SELECT account_number
    FROM atm_transactions
    WHERE year = 2024
    AND month = 7
    AND day = 28
    AND atm_location = 'Leggett Street'
    And transaction_type = 'withdraw'
);

-- Raymond Said: As the thief was leaving the bakery, they called someone who talked to them for less than a minute.

-- Bellow are all the phone numbers of the people who called at that day, and talked for less than 60s: 
SELECT caller
FROM phone_calls
WHERE year = 2024
AND month = 7
AND day = 28
AND duration < 60

-- Raymond Said also: In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked their accomplice to purchase the flight ticket.

-- Bellow is the id of all the flights in the morning of the day next to 28:
SELECT id
FROM flights
WHERE origin_airport_id = (
    SELECT id
    FROM airports
    WHERE city = 'Fiftyville'
)
AND year = 2024
AND month = 7
AND day = 29
and hour < 12;

-- The earliest flight out of Fiftyville was at 8:20, So lets get the passengers of that flight:
SELECT passport_number
FROM passengers
WHERE flight_id = (
    SELECT id
    FROM flights
    WHERE origin_airport_id = (
        SELECT id
        FROM airports
        WHERE city = 'Fiftyville'
    )
    AND year = 2024
    AND month = 7
    AND day = 29
    AND hour = 8
    AND minute = 20
);

-- Bellow are the people who are associated with all these events
SELECT name
FROM people
WHERE phone_number in (
    SELECT caller
    FROM phone_calls
    WHERE year = 2024
    AND month = 7
    AND day = 28
    AND duration < 60
)
AND passport_number in (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = (
        SELECT id
        FROM flights
        WHERE origin_airport_id = (
            SELECT id
            FROM airports
            WHERE city = 'Fiftyville'
        )
        AND year = 2024
        AND month = 7
        AND day = 29
        AND hour = 8
        AND minute = 20
    )
)
AND license_plate in (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2024
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute > 15 AND minute <= 25
    AND activity = 'exit'
)
AND id in (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number in (
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2024
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
        And transaction_type = 'withdraw'
    )
);

-- So Bruse is The thief.

#2 Finding What city the thief escaped to:

-- we know what fight the thief took, so lets get the id of the destination airport:
SELECT destination_airport_id
FROM flights
WHERE origin_airport_id = (
    SELECT id
    FROM airports
    WHERE city = 'Fiftyville'
)
AND year = 2024
AND month = 7
AND day = 29
AND hour = 8
AND minute = 20;

-- lets get the city of that airport with that id

SELECT city
FROM airports
WHERE id = (
    SELECT destination_airport_id
    FROM flights
    WHERE origin_airport_id = (
        SELECT id
        FROM airports
        WHERE city = 'Fiftyville'
    )
    AND year = 2024
    AND month = 7
    AND day = 29
    AND hour = 8
    AND minute = 20
);
-- The city the thief escaped to, is New York City.

#3 Finding Who the thief’s accomplice is:

-- Since we know who the thief is, lets find out who he was talking to at the time Raymond heard him:
-- lets ge tthe phone number of the accomplice:
SELECT receiver
FROM phone_calls
WHERE caller = (
    SELECT phone_number
    FROM people
    WHERE name = 'Bruce'
)
AND year = 2024
AND month = 7
AND day = 28
AND duration < 60;

-- Lets get the name associated with that phone number:
SELECT name
FROM people
WHERE phone_number in (
    SELECT receiver
    FROM phone_calls
    WHERE caller = (
        SELECT phone_number
        FROM people
        WHERE name = 'Bruce'
    )
    AND year = 2024
    AND month = 7
    AND day = 28
    AND duration < 60
);
-- So the the thief’s accomplice, who helped them escape is Robin
