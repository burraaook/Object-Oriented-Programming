/*
** hw2_lib.cpp:
**
** The source file is created for implementing library functions.
**
** Burak Kocausta 1901042605
** 
*/

#include "hw2_lib.h"
// Basic explanations of each function are in the header file.

void playPegSolitaire(){
	int tuser,op;						// tuser is user type(computer,human).
	vector<vector<pegState>> board;		// Declaring vector of vectors for board.
	decltype(op) numOfMove = 0;

	auto loadFlag = getBoardType(board, numOfMove, tuser, op);			// Getting the board type from user.
	
	if(!loadFlag)
		getUserType(board, numOfMove, tuser, op);	// board and op are passed as an argument here too, because user could suddenly want to load a game.
	
	auto endFlag = false;
	do{
		if(tuser == 1){							// If game is computer game, call the proper functions.
			
			displayBoard(board);				// Printing the board initially.
			do{
				cpuMove(board, op);				// Makes random move.
				++numOfMove;
				displayBoard(board);			// Display board after the move.
			}while(!canMove(board,op));					// Loop iterates till there aren't any possible move.
			
			endFlag = false;
			int pegNum = countPeg(board);		// Counting the pegs on the board.
			if(pegNum == 1)						// Printing the result.
				cout << "Computer have achieved maximum score in " << numOfMove << " moves!" << endl << endl;
			else
				cout << "Computer's score is " << pegNum << " in " << numOfMove << " moves." << endl << endl;
			
		}// End of the computer game condition.

		else if(tuser == 2){					// If game is user game, call the proper function.
			endFlag = HumanPegGame(board, numOfMove, tuser, op);	
			
			if(!endFlag){
				auto pegNum = countPeg(board);
				if(pegNum == 1)						// Printing result.
					cout << "Congratulations! You have achieved maximum score in " << numOfMove << " moves!" << endl << endl;
				else
					cout << "Your score is " << pegNum << " in " << numOfMove << " moves." << endl << endl;
			}
		}// End of user game condition.
	}while(endFlag);	
}//End of function.
//================================================================================================================================

