# CS50x Problem Set 7: SQL — 100% Complete

**Status: ALL CHALLENGES CONQUERED**  
**Language:** SQL  
**Focus:** Relational databases, joins, aggregations, subqueries, real-world data analysis

This problem set was the moment I became **fluent in SQL** — the language that powers almost every app and website you use every day.

I completed every single challenge with full marks, turning raw data into meaningful answers.

---

### Challenges Completed

| Challenge       | Folder          | What I Built / What I Discovered |
|-----------------|-----------------|----------------------------------|
| **Songs**       | `songs/`        | Analyzed 8 real music questions using `ORDER BY`, `LIKE`, `IN`, `LIMIT` |
| **Movies**      | `movies/`       | Answered 13 Hollywood movie questions using joins, `DISTINCT`, `COUNT`, `BETWEEN`, subqueries |
| **Fiftyville**  | `fiftyville/`   | Solved a full **crime mystery** — found the thief, accomplice, getaway city using only SQL clues |

---

### Songs

**Purpose**  
Answer 8 real music questions about a 10,000-song database from Spotify.

**What I did**  
Wrote 8 separate queries using:
- `WHERE` with `LIKE '%love%'`
- `ORDER BY` + `DESC`
- `LIMIT 5`
- `IN` with subqueries
- `JOIN` on artists

**How to use**
```bash
cd songs
sqlite3 songs.db
.read <querie number>.sql  # run each querie at a time untill geting all 8 answers
```

**Favorite discovery**  
Finding the only song that has danceability, energy, and valence greater than 0.75 → perfect precision.

---

### Movies

**Purpose**  
Answer 13 questions about 10,000+ Hollywood movies (actors, directors, ratings, years) from IMDB database.

**Important note**  
The `movies.db` file is large (~120 MB) so I could not upload it to GitHub.  
Download it here:

[Movies DataBase](https://cdn.cs50.net/2024/fall/psets/7/movies.zip)  

OR Run the command (Ubuntu Linux):
```
wget https://cdn.cs50.net/2024/fall/psets/7/movies.zip
unzip movies.zip
```
(unzip → you get `movies.db`)

**What I did**  
Wrote 13 powerful queries:
- Movies released in 2010 and their ratings, in descending order by rating.
- People who starred in a movie released in 2004, ordered by birth year.
- Directors who have directed a movie that received a rating of at least 9.0.
- …and more (joins, `GROUP BY`, `HAVING`, subqueries)

**How to use**
```bash
# After downloading and unzipping movies.zip
cd movies
sqlite3 movies.db
.read <querie number>.sql  # run each querie at a time untill geting all 13 answers
```

**Favorite discovery**  
Finding exactly which actor appeared in the most movies in 2004 → real data storytelling.

---

### Fiftyville – The Final Boss

**Purpose**  
Solve a **real crime** using only SQL and a crime scene report. Find the thief, the accomplice, and the city they escaped to.

**What I did**  
Followed 8 clues step-by-step:
1. Crime scene report → found the exact time and location
2. Witness interviews → got license plate and phone call clues
3. ATM withdrawals → found suspect accounts
4. Security footage → matched car plates
5. Phone records → found accomplice
6. Flight records → found the escape city
7. Passenger list → found the thief’s name!

**Result**  
Thief: **Bruce**  
Accomplice: **Robin**  
Escape city: **New York City**

**How to use**
```bash
cd fiftyville
sqlite3 fiftyville.db
.read log.sql     # my step-by-step investigation
```

**Favorite moment**  
Running the third query befere final query that returned only one name — **Bruce**, rnning the next returns the city, and the final returns the accomplice name — after hours of Nested Select. Felt like a real detective.

---

### Final Reflections

**Problem Set 7** was **pure detective work**.

I didn’t just write SQL.  
I **solved crimes**, **analyzed Hollywood history**, and **discovered music patterns** — all with queries.

- From simple `SELECT` to **7-table joins** and **correlated subqueries**
- From 10 rows to **10,000+ row databases**
- From guessing to **finding the exact criminal** in Fiftyville

This wasn’t homework.  
This was **real-world data power**.

**Problem Set 7: Complete.**  
**SQL: Mastered.**

**Next:** Problem Set 8 — Web Development with HTML, CSS, JavaScript.  
From database to full websites.
