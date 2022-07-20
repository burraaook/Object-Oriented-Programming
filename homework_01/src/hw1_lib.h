/*
** hw1_lib.h:
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

using namespace std;

/*=======================================================================================================*/
/* 
*	PegState enum class used to indicate peg's current state. 
*	wall enumerator is used for filling the boards to achieve rectangular shape. wall is added because, 
  all boards can be printed with one function easily with that enumerator.
*/
enum class pegState {empty,peg,wall};
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
*	Directions for user command.
*/
enum class direction {up,down,left,right};
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
*	Function is a main function that performs user interaction and calls necessary helper functions.
* 	vector and string library is necessary for this function.
*/
void playPegSolitaire();
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
*	All of these 6 function creates 2d vectors for representing the boards, whose name is given in the function name, and returns
  that 2d vector.
*/
vector<vector<pegState>> createEuropeanBoard();
vector<vector<pegState>> createWiegleBoard();
vector<vector<pegState>> createAsymmetricalBoard();
vector<vector<pegState>> createEnglishBoard();
vector<vector<pegState>> createDiamondBoard();
vector<vector<pegState>> createTriangularBoard();
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
*	Function checks if there are any possible movement on the board. If it is, it returns true, otherwise false.
*	Function takes 2 parameters, one of that is vector and this parameter is used as read only. Other parameter indicates which board 
 is checked. It can be (1,2,3,4,5,6).
*/
bool canMove(const vector<vector<pegState>>& board, short int op);
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
*	These functions are used for checking is it possible to move spesific directions and sometimes spesific boards.
*	Boolean value will be returned movement is valid it returns true, otherwise false.
*	board is a 2d vector which is used as read only. col is column. colBound and rowBound indicates boundaries of that 2d vector.
*	Boundaries doesn't needed to be added, but they are preffered because these functions are became simple with these parameters. 	
*/

/*
*	checkLeft and checkRight functions needs board type because in triangular board, A little bit different operation
  is needed. That op indicates which operation will be checked. It must between 1-6. 
*/
bool checkLeft(const vector<vector<pegState>>& board, int col, int row, short int op);
bool checkRight(const vector<vector<pegState>>& board, int col, int row, int colBound, short int op);

/*
*	These up and down functions only used for checking first 5 boards.
*/
bool checkDown(const vector<vector<pegState>>& board, int col, int row, int rowBound);
bool checkUp(const vector<vector<pegState>>& board, int col, int row);

/*
*	These functions are only used for checking triangular board. 
*/
bool checkTopLeft(const vector<vector<pegState>>& board, int col, int row);
bool checkTopRight(const vector<vector<pegState>>& board, int col, int row, int colBound);
bool checkBottomLeft(const vector<vector<pegState>>& board, int col, int row, int rowBound);
bool checkBottomRight(const vector<vector<pegState>>& board, int col, int row, int colBound, int rowBound);
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
*	This function performs the given command from user, it is written because it can make 4 different operation.
*	It can make left and right move for first 5 boards, and it can also make left and right move for triangular board.
*	put functions are not written for other moves because, operations are so simple and only takes 2 or 3 lines for them.
*	Function does not checks if this move is valid! Don't use the function before checking validity.
*/
bool putPegHorizontal(vector<vector<pegState>>& board, int col, int row, short int op, direction dir);
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
*	Functions decrypts the string which is user command. Columns and rows are returned as a reference with this function.
*/
bool decryptString(string userMove, int& col, int& row, direction& dir);
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
*	Function performs the given commands. It takes 5 parameters. vector, columnd and row indexes, direction and type of board.
*	If movement made successifully it returns true, otherwise false.
* x is column, y is row.
*/
bool makeMove(vector<vector<pegState>>& board, int x, int y, direction dir, short int op);
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
*	Function makes random movement. It takes to parameters which are vector, and type of board.
*	It returns nothing.
*/
void cpuMove(vector<vector<pegState>>& board, short int op);
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
*	Function simply prints the board. Takes only one parameter which is vector and it is read only.
*/
void displayBoard(const vector<vector<pegState>>& board);
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
*	Function is a helper function of displayBoard. It prints single block according to the given pegState enumerator.
*/
void printBlock(pegState blockVar);
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
*	Function counts how many peg left on the board. It takes vector parameter, and it is read-only.
*	Function returns integer that is number of the peg on the board.
*/
int countPeg(const vector<vector<pegState>>& board);

/*=======================================================================================================*/
/*
*  Function makes movement upper diagonal which are top right and top left.
*  Takes 4 parameters, and returns nothing.
*  Function does not checks if this move is valid! Don't use the function before checking validity.  
*/
void putPegDiagonalUp(vector<vector<pegState>>& board, int col, int row, direction dir);
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
*  Function makes movement lower diagonal which are bottom right and bottom left.
*  Takes 4 parameters, and returns nothing.
*  Function does not checks if this move is valid! Don't use the function before checking validity.  
*/
void putPegDiagonalDown(vector<vector<pegState>>& board, int col, int row, direction dir);