vector<vector<pegState>> createEuropeanBoard(){	// Function creates vector of vectors in European Board style.
	vector<vector<pegState>> board
	{
		{ pegState::wall, pegState::wall, pegState::peg, pegState::peg,   pegState::peg, pegState::wall, pegState::wall},
		{ pegState::wall, pegState::peg,  pegState::peg, pegState::peg,   pegState::peg, pegState::peg,  pegState::wall},
		{ pegState::peg,  pegState::peg,  pegState::peg, pegState::empty, pegState::peg, pegState::peg,  pegState::peg},
		{ pegState::peg,  pegState::peg,  pegState::peg, pegState::peg,   pegState::peg, pegState::peg,  pegState::peg},
		{ pegState::peg,  pegState::peg,  pegState::peg, pegState::peg,   pegState::peg, pegState::peg,  pegState::peg},
		{ pegState::wall, pegState::peg,  pegState::peg, pegState::peg,   pegState::peg, pegState::peg,  pegState::wall},
		{ pegState::wall, pegState::wall, pegState::peg, pegState::peg,   pegState::peg, pegState::wall, pegState::wall}
	};
	return board;
}//End of function.
//================================================================================================================================
vector<vector<pegState>> createWiegleBoard(){	// Function creates vector of vectors in Wiegle Board style.
	vector<vector<pegState>> board
	{
		{ pegState::wall,  pegState::wall,  pegState::wall, pegState::peg, pegState::peg, pegState::peg,  pegState::wall,  pegState::wall,  pegState::wall},
		{ pegState::wall,  pegState::wall,  pegState::wall, pegState::peg, pegState::peg, pegState::peg,  pegState::wall,  pegState::wall,  pegState::wall},
		{ pegState::wall,  pegState::wall,  pegState::wall, pegState::peg, pegState::peg, pegState::peg,  pegState::wall,  pegState::wall,  pegState::wall},
		{ pegState::peg,   pegState::peg,  pegState::peg, pegState::peg,   pegState::peg, pegState::peg,  pegState::peg,   pegState::peg,   pegState::peg},  
		{ pegState::peg,   pegState::peg,  pegState::peg, pegState::peg,   pegState::empty, pegState::peg,pegState::peg,   pegState::peg,   pegState::peg},
		{ pegState::peg,   pegState::peg,  pegState::peg, pegState::peg,   pegState::peg, pegState::peg,  pegState::peg,   pegState::peg,   pegState::peg},
		{ pegState::wall,  pegState::wall,  pegState::wall, pegState::peg, pegState::peg, pegState::peg,  pegState::wall,  pegState::wall,  pegState::wall},
		{ pegState::wall,  pegState::wall,  pegState::wall, pegState::peg, pegState::peg, pegState::peg,  pegState::wall,  pegState::wall,  pegState::wall},
		{ pegState::wall,  pegState::wall,  pegState::wall, pegState::peg, pegState::peg, pegState::peg,  pegState::wall,  pegState::wall,  pegState::wall}
	};
	return board;
}//End of function.
//================================================================================================================================
vector<vector<pegState>> createAsymmetricalBoard(){	// Function creates vector of vectors in Asymmetrical Board style.

	vector<vector<pegState>> board
	{
		{ pegState::wall,  pegState::wall,  pegState::peg, pegState::peg, pegState::peg, pegState::wall,  pegState::wall,  pegState::wall },
		{ pegState::wall,  pegState::wall,  pegState::peg, pegState::peg, pegState::peg, pegState::wall,  pegState::wall,  pegState::wall },
		{ pegState::wall,  pegState::wall,  pegState::peg, pegState::peg, pegState::peg, pegState::wall,  pegState::wall,  pegState::wall },
		{ pegState::peg,   pegState::peg,   pegState::peg, pegState::peg,   pegState::peg, pegState::peg,  pegState::peg,  pegState::peg   },  
		{ pegState::peg,   pegState::peg,   pegState::peg, pegState::empty,   pegState::peg, pegState::peg,  pegState::peg,  pegState::peg },
		{ pegState::peg,   pegState::peg,   pegState::peg, pegState::peg,   pegState::peg, pegState::peg,  pegState::peg,  pegState::peg   },
		{ pegState::wall,  pegState::wall,  pegState::peg, pegState::peg, pegState::peg, pegState::wall,  pegState::wall,  pegState::wall },
		{ pegState::wall,  pegState::wall,  pegState::peg, pegState::peg, pegState::peg, pegState::wall,  pegState::wall,  pegState::wall }	
	};

	return board;
}//End of function.
//================================================================================================================================
vector<vector<pegState>> createEnglishBoard(){	// Function creates vector of vectors in English Board style.

	vector<vector<pegState>> board
	{

		{ pegState::wall, pegState::wall, pegState::peg, pegState::peg,   pegState::peg, pegState::wall, pegState::wall},
		{ pegState::wall, pegState::wall,  pegState::peg, pegState::peg,   pegState::peg, pegState::wall,  pegState::wall},
		{ pegState::peg,  pegState::peg,  pegState::peg, pegState::peg, pegState::peg, pegState::peg,  pegState::peg},
		{ pegState::peg,  pegState::peg,  pegState::peg, pegState::empty,   pegState::peg, pegState::peg,  pegState::peg},
		{ pegState::peg,  pegState::peg,  pegState::peg, pegState::peg,   pegState::peg, pegState::peg,  pegState::peg},
		{ pegState::wall, pegState::wall,  pegState::peg, pegState::peg,   pegState::peg, pegState::wall,  pegState::wall},
		{ pegState::wall, pegState::wall, pegState::peg, pegState::peg,   pegState::peg, pegState::wall, pegState::wall}
	};

	return board;
}//End of function.
//================================================================================================================================
vector<vector<pegState>> createDiamondBoard(){	// Function creates vector of vectors in Diamond Board style.

	vector<vector<pegState>> board
	{
		{ pegState::wall,  pegState::wall,  pegState::wall, pegState::wall, pegState::peg, pegState::wall,  pegState::wall,  pegState::wall,  pegState::wall},
		{ pegState::wall,  pegState::wall,  pegState::wall, pegState::peg, pegState::peg, pegState::peg,  pegState::wall,  pegState::wall,  pegState::wall},
		{ pegState::wall,  pegState::wall,  pegState::peg, pegState::peg, pegState::peg, pegState::peg,  pegState::peg,  pegState::wall,  pegState::wall},
		{ pegState::wall,   pegState::peg,  pegState::peg, pegState::peg,   pegState::peg, pegState::peg,  pegState::peg,  pegState::peg,  pegState::wall},  
		{ pegState::peg,   pegState::peg,  pegState::peg, pegState::peg,   pegState::empty, pegState::peg,  pegState::peg,  pegState::peg,  pegState::peg},
		{ pegState::wall,   pegState::peg,  pegState::peg, pegState::peg,   pegState::peg, pegState::peg,  pegState::peg,  pegState::peg,  pegState::wall},
		{ pegState::wall,  pegState::wall,  pegState::peg, pegState::peg, pegState::peg, pegState::peg,  pegState::peg,  pegState::wall,  pegState::wall},
		{ pegState::wall,  pegState::wall,  pegState::wall, pegState::peg, pegState::peg, pegState::peg,  pegState::wall,  pegState::wall,  pegState::wall},
		{ pegState::wall,  pegState::wall,  pegState::wall, pegState::wall, pegState::peg, pegState::wall,  pegState::wall,  pegState::wall,  pegState::wall}
	};

	return board;
}//End of function.
//================================================================================================================================
vector<vector<pegState>> createTriangularBoard(){	// Function creates vector of vectors in Triangular Board style.

	vector<vector<pegState>> board
	{	
		{pegState::wall, pegState::wall, pegState::wall, pegState::wall, pegState::empty, pegState::wall, pegState::wall, pegState::wall, pegState::wall},
		{pegState::wall, pegState::wall, pegState::wall, pegState::peg, pegState::wall, pegState::peg, pegState::wall, pegState::wall, pegState::wall},
		{pegState::wall, pegState::wall, pegState::peg, pegState::wall, pegState::peg, pegState::wall, pegState::peg, pegState::wall, pegState::wall},
		{pegState::wall, pegState::peg, pegState::wall, pegState::peg, pegState::wall, pegState::peg, pegState::wall, pegState::peg, pegState::wall},
		{pegState::peg, pegState::wall, pegState::peg, pegState::wall, pegState::peg, pegState::wall, pegState::peg, pegState::wall, pegState::peg}
	};
	return board;
}//End of function.
//================================================================================================================================

