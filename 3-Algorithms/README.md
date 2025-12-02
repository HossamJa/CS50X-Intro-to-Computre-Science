# CS50x Problem Set 3: Algorithms – Voting Systems & Sorting

**100% Complete – All challenges submitted**  
**Including the legendary Tideman (very, very, very comfortable version)**  
**Language:** C

This problem set was a deep dive into **algorithms, data structures, and real-world democratic systems** — one of the most intellectually rewarding weeks in CS50x.

## Challenges Completed

| Problem       | Folder           | Description                                                                                   | Difficulty Level           |
|---------------|------------------|-----------------------------------------------------------------------------------------------|----------------------------|
| **Sort**      | `sort/`          | Implements and compares three sorting algorithms: Bubble, Selection, and Insertion Sort      | Core                       |
| **Plurality** | `plurality/`     | Simulates a plurality vote election – first past the post (winner-takes-all)                 | Standard                   |
| **Runoff**    | `runoff/`        | Simulates a ranked-choice runoff election – eliminates candidates with fewest votes each round | Comfortable                |
| **Tideman**   | `tideman/`       | Implements the **Tideman method** (ranked pairs) – a Condorcet-compliant voting system        | Very, very, very comfortable |

**I completed both Runoff and Tideman** — including the infamous **Tideman**, widely regarded as one of the hardest problems in CS50x.

## Key Concepts Mastered

- **Sorting Algorithms**:
  - Bubble Sort (O(n²))
  - Selection Sort
  - Insertion Sort
- **2D Arrays** and dynamic preference tracking
- **Graph Theory** in Tideman:
  - Building a **preference graph** from voter rankings
  - Detecting and avoiding **cycles** using locked pairs
  - **Locking pairs** in strength order
  - Determining the true winner (source of the directed graph)
- Ranked-choice voting systems
- Eliminating candidates and redistributing votes
- Pointers, arrays, and memory-safe iteration
            |

## Tideman – The Crown Jewel

**Tideman** is legendary in CS50 for good reason:
- Combines **graph theory**, **cycle detection**, and **voting logic**
- Requires perfect understanding of **2D arrays**, **pointer arithmetic**, and **logical flow**
- No margin for error — one off-by-one and the entire election breaks

I implemented:
- Pair strength ranking
- Cycle detection via depth-first search logic
- Correct locking order (strongest → weakest)
- Final winner identification

**It passed `check50` on the first try.**

## Project Structure

```
pset3/
├── sort/         → Implements three sorting algorithms
├── plurality/    → First-past-the-post election
├── runoff/       → Ranked-choice instant runoff
└── tideman/      → Full Tideman (ranked pairs) method
```

All programs pass `check50` and `style50` with full credit.

## Final Thoughts

Problem Set 3 wasn’t just about coding — it was about **understanding fairness in democracy**, **algorithmic efficiency**, and **how complex systems emerge from simple rules**.

**Tideman** felt like solving a logic puzzle at the level of a Harvard math proof — and I loved every second of it.

> “Anyone who says Tideman is impossible just hasn’t tried hard enough.”  
> — Me, after finally seeing “Tideman is working correctly!”

**From sorting numbers to electing presidents — I just built democracy in C.**

**Next stop:** Problem Set 4 – Memory, pointers, and file I/O  
The real C begins.
