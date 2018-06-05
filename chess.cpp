// Chess in c++
// Owen Cannon
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

int const board_size = 8;
// A data type that will hold all the information of a chess piece.
struct Piece
{
    int xpos;
    int ypos;
    string symbol;
};

// Creates the white pieces in their starting positions.
void load_white (vector <Piece> &white)
{
    for (int i = 0; i < board_size; ++i)
    {
        Piece temp {i, 1, "P"};
        white.push_back(temp);
    }

    Piece temp = {0, 0, "R"};
    white.push_back(temp);
    temp.xpos = board_size - 1;
    white.push_back(temp);

    temp = {1, 0, "H"};
    white.push_back(temp);
    temp.xpos = board_size -2;
    white.push_back(temp);

    temp ={2, 0, "B"};
    white.push_back(temp);
    temp.xpos = board_size - 3;
    white.push_back(temp);

    temp = {3, 0,"Q"};
    white.push_back(temp);

  temp ={4, 0, "K"};
    white.push_back(temp);

}

// Creates the black pieces in their starting position.
void load_black (vector <Piece> &black)
{
        for (int i = 0; i < board_size; ++i)
        {
            Piece temp {i, 6, "p"};
            black.push_back(temp);
        }

        Piece temp = {0, 7, "r"};
        black.push_back(temp);
        temp.xpos = board_size - 1;
        black.push_back(temp);

        temp = {1, 7, "h"};
        black.push_back(temp);
        temp.xpos = board_size -2;
        black.push_back(temp);

        temp ={2, 7, "b"};
        black.push_back(temp);
        temp.xpos = board_size - 3;
        black.push_back(temp);

        temp = {3, 7, "q"};
        black.push_back(temp);

        temp ={4, 7, "k"};
        black.push_back(temp);
}

// Board is a vector of vectors so it can be thought of as an 8x8 matrix.
// draw_board will print out each row of the matrix.
void draw_board(vector <vector<string> > &board)
{
    cout << "   0 1 2 3 4 5 6 7  " << endl;
    // Loops through the rows
    for (int i = 0; i < board.size(); ++i)
    {   cout << i << " |";
        // Loops through the columns
        for (int k = 0; k < board[i].size(); ++k)
        {
            cout << board[i][k] << "|";
        }
        cout << endl;
    }
    cout << endl;
}

