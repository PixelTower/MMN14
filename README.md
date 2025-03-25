# MMN14 - Two-Pass Assembler

This is an implementation of a two-pass assembler that processes assembly language code. The project is structured in multiple components:

1. **Preprocessor (Prepro)**:

   - Handles macro expansions
   - Cleans up input code

2. **Front End**:

   - Initial processing of assembly code
   - Empty implementation currently

3. **Middle End**:

   - First Pass: Collects labels and calculates addresses
   - Second Pass: Converts labels to addresses

4. **Back End**:
   - Manages label table
   - Handles symbol resolution

The assembler works in two passes:

- First Pass: Scans for labels, calculates memory addresses
- Second Pass: Resolves labels and generates final machine code

Currently tracking both instruction counter (IC) and data counter (DC) for memory allocation.