void displayBoard(const vector<vector<pegState>>& board){	// Function prints the given vector of vectors properly.

	// Variables for boundaries of vector.
	
	auto colBound = board[0].size();
	auto rowBound = board.size();

	cout << endl << "   ";

	for(decltype(colBound) i = 0; i < colBound; ++i)		// Printing Alphabets for cols.
		cout << static_cast<char>('A' + i) << " ";

	cout << endl;
	for(decltype(rowBound) i = 0; i < rowBound; ++i){						// Printing the rest of the board.
		cout << i + 1  << " ";
		colBound = board[i].size();

		for(decltype(rowBound) j = 0; j < colBound; ++j){
			cout << " ";
			printBlock(board[i][j]);						// Print single block peg or empty(P,.).
		}
		cout << endl;
	}
	cout << endl;
}//End of function.
//================================================================================================================================

void printBlock(pegState blockVar){ 		// Function prints single block.

	switch(blockVar){						// Selecting the proper letter.
		case pegState::peg:
			cout << "P";
			break;
		case pegState::empty:
			cout << ".";
			break;
		default:
			cout << " ";
	}//End of selection.
}//End of function.
//================================================================================================================================

bool canMove(const vector<vector<pegState>>& board, int op){		// Function checks are there any move can be made.
	auto flag = true;
	auto rowBound = board.size();						
	auto colBound = board[0].size();					// Column boundary is same for every row.

	for(decltype(rowBound) i = 0; i < rowBound && flag; ++i){
		
		for(decltype(colBound) j = 0; j < colBound && flag; ++j){

			if(board[i][j] == pegState::peg){
				
				if(op != 2){		// If board is not triangular make different checks.
					if(checkUp(board,j,i) || checkDown(board,j,i,rowBound) || checkLeft(board, j, i, op) || checkRight(board, j, i, colBound, op))
						flag = false;
				}
				else{				// If board is triangular there are 6 checkings.
					if(checkTopLeft(board, j, i) || checkBottomLeft(board, j, i, rowBound) ||  
					   checkTopRight(board, j, i, colBound) || checkBottomRight(board, j, i, colBound, rowBound) ||
					   checkLeft(board, j, i, op) || checkRight(board, j, i, colBound, op)){
							flag = false;
					}
				}
			}	
		}
	}
	return flag;
}//End of function.
//================================================================================================================================
bool makeMove(vector<vector<pegState>>& board,const size_t& x,const size_t& y,const direction& dir, int op){
	auto flag = false;

	auto rowBound = board.size();				
	auto colBound = board[y].size();

	if(y < rowBound && x < colBound){		// Checking the initial conditions.

		if(board[y][x] == pegState::peg){						// Given indexes must be represent the peg.

			switch(dir){										// Selecting functions or making operations according to the direction.
				case direction::left:
					if(checkLeft(board, x, y, op))
						flag = putPegHorizontal(board, x, y, direction::left, op);				
					break;
				case direction::right:
					if(checkRight(board, x, y, colBound, op))
						flag = putPegHorizontal(board, x, y, direction::right, op);	
					break;
				case direction::down:
					if(op != 2 && checkDown(board, x, y, rowBound)){
						board[y][x] = board[y+1][x] = pegState::empty;		
						board[y+2][x] = pegState::peg;
						flag = true;
					}
					else if(op == 2){		// If it is triangular board, make diagonal moves.
						
						bool flagBR = checkBottomRight(board, x, y, colBound, rowBound);	// Check if bottom right move is valid. 
						bool flagBL = checkBottomLeft(board, x, y, rowBound);

						if(flagBR && flagBL){									// If both flag is true than randomly choose one of them.
							int moveType = rand() % 2;
							flag = true;

							if(moveType)
								putPegDiagonalDown(board, x, y, direction::right);
							else
								putPegDiagonalDown(board, x, y, direction::left);		
						} 
						else if(flagBR){										// If both of them is not true, chose valid one.
							putPegDiagonalDown(board, x, y, direction::right);
							flag = true;
						}
						else if(flagBL){
							putPegDiagonalDown(board, x, y, direction::left);
							flag = true;
						}
					}
					break;
				case direction::up:
					if(op != 2 && checkUp(board, x, y)){
						board[y][x] = board[y-1][x] = pegState::empty;
						board[y-2][x] = pegState::peg;
						flag = true;
					}
					else if(op == 2){		// If it is triangular board, make diagonal moves.

						bool flagTR = checkTopRight(board, x, y, colBound);		// Check if top right movement is valid. 
						bool flagTL = checkTopLeft(board, x, y);

						if(flagTR && flagTL){									// If both flag is true than randomly choose one of them.
							int moveType = rand() % 2;	
							flag = true;

							if(moveType)
								putPegDiagonalUp(board, x, y, direction::right);		
							else
								putPegDiagonalUp(board, x, y, direction::left);		
						}
						else if(flagTR){										// If both of them is not true, chose valid one.
							putPegDiagonalUp(board, x, y, direction::right);
							flag = true;
						}
						else if(flagTL){
							putPegDiagonalUp(board, x, y, direction::left);
							flag = true;
						}
					}
			}// End of selection.
		}
	}
	return flag;
}//End of function.
//================================================================================================================================
void cpuMove(vector<vector<pegState>>& board, int op){				// Function makes random valid movement. 
	srand((static_cast<unsigned int>(time(NULL))));
	auto flag = false;
	char col;
	string strDir;
	direction dir;
	size_t i,j;		// i is row j is col.

	while(!flag){											// Iterate till valid command is generated.

		i = rand() % board.size();
		j = rand() % board[i].size();
		dir = static_cast<decltype(dir)>(rand() % 4);

		flag = makeMove(board, j, i, dir, op);				// Check if generated command is valid.
	}

	col = static_cast<decltype(col)>(j + static_cast<decltype(j)>('A'));		// Casting the commands to characters.

	switch(dir){					// Selecting the string version of direction.
		case direction::left:
			strDir = "L";
			break;
		case direction::right:
			strDir = "R";
			break;
		case direction::up:
			strDir = "U";
			break;
		case direction::down:
			strDir = "D";
			break;
		default:
			strDir = "-";
			break;
	}
	cout << "================================================================================";
	cout << "\nMove " << col << i+1 << "-" << strDir << " made by computer." << endl << endl;	// Printing the generated command.
}//End of function.
//================================================================================================================================

