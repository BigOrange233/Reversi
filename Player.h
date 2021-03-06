#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

class Player {

  public:

    //set points
    virtual void setPoints(int po) = 0; 

    //get points
    virtual int getPoints() = 0;

    //show points
    virtual void showPoints() = 0;

    //vitrual des
    virtual ~Player(){};


};// class player



