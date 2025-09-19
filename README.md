# practice-git

## Interactive Graphical Editor

This repository contains an implementation of an interactive graphical editor that can manipulate a rectangular table of pixels.

### Building

```bash
make
```

### Usage

```bash
./editor < input.txt
```

### Commands

1. `I M N` - Creates a new M×N table filled with 'O' (white pixels)
2. `C` - Clears the table (sets all pixels to 'O')
3. `L X Y C` - Colors pixel at position (X,Y) with color C
4. `V X Y1 Y2 C` - Draws vertical line in column X from Y1 to Y2 with color C
5. `H X1 X2 Y C` - Draws horizontal line in row Y from X1 to X2 with color C
6. `K X1 Y1 X2 Y2 C` - Draws filled rectangle from (X1,Y1) to (X2,Y2) with color C
7. `F X Y C` - Flood fills region starting at (X,Y) with color C
8. `S Name` - Saves current table to file Name and displays it
9. `X` - Terminates the program

### Example

Input:
```
I 5 6
L 2 3 A
S one.bmp
G 2 3 J
F 3 3 J
V 2 3 4 W
H 3 4 2 Z
S two.bmp
X
```

Output:
```
one.bmp
OOOOO
OOOOO
OAOOO
OOOOO
OOOOO
OOOOO
two.bmp
JJJJJ
JJZZJ
JWJJJ
JWJJJ
JJJJJ
JJJJJ
```