// Function decrypts string input to usable variables. Returns as a reference.
bool decryptString(string userMove, int& col, int& row, direction& dir){	
	auto ans = false, flag = false;
	auto strLen = userMove.length();				// Taking the length of string input.
	auto dirVar = '-';

	if(strLen > 0){
		if(userMove[0] >= 'A' && userMove[0] <= 'Z'){
			col = static_cast<int>(userMove[0]) - static_cast<int>('A');
			flag = true;
		}
		else if(userMove[0] >= 'a' && userMove[0] <= 'z'){
			col = static_cast<int>(userMove[0]) - static_cast<int>('a');
			flag = true;
		}
	}
	if(flag){
		if(strLen == 4 && userMove[2] == '-'){			
			dirVar = userMove[3];
			flag = convertAssignStr(userMove.substr(1,1), row);
			--row;
		}
		else if(strLen == 5 && userMove[3] == '-'){
			dirVar = userMove[4];
			flag = convertAssignStr(userMove.substr(1,2), row);
			--row;
		}		
	}
	if(flag){												// If previous conditions are true decrypt direction part.
		switch(dirVar){
			case 'R':
			case 'r':
				dir = direction::right;
				ans = true;
				break;
			case 'L':
			case 'l':
				dir = direction::left;
				ans = true;
				break;
			case 'U':
			case 'u':
				dir = direction::up;
				ans = true;
				break;
			case 'D':
			case 'd':
				dir = direction::down;
				ans = true;
				break;
		}// End of selection.
	}
	return ans;
}//End of function.

