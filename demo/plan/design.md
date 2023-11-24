# Demo Design

Target: Design a demo version of the game using object-oriented programming.

## Objects

- `Board`: The board of the game, which contains the information of the pieces on the board.
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

- `vector<node> get_history()`: Get the history of the game.

- `int get_situ(int x,int y)`: Get the situation of a position on the board. (To avoid the usage of pointers)

- `pair<int,int> get_score()`: Get the score of the game.(Count the number of pieces of each color)

### Game 

#### Private Members

- `Board br`: The board of the game, which contains the information of the pieces on the board.

#### Public Members

- `Game()`: The constructor of the game, which initializes the game.

- `void start()`: Start the game.

- `void round(int color)`: Start a round of the game , `color` is the color of the player to move.

- `void replay(string filename)`: Replay the given game.