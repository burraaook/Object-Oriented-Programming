/*
** hw1_lib.cpp:
**
** The source file is created for implementing library functions.
**
** Burak Kocausta 1901042605
** 
*/

#include "hw1_lib.h"
// Basic explanations of each function are in the header file.

void playPegSolitaire(){
	short int tboard, tuser;			// tboard is used to represent board type(1-6), tuser is user type(computer,human).
	bool inputFlag;						// inputFlag is used for represent user input's validity.
	vector<vector<pegState>> board;		// Declaring 2d vector for board.

	do{									// This loop takes proper input for boards.
		
		cout << "Which board do you want to play?\n1 - French (European) style, 37 holes\n2 - J. C. Wiegleb, Germany, 45 holes" << endl
			 << "3 - Asymmetrical 3-3-2-2 as described by George Bell\n4 - English style (standard), 33 holes" << endl 
			 << "5 - Diamond, 41 holes\n6 - Triangular, 15 holes\nInput(1-6): ";

		string userInput;

		getline(cin,userInput);
		if(userInput.length() == 1){
			tboard = static_cast<short int>(userInput[0]) - static_cast<short int>('0');
			inputFlag = (tboard >= 1 && tboard <= 6);
		}
		else
			inputFlag = false;	
		
		if(!inputFlag)
			cout << "Wrong input! Please enter the numbers given next to the board name." << endl << endl;

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

	do{									// This loop lets user to chose if game is computer game or human game.
		string userInput;
		cout << "\n\nPlease enter the user type\n1 - Computer Game\n2 - Human Player Game\nInput(1-2): ";

		getline(cin,userInput);
		
		if(userInput.length() == 1){
			tuser = static_cast<short int>(userInput[0]) - static_cast<short int>('0');
			inputFlag = (tuser == 1 || tuser == 2);
		}
		else
			inputFlag = false;
		
		if(!inputFlag)
			cout << "Wrong input! Please enter 1 or 2." << endl << endl;

	}while(!inputFlag);					// Iterates till proper input is entered.

	if(tuser == 1){						// If game is computer game, call the proper functions.

		displayBoard(board);			// Printing the board initially.
		
		do{
			cpuMove(board, tboard);		// Makes random move.
			displayBoard(board);		// Display board after the move.
		}while(!canMove(board,tboard));	// Loop iterates till there aren't any possible move.
		
		int pegNum = countPeg(board);	// Counting the pegs on the board.

		if(pegNum == 1)					// Printing the result.
			cout << "Computer have achieved maximum score!" << endl << endl;
		else
			cout << "Computer's score is " << pegNum << "." << endl << endl;
		
	}// End of the computer game condition.

	else if(tuser == 2){				// If game is user game, call the proper functions.
		int column,row;					// These variable will be used as vector indexes.
		direction dir;
		string userCommand;				// Input will be taken as a string. 

		displayBoard(board);			// Printing the board initally.

		cout << "\nEnter your command in a format like (column)(row)-(direction like R,L,U,D)\n Example input = B4-R" << endl;
							
		if(tboard == 6){	// If board is triangular board, there will be slightly different message.
			cout << "Since this is a triangular board pegs can move diagonal U means, top right or top left."
				 << "D means, bottom right or bottom left." << endl;
		}

		do{								// This loop lets user play the game.			
			cout << "\n================================================================\nInput = ";
			getline(cin,userCommand);
			
			inputFlag = decryptString(userCommand, column, row, dir);		// Passing necessary variables as reference.

			if(inputFlag){				// if command is valid, call the makeMove function.
				bool moveFlag;

				// Checking the first validity.
				if(row >= static_cast<int>(board.size()) || row < 0 || column >= static_cast<int>(board[row].size()) || column < 0)
					moveFlag = false;
				else	
					moveFlag = makeMove(board, column, row, dir, tboard); 		
				
				if(!moveFlag)	// If move cannot be made print message.
					cout << "This move cannot be done according to the rules." << endl;
				displayBoard(board);
			}
			else				// Error message for user's wrong formatted command.
				cout << "Input format is wrong! Please write input according to the given example." << endl << endl;

		}while(!canMove(board,tboard));		// Iterates till there are not any possible move.

		int pegNum = countPeg(board);

		if(pegNum == 1)						// Printing result.
			cout << "Congratulations! You have achieved maximum score!" << endl << endl;
		else
			cout << "Your score is " << pegNum << "." << endl << endl;
		
	}// End of user game condition.
}//End of function.
//================================================================================================================================

vector<vector<pegState>> createEuropeanBoard(){	// Function creates 2d vector in European Board style.
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
vector<vector<pegState>> createWiegleBoard(){	// Function creates 2d vector in Wiegle Board style.
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
vector<vector<pegState>> createAsymmetricalBoard(){	// Function creates 2d vector in Asymmetrical Board style.

	vector< vector<pegState>> board
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
vector<vector<pegState>> createEnglishBoard(){	// Function creates 2d vector in English Board style.

	vector< vector<pegState>> board
	{

		{ pegState::wall, pegState::wall, pegState::peg, pegState::peg,   pegState::peg, pegState::wall, pegState::wall},
		{ pegState::wall, pegState::wall,  pegState::peg, pegState::peg,   pegState::peg, pegState::wall,  pegState::wall},
		{ pegState::peg,  pegState::peg,  pegState::peg, pegState::empty, pegState::peg, pegState::peg,  pegState::peg},
		{ pegState::peg,  pegState::peg,  pegState::peg, pegState::peg,   pegState::peg, pegState::peg,  pegState::peg},
		{ pegState::peg,  pegState::peg,  pegState::peg, pegState::peg,   pegState::peg, pegState::peg,  pegState::peg},
		{ pegState::wall, pegState::wall,  pegState::peg, pegState::peg,   pegState::peg, pegState::wall,  pegState::wall},
		{ pegState::wall, pegState::wall, pegState::peg, pegState::peg,   pegState::peg, pegState::wall, pegState::wall}
	};

	return board;
}//End of function.
//================================================================================================================================
vector<vector<pegState>> createDiamondBoard(){	// Function creates 2d vector in Diamond Board style.

	vector< vector<pegState>> board
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
vector<vector<pegState>> createTriangularBoard(){	// Function creates 2d Vector in Triangular Board style.

	vector< vector<pegState>> board
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

void displayBoard(const vector<vector<pegState>>& board){	// Function prints the given 2d vector properly.

	int colBound,rowBound;									// Variables for boundaries of vector.

	colBound = static_cast<int>(board[0].size());			// Casting the boundaries of vectors to integer.
	rowBound = static_cast<int>(board.size());

	cout << endl << "   ";

	for(int i = 0; i < colBound; ++i)						// Printing Alphabets for columns.
		cout << static_cast<char>('A' + i) << " ";

	cout << endl;
	for(int i = 0; i < rowBound; ++i){						// Printing the rest of the board.
		cout << i + 1  << " ";
		colBound = static_cast<int>(board[i].size());

		for(int j = 0; j < colBound; ++j){
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

bool canMove(const vector<vector<pegState>>& board, short int op){		// Function checks are there any move can be made.
	bool flag = true;
	int rowBound = static_cast<int>(board.size());						// Casting the vector's index boundaries.
	int colBound = static_cast<int>(board[0].size());					// Column boundary is same for every row.

	for(int i = 0; i < rowBound && flag; ++i){
		
		for(int j = 0; j < colBound && flag; ++j){

			if(board[i][j] == pegState::peg){
				
				if(op != 6){		// If board is not triangular make different checks.
					if(checkUp(board,j,i) || checkDown(board,j,i,rowBound) || checkLeft(board, j, i, op) || checkRight(board, j, i, colBound, op))
						flag = false;
				}
				else{				// If board is triangular there are 6 checkings.
					if(checkTopLeft(board, j, i) || checkBottomLeft(board, j, i, rowBound) ||  
					   checkTopRight(board, j, i, rowBound) || checkBottomRight(board, j, i, colBound, rowBound) ||
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
bool makeMove(vector<vector<pegState>>& board, int x, int y, direction dir, short int op){	// Function performs given command.
	bool flag = false;

	int rowBound = static_cast<int>(board.size());				// Casting the vector boundaries to integer.
	int colBound = static_cast<int>(board[y].size());

	if(y >= 0 && y < rowBound && x >= 0 && x < colBound){		// Checking the initial conditions.

		if(board[y][x] == pegState::peg){						// Given indexes must be represent the peg.

			switch(dir){										// Selecting functions or making operations according to the direction.
				case direction::left:
					if(checkLeft(board, x, y, op))
						flag = putPegHorizontal(board, x, y, op, direction::left);				
					break;
				case direction::right:
					if(checkRight(board, x, y, colBound, op))
						flag = putPegHorizontal(board, x, y, op, direction::right);	
					break;
				case direction::down:
					if(op != 6 && checkDown(board, x, y, rowBound)){
						board[y][x] = board[y+1][x] = pegState::empty;		
						board[y+2][x] = pegState::peg;
						flag = true;
					}
					else if(op == 6){		// If it is triangular board, make diagonal moves.
						
						bool flagBR = checkBottomRight(board, x, y, colBound, rowBound);	// Check if bottom right move is valid. 
						bool flagBL = checkBottomLeft(board, x, y, rowBound);

						if(flagBR && flagBL){									// If both flag is true than randomly choose one of them.
							short int moveType = rand() % 2;
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
					if(op != 6 && checkUp(board, x, y)){
						board[y][x] = board[y-1][x] = pegState::empty;
						board[y-2][x] = pegState::peg;
						flag = true;
					}
					else if(op == 6){		// If it is triangular board, make diagonal moves.

						bool flagTR = checkTopRight(board, x, y, colBound);		// Check if top right movement is valid. 
						bool flagTL = checkTopLeft(board, x, y);

						if(flagTR && flagTL){									// If both flag is true than randomly choose one of them.
							short int moveType = rand() % 2;	
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
void cpuMove(vector<vector<pegState>>& board, short int op){	// Function makes random valid movement. 
	srand((time(0)));
	bool flag = false;
	char row, column;
	string strDir;
	direction dir;
	int i,j;		// i is row j is column.

	while(!flag){											// Iterate till valid command is generated.

		i = rand() % board.size();
		j = rand() % board[i].size();
		dir = static_cast<direction>(rand() % 4);

		flag = makeMove(board, j, i, dir, op);				// Check if generated command is valid.
	}

	row = static_cast<char>(j + static_cast<int>('A'));		// Casting the commands to characters. 
	column = static_cast<char>(i + static_cast<int>('0') + 1);
	
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
	cout << "\nMove " << row << column << "-" << strDir << " made by computer." << endl << endl;	// Printing the generated command.
}//End of function.
//================================================================================================================================

bool decryptString(string userMove, int& col, int& row, direction& dir){	// Function decrypts string input to usable variables. Returns as reference.
	bool ans = false, flag = false;
	int strLen = static_cast<int>(userMove.length());						// Taking the length of string input.

	if(strLen == 4 && userMove[2] == '-' && (userMove[1] >= '1' && userMove[1] <= '9')){			// First conditions for proper format.

		if(userMove[0] >= 'A' && userMove[0] <= 'Z'){						// Checking Letters.

			col = static_cast<int>(userMove[0]) - static_cast<int>('A');
			row = static_cast<int>(userMove[1]) - static_cast<int>('0') - 1;
			flag = true;
		}
		else if(userMove[0] >= 'a' && userMove[0] <= 'z'){

			col = static_cast<int>(userMove[0]) - static_cast<int>('a');
			row = static_cast<int>(userMove[1]) - static_cast<int>('0') - 1;
			flag = true;
		}

		if(flag){												// If previous conditions are true decrypt direction part.
			switch(userMove[3]){
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
	}
	return ans;
}//End of function.
//================================================================================================================================
bool checkLeft(const vector<vector<pegState>>& board, int col, int row, short int op){	// Function checks if left move is valid or invalid.
	int step;

	if(op != 6)			// If board is not triangular decrease the step.
		step = 2;
	else				// If it is triangular, then there is a wall between each peg, so step must be twice as others.
		step = 4;

	if(col-step >= 0 && board[row][col-step] == pegState::empty && board[row][col-step+step/2] == pegState::peg)	// Checking validity.
		return true;
	return false;
}//End of function.
//================================================================================================================================
bool checkRight(const vector<vector<pegState>>& board, int col, int row, int colBound, short int op){	// Function checks if right move is valid or invalid.
	int step;

	if(op != 6)			// If board is not triangular decrease the step.
		step = 2;
	else				// If it is triangular, then there is a wall between each peg, so step must be twice as others.
		step = 4;

	if(col+step < colBound && board[row][col+step] == pegState::empty && board[row][col+step-step/2] == pegState::peg)	// Checking validity.
		return true;
	return false;
}//End of function.
//================================================================================================================================

bool checkDown(const vector<vector<pegState>>& board, int col, int row, int rowBound){	// Function checks if down move is valid or invalid.
	if(row+2 < rowBound && board[row+2][col] == pegState::empty && board[row+1][col] == pegState::peg)	// Checking validity.
		return true;
	return false;
}//End of function.
//================================================================================================================================

bool checkUp(const vector<vector<pegState>>& board, int col, int row){	// Function checks if up move is valid or invalid.
	if(row-2 >= 0 && board[row-2][col] == pegState::empty && board[row-1][col] == pegState::peg)	// Checking validity.
		return true;
	return false;
}//End of function.
//================================================================================================================================

bool checkTopLeft(const vector<vector<pegState>>& board, int col, int row){					// Function checks if top left move is valid or invalid.
	if(col-2 >= 0 && row-2 >= 0 && board[row-2][col-2] == pegState::empty && board[row-1][col-1] == pegState::peg)	// Checking validity.
		return true;
	return false;
}//End of function.
//================================================================================================================================

bool checkTopRight(const vector<vector<pegState>>& board, int col, int row, int colBound){	// Function checks if top right move is valid or invalid.
	if(col+2 < colBound && row-2 >= 0 && board[row-2][col+2] == pegState::empty && board[row-1][col+1] == pegState::peg)
		return true;
	return false;
}//End of function.
//================================================================================================================================

bool checkBottomLeft(const vector<vector<pegState>>& board, int col, int row, int rowBound){ // Function checks if bottom left move is valid or invalid.
	if(col-2 >= 0 && row+2 < rowBound && board[row+2][col-2] == pegState::empty && board[row+1][col-1] == pegState::peg) // Checking validity.
		return true;
	return false;
}//End of function.
//================================================================================================================================

bool checkBottomRight(const vector<vector<pegState>>& board, int col, int row, int colBound, int rowBound){	// Function checks if bottom right move is valid or invalid.
	if(col+2 < colBound && row+2 < rowBound && board[row+2][col+2] == pegState::empty && board[row+1][col+1] == pegState::peg) // Checking validity.
		return true;
	return false;
}//End of function.
//================================================================================================================================

int countPeg(const vector<vector<pegState>>& board){		// Function counts how many pegs left.
	int rowBound = static_cast<int>(board.size());
	int colBound = static_cast<int>(board[0].size());
	int pegCounter = 0;

	for(int i = 0; i < rowBound; ++i){
		for(int j = 0; j < colBound; ++j){
			if(board[i][j] == pegState::peg)			// If peg is found increment counter.
				++pegCounter;
		}
	}
	return pegCounter;
}//End of function.
//================================================================================================================================

bool putPegHorizontal(vector<vector<pegState>>& board, int col, int row, short int op, direction dir){	// Function makes horizontal operations on board.
	int step;

	if(op != 6)			// If board is not triangular, step is 2.
		step = 2;
	else				// If board is triangular, step must be twice as bigger.
		step = 4;

	if(dir == direction::left)		// If direction is left step must be negative number.
		step *= -1;

	board[row][col+step-(step/2)] = board[row][col] = pegState::empty;		// Making the swap operation.
	board[row][col+step] = pegState::peg;

	return true;
}//End of function.
//================================================================================================================================

void putPegDiagonalUp(vector<vector<pegState>>& board, int col, int row, direction dir){ // Function makes upper diagonal movements.
	int step = 2;

	if(dir == direction::left)	// Deciding step size according to the direction
		step *= -1;

	board[row-1][col+step-step/2] = board[row][col] = pegState::empty;		// Making the swap operation.
	board[row-2][col+step] = pegState::peg;
}//End of function.
//================================================================================================================================

void putPegDiagonalDown(vector<vector<pegState>>& board, int col, int row, direction dir){	// Function makes upper diagonal movements.
	int step = 2;

	if(dir == direction::left)	// Deciding step size according to the direction
		step *= -1;

	board[row+1][col+step-step/2] = board[row][col] = pegState::empty;	// Making the swap operation.
	board[row+2][col+step] = pegState::peg;
}//End of function.
//================================================================================================================================