//================================================================================================================================

// Function checks if left move is valid or invalid.
bool checkLeft(const vector<vector<pegState>>& board,const size_t& col,const size_t& row, int op){	
	size_t step = 2;

	if(op == 2)			// If it is triangular, then there is a wall between each peg, so step must be twice as others.
		step = 4;

	if(col >= step && board[row][col-step] == pegState::empty && board[row][col-step+step/2] == pegState::peg)	// Checking validity.
		return true;
	return false;
}//End of function.

// Function checks if right move is valid or invalid.
bool checkRight(const vector<vector<pegState>>& board,const size_t& col,const size_t& row,const size_t& colBound, int op){	
	size_t step = 2;
	
	if(op == 2)				// If it is triangular, then there is a wall between each peg, so step must be twice as others.
		step = 4;

	if(col+step < colBound && board[row][col+step] == pegState::empty && board[row][col+step-step/2] == pegState::peg)	// Checking validity.
		return true;
	return false;
}//End of function.

// Function checks if down move is valid or invalid.
bool checkDown(const vector<vector<pegState>>& board,const size_t& col,const size_t& row,const size_t& rowBound){	
	if(row+2 < rowBound && board[row+2][col] == pegState::empty && board[row+1][col] == pegState::peg)	// Checking validity.
		return true;
	return false;
}//End of function.

// Function checks if up move is valid or invalid.
bool checkUp(const vector<vector<pegState>>& board,const size_t& col,const size_t& row){	
	if(row >= 2 && board[row-2][col] == pegState::empty && board[row-1][col] == pegState::peg)	// Checking validity.
		return true;
	return false;
}//End of function.

// Function checks if top left move is valid or invalid.
bool checkTopLeft(const vector<vector<pegState>>& board,const size_t& col,const size_t& row){	
	if(col >= 2 && row >= 2 && board[row-2][col-2] == pegState::empty && board[row-1][col-1] == pegState::peg)	// Checking validity.
		return true;
	return false;
}//End of function.

// Function checks if top right move is valid or invalid.
bool checkTopRight(const vector<vector<pegState>>& board,const size_t& col,const size_t& row,const size_t& colBound){	
	if(col+2 < colBound && row >= 2 && board[row-2][col+2] == pegState::empty && board[row-1][col+1] == pegState::peg)
		return true;
	return false;
}//End of function.

// Function checks if bottom left move is valid or invalid.
bool checkBottomLeft(const vector<vector<pegState>>& board,const size_t& col,const size_t& row,const size_t& rowBound){ 
	if(col >= 2 && row+2 < rowBound && board[row+2][col-2] == pegState::empty && board[row+1][col-1] == pegState::peg) // Checking validity.
		return true;
	return false;
}//End of function.

// Function checks if bottom right move is valid or invalid.
bool checkBottomRight(const vector<vector<pegState>>& board,const size_t& col,const size_t& row,const size_t& colBound,const size_t& rowBound){
	if(col+2 < colBound && row+2 < rowBound && board[row+2][col+2] == pegState::empty && board[row+1][col+1] == pegState::peg) // Checking validity.
		return true;
	return false;
}//End of function.
//================================================================================================================================
int countPeg(const vector<vector<pegState>>& board){	// Function counts how many pegs left.
	auto rowBound = board.size();
	auto colBound = board[0].size();
	int pegCounter = 0;

	for(decltype(rowBound) i = 0; i < rowBound; ++i){
		for(decltype(colBound) j = 0; j < colBound; ++j){
			if(board[i][j] == pegState::peg)			// If peg is found increment counter.
				++pegCounter;
		}
	}
	return pegCounter;
}//End of function.
//================================================================================================================================

// Function makes horizontal operations on board.
bool putPegHorizontal(vector<vector<pegState>>& board,const size_t& col,const size_t& row,const direction& dir,int op){
	auto step = 2;
	if(op == 2)				// If board is triangular, step must be twice as bigger.
		step = 4;

	if(dir == direction::left)		// If direction is left step must be negative number.
		step *= -1;

	board[row][col+step-(step/2)] = board[row][col] = pegState::empty;		// Making the swap operation.
	board[row][col+step] = pegState::peg;

	return true;
}//End of function.
//================================================================================================================================

// Function makes upper diagonal movements.
void putPegDiagonalUp(vector<vector<pegState>>& board, const size_t& col, const size_t& row, const direction& dir){ 
	int step = 2;

	if(dir == direction::left)	// Deciding step size according to the direction
		step *= -1;

	board[row-1][col+step-step/2] = board[row][col] = pegState::empty;		// Making the swap operation.
	board[row-2][col+step] = pegState::peg;
}//End of function.
//================================================================================================================================

