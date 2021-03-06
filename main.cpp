/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Jiaming Gong
// St.# : 301358090
// Email: jga104@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

#include "Board.h"

#include "Player.h"

using namespace std;

int game_turns;
int input_row = 0;
char input_coloum;
int humanpass = 0;
int botpass = 0;

//CLASS BOARD////CLASS BOARD////CLASS BOARD////CLASS BOARD////CLASS BOARD////CLASS BOARD////CLASS BOARD////CLASS BOARD////CLASS BOARD////CLASS BOARD////CLASS BOARD////CLASS BOARD////CLASS BOARD////CLASS BOARD//
class Board: public Class_Board {
  private:

    public: int col;
  int row;
  // col and row are 8 * 8
  //   //2 - black
  //   //1 - white
  //   //0 - empty
  int ** board;
  int pieces_in_board;

  Board() {
    col = 8;
    row = 8;
    board = new int * [8];
    board[0] = new int[64];
    for (int r = 1; r < row; r++) {
      board[r] = board[0] + col * r;
    }

    pieces_in_board = 4;

    //set the initial 4 values
    board[row / 2][col / 2] = 1;
    board[row / 2 - 1][col / 2] = 2;
    board[row / 2][col / 2 - 1] = 2;
    board[row / 2 - 1][col / 2 - 1] = 1;
  }

  int ** getBoard() {
    return board;
  }

  int getPiecesInBoard() {
    int total = 0;
    for (int c = 0; c < col; c++) {
      for (int r = 0; r < row; r++) {
        if (board[c][r] == 1 || board[c][r] == 2) {
          total++;
        }
      }
    }
    return total;
  }

  int get_X_O(int who) {
    int total = 0;
    for (int c = 0; c < col; c++) {
      for (int r = 0; r < row; r++) {
        if (board[c][r] == who) {
          total++;
        }
      }
    }
    return total;
  }

  void setChess(int x, char y, int who) {
    int equal_y;
    equal_y = (int) y - 65;
    board[x][equal_y] = who;

  }

  void printBoard() {
    //colors
    const string red = "\033[0;31m";
    const string green = "\033[1;32m";
    const string yellow = "\033[1;33m";
    const string cyan = "\033[0;36m";
    const string mag = "\033[0;35m";
    const string rs = "\033[0m";

    //print the first row
    cout << "   ";
    for (int c = 0; c < col; c++) {
      cout << red << setw(2) << (char)(65 + c) << rs;
    }
    cout << endl;

    for (int r = 0; r < row; r++) {
      cout << red << setw(3) << r << rs;

      for (int c = 0; c < col; c++) {
        if (board[r][c] == 1) {
          cout << green << setw(2) << 'X' << rs;
        } //if
        else if (board[r][c] == 2) {
          cout << cyan << setw(2) << 'O' << rs;
        } //esif
        else if (board[r][c] == 0) {
          cout << setw(2) << "*";
        } else if (board[r][c] == 3) {
          cout << yellow << setw(2) << "$" << rs;
        } else {
          cout << setw(2) << board[r][c];
        } //es

      }
      cout << red << setw(3) << r << rs;
      cout << endl;
    }
    cout << "   ";
    for (int c = 0; c < col; c++) {
      cout << red << setw(2) << (char)(65 + c) << rs;
    }
    cout << endl;
    cout << " ----------------------" << endl;

  } //printBoard

  void ClearBoard() {
    for (int c = 0; c < col; c++) {
      for (int r = 0; r < row; r++) {
        // for (int c = 0; c < col; c++) {
          if (board[r][c] == 3) {
            setChess(r, (char) c + 65, 0);
          }
        // }
      }
    }
  } //ClearBoard

  bool check_Up(int x, char y, int type) {
    int inverse_type = 0;
    if (type == 2) {
      inverse_type = 1;
    } else {
      inverse_type = 2;
    }
    int equal_y;
    equal_y = (int) y - 65;
    //check 1 which is X; 2 = O
    //check the same column above
    if (x - 1 >= 0 && board[x - 1][equal_y] == inverse_type) {
      bool found_same_type = false;
      for (int c = x - 1; c >= 0; --c) {
        if (board[c][equal_y] == type) {
          found_same_type = true;
          break;
        }
        else if (board[c][equal_y] == 3 || board[c][equal_y] == 0){
          return false;
        }
      }
      if (found_same_type) {
        return true;
      }
    }
    return false;
  }

