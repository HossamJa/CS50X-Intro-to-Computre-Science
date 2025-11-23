# CS50x Problem Set 2: C – Strings & Command-Line Arguments

**100% Complete** – All challenges submitted (including both Caesar and Substitution)  
**Language:** C  
**Focus:** String manipulation, command-line arguments, ASCII, cryptography basics

This problem set leveled up my C skills by diving deep into **strings**, **character arrays**, and **command-line interaction** — essential building blocks for real-world programming.

## Challenges Completed

| Problem           | Folder             | Description                                                                 | Status       |
|-------------------|--------------------|-----------------------------------------------------------------------------|--------------|
| **Scrabble**      | `scrabble/`        | Determines which of two words wins in Scrabble based on letter points       | Complete     |
| **Readability**   | `readability/`     | Computes Coleman-Liau index to determine U.S. grade level of text           | Complete     |
| **Caesar**        | `caesar/`          | Encrypts messages using Caesar’s cipher with rotating key from argv[1]     | Complete     |
| **Substitution**  | `substitution/`   | Encrypts messages using a 26-character substitution key from argv[1]       | Complete     |

**I completed both Caesar and Substitution** — pushing beyond the minimum to master encryption logic and input validation.

## Key Concepts Mastered

- Working with `char` arrays and null-terminated strings
- Command-line arguments (`argc`, `argv`)
- ASCII arithmetic and character classification (`isalpha`, `isupper`, `islower`)
- Modular arithmetic (`% 26`) for cipher rotation
- Input validation and error handling
- Preserving case in encryption
- Using `string` type from CS50 library (`#include <cs50.h>`)

## Favorite Challenge

**Substitution** — Building a full alphabetic substitution cipher with key validation (all 26 letters, no duplicates) felt like writing a real encryption tool. The logic of mapping each letter while preserving case and non-alphabetic characters was both challenging and deeply rewarding.

## Project Structure

```
pset2/
├── scrabble/         → scrabble.c
├── readability/      → readability.c
├── caesar/           → caesar.c
└── substitution/     → substitution.c
```

All programs pass `check50` and `style50` with full marks.

## Final Thoughts

Problem Set 2 transformed how I think about text in programming. Strings aren’t just data — they’re **dynamic**, **mutable**, and **powerful** when handled correctly. Going from printing "hello, world" to encrypting secret messages in pure C? That’s real growth.

**From plaintext to ciphertext — I now speak the language of strings.**

**Next:** Problem Set 3 — Algorithms and recursion await!