// This function helps to determine if the king is in check or checkmate.
// Given the current state of the board, the position of a piece, and a direction this
// function will move in that direction to see if there is an opposing piece that could
// take the piece that was passed as a parameter.
bool danger(const vector< vector<string> > &board, Piece piece, int x, int y, int xdir, int ydir)
{
  int xstart = x;
  int ystart = y;

  bool uppercase = isupper(piece.symbol[0]);
  string type;

  if(x+xdir > 7 || x+xdir < 0 || y+ ydir > 7 || y + ydir < 0)
  {
    return false;
  }
  x += xdir;
  y += ydir;

  while(x <= 7 && x >= 0 && y <= 7 && y >= 0)
  {
    if(board[y][x] != " ")
    {
      bool temp = isupper(board[y][x][0]);
      if(temp == uppercase)
      {
        return false;
      }
      type = board[y][x];
      break;
      }
      x += xdir;
      y += ydir;
    }

    if(type =="P")
    {
      if(ystart - y == 1 && abs(xstart - x) == 1)
      {
        return true;
      }
      return false;
    }
    if(type == "p")
    {
      if(ystart - y == -1 && abs(xstart -x) == 1)
      {
        return true;
      }
      return false;
    }
    if(type == "R" || type == "r")
    {
      if((xstart - x) == 0 || (ystart - y) == 0)
      {
        return true;
      }
      return false;
    }

    if(type == "B" || type == "b")
    {
      if(xstart - x == ystart - y)
      {
        return true;
      }
      return false;
    }

    if(type == "Q" || type == "q")
    {
      return true;
    }
    if(type == "K" || type == "k")
    {
      return false;
    }
    return false;
  }

  // Calls on danger() with all 8 possible directions. If any of them come back true
  // then check will return true else check will return false. (also checks for knights)
  bool check(const vector< vector<string> > &board, Piece piece, int x, int y)
  {
    //upwards
    if(danger(board, piece, x, y, 0, -1) == true)
    {
      return true;
    }

    // right
    if(danger(board, piece, x, y, 1, 0) == true)
    {
      return true;
    }
    // downwards
    if(danger(board, piece, x, y, 0, 1) == true)
    {
      return true;
    }
    if(danger(board, piece, x, y, -1, 0) == true)
    {
      return true;
    }
    //upper left
    if(danger(board,piece, x, y, -1, -1) == true)
    {
      return true;
    }
    //upper right
    if(danger(board, piece, x, y, 1, -1) == true)
    {
      return true;
    }
    //lower right
    if(danger(board, piece, x, y, 1,1) == true)
    {
      return true;
    }
    // lower left
    if(danger(board, piece, x, y, -1, 1) == true)
    {
      return true;
    }

    // check for knights
    bool uppercase = isupper(piece.symbol[0]);
    int xknight = x + 2;
    int yknight = y + -1;
    if(xknight >= 0 && xknight <= 7 && yknight >= 0 && yknight <= 7)
    {
      if(board[yknight][xknight] != " ")
      {
        if(board[yknight][xknight] == "H" || board[yknight][xknight] == "h")
        {
          if(bool(isupper(board[yknight][xknight][0])) != uppercase)
          {
            return true;
          }
        }
      }
    }

    // check for knights
    xknight = x + 2;
    yknight = y + 1;
    if(xknight >= 0 && xknight <= 7 && yknight >= 0 && yknight <= 7)
    {
      if(board[yknight][xknight] != " ")
      {
        if(board[yknight][xknight] == "H" || board[yknight][xknight] == "h")
        {
          if(bool(isupper(board[yknight][xknight][0])) != uppercase)
          {
            return true;
          }
        }
      }
    }
    // check for knights
    xknight = x + 1;
    yknight = y + 2;
    if(xknight >= 0 && xknight <= 7 && yknight >= 0 && yknight <= 7)
    {
      if(board[yknight][xknight] != " ")
      {
        if(board[yknight][xknight] == "H" || board[yknight][xknight] == "h")
        {
          if(bool(isupper(board[yknight][xknight][0])) != uppercase)
          {
            return true;
          }
        }
      }
    }
    // check for knights
    xknight = x + -1;
    yknight = y + 2;
    if(xknight >= 0 && xknight <= 7 && yknight >= 0 && yknight <= 7)
    {
      if(board[yknight][xknight] != " ")
      {
        if(board[yknight][xknight] == "H" || board[yknight][xknight] == "h")
        {
          if(bool(isupper(board[yknight][xknight][0])) != uppercase)
          {
            return true;
          }
        }
      }
    }
    // check for knights
    xknight = x + -2;
    yknight = y + 1;
    if(xknight >= 0 && xknight <= 7 && yknight >= 0 && yknight <= 7)
    {
      if(board[yknight][xknight] != " ")
      {
        if(board[yknight][xknight] == "H" || board[yknight][xknight] == "h")
        {
          if(bool(isupper(board[yknight][xknight][0])) != uppercase)
          {
            return true;
          }
        }
      }
    }
    // check for knights
    xknight = x + -2;
    yknight = y + -1;
    if(xknight >= 0 && xknight <= 7 && yknight >= 0 && yknight <= 7)
    {
      if(board[yknight][xknight] != " ")
      {
        if(board[yknight][xknight] == "H" || board[yknight][xknight] == "h")
        {
          if(bool(isupper(board[yknight][xknight][0])) != uppercase)
          {
            return true;
          }
        }
      }
    }
    // check for knights
    xknight = x + -1;
    yknight = y + -2;
    if(xknight >= 0 && xknight <= 7 && yknight >= 0 && yknight <= 7)
    {
      if(board[yknight][xknight] != " ")
      {
        if(board[yknight][xknight] == "H" || board[yknight][xknight] == "h")
        {
          if(bool(isupper(board[yknight][xknight][0])) != uppercase)
          {
            return true;
          }
        }
      }
    }
    // check for knights
    xknight = x + 1;
    yknight = y + -2;
    if(xknight >= 0 && xknight <= 7 && yknight >= 0 && yknight <= 7)
    {
      if(board[yknight][xknight] != " ")
      {
        if(board[yknight][xknight] == "H" || board[yknight][xknight] == "h")
        {
          if(bool(isupper(board[yknight][xknight][0])) != uppercase)
          {
            return true;
          }
        }
      }
    }

    return false;
  }

  // Given the position of a king this function will determine all the possible moves
  // a king can make and pass the position of that move to check(). If all possible moves
  // (plus its own position) results in a check then check_mate() will return true.
  bool check_mate(const vector< vector<string> > &board, const vector<Piece> &pieces)
  {

    Piece king;
    for(int i = 0; i < pieces.size(); ++ i)
    {
      if(pieces[i].symbol == "K" || pieces[i].symbol == "k")
      {
        king = pieces[i];
        break;
      }
    }

    int x = king.xpos;
    int y = king.ypos;
    bool uppercase = isupper(king.symbol[0]);


    if(x+1 <= 7)
    {

      if(board[y][x+1] == " " || bool(isupper(board[y][x+1][0])) != uppercase)
      {
        if(check(board, king, x+1, y) == false)
        {
          return false;
        }
      }
    }

    if(x-1 >= 7)
    {

      if(board[y][x-1] == " " || bool(isupper(board[y][x-1][0])) != uppercase)
      {
        if(check(board, king, x-1, y) == false)
        {
          return false;
        }
      }
    }

    if(y+1 <= 7)
    {

      if(board[y+1][x] == " " || bool(isupper(board[y+1][x][0])) != uppercase)
      {
        if(check(board, king, x, y+1) == false)
        {
          return false;
        }
      }
    }

    if(y-1 >= 0)
    {

      if(board[y-1][x] == " " || bool(isupper(board[y-1][x][0])) != uppercase)
      {
        if(check(board, king, x, y-1) == false)
        {
          return false;
        }
      }
    }

    if(x+1 <= 7 && y +1 <= 7)
    {

      if(board[y+1][x+1] == " " || bool(isupper(board[y+1][x+1][0])) != uppercase)
      {
        if(check(board, king, x+1, y+1) == false)
        {
          return false;
        }
      }
    }

    if(x-1 >= 0 && y + 1 <=7)
    {

      if(board[y+1][x-1] == " " || bool(isupper(board[y+1][x-1][0])) != uppercase)
      {
        if(check(board, king, x-1, y+1) == false)
        {
          return false;
        }
      }
    }

    if(x-1 >= 0 && y-1 >= 0)
    {

      if(board[y-1][x-1] == " " || bool(isupper(board[y-1][x-1][0])) != uppercase)
      {
        if(check(board, king, x-1, y-1) == false)
        {
          return false;
        }
      }
    }

    if(x+1 <= 7 && y-1 >=0)
    {

      if(board[y-1][x+1] == " " || bool(isupper(board[y-1][x+1][0])) != uppercase)
      {
        if(check(board, king, x+1, y-1) == false)
        {
          return false;
        }
      }
    }
    return true;
  }