// Function makes upper diagonal movements.
void putPegDiagonalDown(vector<vector<pegState>>& board, const size_t& col, const size_t& row, const direction& dir){	
	int step = 2;

	if(dir == direction::left)	// Deciding step size according to the direction
		step *= -1;

	board[row+1][col+step-step/2] = board[row][col] = pegState::empty;	// Making the swap operation.
	board[row+2][col+step] = pegState::peg;
}//End of function.
//================================================================================================================================
int checkFileCommand(string userInput){		// Returns 1 if command is LOAD, returns 2 if it is SAVE, returns 0 if command is invalid.
	int ans = 0;

	if(userInput.compare(0,4,"LOAD") == 0)
		ans = 1;
	else if(userInput.compare(0,4,"SAVE") == 0)
		ans = 2;
	
	return ans;
}//End of function.
//================================================================================================================================

// Function loads game from given filename. Returns true if it operation is successful.
bool loadGame(vector<vector<pegState>>& board, string userInput, int& numOfMove, int& tuser, int& op){
	ifstream inFile;				// Open file in read-only mode.
	
	auto ans = true;
	inFile.open(userInput.substr(5,userInput.length()-5));		//Filename shouldn't be include commands.

	if(inFile.is_open()){										// If file opened successfully perform the operation.

		size_t colBound = 0,rowBound = 0;		
		vector<int> keyVariables(5,0);							// Creating integer and string vectors.
		vector<string> keyStrings {"usertype = ", "operationType = ", "rowBound = ", "colBound = ", "number of moves = "};
			
		string line;

		for(int i = 0; i < 5 && ans; ++i){						// Reading first 5 information from file.
			if(getline(inFile, line)){
				correctCR(line);								// Delete CR character if it is exist.
				ans = readIntFromLine(line, keyStrings[i], keyVariables[i]);	// Assign value to integer element from string.
			}
			else		// If getline goes wrong return false.
				ans = false;
		}
		
		rowBound = static_cast<size_t>(keyVariables[2]);		// Cast these integers to size_t and assign to boundary variables.
		colBound = static_cast<size_t>(keyVariables[3]);

		// Create vector of vectors which has elements defaulted to wall.
		vector<vector<pegState>> temp_board(rowBound, vector<pegState>(colBound, pegState::wall));
		
		// Check boundaries and ans, if they are true read board from file.
		if(ans && rowBound > 0 && rowBound <= 99 && colBound > 0 && colBound <= 99)	
			ans = readBoardFromFile(temp_board, inFile, colBound, rowBound);
		else
			ans = false;

		if(ans){	// If board readed successfully return the taken values.
			board = temp_board;
			tuser = keyVariables[0];
			op = keyVariables[1];
			numOfMove = keyVariables[4];
		}
		inFile.close();	// Close the file.
	}
	else
		ans = false;
	
	return ans;
}//End of function.
//================================================================================================================================

// Functions saves the game to given filename. Returns true if it operation is successful.
bool saveGame(vector<vector<pegState>>& board, string userInput, const int& numOfMove, const int& tuser, const int& op){	
	ofstream outFile;
	outFile.open(userInput.substr(5,userInput.length()-5));
	auto ans = true;
	
	if(outFile.is_open()){		
		auto colBound = board[0].size();			// Taking the boundaries from vector.
		auto rowBound = board.size();

		outFile << "usertype = " << tuser << endl << "operationType = " << op << endl
				<< "rowBound = " << rowBound << endl
				<< "colBound = " << colBound << endl
				<< "number of moves = " << numOfMove << endl;

		for(decltype(rowBound) i = 0; i < rowBound; ++i){		// Writing board to file.			
			
			colBound = board[i].size();
			for(decltype(colBound) j = 0; j < colBound; ++j){
					switch(board[i][j]){						// Selecting the proper letter.
						case pegState::peg:
							outFile << "P";
							break;
						case pegState::empty:
							outFile << ".";
							break;
						default:
							outFile << " ";
					}//End of selection.
			}
			outFile << endl;
		}
		outFile.close();										// Closing file.
	}
	else
		ans = false;

	return ans;
}//End of function.
//================================================================================================================================

