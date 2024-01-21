== https://edabit.com/challenge/rscwis53jKokoKRYo ==

Create a function that takes an array of char inputs from a Tic Tac Toe game. Inputs will be taken from player1 as "X", player2 as "O", and empty spaces as "#". The program will return the winner or tie results.
Examples

ticTacToe([
  ["X", "O", "O"],
  ["O", "X", "O"],
  ["O", "#", "X"]
]) ➞ "Player 1 wins"

ticTacToe([
  ["X", "O", "O"],
  ["O", "X", "O"],
  ["X", "#", "O"]
]) ➞ "Player 2 wins"

ticTacToe([
  ["X", "X", "O"],
  ["O", "X", "O"],
  ["X", "O", "#"]
]) ➞ "It's a Tie"

Notes

All inputs are valid (there will be no games where both players win).