// Determines if the position entered by the user is a valid move for the pieces
// they selected.
bool valid_move(Piece piece, int &x, int &y, const vector< vector<string> > &board)
{
  int oldx = piece.xpos;
  int oldy = piece.ypos;

  string type = piece.symbol;

  // Gets user input. If the user does not enter an integer the game will exit.
  cout << "Where would you like to move it?" << endl;
  cin >> x >> y;
  if(cin.fail())
  {
    exit(0);
  }

  if( x >= 8 || y >= 8)
  {
    return false;
  }
  // White Pawn
  if(type == "P")
  {
    if((oldx - x) == 0)
    {
      if(y-oldy == 1 && board[y][oldx] == " ")
      {
        return true;
      }
      if(y-oldy == 2 && oldy == 1)
      {
        if(board[y][oldx] == " " && board[y-1][oldx] == " ")
        {
          return true;
        }
        return false;
      }
    }
    // This checks if the pawn can move diagonally to take a piece. Currently
    // it does not check whose piece it is so it can takes it own.
    if(abs(x - oldx) == 1 && (y-oldy) == 1)
    {
      if(board[y][x] != " " )
      {
        return true;
      }
      return false;
    }
    return false;
  }

  // White Rook
  if (type == "R")
  {
    // moving vertically
    if(y > oldy)
    {

      if(x-oldx != 0)
      {
        return false;
      }

      for(int i = oldy+1; i < y; ++i)
      {

        if(board[i][oldx] != " ")
        {
          return false;
        }
      }
      if(islower(board[y][x][0]) || board[y][x] == " ")
      {
        return true;
      }
      return false;
    }



    if(y < oldy)
    {
      if(x-oldx != 0)
      {
        return false;
      }
      for(int i = oldy -1; i > y; --i)
      {
        if(board[i][oldx] != " ")
        {
          return false;
        }
      }
      if(islower(board[y][x][0]) || board[y][x] == " ")
      {
        return true;
      }
      return false;
    }

    // moving horizontally
    if(x > oldx)
    {
      if(y-oldy != 0)
      {
        return false;
      }
      for( int k = oldx+1; k < x; ++k)
      {
        if(board[k][oldy] != " ")
        {
          return false;
        }
      }
      if(islower(board[y][x][0]) || board[y][x] == " ")
      {
        return true;
      }
      return false;
    }
    if(x < oldx)
    {
      if(y-oldy != 0)
      {
        return false;
      }
      for( int k = oldx-1; k > x; --k)
      {
        if(board[oldy][k] != " ")
        {
          return false;

        }
      }
      if(islower(board[y][x][0]) || board[y][x] == " ")
      {
        return true;
      }
      return false;
    }
  }

  // White Knight
  if(type == "H")
  {
    if(x > 7 || y > 7)
    {
      return false;
    }
    if(isupper(board[y][x][0]))
    {
      return false;
    }
    if(abs(y - oldy) == 2 && abs(x - oldx) == 1)
    {
      return true;
    }

    if(abs(y - oldy) == 1 && abs(x - oldx) == 2)
    {
      return true;
    }
    return false;
  }

  // White Bishop
  if(type == "B")
  {
    int xdiff = x -oldx;
    int ydiff = y - oldy;
  if(y > 7 || x > 7)
  {
    return false;
  }
  if(isupper(board[y][x][0]))
  {
    return false;
  }
  if(abs(xdiff) != abs(ydiff))
  {
    return false;
  }
  if(ydiff > 0)
  {
    if(xdiff > 0)
    {
      for(int i = 1; i < xdiff; ++i)
      {
        if(board[oldy+ i][oldx + i] != " ")
        {
          return false;
        }
      }
      return true;
    }
    else
    {
      for(int i = 1; i < xdiff; ++i)
      {
        if(board[oldy+ i][oldx - 1] != " ")
        {
          return false;
        }
      }
      return true;
    }
  }
  else
  {
    if(xdiff > 0)
    {
      for(int i = 1; i < xdiff; ++i)
      {
        if(board[oldy - i][oldx + i] != " ")
        {
          return false;
        }
      }
      return true;
    }
    else
    {
      for(int i = 1; i < xdiff; ++i)
      {
        if(board[oldy - i][oldx - i] != " ")
        {
          return false;
        }
      }
      return true;
    }
  }
  }

  if(type == "Q")
  {
    int xdiff = x -oldx;
    int ydiff = y - oldy;
    if(y > 7 || x > 7)
    {
      return false;
    }
    if(isupper(board[y][x][0]))
    {
      return false;
    }
if(xdiff == 0 || ydiff == 0)
{
  if(xdiff == 0)
  { // moving down
    if(ydiff > 0)
    {
      for(int i = oldy + 1; i < y; ++i)
      {
        if(board[i][oldx] != " ")
        {
          return false;
        }
      }
      return true;
    } // moving upwards
    else
    {
      for(int k = oldy -1; k > y; --k)
      {
        if(board[k][oldx] != " ")
        {
          return false;
        }
      }
    }
    return true;
  }


  if(ydiff == 0)
  { // moving right
    if(xdiff > 0)
    {
      for(int i = oldx + 1; i < x; ++i)
      {
        if(board[oldy][i] != " ")
        {
          return false;
        }
      }
      return true;
    }
    // moving left
    else
    {
      for(int k = oldx -1; k > x; --k)
      {
        if(board[oldy][k] != " ")
        {
          return false;
        }
      }
      return true;
    }
  }
}

else
{
  if(abs(xdiff) != abs(ydiff))
  {
    return false;
  }
  if(ydiff > 0)
  {

    if(xdiff > 0)
    {
      for(int i = 1; i < xdiff; ++i)
      {
        if(board[oldy+ i][oldx + i] != " ")
        {
          return false;
        }
      }
      return true;
    }
    else
    {
      for(int i = 1; i < xdiff; ++i)
      {
        if(board[oldy+ i][oldx - 1] != " ")
        {
          return false;
        }
      }
      return true;
    }
  }
  else
  {
    if(xdiff > 0)
    {
      for(int i = 1; i < xdiff; ++i)
      {
        if(board[oldy - i][oldx + i] != " ")
        {
          return false;
        }
      }
      return true;
    }
    else
    {
      for(int i = 1; i < xdiff; ++i)
      {
        if(board[oldy - i][oldx - i] != " ")
        {
          return false;
        }
      }
      return true;
    }
  }
  }
}


if(type == "K")
{
  return(!check(board, piece, x ,y ));

}

// Black pawn
if(type == "p")
{
  if(x -oldx == 0)
  {
    if(oldy-y == 1 && board[y][oldx] == " ")
    {
      return true;
    }
    if(oldy-y == 2 && oldy == 6)
    {
      if(board[y][x] == " " && board[y+1][x] == " ")
      {
        return true;
      }
      return false;
    }
    return false;
  }
  if(abs(oldx- x) == 1 && (oldy -y) == 1)
  {
    if(board[y][x] != " ")
    {
      return true;
    }
    return false;
  }
  return false;
}

// Black Rook
  if (type == "r")
  {
    // moving vertically
    if(y > oldy)
    {

      if(x-oldx != 0)
      {
        return false;
      }

      for(int i = oldy+1; i < y; ++i)
      {

        if(board[i][oldx] != " ")
        {
          return false;
        }
      }
      if(isupper(board[y][x][0]) || board[y][x] == " ")
      {
        return true;
      }
      return false;
    }

    if(y < oldy)
    {
      if(x-oldx != 0)
      {
        return false;
      }
      for(int i = oldy -1; i > y; --i)
      {
        if(board[i][oldx] != " ")
        {
          return false;
        }
      }
      if(isupper(board[y][x][0]) || board[y][x] == " ")
      {
        return true;
      }
      return false;
    }

    // moving horizontally
    if(x > oldx)
    {
      if(y-oldy != 0)
      {
        return false;
      }
      for( int k = oldx+1; k < x; ++k)
      {
        if(board[k][oldy] != " ")
        {
          return false;
        }
      }
      if(isupper(board[y][x][0]) || board[y][x] == " ")
      {
        return true;
      }
      return false;
    }
    if(x < oldx)
    {
      if(y-oldy != 0)
      {
        return false;
      }
      for( int k = oldx-1; k > x; --k)
      {
        if(board[oldy][k] != " ")
        {
          return false;

        }
      }
      if(isupper(board[y][x][0]) || board[y][x] == " ")
      {
        return true;
      }
      return false;
    }
  }
  // Black Knight
  if(type == "h")
  {
    if(x > 7 || y > 7)
    {
      return false;
    }
    if(islower(board[y][x][0]))
    {
      return false;
    }
    if(abs(y - oldy) == 2 && abs(x - oldx) == 1)
    {
      return true;
    }

    if(abs(y - oldy) == 1 && abs(x - oldx) == 2)
    {
      return true;
    }
    return false;
  }
  // Black Bishop
  if(type == "b")
  {
    int xdiff = x -oldx;
    int ydiff = y - oldy;
  if(y > 7 || x > 7)
  {
    return false;
  }

  if(islower(board[y][x][0]))
  {
    return false;
  }

  if(abs(xdiff) != abs(ydiff))
  {
    return false;
  }

  if(ydiff > 0)
  {
    if(xdiff > 0)
    {
      for(int i = 1; i < xdiff; ++i)
      {
        if(board[oldy+ i][oldx + i] != " ")
        {
          return false;
        }
      }
      return true;
    }
    else
    {
      for(int i = 1; i < xdiff; ++i)
      {
        if(board[oldy+ i][oldx - 1] != " ")
        {
          return false;
        }
      }
      return true;
    }
  }
  else
  {
    if(xdiff > 0)
    {
      for(int i = 1; i < xdiff; ++i)
      {
        if(board[oldy - i][oldx + i] != " ")
        {

          return false;
        }
      }
      return true;
    }
    else
    {
      for(int i = 1; i < xdiff; ++i)
      {
        if(board[oldy - i][oldx - i] != " ")
        {
          return false;
        }
      }
      return true;
    }
  }
  }

  // Black Queen
  if(type == "q")
  {
    int xdiff = x -oldx;
    int ydiff = y - oldy;
    if(y > 7 || x > 7)
    {
      return false;
    }
    if(islower(board[y][x][0]))
    {
      return false;
    }
if(xdiff == 0 || ydiff == 0)
{
  if(xdiff == 0)
  { // moving down
    if(ydiff > 0)
    {
      for(int i = oldy + 1; i < y; ++ i)
      {
        if(board[i][oldx] != " ")
        {
          return false;
        }
      }
      return true;
    } // moving upwards
    else
    {
      for(int k = oldy -1; k > y; --k)
      {
        if(board[k][oldx] != " ")
        {
          return false;
        }
      }
    }
    return true;
  }


  if(ydiff == 0)
  { // moving right
    if(xdiff > 0)
    {
      for(int i = oldx + 1; i < x; ++i)
      {
        if(board[oldy][i] != " ")
        {
          return false;
        }
      }
      return true;
    }
    // moving left
    else
    {
      for(int k = oldx -1; k > x; --k)
      {
        if(board[oldy][k] != " ")
        {
          return false;
        }
      }
      return true;
    }
  }
}


else
{
  if(abs(xdiff) != abs(ydiff))
  {
    return false;
  }
  if(ydiff > 0)
  {

    if(xdiff > 0)
    {
      for(int i = 1; i < xdiff; ++i)
      {
        if(board[oldy+ i][oldx + i] != " ")
        {
          return false;
        }
      }
      return true;
    }
    else
    {
      for(int i = 1; i < xdiff; ++i)
      {
        if(board[oldy+ i][oldx - 1] != " ")
        {
          return false;
        }
      }
      return true;
    }
  }
  else
  {
    if(xdiff > 0)
    {
      for(int i = 1; i < xdiff; ++i)
      {
        if(board[oldy - i][oldx + i] != " ")
        {
          return false;
        }
      }
      return true;
    }
    else
    {
      for(int i = 1; i < xdiff; ++i)
      {
        if(board[oldy - i][oldx - i] != " ")
        {
          return false;
        }
      }
      return true;
    }
  }
  }
}

  if(type == "k")
  {
    return(!check(board, piece,x, y));
  }
}

