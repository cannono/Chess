// Chess in c++
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

using namespace std;

int const board_size = 8;

struct Piece
{
    int xpos;
    int ypos;
    string color;
    string symbol;



};

void load_white (vector <Piece> &white)
{

    for (int i = 0; i < board_size; ++i)
    {
        piece temp {i, 1, "white", "P"};
        white.push_back(temp);
    }
    piece temp = {0, 0, "white", "R"};
    white.push_back(temp);
    temp.xpos = board_size - 1;
    white.push_back(temp);

    piece temp = {1, 0, "white", "K"};
    white.push_back(temp);
    temp.xpos = board_size -2;
    white.push_back(temp);

    piece temp ={2, 0, "white", "B"};
    white.push_back(temp);
    temp.xpos = board_size - 3;
    white.push_back(temp);

    piece temp = {3, 0, "white", "Q"};
    white.push_back(temp);

    pieve temp ={4, 0, "white", "K"};
    white.push_back(temp);

}

void load_black (vector <Piece> &black)
{
        for (int i = 0; i < board_size; ++i)
        {
            piece temp {i, 7, "black", "p"};
            white.push_back(temp);
        }
        piece temp = {0, 6, "black", "r"};
        white.push_back(temp);
        temp.xpos = board_size - 1;
        black.push_back(temp);

        piece temp = {1, 6, "black", "k"};
        black.push_back(temp);
        temp.xpos = board_size -2;
        black.push_back(temp);

        piece temp ={2, 6, "black", "b"};
        black.push_back(temp);
        temp.xpos = board_size - 3;
        black.push_back(temp);

        piece temp = {3, 6, "black", "q"};
        black.push_back(temp);

        pieve temp ={4, 6, "black", "k"};
        black.push_back(temp);

}

void update(vector <Piece> &white, vector <Piece> &black)
{
    vector <string> blank(8, " ");
    vector <vector <string> > board(8, blank);

    for (int i = 0; i < white.size(); ++i)
    {
        board[white[i].ypos][white[i].xpos] = white[i].symbol;
    }
    for (int k = 0; k < white.size(); ++k)
    {
        board[black[k].ypos][black[k].xpos] = black[k].symbol;
    }
    draw_board(board);
}

void draw_board(vector <vector<string> > &board)
{
    for (int i = 0; i < board.size(); ++i)
    {   cout << "|"
        for (int k = 0; < board[i].size(); ++k)
        {
            cout << board[i][k] << "|"
        }
        cout << endl;
    }
}

bool valid_move(Piece &piece, int newx, int newy)
{
    // Implement this later, but for now just return true.
    // if the move is valid it will also make the move and store it in piece.

    /*&string type = piece.symbol
    int xdiff = piece.xpos - newx;
    int ydiff = piece.ypos - newy;

    if(newx > board_size || newy > board_size)
    {
        return false;
    }
    if (type == "P")
    {
        if(piece.first_move == true)
        {
            if(xdiff >)
        }
    }
    */


    piece.xpos = newx;
    piece.ypos = newy;
    return true;
}

bool valid_piece(vector <string> pieces, int x, int y, Piece &piece, int &index )
{
    for (int i = 0; i < pieces.size(); ++i)
    {
        if(pieces[i].xpos == x && pices[i].ypos ==y )
        {   piece = pieces[i];
            return true;
        }
    }
    return false;
}

void get_white_move(vector <string> &white)
{   int oldx;
    int newx;
    int oldy;
    int newy;
    int index
    Piece piece;
    cout << "What piece would you like to move? "
    cin >> oldx >> oldy;
    if(!valid_piece(white, oldx, oldy, piece, index))
    {
        cout << "That is not a valid piece" << endl;
        get_white_move(white);
    }
    cout << "Where would you like to move it? "
    cin >> newx >> newy;
    if(!valid_move(piece, newx, newy))
    {
        cout << "That is not a valid move" << endl;
        get_white_move(white);
    }
    white[index] = piece;

}

void get_black_move(vector <string> &black)
{
    int oldx;
    int newx;
    int oldy;
    int newy;
    int index
    Piece piece;

    cout << "What piece would you like to move? "
    cin >> oldx >> oldy;
    if(!valid_piece(black, oldx, oldy, piece, index))
      {
        cout << "That is not a valid piece" << endl;
        get_black_move(black);
      }
    cout << "Where would you like to move it? "
    cin >> newx >> newy;
    if(!valid_move(piece, newx, newy))
      {
        cout << "That is not a valid move" << endl;
        get_black_move(black);
      }
    black[index] = piece;
}
int main()
{
cout << "Welcome to my chess game. Moves will be made by entering the coordinates (1-8,1-8) with a space inbetween and no parenthesis ";
cout << "of the piece you would like to move, followed by the coordinates you would like to move that piece to. Enjoy!" << endl;
bool checkmate = false;
vector <piece> white;
vector <piece> black;
string winner "";

load_white(white);
load_black(black);

update(white, black);

while(!checkmate)
{
    cout << "It is white's turn" << enld;
    get_white_move();
    update();
    checkmate();
    cout << "It is black's turn" << endl;
    get_black_move();
    update();
    checkmate()


}
cout << "Checkmate! " << winner << " wins!" << endl;

return 0;
}
