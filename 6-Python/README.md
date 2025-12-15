# CS50x Problem Set 6: Python — 100% Complete

**Status: ALL CHALLENGES CONQUERED**  
**Language:** Python  
**Focus:** Transition to Python, file I/O, string processing, bioinformatics

This problem set marked my **official switch from C to Python** — and what a joy it was. After mastering memory management and pointers, Python felt like magic: clean syntax, powerful built-ins, and rapid development.

I completed **every version** — both "less" and "more" comfortable — to fully embrace Python's capabilities.

---

### Challenges Completed

| Challenge              | Folder              | Version Completed                  | Description |
|------------------------|---------------------|------------------------------------|-----------|
| **Hello**              | `hello/`            | Standard                           | First Python program: greet the user |
| **Mario (Less)**       | `mario-less/`       | Completed                          | Pyramid with `#` blocks |
| **Mario (More)**       | `mario-more/`       | **Completed**                      | Double pyramid with gap (like C version) |
| **Cash**               | `cash/`             | Completed                          | Greedy change calculator |
| **Credit**             | `credit/`           | **Completed**                      | Luhn’s algorithm + card detection |
| **Readability**        | `readability/`      | Completed                          | Coleman-Liau readability index |
| **DNA**                | `dna/`              | **Completed**                      | STR matching for forensic DNA identification |

---

### Hello

**Purpose**  
My first Python program — simple but symbolic.

**How to use**
```bash
python hello.py
```
→ Prompts for name → prints `hello, name`

**Learned:** `input()`, f-strings, Python's simplicity

---

### Mario (More)

**Purpose**  
Recreate the classic double Mario pyramid — now in Python elegance.

**How to use**
```bash
python mario.py
```
→ Enter height (1–8) → prints centered double pyramid

**Example Output (height 4)**
```
   #  #
  ##  ##
 ###  ###
####  ####
```

**Learned:** Nested loops, string multiplication (`" " * n`), centering with `.rjust()`

---

### Credit

**Purpose**  
Validate credit card numbers using **Luhn’s algorithm** and identify card type.

**How to use**
```bash
python credit.py
```
→ Enter card number → outputs `AMEX`, `MASTERCARD`, `VISA`, or `INVALID`

**Learned:** String slicing, digit extraction, checksum logic

---

### Readability

**Purpose**  
Compute the U.S. grade level of text using the **Coleman-Liau index**.

**How to use**
```bash
python readability.py
```
→ Enter text → outputs `Grade X`

**Learned:** Text analysis, counting letters/words/sentences, floating-point math

---

### DNA — The Capstone of PSet 6

**Purpose**  
Forensic DNA identification: find the person whose DNA matches a crime scene sample by counting **Short Tandem Repeats (STRs)**.

**How it works**
- Reads a CSV database of people and their STR counts
- Reads a DNA sequence text file
- Counts consecutive repeats of each STR (e.g., AGATC)
- Matches against database → prints name or "No match"

**How to use**
```bash
python dna.py databases/large.csv sequences/5.txt
```

**Learned:** File parsing, regex (`.count()` with overlap), dictionary lookups, real-world bioinformatics

---

### Final Reflections

**Problem Set 6** was a **revelation**.

After wrestling with pointers and memory in C, Python felt like **flying**.

- No more `malloc`/`free` → just clean, readable code
- Built-in string methods → solved in 10 lines what took 100 in C
- `dna.py` felt like real science — matching crime scene DNA!

This wasn’t just learning Python.  
It was **rediscovering joy in programming**.

**From C’s raw power to Python’s elegance — I now speak both languages.**

**Problem Set 6: Complete.**  
**Python: Mastered.**

**Next:** Problem Set 7 — SQL and databases.  
From files to structured data.

The transformation continues.