// Function gets board type from user. Returns true if operation is successful.
bool getBoardType(vector<vector<pegState>>& board, int& numOfMove, int& tuser, int& op){
	int tboard;
	bool inputFlag, loadFlag;

	do{									// This loop takes proper input for boards.
		cout << "Which board do you want to play?\n\n1 - French (European) style, 37 holes\n2 - J. C. Wiegleb, Germany, 45 holes" << endl
			 << "3 - Asymmetrical 3-3-2-2 as described by George Bell\n4 - English style (standard), 33 holes" << endl 
			 << "5 - Diamond, 41 holes\n6 - Triangular, 15 holes\nInput(1-6 or LOAD): ";

		string userInput;
		
		loadFlag = false;
		inputFlag = false;

		getline(cin,userInput);
		correctCR(userInput);				// If string includes CR character remove it.

		if(userInput.length() == 1){
			tboard = static_cast<decltype(tboard)>(userInput[0]) - static_cast<decltype(tboard)>('0');
			inputFlag = (tboard >= 1 && tboard <= 6);
		}
		else if(userInput.length() > 5){	// LOAD command string must be bigger than 5 characters.
			auto fileFlag = checkFileCommand(userInput); // returns integer
			
			if(fileFlag == 1){
				loadFlag = loadGame(board, userInput, numOfMove, tuser, op);
				if(!loadFlag){
					cerr << "File cannot be loaded! File does not exist or some other error occurred." << endl << endl;
					continue;
				}
				else
					cout << "File successfully loaded!" << endl;
				
				inputFlag = loadFlag;
				tboard = 0;
			}
			else if(fileFlag == 2)			// Cannot save in this session.
				cerr << "You can only load save files before the game. For saving game, please start a game session." << endl;
		}
	
		if(!inputFlag)
			cerr << "\nWrong input! Please enter the numbers given next to the board name or load a file using LOAD command(ex: LOAD FILE.TXT)." << endl << endl;

	}while(!inputFlag);					// Iterates till proper input is entered.

	switch(tboard){						// Selecting the operation according to type of board. Functions return vector.
		case 1:
			board = createEuropeanBoard();		
			break;
		case 2:
			board = createWiegleBoard();
			break;
		case 3:
			board = createAsymmetricalBoard();
			break;
		case 4:
			board = createEnglishBoard();
			break;
		case 5:
			board = createDiamondBoard();
			break;
		case 6:
			board = createTriangularBoard();
			break;
	} // End of selection

	if(!loadFlag){
		if(tboard < 6 && tboard >= 1)
			op = 1;
		else if(tboard == 6)
			op = 2;
	}
	return loadFlag;
}//End of function.
//================================================================================================================================

// Function gets user type(Human or Computer) from user.
void getUserType(vector<vector<pegState>>& board, int& numOfMove, int& tuser, int& op){
	bool inputFlag;

	do{									// This loop lets user to chose if game is computer game or human game.
		string userInput;
		inputFlag = false;
		
		cout << "\nPlease enter the user type\n1 - Computer Game\n2 - Human Player Game\nInput(1-2 or LOAD): ";
		getline(cin,userInput);
		correctCR(userInput);

		if(userInput.length() == 1){
			tuser = static_cast<int>(userInput[0]) - static_cast<int>('0');
			inputFlag = (tuser == 1 || tuser == 2);
		}
		else if(userInput.length() > 5){
			auto fileFlag = checkFileCommand(userInput); // returns integer

			if(fileFlag == 1){
				decltype(inputFlag) loadFlag = loadGame(board, userInput, numOfMove, tuser, op);
				if(!loadFlag){
					cerr << "File cannot be loaded! File does not exist or some other error occurred." << endl << endl;
					continue;
				}
				else
					cout << "File successfully loaded!" << endl;
				inputFlag = loadFlag;
			}
			else if(fileFlag == 2)						// Cannot save in this session.
				cerr << "You can only load save files before the game. For saving game, please start a game session." << endl;
			else
				inputFlag = false;		
		} 
		
		if(!inputFlag)
			cerr << "\nWrong input! Please enter 1 or 2, or load a file using LOAD command(ex: LOAD FILE.TXT)." << endl << endl;

	}while(!inputFlag);					// Iterates till proper input is entered.
}//End of function.
//================================================================================================================================