  bool check_Up_Right(int x, char y, int type) {
    int inverse_type = 0;
    if (type == 2) {
      inverse_type = 1;
    } else {
      inverse_type = 2;
    }

    int equal_y;
    equal_y = (int) y - 65;
    //check 1 which is X; 2 = O
    //check the same column above
    int r = x - 1;
    int c = equal_y + 1;
    if (r >= 0 && c <= 7 && board[r][c] == inverse_type) {
      bool found_same_type = false;
      while (r >= 0 && c <= 7) {
        if (board[r][c] == type) {
          found_same_type = true;
          break;
        }
        else if (board[r][c] == 3 || board[r][c] == 0){
          return false;
        }
        r--;
        c++;

      }

      if (found_same_type) {
        return true;
      }
    }
    return false;
  }

  bool check_Right(int x, char y, int type) {
    int inverse_type = 0;
    if (type == 2) {
      inverse_type = 1;
    } else {
      inverse_type = 2;
    }
    int equal_y;
    equal_y = (int) y - 65;
    //check 1 which is X , 2 is O
    //check the same row on the right

    if ((equal_y + 1) <= 7 && board[x][equal_y + 1] == inverse_type) {
      bool found_same_type = false;
      for (int r = (equal_y + 1); r <= 7; ++r) {
        if (board[x][r] == type) {
          found_same_type = true;
          break;
        }
        else if (board[x][r] == 3 || board[x][r] == 0){
          return false;
        }
      }
      if (found_same_type) {
        return true;
      }
    }
    return false;
  }

  bool check_Down_Right(int x, char y, int type) {
    int inverse_type = 0;
    if (type == 2) {
      inverse_type = 1;
    } else {
      inverse_type = 2;
    }

    int equal_y;
    equal_y = (int) y - 65;
    //check 1 which is X; 2 = O
    //check the same column above
    int r = x + 1;
    int c = equal_y + 1;
    if (r <= 7 && c <= 7 && board[r][c] == inverse_type) {
      bool found_same_type = false;
      while (r <= 7 && c <= 7) {
        if (board[r][c] == type) {
          found_same_type = true;
          break;
        }
        else if (board[r][c] == 3 || board[r][c] == 0){
          return false;
        }
        r++;
        c++;

      }

      if (found_same_type) {
        return true;
      }
    }
    return false;
  }

  bool check_Down(int x, char y, int type) {
    int inverse_type = 0;
    if (type == 2) {
      inverse_type = 1;
    } else {
      inverse_type = 2;
    }
    int equal_y;
    equal_y = (int) y - 65;
    //check 1 which is X; 2 = O
    //check the same column above
    if (x + 1 <= 7 && board[x + 1][equal_y] == inverse_type) {
      bool found_same_type = false;
      for (int c = x + 1; c <= 7; ++c) {
        if (board[c][equal_y] == type) {
          found_same_type = true;
          break;
        }
        else if (board[c][equal_y] == 3 || board[c][equal_y] == 0){
          return false;
        }
      }
      if (found_same_type) {
        return true;
      }
    }
    return false;
  }

  bool check_Down_Left(int x, char y, int type) {
    int inverse_type = 0;
    if (type == 2) {
      inverse_type = 1;
    } else {
      inverse_type = 2;
    }

    int equal_y;
    equal_y = (int) y - 65;
    //check 1 which is X; 2 = O
    //check the same column above
    int r = x + 1;
    int c = equal_y - 1;
    if (r <= 7 && c >= 0 && board[r][c] == inverse_type) {
      bool found_same_type = false;
      while (r <= 7 && c >= 0) {
        if (board[r][c] == type) {
          found_same_type = true;
          break;
        }
        else if (board[r][c] == 3 || board[r][c] == 0){
          return false;
        }
        r++;
        c--;

      }

      if (found_same_type) {
        return true;
      }
    }
    return false;
  }

