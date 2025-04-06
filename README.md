# MMN14 - Two-Pass Assembler

This project implements a **two-pass assembler** in ANSI C (C90) as part of the MMN14 course (System Programming, Semester 2025א).

The assembler is modular, divided into logical components:

---

## Project Structure

### 1. **Preprocessor (Prepro)**
- Handles macro expansion (`mcro ... endmcro`)
- Removes extra whitespace and cleans input
- Generates a temporary `.am` file

### 2. **Front End**
- Coordinates the full compilation process
- Manages all phases and tracks errors
- Builds and prints a macro AST (used for macro validation)

### 3. **Middle End**
- **First Pass**: 
  - Scans for labels
  - Calculates instruction/data addresses
  - Validates opcodes and operands
- **Second Pass**: 
  - Resolves symbols
  - Generates binary output (object + extern + entry files)

### 4. **Back End**
- Manages label and symbol tables
- Handles .entry and .extern directives
- Converts encoded lines into final base64 output

---

## 🔁 Two-Pass Flow

1. **First Pass**:
   - Builds symbol table
   - Calculates memory offsets using IC/DC

2. **Second Pass**:
   - Fills in missing addresses
   - Generates final `.ob`, `.ent`, `.ext` files

Instruction counter (IC) and data counter (DC) are tracked separately for memory alignment.

---

## ⚙️ Build & Run

```bash
make
./assembler example.as