// Gets an x and y position from the user and checks if this tile is occupied by one of their pieces.
bool get_valid_piece(const vector < vector<string> > &board, vector <Piece> pieces, int &x , int &y, int &index)
{
  Piece king;
  for(int i = 0; i < pieces.size(); ++i)
  {
    if(pieces[i].symbol == "K" || pieces[i].symbol == "k")
    {
      king = pieces[i];
    }
  }

  // If their king is in check they are forced to move it out of check.
  if(check(board, king, king.xpos, king.ypos))
  {
    cout << "Your king is in check. You must move it. Enter its position" << endl;
    cin >> x >> y;
    if(cin.fail())
    {
      exit(0);
    }
  }
  // If their king is not in check...
  else
  {
    cout << "What piece would you like to move" << endl;
    // If an integer is not entered the game will exit.
    cin >> x >> y;
    if(cin.fail())
    {
      exit(0);
    }
  }
  for(int i = 0; i < pieces.size(); ++i)
  {
    if(pieces[i].xpos == x && pieces[i].ypos == y)
    {
      index = i;
      return true;
    }
  }
  return false;

}


// Gets a valid piece and move from the user and then updates the position of that piece and
// any opposing piece that it may take.
void get_white_move(vector<Piece> &white, vector<Piece> &black, const vector< vector<string> > &board)
{
  int xpos;
  int ypos;
  int newx;
  int newy;
  int index;
  bool move = false;
  bool valid_piece = false;

  // calls on get_valid_piece() until a valid piece is entered.
  // this wile loop could have while(false) since a break statement
  // is exiting the loop but whatever.
  while(!valid_piece)
  {
    valid_piece = get_valid_piece(board, white, xpos, ypos, index);
    if(valid_piece)
    {
      break;
    }
    cout << "That is not a valid piece" << endl;

  }

  // calls on valid_move() until a valid move is entered for the selected piece.
  // once again this while loop could be while(false)
  while(!move)
  {

    move = valid_move(white[index], newx, newy, board);
    if(move)
    {
      break;
    }
    cout << "That is not a valid move" << endl;
  }

  white[index].xpos = newx;
  white[index].ypos = newy;

  // If this tile is occupied by an opposing piece it will be "taken" by erasing
  // it from their vector of pieces.
  for(int i =0; i < black.size(); ++i)
  {
    if(black[i].xpos == newx && black[i].ypos == newy)
    {
    black.erase(black.begin() + i);
    continue;
    }
  }
}