  bool check_Left(int x, char y, int type) {
    int inverse_type = 0;
    if (type == 2) {
      inverse_type = 1;
    } else {
      inverse_type = 2;
    }
    int equal_y;
    equal_y = (int) y - 65;
    //check 1 which is X , 2 is O
    //check the same row on the right
    if ((equal_y - 1) >= 0 && board[x][equal_y - 1] == inverse_type) {
      bool found_same_type = false;
      for (int r = (equal_y - 1); r >= 0; --r) {
        if (board[x][r] == type) {
          found_same_type = true;
          break;
        }
        else if (board[x][r] == 3 || board[x][r] == 0){
          return false;
        }
      }
      if (found_same_type) {
        return true;
      }
    }
    return false;
  }

  bool check_Up_Left(int x, char y, int type) {
    int inverse_type;
    int equal_y;
    equal_y = (int) y - 65;
    if (type == 2) {
      inverse_type = 1;
    } else {
      inverse_type = 2;
    }

    //check 1 which is X; 2 = O
    //check the same column above
    int r = x - 1;
    int c = equal_y - 1;
    if (r >= 0 && c >= 0 && board[r][c] == inverse_type) {
      bool found_same_type = false;
      while (r >= 0 && c >= 0) {
        if (board[r][c] == type) {
          found_same_type = true;
          break;
        }
        else if (board[r][c] == 3 || board[r][c] == 0){
          return false;
        }
        r--;
        c--;

      }

      if (found_same_type) {
        return true;
      }
    }
    return false;
  }

  void setAllChess(int r, char c, int type) {
    int inverse_type;
    if (type == 2) {
      inverse_type = 1;
    } else {
      inverse_type = 2;
    }
    int equal_y;
    equal_y = (int) c - 65;
    bool changed = false;
    // up

    if (check_Up(r, c, type)) {
      for (int a = r; a >= 0; a--) {
        if (a >= 0 && board[a][equal_y] == inverse_type) {
          setChess(a, c, type);
          changed = true;
        } else if (a >= 0 && board[a][equal_y] == type) {
          break;
        }
      }

    }  if (check_Up_Right(r, c, type)) {
      int b = r - 1;
      int cc = equal_y + 1;
      while (b >= 0 && cc <= 7) {
        if (b >= 0 && cc <= 7 && board[b][cc] == inverse_type) {
          setChess(b, (char) cc + 65, type);
          changed = true;

        } else if (b >= 0 && cc <= 7 && board[b][cc] == type) {
          break;
        }
        b--;
        cc++;
      }
    }  if (check_Right(r, c, type)) {
      for (int d = equal_y; d <= 7; d++) {
        if (d <= 7 && board[r][d] == inverse_type) {
          setChess(r, (char) d + 65, type);
          changed = true;

        } else if (d <= 7 && board[r][d] == type) {
          break;
        }
      }
    }  if (check_Down_Right(r, c, type)) {
      int e = r + 1;
      int f = equal_y + 1;
      while (e <= 7 && f <= 7) {
        if (e <= 7 && f <= 7 && board[e][f] == inverse_type) {
          setChess(e, (char) f + 65, type);
          changed = true;

        } else if (e >= 0 && f <= 7 && board[e][f] == type) {
          break;
        }
        e++;
        f++;
      }
    }  
    if (check_Down(r, c, type)) {
      for (int g = r; g <= 7; g++) {

        if (g <= 7 && board[g][equal_y] == inverse_type) {
          setChess(g, c, type);
          changed = true;

        } else if (g <= 7 && board[g][equal_y] == type) {
          break;
        }
      }
    }  if (check_Down_Left(r, c, type)) {
      int h = r + 1;
      int i = equal_y - 1;

      while (h <= 7 && i >= 0) {
        if (h <= 7 && i >= 0 && board[h][i] == inverse_type) {
          setChess(h, (char) i + 65, type);
          changed = true;

        } else if (h <= 7 && i >= 0 && board[h][i] == type) {
          break;
        }
        h++;
        i--;
      }
    }  if (check_Left(r, c, type)) {

      for (int j = equal_y; j >= 0; j--) {
        if (j >= 0 && board[r][j] == inverse_type) {
          setChess(r, (char) j + 65, type);
          changed = true;

        } else if (j >= 0 && board[r][j] == type) {
          break;
        }
      }
    }  if (check_Up_Left(r, c, type)) {
      int k = r - 1;
      int l = equal_y - 1;

      while (k >= 0 && l >= 0) {
        if (k >= 0 && l >= 0 && board[k][l] == inverse_type) {
          setChess(k, (char) l + 65, type);
          changed = true;

        } else if (k >= 0 && l >= 0 && board[k][l] == type) {
          break;
        }
        k--;
        l--;
      }
    }
    if (changed){
      setChess(r, c, type);
    }

  } //set ALL CHESS





