## Project Description

In this project I wrote code to solve a hexadoku puzzle, which is essentially 16x16 hexadecimal sudoku. My code currently only works for hexadoku puzzles that will always have a cell it can fill with 100% certainty.

### To Run

In the project's directory, run these two commands in order:

>make<br>
./hex <hexadoku board filename>.txt

An example of a hexadoku board can be seen below, where -'s represent empty spaces in the board.

E - 5 2 6 1 A B 3 7 D F - C 0 -<br>
F 4 0 C 9 7 D 3 2 1 B 5 6 A 8 E<br>
A 7 6 - 5 E F 4 8 - 0 C 2 - - B<br>
\- 1 3 B 0 8 C 2 A 4 E - 7 5 F D<br>
4 0 - 9 B 3 8 - E - F A 1 6 7 2<br>
B E 2 - 7 F 4 9 1 3 6 0 C 8 - -<br>
3 5 F 1 E - 6 - 7 8 C 2 B 4 9 A<br>
\- 6 C 7 A 5 2 1 D B 4 9 F 3 E 0<br>
C D 8 0 F B - E 9 6 A 4 - 7 - -<br>
7 A E 3 - 6 9 8 B C 5 D 0 F 4 1<br>
6 F 9 4 D - 3 5 0 2 - - - B - 8<br>
1 - B 5 C 4 7 0 F E 3 8 A D 6 9<br>

### Output

The code will either output the solved hexadoku board to STDOUT, or it will alert the user that the provided board was unsolvable.
