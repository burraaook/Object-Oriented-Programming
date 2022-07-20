/*
** hw3_lib.h:
**
** The header file is created for declaring library functions.
**
** Burak Kocausta	1901042605
*/


#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

/*=======================================================================================================*/
/* 
* wall enumerator is used for filling the boards to achieve rectangular shape. wall is added because, 
all boards can be printed with one function easily with that enumerator.
*/
enum class pegState {empty,peg,wall};
/*=======================================================================================================*/

enum class direction {up,down,left,right};
/*=======================================================================================================*/

/*
* Class lets the programmer to create a user interacted Peg Solitaire game.
* All necessary member functions and data is encapsulated inside this class.
* All necessary Error checkings are made.
* Class can be constructed in 4 ways all of them explained in constructor definiton below.
*/
class PegSolitaire{

public:

  class Cell{   // Inner class which holds position and peg state for each cell.
  /* 
  * There aren't any stream input outputs in this class.
  * No need for error checking in Cell class. Because, none of the arguments in setters and constructors causes to runtime error.                             
  * Game might be automatically terminated afterwards if programmer enters unlogical values inside this class.
  */
 
  public:

    /* Constructors */
    Cell(pegState pegValue ,char columnValue, int rowValue) : pstate(pegValue), colPos(columnValue), rowPos(rowValue) {}    
    Cell(pegState pegValue, char columnValue) :  pstate(pegValue), colPos(columnValue) {}
    Cell(pegState pegValue) : pstate(pegValue) {}
    Cell() : pstate(pegState::peg), colPos('-'), rowPos(1) {}

    void setCell(char columnValue, int rowValue, pegState pegValue)  /* Inlined Mutator functions. */
                                                     {colPos = columnValue; rowPos = rowValue; pstate = pegValue;}

    void setPosition(char columnValue, int rowValue) {colPos = columnValue; rowPos = rowValue;}
                                                     
    void setState(pegState pegValue)                 {pstate = pegValue;}
    
    int getRow() const {return rowPos;}                             /* Accessor function. */  
    char getColumn() const {return colPos;}                                                   
    pegState getState() const {return pstate;}
  
  private:
    pegState pstate;
    char colPos;
    int rowPos;
  };

  // Accepts integers only between 1-6(both included). 
  PegSolitaire(int BoardTypeVal);

  // Creates a square board game. It only accepts integer bigger or equal than 5 and boundaries must be equal. 
  PegSolitaire(int colBoundVal, int rowBoundVal);

  // It accepts board and creates game according to the given vector. If board is not valid, program will be terminated.
  // newBoard vector's all inner vectors have to be same sized.               
  PegSolitaire(vector<vector<Cell>> newBoard);

  // Default constructor creates a default game.
  PegSolitaire();

  void setBoardType(int newType) { boardType = newType; }             // Mutators
  void setEndState(bool stateVar) {EndState = stateVar; }             
  void setBoard(vector<vector<Cell>> newBoard);
  
  int getBoardType() const      {return boardType;}                   // Accessors. All of them are inlined.
  int getNumOfPeg() const       {return numOfPeg;}
  int getNumOfEmptyCell() const {return numOfEmptyCell;}
  int getNumOfPegOut() const    {return numOfPegOut;}
  bool getEndState() const      {return EndState;}
  vector<vector<Cell>> getBoardVector() const{return board;}

  // Returns total number of pegs in all games.
  static int getTotalNumber();                                        

  // Prints the board vector properly.
  void displayBoard() const;

  // Displays the boards and takes user input. Modifies all the data inside class according to the input.
  bool boardTypeInput();

  // loads, and saves the board to files. Checks the input validity.
  bool loadFile(const string& userInput);
  bool saveFile(const string& userInput) const;

  // Makes one random move.
  bool play();

  // Accepts commands like A3-4, B2-U and performs the command. Checks the command's validity.
  bool play(const string& command);

  void playGame();        // It asks the user to enter the board type, and plays the game till the end.
  void playCurrentGame(); // It plays the game till the end on current board.

  // Compares this game's total peg number with inputted game's peg number and returns false if other game has more pegs. 
  bool compareGames(const PegSolitaire& otherGame) const;

  // These three inline function manipulates the static data.
  void subtractPegFromTotal() const { totalNumberOfPegs -= numOfPeg;}
  void addPegToTotal()  const       { totalNumberOfPegs += numOfPeg; }
  void decrementTotal() const       { --totalNumberOfPegs; } 

private:
  vector<vector<Cell>> board;
  size_t colBound;
  size_t rowBound;
  int boardType;
  int numOfPeg;
  int numOfEmptyCell;
  int numOfPegOut;
  static int totalNumberOfPegs;
  bool EndState;

  bool isEnd();   // Checks if there any move can be made.

  void createEuropeanBoard();
  void createWiegleBoard();
  void createAsymmetricalBoard();
  void createEnglishBoard();
  void createDiamondBoard();
  void createTriangularBoard();

  int countNumOfPeg();
  int countNumOfEmptyCell();

  // Function manipulates the Cell class type.
  // It modifies the position variables properly in board.
  void fillObjectPosition();

  bool makeMove(const int& x,const int& y,const direction& dir);

  // Helper functions of makeMove.       
  bool checkLeft(const int& col,const int& row) const;
  bool checkRight(const int& col, const int& row) const;
  bool checkDown(const int& col,const int& row) const;
  bool checkUp(const int& col,const int& row) const;
  bool checkTopLeft(const int& col,const int& row) const;
  bool checkTopRight(const int& col,const int& row) const;
  bool checkBottomLeft(const int& col,const int& row) const;
  bool checkBottomRight(const int& col,const int& row) const;
  void putPegHorizontal(const int& col,const int& row,const direction& dir);
  void putPegDiagonalUp(const int& col, const int& row, const direction& dir);
  void putPegDiagonalDown(const int& col, const int& row, const direction& dir);

  // Helper functions for string operations.
  bool decryptString(string userMove, int& col, int& row, direction& dir) const;
  bool readIntFromLine(string line, string name, int& givenType) const;
  bool convertAssignStr(string numStr, int& givenType) const;
  void correctCR(string& buffer) const;

  // Helper function which used in loadfile().
  bool readBoardFromFile(vector<vector<Cell>>& temp_board, ifstream& inFile, const size_t& tempCowBound, const size_t& tempRowBound) const;
};