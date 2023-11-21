# Demo Design

Target: Design a demo version of the game using object-oriented programming.

## Objects

- `Board`: The board of the game, which contains the information of the pieces on the board.
- `Player`: The human player of the game, which contains the information of the player.
- `AI`: The AI player of the game, which contains the information of the player and the algorithm of the AI.
- `Game`: The game, which contains the information of the game and the functions of the game.

### Board

#### Private Members

- `int board[8][8]`: The board of the game, which contains the information of the pieces on the board. `0` means empty, `1` means black, `-1` means white.

- `stack<node> history`: The history of the game, which contains the information of the moves.

- `struct node{int x,y,z;}` : a tuple to store the move. `x` and `y` are the coordinates of the move, `z` is the color of the move.

#### Public Members

- `Board()`: The constructor of the board, which initializes the board.

- `void print()`: Print the board.

- `void print_with_hint(int turn)`: Print the board with the hint of the next move.

- `void print_with_predict(node t)`: Print the board with the prediction of the board after an undecided move.

- `void move(node t)`: Make a move.

- `void undo()`: Undo the last move.

- `bool check(node t)`: Check if a move is valid.

- `void save(string filename)`: Save the game to a file in the format of `.rps`.

- `void load(string filename)`: Load the game from a file in the format of `.rps`.