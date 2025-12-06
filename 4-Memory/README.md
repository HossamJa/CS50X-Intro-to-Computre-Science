# CS50x Problem Set 4: Memory — 100% Complete

**Status: ALL CHALLENGES CONQUERED**  
**Language:** C  
**Completed:** Volume • Filter (Less) • Filter (More) • Recover

This problem set is legendary in CS50 — and for good reason.  
We went from printing text to **manipulating raw memory**, **processing real audio**, **building computer vision filters**, and **performing digital forensics** — all in pure C.

This README documents my full journey through **Problem Set 4**.

---

### Challenges Completed

| Challenge         | Status      | Folder             | What I Built |
|-------------------|-------------|--------------------|-------------|
| **Volume**        | Completed   | `volume/`          | Audio volume scaler (raw WAV manipulation) |
| **Filter (Less)** | Completed   | `filter-less/`     | Grayscale, Sepia, Reflect, Blur |
| **Filter (More)** | Completed   | `filter-more/`     | All above + **Sobel Edge Detection** |
| **Recover**       | **Completed** | `recover/`         | JPEG forensic recovery from raw memory card |

---

### Volume

**Purpose**  
Change the volume of any WAV file by scaling its raw 16-bit audio samples.

**How to use**
```bash
make volume
./volume input.wav output.wav 2.0    # double volume
./volume input.wav quiet.wav 0.5     # half volume
```

**Learned:** File I/O, binary data, `int16_t`, header preservation

---

### Filter (Less & More)

**Purpose**  
Apply classic and advanced image filters to 24-bit BMP images using only C and pointer math.

**Filters Implemented**
| Filter     | Effect                          | Algorithm |
|-----------|----------------------------------|---------|
| Grayscale | Black & white                   | Average R+G+B |
| Sepia     | Vintage photo                   | Weighted RGB formula |
| Reflect   | Mirror image                    | Horizontal pixel swap |
| Blur      | Soft focus                      | 3×3 box blur |
| **Edges** | **Object boundaries**           | **Sobel operator (Gx + Gy)** |

**How to use**
```bash
make filter
./filter -g images/yard.bmp out.bmp      # grayscale
./filter -s images/stadium.bmp out.bmp   # sepia
./filter -r images/courtyard.bmp out.bmp # reflect
./filter -b images/tower.bmp out.bmp     # blur
./filter -e images/stadium.bmp out.bmp   # edges
```

**Highlight:** Sobel edge detection turns photos into **line drawings** — pure computer vision magic.

---

### Recover — The Legendary Final Boss

**Purpose**  
**Digital forensics**: Recover **50 deleted JPEG photos** from a raw memory card image (`card.raw`) by detecting JPEG headers in the binary stream.

**How it works**
- Reads `card.raw` in 512-byte blocks (FAT block size)
- Looks for JPEG header: `0xff 0xd8 0xff 0xeX`
- When found → opens new file `000.jpg`, `001.jpg`, etc.
- Writes every subsequent block to current JPEG until next header
- Continues until end of file

**Result:** 50 perfectly recovered photos (`000.jpg` to `049.jpg`)

**How to use**
```bash
make recover
./recover card.raw
```

**Output**
```
Recovered 50 images: 000.jpg through 049.jpg
```

**Learned:** Binary file parsing, hexadecimal signatures, slack space, forensic recovery

---

### Final Reflections

**Problem Set 4** was a **rite of passage**.

I didn’t just write code.  
I **controlled memory**.

- I made music louder with math.
- I turned color photos into vintage art.
- I taught a computer to **see edges**.
- I brought **50 lost photos back to life** from corrupted data.

This wasn’t programming.  
This was **digital archaeology**.

**From `printf("hello, world");` to recovering deleted evidence — in 4 weeks.**

**Problem Set 4: Complete.**  
**Memory: Mastered.**

**Next stop:** Problem Set 5 — Python, DNA, and the power of scripting.

The machine is no longer a mystery.  
**It’s an extension of my mind.**

— Proud CS50x Student · 2025
