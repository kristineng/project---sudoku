# project-sudoku-game

## Overview
  In this project, I create a single-player Sudoku Game in C programming language with additional features.
## Introduction
  - Sudoku is a number-placement logic-based puzzle.
  - Objective:  to fill a 9×9 grid with digits 1, 2, . . . , 9. Each row, column, and nine 3×3 
    neighboring subgrids forming the 9×9 grid must compose all digits 1 to 9 without repetition.
  - Sudoku puzzle -  a grid partially filled with clues.
  -->  In this project, the given puzzles are assumed to be proper, i.e., puzzles that have one 
    unique solution.
### Figure 1a and 1b shows a puzzle with 24 clues and its solution:
<img width="900" alt="image" src="https://github.com/user-attachments/assets/1ed8391b-b781-4b8b-8807-a7308b389ee1">

## The programme will:
  1. Allow the  player to select Easy or Hard mode.
  2. Read the puzzle & solution from source:
    - The puzzle is assumed to have only a unique solution (you do not need to check they
      have a unique solution).
    - The solution is assumed to be valid for the corresponding puzzle.
  3. Display the Sudoku puzzle.
  4. Read the player’s input and update the game board accordingly:
    - The player will select a cell by inputting (row, column).
    - The selected cell will display an ‘X’.
  5. Tell the player if it inputs a wrong number (comparing to the solution) in Easy mode. In 
     Hard mode, the program:
    - will store the number of chances left (starting at 3).
    - will only check if the number collides with other numbers in that row, column, and
      subgrid. If so, it consumes one chances,
    - does not support edits (and eventually loses) if an incorrect number is inputted.
  6. Help fill a cell in the Easy mode.
  7. Check if the player wins or (in Hard mode) loses.
  ### Program Flow:
  <img width="900" alt="image" src="https://github.com/user-attachments/assets/ac5cd8b5-88a3-4d6c-a084-04d11cb8b995">