    void CheckLen(int r, char c, int type) {
    int inverse_type;
    if (type == 2) {
      inverse_type = 1;
    } else {
      inverse_type = 2;
    }
    int equal_y;
    equal_y = (int) c - 65;
    bool changed = false;
    // up

    if (check_Up(r, c, type)) {
      for (int a = r; a >= 0; a--) {
        if (a >= 0 && board[a][equal_y] == inverse_type) {
          setChess(a, c, type);
          changed = true;
        } else if (a >= 0 && board[a][equal_y] == type) {
          break;
        }
      }
    } 
    if (check_Up_Right(r, c, type)) {
      int b = r - 1;
      int cc = equal_y + 1;
      while (b >= 0 && cc <= 7) {
        if (b >= 0 && cc <= 7 && board[b][cc] == inverse_type) {
          setChess(b, (char) cc + 65, type);
          changed = true;
        } else if (b >= 0 && cc <= 7 && board[b][cc] == type) {
          break;
        }
        b--;
        cc++;
      }
     
    } 
    if (check_Right(r, c, type)) {
      for (int d = equal_y; d <= 7; d++) {
        if (d <= 7 && board[r][d] == inverse_type) {
          setChess(r, (char) d + 65, type);
          changed = true;
        } else if (d <= 7 && board[r][d] == type) {
          break;
        }
      }
     
    } 
    if (check_Down_Right(r, c, type)) {
      int e = r + 1;
      int f = equal_y + 1;
      while (e <= 7 && f <= 7) {
        if (e <= 7 && f <= 7 && board[e][f] == inverse_type) {
          setChess(e, (char) f + 65, type);
          changed = true;
        } else if (e >= 0 && f <= 7 && board[e][f] == type) {
          break;
        }
        e++;
        f++;
      }
      
    } 
    if (check_Down(r, c, type)) {
      for (int g = r; g <= 7; g++) {
        if (g <= 7 && board[g][equal_y] == inverse_type) {
          setChess(g, c, type);
          changed = true;
        } else if (g <= 7 && board[g][equal_y] == type) {
          break;
        }
      }
      
    } 
    if (check_Down_Left(r, c, type)) {
      int h = r + 1;
      int i = equal_y - 1;

      while (h <= 7 && i >= 0) {
        if (h <= 7 && i >= 0 && board[h][i] == inverse_type) {
          setChess(h, (char) i + 65, type);
          changed = true;
        } else if (h <= 7 && i >= 0 && board[h][i] == type) {
          break;
        }
        h++;
        i--;
      }
   
    } 
    if (check_Left(r, c, type)) {

      for (int j = equal_y; j >= 0; j--) {
        if (j >= 0 && board[r][j] == inverse_type) {
          setChess(r, (char) j + 65, type);
          changed = true;
        } else if (j >= 0 && board[r][j] == type) {
          break;
        }
      }
      
    } 
    if (check_Up_Left(r, c, type)) {
      int k = r - 1;
      int l = equal_y - 1;

      while (k >= 0 && l >= 0) {
        if (k >= 0 && l >= 0 && board[k][l] == inverse_type) {
          setChess(k, (char) l + 65, type);
          changed = true;
        } else if (k >= 0 && l >= 0 && board[k][l] == type) {
          break;
        }
        k--;
        l--;
      }
    
    }

    if(changed){
      setChess(r,c,type);
    }

  } //set ALL CHESS






  

  ~Board() {
    delete[] board[0];
    delete[] board;
    board = NULL;
    pieces_in_board = 0;
    row = 0;
    col = 0;
  } //destructor

};

//CLASS BOARD//CLASS BOARD////CLASS BOARD////CLASS BOARD////CLASS BOARD////CLASS BOARD////CLASS BOARD////CLASS BOARD////CLASS BOARD//

//CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER//
class Human_Player: public Player {
  private: int points;

  public: Human_Player() {
    points = 0;
  }
  void setPoints(int po) {
    points = po;
  }
  int getPoints() {
    return points;
  }
  void showPoints() {
    const string yellow = "\033[1;33m";
    const string rs = "\033[0m";
    cout << yellow << setw(3) << "your point: " << getPoints() << rs << "  ";
  }

  ~Human_Player() {
    points = 0;
  }
};
//CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER////CLASS HUM_PLAYER//

//CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER//

class Bot_Player: public Player {
  private: int points;

  public: Bot_Player() {
    points = 0;
  }
  void setPoints(int po) {
    points = po;
  }
  int getPoints() {
    return points;
  }
  void showPoints() {
    const string yellow = "\033[1;33m";
    const string rs = "\033[0m";
    cout << yellow << setw(3) << "Bot's point: " << getPoints() << rs << "\n\n";
  }

  ~Bot_Player() {
    points = 0;
  }
};

//CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER////CLASS BOT_PLAYER//

void welcome() {
  const string yellow = "\033[1;33m";
  const string rs = "\033[0m";
  cout << yellow <<
    "Welcome to my Reversi game: \nYou are a human player, the current board are as below:\n" <<
    "You have to enter the row number AND coloum letter.\n" <<
    "Enter the row number first and the coloum letter\n" <<
    "For example: First, Enter '1'. Second, Enter 'A'\n\n" <<
    rs;
  return;
}

bool human_putchess(Board & dude) {

  //   //find the avaliable spots
  //   //find the min_row; max_row, min_col, and max_col
  int min_row = 8, max_row = 0, min_col = 8, max_col = 0;
  for (int r = 0; r < dude.row; r++) {
    for (int c = 0; c < dude.col; c++) {
      if (dude.board[r][c] != 0) { //exist
        if (r < min_row) min_row = r;
        if (r > max_row) max_row = r;
        if (c < min_col) min_col = c;
        if (c > max_col) max_col = c;
      }
    }
  }

  if (min_row > 0) min_row--;
  if (max_row < 8) max_row++;
  if (min_col > 0) min_col--;
  if (max_col < 8) max_col++;
  bool available = false;
  for (int r = min_row; r <= max_row; r++) {
    for (int c = min_col; c <= max_col; c++) {
      if(dude.board[r][c] != 1 && dude.board[r][c] != 2){
        if (dude.check_Up(r, (char)(c + 65), 2)) {
          dude.setChess(r, (char)(c + 65), 3);
          available = true;
        }
        if (dude.check_Up_Right(r, (char)(c + 65), 2)) {
          dude.setChess(r, (char)(c + 65), 3);
          available = true;
        }
        if (dude.check_Right(r, (char)(c + 65), 2)) {
          dude.setChess(r, (char)(c + 65), 3);
          available = true;
        }
        if (dude.check_Down_Right(r, (char)(c + 65), 2)) {
          dude.setChess(r, (char)(c + 65), 3);
          available = true;
        }
        if (dude.check_Down(r, (char)(c + 65), 2)) {
          dude.setChess(r, (char)(c + 65), 3);
          available = true;
        }
        if (dude.check_Down_Left(r, (char)(c + 65), 2)) {
          dude.setChess(r, (char)(c + 65), 3);
          available = true;
        }
        if (dude.check_Left(r, (char)(c + 65), 2)) {
          dude.setChess(r, (char)(c + 65), 3);
          available = true;
        }
        if (dude.check_Up_Left(r, (char)(c + 65), 2)) {
          dude.setChess(r, (char)(c + 65), 3);
          available = true;
        }
      } //end if
    }
  } //end for
  dude.printBoard();
  dude.ClearBoard();
  if (available) {
    cout << "Enter the location u want to put a piece. \nEnter the row first: ";
    cin >> input_row;

    while (input_row < 0 || input_row > 7) {
      cout << "Please enter a valid number from one to nine: ";
      cin >> input_row;
    }
    cout << "Enter the coloum :";
    cin >> input_coloum;
    while ((int)(input_coloum) < 65 || (int)(input_coloum) > 72) {
      cout << "Please enter a valid letter from A to H: ";
      cin >> input_coloum;
    }
    cout << endl;
    dude.setAllChess(input_row, input_coloum, 2);
    dude.printBoard();
    return true;
  } else {
    cout << "There is no available pieces for you to put, so u passed this term.\n";
    humanpass = 1;
    return false;
  }

} //////////////////human

