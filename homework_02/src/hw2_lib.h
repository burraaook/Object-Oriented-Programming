/*
** hw2_lib.h:
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
*	Function checks if there are any possible movement on the board. If it is, it returns false, otherwise true.
*	Function takes 2 parameters, one of that is vector and this parameter is used as read only. Other parameter indicates which board 
 is checked. It can be 1 or 2.
*/
bool canMove(const vector<vector<pegState>>& board, int op = 1);
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
*	These functions are used for checking is it possible to move spesific directions and sometimes spesific boards.
*	Boolean value will be returned movement is valid it returns true, otherwise false.
*	board is a 2d vector which is used as read only. col is column. colBound and rowBound indicates boundaries of that vector of vectors.
*	Boundaries doesn't needed to be added, but they are preffered because these functions are became simple with these parameters. 	
*/

/*
*	checkLeft and checkRight functions needs board type(OP) because in triangular board, A little bit different operation
  is needed. That op indicates which operation will be checked. It must be 1 or 2. 
*/
bool checkLeft(const vector<vector<pegState>>& board,const size_t& col,const size_t& row, int op = 1);
bool checkRight(const vector<vector<pegState>>& board,const  size_t& col,const  size_t& row,const  size_t& colBound, int op = 1);

/*
*	These up and down functions only used for checking first 5 boards.
*/
bool checkDown(const vector<vector<pegState>>& board,const size_t& col,const size_t& row,const size_t& rowBound);
bool checkUp(const vector<vector<pegState>>& board,const size_t& col,const size_t& row);

/*
*	These functions are only used for checking triangular board. 
*/
bool checkTopLeft(const vector<vector<pegState>>& board,const  size_t& col,const  size_t& row);
bool checkTopRight(const vector<vector<pegState>>& board,const  size_t& col,const  size_t& row,const  size_t& colBound);
bool checkBottomLeft(const vector<vector<pegState>>& board,const  size_t& col,const  size_t& row,const  size_t& rowBound);
bool checkBottomRight(const vector<vector<pegState>>& board,const  size_t& col,const  size_t& row, const size_t& colBound,const size_t& rowBound);
/*=======================================================================================================*/

/*=======================================================================================================*/

/*
*	This function performs the given command from user, it is written because it can make 4 different operation.
*	It can make left and right move for first 5 boards, and it can also make left and right move for triangular board.
*	put functions are not written for other moves because, operations are so simple and only takes 2 or 3 lines for them.
*	Function does not checks if this move is valid! Don't use the function before checking validity.
*/
bool putPegHorizontal(vector<vector<pegState>>& board,const size_t& col,const size_t& row,const direction& dir, int op = 1);

/*
*  Function makes movement upper diagonal which are top right and top left.
*  Takes 4 parameters, and returns nothing.
*  Function does not checks if this move is valid! Don't use the function before checking validity.  
*/
void putPegDiagonalUp(vector<vector<pegState>>& board, const size_t& col, const size_t& row,const direction& dir);

/*
*  Function makes movement lower diagonal which are bottom right and bottom left.
*  Takes 4 parameters, and returns nothing.
*  Function does not checks if this move is valid! Don't use the function before checking validity.  
*/
void putPegDiagonalDown(vector<vector<pegState>>& board,const size_t& col,const size_t& row,const direction& dir);
/*=======================================================================================================*/
/*=======================================================================================================*/
/*
*	Functions decrypts the string which is user command. Columns and rows are returned as a reference with this function.
*/
bool decryptString(string userMove, int& col, int& row, direction& dir);
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
*	Function performs the given commands. It takes 5 parameters. vector, cold and row indexes, direction and type of board.
*	If movement made successfully it returns true, otherwise false.
* x is col, y is row.
*/
bool makeMove(vector<vector<pegState>>& board,const size_t& x,const size_t& y,const direction& dir, int op = 1);
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
*	Function makes random movement. It takes to parameters which are vector, and type of board.
*	It returns nothing.
*/
void cpuMove(vector<vector<pegState>>& board, int op = 1);
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
* These functions are used for reading and writing to file.
*/

/*
* Functions decomposes the user input and returns which file operations will be operated.
* Returns 1 if file command is LOAD, 2 if file command is SAVE.
* PRECONDITION: string length must be minimum 6. Check length before using that function.
*/
int checkFileCommand(string userInput);

/*
* Function saves the given information to given filename.
* Returns true if game saved successfully, otherwise false.
*/
bool saveGame(vector<vector<pegState>>& board, string userInput, const int& numOfMove, const int& tuser, const int& op);

/*
* Function reads game information from given filename.
* File must be formatted in wanted way. It is described on README.txt.
*/
bool loadGame(vector<vector<pegState>>& board, string userInput, int& numOfMove, int& tuser, int& op);

/*
* Function is a helper function used in loadGame.
*/
bool readBoardFromFile(vector<vector<pegState>>& board, ifstream& inFile, size_t& colBound, size_t& rowBound);
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
* Function takes type of board properly from user.
* numOfMove, tuser, and op parameters are passed because user could suddenly load a file.
*/
bool getBoardType(vector<vector<pegState>>& board, int& numOfMove, int& tuser, int& op);
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
* Function gets user type properly.
* numOfMove, tuser, and op parameters are passed because user could suddenly load a file.
*/
void getUserType(vector<vector<pegState>>& board, int& numOfMove, int& tuser, int& op);
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
* Function lets user play the game.
* returns true if game is finished, otherwise false.
*/
bool HumanPegGame(vector<vector<pegState>>& board, int& numOfMove, int& tuser, int& op);
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
* Functions reads integer from given line and assigns it to givenType.
* Returns true if operation performed successfully, otherwise false.
*/
bool readIntFromLine(string line, string name, int& givenType);
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
* Function converts given string to integer.
* It works only for one and two digit numbers.
* Returns true if operation performed successfully, otherwise false.
*/
bool convertAssignStr(string numStr, int& givenType);
/*=======================================================================================================*/

/*=======================================================================================================*/
/*
* Function deletes if buffer has carriage return character('\r') at end of the string.
*/
void correctCR(string& buffer);