// Function lets user to play the game.
bool HumanPegGame(vector<vector<pegState>>& board, int& numOfMove, int& tuser, int& op){
	int col,row;					// These variable will be used as vector indexes.
	direction dir;
	string userCommand;				// Input will be taken as a string. 
	displayBoard(board);			// Printing the board initally.
	auto stateFlag = false;

	cout << "\nEnter your command in a format like (col)(row)-(direction like R,L,U,D)\n Example input = B4-R" << endl;
	cout << "You can LOAD or SAVE a game.\nExample input for loading = LOAD FILE.TXT\nExample input for saving = SAVE FILE.TXT" << endl;					
	if(op == 2){	// If board is triangular board, there will be slightly different message.
		cout << "Since this is a triangular board pegs can move diagonal U means, top right or top left."
			 << "D means, bottom right or bottom left." << endl;
	}

	do{								// This loop lets user play the game.			
		cout << "\n================================================================\nInput = ";
		
		getline(cin,userCommand);
		correctCR(userCommand);
		
		auto inputFlag = false;

		if(userCommand.length() > 5){
			auto fileFlag = checkFileCommand(userCommand); // returns integer
			if(fileFlag == 1){
				auto loadFlag = loadGame(board, userCommand, numOfMove, tuser, op);
				if(!loadFlag)
					cerr << "File cannot be loaded! Given file name does not exist or command format is wrong!" << endl;
				else{
					cout << "File successfully loaded. Here is the board: " << endl;
					displayBoard(board);
				}
			}
			else if(fileFlag == 2){
				auto saveFlag = saveGame(board, userCommand, numOfMove, tuser, op);			
				if(!saveFlag)
					cerr << "File cannot be saved! Command format might be wrong or some other error occured." << endl;
				else
					cout << userCommand.substr(5,userCommand.length()-5) << " is saved." << endl;	
			}
			else
				cerr << "File cannot be loaded or saved! Given file name does not exist or some other error occurred." << endl;			
		}
		else{
			inputFlag = decryptString(userCommand, col, row, dir);		// Passing necessary variables as reference.
			
			if(inputFlag){				// if command is valid, call the makeMove function.
				bool moveFlag;

				// Checking the first validity.
				if(static_cast<size_t>(row) >= board.size() || row < 0 || static_cast<size_t>(col) >= board[row].size() || col < 0)
					moveFlag = false;
				else	
					moveFlag = makeMove(board, col, row, dir, op); 		
				
				if(!moveFlag)	// If move cannot be made print message.
					cerr << "This move cannot be done according to the rules." << endl;
				else
					++numOfMove;
				displayBoard(board);
			}
			else				// Error message for user's wrong formatted command.
				cerr << "Input format is wrong! Please write input according to the given example." << endl << endl;
		}
		stateFlag = !canMove(board,op);
	}while(stateFlag && tuser == 2);			// Iterates till there are not any possible move or user changes.

	return stateFlag;
}//End of function.
//================================================================================================================================

// Function reads integer from given line after the name.
bool readIntFromLine(string line, string name, int& givenType){
	auto flag = false;

	auto lenLine = line.length();	// Taking the boundaries.
	auto lenName = name.length();

	if(lenLine >= lenName + 1 && line.compare(0, lenName , name) == 0){

		string numStr = line.substr(lenName, lenLine-1);	// Taking the integer string.
		flag = convertAssignStr(numStr, givenType);			// Function converts string to integer.
	}
	return flag;
}//End of function.
//================================================================================================================================

// Function converts string to integer.
bool convertAssignStr(string numStr, int& givenType){
	auto flag = (numStr[0] >= '0' && numStr[0] <= '9');

	if(flag){
		givenType = static_cast<int>(numStr[0] - static_cast<int>('0'));
		if(numStr.length() == 2){											// If it has 2 digits.
			flag = (numStr[1] >= '0' && numStr[1] <= '9');
			if(flag){
				givenType *= 10;
				givenType += (static_cast<int>(numStr[1] - static_cast<int>('0')));
			}
		}		
	}
	return flag;
}//End of function.
//================================================================================================================================

// Function reads board from given file reference.
bool readBoardFromFile(vector<vector<pegState>>& board, ifstream& inFile, size_t& colBound, size_t& rowBound){
	string line;
	auto ans = true;

	for(size_t i = 0; ans && i < rowBound; ++i){	// Read according to the boundaries.

		if(getline(inFile, line)){

			correctCR(line);

			auto lenLine = line.length();
			if(lenLine > colBound)
				ans = false;
			for(decltype(lenLine) j = 0; ans && j < lenLine; ++j){

				switch(line[j]){	// Take pegState according to the character written.
					case 'P':
					case 'p':
						board[i][j] = pegState::peg;
						break;
					case '.':
						board[i][j] = pegState::empty;
						break;
					case ' ':
						board[i][j] = pegState::wall;
						break;
					case '\n':
					case '\r':
					case '\0':
						break;
					default:
						ans = false;
						break;
				}// End of selection.
			}
		}//End of inner loop.
		else					// If getline goes wrong return false.
			ans = false;
	}
	return ans;
}//End of function.
//================================================================================================================================

// Function checks and removes from CR character from end of the given string.
void correctCR(string& buffer){
	if(buffer.length() > 0){
		if(buffer[buffer.length()-1] == '\r')
			buffer.pop_back();
	}
}//End of function.
//================================================================================================================================