bool bot_putchess(Board & dude) {

  //   //find the avaliable spots
  //   //find the min_row; max_row, min_col, and max_col
  int min_row = 8, max_row = 0, min_col = 8, max_col = 0;
  for (int r = 0; r < dude.row; r++) {
    for (int c = 0; c < dude.col; c++) {
      if (dude.board[r][c] != 0) { //exist
        if (r < min_row) min_row = r;
        if (r > max_row) max_row = r;
        if (c < min_col) min_col = c;
        if (c > max_col) max_col = c;
      }
    }
  }

  if (min_row > 0) min_row--;
  if (max_row < 8) max_row++;
  if (min_col > 0) min_col--;
  if (max_col < 8) max_col++;
  int r, c;
  bool available = false;
  for ( r= min_row; r <= max_row; r++) {
    for (c = min_col; c <= max_col; c++) {
      if(dude.board[r][c] != 1 && dude.board[r][c] != 2){
        if (dude.check_Up(r, (char)(c + 65), 1)) {

          available = true;
          break;
        }
        if (dude.check_Up_Right(r, (char)(c + 65), 1)) {

          available = true;
          break;
        }
        if (dude.check_Right(r, (char)(c + 65), 1)) {

          available = true;
          break;
        }
        if (dude.check_Down_Right(r, (char)(c + 65), 1)) {

          available = true;
          break;
        }
        if (dude.check_Down(r, (char)(c + 65), 1)) {

          available = true;
          break;
        }
        if (dude.check_Down_Left(r, (char)(c + 65), 1)) {

          available = true;
          break;
        }
        if (dude.check_Left(r, (char)(c + 65), 1)) {

          available = true;
          break;
        }
        if (dude.check_Up_Left(r, (char)(c + 65), 1)) {
          available = true;
          break;
        }
      }
    } //end for
    if (c != max_col+1){
        break;
      }
  } //end for
  if (available) {
    cout << "iM BOT\n";
    dude.CheckLen(r, (char)c+65, 1);
    dude.printBoard();
    return true;
  } else {
    cout << "Ima pass this tern :)\n";
    botpass = 1;
    return false;
  }
} /////bot player

int main() {

  //game play//////////////////////////////////
  // int r,c;
  // r = c = 0;
  //bool avaliable=false;
  int hum_point, bot_point;
  // int input_row = 0;
  // char input_coloum;

  hum_point = bot_point = 0;

  Board dude {};

  Human_Player mate {};
  Bot_Player bro {};

  welcome();


  game_turns = 0;
  while (game_turns < 64) {


    //points set;
    hum_point = dude.get_X_O(2);
    bot_point = dude.get_X_O(1);
    mate.setPoints(hum_point);
    bro.setPoints(bot_point);

    //points set;

    human_putchess(dude);

    //points set;
    hum_point = dude.get_X_O(2);
    bot_point = dude.get_X_O(1);
    mate.setPoints(hum_point);
    bro.setPoints(bot_point);
    mate.showPoints();
    bro.showPoints();
    //points set;

    // cout << "The turn is: " << game_turns << endl;

    bot_putchess(dude);

    //points set;
    hum_point = dude.get_X_O(2);
    bot_point = dude.get_X_O(1);
    mate.setPoints(hum_point);
    bro.setPoints(bot_point);
    mate.showPoints();
    bro.showPoints();
    //points set;

    if (humanpass == 1 && botpass == 1) {
      break;
    }
    game_turns++;

  }
  hum_point = dude.get_X_O(2);
  bot_point = dude.get_X_O(1);

  if(hum_point > bot_point){
    cout << "YOU WIN!!!";
  }else if(hum_point < bot_point){
    cout << "YOU LOST!!!";
  }else if(hum_point == bot_point){
    cout << "TIEEEEE";
  }

  
}
