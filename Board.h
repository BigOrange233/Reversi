#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;




class Class_Board  {

public:
  // get the board
  virtual int ** getBoard() = 0;

  //print the board
  virtual void printBoard() = 0;

  //clear the $
  virtual void ClearBoard() = 0;

  //Calculate the pieces in the board
  virtual int getPiecesInBoard() = 0;

  //Calculate the pieces for each whether X or O
  virtual int get_X_O(int who) = 0;

///////////////////////////////set chess
  //set chess
  virtual void setChess(int x,char y,int who) = 0;
///////////////////////////////set chess

  //check line (Up)
  virtual bool check_Up(int x,char y, int type) = 0;

  // //check line (up Right)
  virtual bool check_Up_Right(int x,char y, int type) = 0;

  // //check line (Right)
  virtual bool check_Right(int x,char y,int type) = 0;

  // //check line (Down Right)
  virtual bool check_Down_Right(int x,char y,int type) = 0;

  // //check line (Down)
  virtual bool check_Down(int x,char y,int type) = 0;

  // //check line (Down Left)
  virtual bool check_Down_Left(int x,char y,int type) = 0;

  // //check line (Left)
  virtual bool check_Left(int x,char y,int type) = 0;

  // //check line (Up Left)
  virtual bool check_Up_Left(int x,char y,int type) = 0;

  //set all chess
  virtual void setAllChess(int r, char c,int type)=0;

  //check length 
  virtual void CheckLen(int r, char c, int type) = 0;


  // virtual destructor
  virtual ~Class_Board(){};
 



}; // class Board