// The same process as get_white_move()
void get_black_move(vector<Piece> &white, vector<Piece> &black, const vector< vector<string> > &board)
{
  int xpos;
  int ypos;
  int newx;
  int newy;
  int index;
  bool valid_piece = false;
  bool move = false;


  while(!valid_piece)
  {

    valid_piece = get_valid_piece(board, black, xpos, ypos, index);
    if(valid_piece)
    {
      break;
    }
    cout << "That is not a valid piece" << endl;
  }


  while(!move)
  {
    move = valid_move(black[index], newx, newy, board);
    if(move)
    {
      break;
    }
    cout << "That is not a valid move" << endl;
  }

  black[index].xpos = newx;
  black[index].ypos = newy;

  for(int i =0; i < black.size(); ++i)
  {
    if(white[i].xpos == newx && white[i].ypos == newy)
    {
    white.erase(white.begin() + i);
    continue;
    }
  }


}

// Takes both vector of pieces and will update the board
vector< vector<string> > update_board(vector<Piece> white, vector<Piece> black)
{
  vector <string> blank(8, " ");
  vector <vector <string> > board(8, blank);

  for(int i = 0; i < white.size(); ++i)
  {
    board[white[i].ypos][white[i].xpos] = white[i].symbol;
  }

  for(int k = 0; k < black.size(); ++k)
  {
    board[black[k].ypos][black[k].xpos] = black[k].symbol;
  }
  return board;
}

int main()
{
  bool checkmate = false;
  vector <Piece> white;
  vector <Piece> black;
  string winner = "";
  vector <string> blank(8, " ");
  vector <vector <string> > board(8, blank);
load_white(white);
load_black(black);
board = update_board(white, black);
cout << "Welcome to my chess game. Moves will be made by entering ";
cout << "the x position of the piece you want to move followed by the y position ";
cout << "with a space inbetween. White is represented by uppercase letters and will ";
cout << "go first. The game may be exited by typing any non numerical character. Enjoy. " << endl;

while(!checkmate)
{
  draw_board(board);
  cout << "It's whites turn" << endl;
  get_white_move(white, black, board);
  board = update_board(white, black);
  draw_board(board);
  checkmate = check_mate(board, black);
  if(checkmate == true)
  {
    cout << "Checkmate. White wins!!";
    return 0;
  }

  cout << "It's black's turn" << endl;
  get_black_move(white, black, board);
  board = update_board(white, black);
  draw_board(board);
  checkmate = check_mate(board, white);
  if(checkmate == true)
  {
    cout << "Checkmate. Black wins!!" << endl;
    return 0;
  }
}
return 0;
}
