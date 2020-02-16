# tictactoe
A C implementation of tic-tac-toe with a negamax-powered AI.

It runs completely on the terminal. Here's how it looks waiting for your next move:
```
   | a | b | c
---+---+---+---
 1 | O |   |
---+---+---+---
 2 |   | X |
---+---+---+---
 3 |   |   |
>
```

To actually make a move, type [column][row], such as:
```
> a3
```

## arguments
If no arguments are provided, tictactoe runs in two-player mode.
You can provide the argument `--ai` followed by an `X` or an `O`, if you want the AI to play Xs or Os, respectively.
