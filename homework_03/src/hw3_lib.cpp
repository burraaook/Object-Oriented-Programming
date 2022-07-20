/*
** hw3_lib.cpp:
**
** The source file is created for implementing library functions.
**
** Burak Kocausta 1901042605
** 
*/

#include "hw3_lib.h"
// Basic explanations of each function and constructor are in the header file.

int PegSolitaire::totalNumberOfPegs = 0;	// Total peg number in all PegSolitaire objects.

/*----------------------------------------------------------------------------------------*/
PegSolitaire::PegSolitaire(int BoardTypeVal) : 		numOfEmptyCell(1), numOfPegOut(0), EndState(false)
{ 
	if (BoardTypeVal >= 1 && BoardTypeVal <= 6) {
	    switch(BoardTypeVal){
	      case 1:
	          createEuropeanBoard();    		// All 6 option manipulates private board vector.
	          break;
	      case 2:
	          createWiegleBoard();
	          break;
	      case 3:
	          createAsymmetricalBoard();
	          break;
	      case 4:
	          createEnglishBoard();
	          break;
	      case 5:
	          createDiamondBoard();
	          break;
	      case 6:
	          createTriangularBoard();
	          break;
	    }
	   	rowBound = board.size();			// updating the other private member data.
		colBound = board[0].size();
		fillObjectPosition();				// Modifying each cell properly.
		boardType = BoardTypeVal;
		numOfPeg = countNumOfPeg();
	}
	else{
		cerr << "ERROR! Given board type input must be between 1 and 6. Object cannot be constructed. Terminating...\n\n";
		exit(1);
	}
}/*End of Constructor.*/
/*----------------------------------------------------------------------------------------*/
PegSolitaire::PegSolitaire(vector<vector<Cell>> newBoard) : boardType(8), EndState(false)
{
	auto ans = true;

	decltype(colBound) colBoundTemp;

	// Checking the vector inputs validity.
	if(newBoard.size() > 0){
		if(newBoard.size() < 5 && newBoard[0].size() < 5) ans = false;
		
		else
			colBoundTemp = newBoard[0].size(); 
	}
	else
		ans = false;

	for(decltype(rowBound) i = 0; i < newBoard.size() && ans; ++i){
		if(newBoard[i].size() != colBoundTemp)								// All inner vectors size must be equal.
			ans = false;

		for(decltype(colBound) j = 0; j < newBoard[i].size() && ans; ++j){	// Checking each cell.
			if(!(newBoard[i][j].getState() == pegState::peg || newBoard[i][j].getState() == pegState::empty ||
				newBoard[i][j].getState() == pegState::wall)){
				ans = false;
			}
		}
	}

	if(ans){
		board = newBoard;					// Updating the inner private data, if vector is valid.
		rowBound = board.size();
		colBound = board[0].size();
		fillObjectPosition();				// Modifying each cell properly.
		numOfPeg = countNumOfPeg();
		numOfEmptyCell = countNumOfEmptyCell();
		numOfPegOut = numOfEmptyCell - 1;
		if(numOfEmptyCell == 0){			// If there are empty cell in given vector, terminate program.
			cerr << "There MUST be at least 1 empty cell! Contruction failed! Terminating...\n";
			exit(1);
		} 
	}
	else{
		cerr << "Construction failed! Terminating...\n";
		exit(1);
	}
}/*End of Constructor.*/
/*----------------------------------------------------------------------------------------*/
// Constructor creates nxn square board included game.
PegSolitaire::PegSolitaire(int colBoundVal, int rowBoundVal) : boardType(7), numOfEmptyCell(1), numOfPegOut(0), EndState(false)
{ 
  	auto BoundFlag = (colBoundVal >= 5 && rowBoundVal >= 5 && colBoundVal <= 99 && rowBoundVal <= 99 && colBoundVal == rowBoundVal);

	if(BoundFlag){
		rowBound = static_cast<decltype(rowBound)>(rowBoundVal);
		colBound = static_cast<decltype(colBound)>(colBoundVal);
		
		board.resize(rowBound,vector<Cell>(colBound,Cell(pegState::peg)));	
		board[rowBoundVal/2][rowBoundVal/2] = Cell(pegState::empty);		// Putting an empty cell middle of the board.
		fillObjectPosition();
		numOfPeg = colBoundVal*rowBoundVal - 1;
	}
    else{
    	cerr << "ERROR! Given 2 integer input must be equal or bigger than 5. Only square board created with this constructor. Terminating...\n";
    	exit(1);
    }
}/*End of Constructor.*/
/*----------------------------------------------------------------------------------------*/
// Default constructor creates a default game.
PegSolitaire::PegSolitaire() : 	boardType(1), numOfEmptyCell(1), numOfPegOut(0), EndState(false)
{
	createEuropeanBoard();
	rowBound = board.size();
	colBound = board[0].size();
	fillObjectPosition();
	numOfPeg = countNumOfPeg();
}/*End of Constructor.*/
/*----------------------------------------------------------------------------------------*/

// Static function
int PegSolitaire::getTotalNumber() {
	return totalNumberOfPegs;
}//End of function.

void PegSolitaire::displayBoard() const{

	cout << endl << "   ";
	for(decltype(colBound) j = 0; j < colBound; ++j)		// Printing Alphabets for cols.
		cout << board[0][j].getColumn() << " ";

	cout << endl;
	for(decltype(rowBound) i = 0; i < rowBound; ++i){		// Printing the rest of the board.
		cout << board[i][0].getRow() << " ";

		for(decltype(rowBound) j = 0; j < colBound; ++j){
			cout << " ";
			switch(board[i][j].getState()){					// Print single block peg or empty(P,.).
				case pegState::peg:
					cout << "P";
					break;
				case pegState::empty:
					cout << ".";
					break;
				default:
					cout << " ";
			}//End of selection.						
		}
		cout << endl;
	}
	cout << endl;
}//End of function.

void PegSolitaire::setBoard(vector<vector<Cell>> newBoard){
	auto ans = true;

	decltype(colBound) colBoundTemp;

	// Checking the boards validity.
	if(newBoard.size() > 0){
		if(newBoard.size() < 5 && newBoard[0].size() < 5) ans = false;
		
		else
			colBoundTemp = newBoard[0].size(); 
	}
	else
		ans = false; 

	for(decltype(rowBound) i = 0; i < newBoard.size() && ans; ++i){
		if(newBoard[i].size() != colBoundTemp)
			ans = false;

		for(decltype(colBound) j = 0; j < board[i].size() && ans; ++j){		// Checking each cell.
			if(!(newBoard[i][j].getState() == pegState::peg || newBoard[i][j].getState() == pegState::empty ||
				newBoard[i][j].getState() == pegState::wall)){
				ans = false;
			}
		}
	}

	if(ans){
		board = newBoard;							// If board is valid, update other inner private data.
		rowBound = board.size();
		colBound = board[0].size();
		fillObjectPosition();
		numOfPeg = countNumOfPeg();
		numOfEmptyCell = countNumOfEmptyCell();
		numOfPegOut = numOfEmptyCell - 1;
		boardType = 8;
		EndState = false;
	}
	else
		cerr << "Error! Given vector failed to be set! Create the vector properly.\n";
}//End of function.

bool PegSolitaire::loadFile(const string& userInput){
	ifstream inFile;

	auto ans = true;	// this will be returned.
	
	if(userInput.length() > 5 && 
	  (userInput.compare(0,5,"LOAD ") == 0 || userInput.compare(0,5,"load ") == 0)){	// Checking input strings validity.

		int userType;
		decltype(rowBound) tempRowBound = 0, tempColBound = 0;

		inFile.open(userInput.substr(5,userInput.length()-5));

		if(inFile.is_open()){
									// Each data will be read from board is stored in a an temporary integer vector, before updating.
			vector<int> keyVariables(5,0);	
			vector<string> keyStrings {"usertype = ", "boardType = ", "rowBound = ", "colBound = ", "number of moves = "};
				
			string line;

			for(int i = 0; i < 5 && ans; ++i){
				if(getline(inFile, line)){
					correctCR(line);		// Deletes carriage return character from line.
					ans = readIntFromLine(line, keyStrings[i], keyVariables[i]);
				}
				else
					ans = false;
			}
			
			tempRowBound = static_cast<decltype(rowBound)>(keyVariables[2]);
			tempColBound = static_cast<decltype(colBound)>(keyVariables[3]);

			// Creating temporary board, before reading from file.
			vector<vector<Cell>> temp_board(tempRowBound, vector<Cell>(tempColBound, pegState::wall));
			
			if(ans && tempRowBound >= 5 && tempRowBound <= 99 && tempColBound >= 5 && tempColBound <= 99)	
				ans = readBoardFromFile(temp_board, inFile, tempColBound, tempRowBound);
			else
				ans = false;

			if(ans){
				subtractPegFromTotal();		// Delete old board's peg number from static variable.
				board = temp_board;
				rowBound = tempRowBound;
				colBound = tempColBound;
				userType = keyVariables[0];
				boardType = keyVariables[1];
				numOfPegOut = keyVariables[4];
				numOfPeg = countNumOfPeg();
				numOfEmptyCell = countNumOfEmptyCell();
				addPegToTotal();
				fillObjectPosition();
			}
			inFile.close();
		}
		else
			ans = false;

		if(ans && userType == 1){	// If loaded game is a computer game play game automatically.
			cout << "Computer game loaded from file! Board is: \n";
			displayBoard();
			playCurrentGame();
		}		
	}
	else
		ans = false;

	return ans;
}//End of function.

bool PegSolitaire::saveFile(const string& userInput) const{
	ofstream outFile;
	
	auto ans = true;

	if (userInput.length() > 5 && 
	   (userInput.compare(0,5,"SAVE ") == 0 || userInput.compare(0,5,"save ") == 0)) {

	   	outFile.open(userInput.substr(5,userInput.length()-5));
		int userType = 2;
		if(outFile.is_open()){		

			outFile << "usertype = " << userType << endl << "boardType = " << boardType << endl
					<< "rowBound = " << rowBound << endl
					<< "colBound = " << colBound << endl
					<< "number of moves = " << numOfPegOut << endl;

			for(decltype(rowBound) i = 0; i < rowBound; ++i){						
				for(decltype(colBound) j = 0; j < colBound; ++j){
						switch(board[i][j].getState()){						// Selecting the proper letter.
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
			outFile.close();
		}
		else
			ans = false;
	}
	else
		ans = false;

	return ans;	
}//End of function.

bool PegSolitaire::play(){
	srand((static_cast<unsigned int>(time(NULL))));
	auto flag = false;
	string strDir;
	direction dir;
	int i,j;			// i is row j is col.

	while(!flag){													// Iterate till valid command is generated.

		i = rand() % rowBound;
		j = rand() % colBound;
		dir = static_cast<decltype(dir)>(rand() % 4);

		flag = makeMove(j, i, dir);						// Check if generated command is valid.
	}
	decrementTotal();				// subtracts 1 from static variable

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
	cout << "\nMove " << board[i][j].getColumn() << board[i][j].getRow() << "-" << strDir << " made by computer." << endl << endl;	// Printing the generated command.
	return flag;
}//End of function.

bool PegSolitaire::play(const string& command){
	direction dir;
	int col,row;
	auto ans = false;
	
	if(decryptString(command, col, row, dir)){
		ans = makeMove(col, row, dir);
	}
	if(ans)
		decrementTotal();

	return ans;
}//End of function.

void PegSolitaire::playGame(){
	auto flag = boardTypeInput();
	if(flag)
		playCurrentGame();
	else
		cerr << "Input cannot be taken! Some error occured!" << endl;
}//End of function.

void PegSolitaire::playCurrentGame(){	
	while(!isEnd()){
	 	play();
	 	displayBoard();
	}
}//End of function.

bool PegSolitaire::compareGames(const PegSolitaire& otherGame) const{
	auto ans = false;

	if(getNumOfPeg() >= otherGame.getNumOfPeg())
		ans = true;

	return ans;
}//End of function.

bool PegSolitaire::boardTypeInput(){
	
	bool inputFlag;
	do{									// This loop takes proper input for boards.
		cout << "Which board for the game?\n1 - French (European) style, 37 holes\n2 - J. C. Wiegleb, Germany, 45 holes" << endl
			 << "3 - Asymmetrical 3-3-2-2 as described by George Bell\n4 - English style (standard), 33 holes" << endl 
			 << "5 - Diamond, 41 holes\n6 - Triangular, 15 holes\nInput(1-6): ";

		string userInput;
		
		inputFlag = false;

		getline(cin,userInput);
		correctCR(userInput);

		if(userInput.length() == 1){
			int tempType = static_cast<decltype(tempType)>(userInput[0]) - static_cast<decltype(tempType)>('0');
			inputFlag = (tempType >= 1 && tempType <= 6);
			if(inputFlag)
				boardType = tempType;
		}
	
		if(!inputFlag)
			cerr << "Wrong input! Please enter the numbers given next to the board name." << endl << endl;

	}while(!inputFlag);					// Iterates till proper input is entered.

	switch(boardType){						// Selecting the operation according to type of board. Functions return vector.
		case 1:
			createEuropeanBoard();		
			break;
		case 2:
			createWiegleBoard();
			break;
		case 3:
			createAsymmetricalBoard();
			break;
		case 4:
			createEnglishBoard();
			break;
		case 5:
			createDiamondBoard();
			break;
		case 6:
			createTriangularBoard();
			break;
	} // End of selection
	
   	rowBound = board.size();				// updating values
	colBound = board[0].size();
	fillObjectPosition();
	subtractPegFromTotal();
	numOfPeg = countNumOfPeg();
	addPegToTotal();
	numOfEmptyCell = countNumOfEmptyCell();
	numOfPegOut = 0;
	EndState = false;

	return inputFlag;
}//End of function.

int PegSolitaire::countNumOfPeg(){
	decltype(numOfPeg) counter = 0;

	for(decltype(rowBound) i = 0; i < rowBound; ++i){
		for(decltype(colBound) j = 0; j < colBound; ++j){
			if(board[i][j].getState() == pegState::peg)
				++counter;
		}
	}

	numOfPeg = counter;
	return counter;
}//End of function.

int PegSolitaire::countNumOfEmptyCell(){
	decltype(numOfEmptyCell) counter = 0;

	for(decltype(rowBound) i = 0; i < rowBound; ++i){
		for(decltype(colBound) j = 0; j < colBound; ++j){
			if(board[i][j].getState() == pegState::empty)
				++counter;
		}
	}

	numOfEmptyCell = counter;
	return counter;
}//End of function.

void PegSolitaire::fillObjectPosition(){
	for(int i = 0; static_cast<decltype(rowBound)>(i) < rowBound; ++i){
		for(int j = 0; static_cast<decltype(colBound)>(j) < colBound; ++j){
			if(j < 27)
				board[i][j].setPosition('A' + j, i+1);
			else
				board[i][j].setPosition('-', i+1);
		}
	}
}//End of function.

void PegSolitaire::createEuropeanBoard(){

	vector<vector<Cell>> temp_board
	{
		{ Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::peg),
		 Cell(pegState::peg),   Cell(pegState::peg),  Cell(pegState::wall), Cell(pegState::wall)},
		{ Cell(pegState::wall), Cell(pegState::peg),  Cell(pegState::peg), 
		 Cell(pegState::peg),   Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::wall)},
		{ Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::peg), 
		 Cell(pegState::empty), Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::peg)},
		{ Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::peg), 
		 Cell(pegState::peg),   Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::peg)},
		{ Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::peg), 
 		 Cell(pegState::peg),   Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::peg)},
		{ Cell(pegState::wall), Cell(pegState::peg),  Cell(pegState::peg), 
		 Cell(pegState::peg),   Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::wall)},
		{ Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::peg), 
		 Cell(pegState::peg),   Cell(pegState::peg),  Cell(pegState::wall), Cell(pegState::wall)}
	};

	board = temp_board;
}//End of function.

void PegSolitaire::createWiegleBoard(){
	vector<vector<Cell>> temp_board
	{
		{ Cell(pegState::wall),  Cell(pegState::wall), Cell(pegState::wall), 
		Cell(pegState::peg), Cell(pegState::peg),  Cell(pegState::peg), Cell(pegState::wall),  Cell(pegState::wall),  Cell(pegState::wall)},
		{ Cell(pegState::wall),  Cell(pegState::wall), Cell(pegState::wall), 
		Cell(pegState::peg), Cell(pegState::peg),  Cell(pegState::peg), Cell(pegState::wall),  Cell(pegState::wall),  Cell(pegState::wall)},
		{ Cell(pegState::wall),  Cell(pegState::wall), Cell(pegState::wall), 
		Cell(pegState::peg), Cell(pegState::peg),  Cell(pegState::peg), Cell(pegState::wall),  Cell(pegState::wall),  Cell(pegState::wall)},
		{ Cell(pegState::peg),   Cell(pegState::peg),  Cell(pegState::peg), 
		Cell(pegState::peg), Cell(pegState::peg),  Cell(pegState::peg), Cell(pegState::peg),   Cell(pegState::peg),   Cell(pegState::peg)},  
		{ Cell(pegState::peg),   Cell(pegState::peg),  Cell(pegState::peg), 
		Cell(pegState::peg), Cell(pegState::empty),Cell(pegState::peg), Cell(pegState::peg),   Cell(pegState::peg),   Cell(pegState::peg)},
		{ Cell(pegState::peg),   Cell(pegState::peg),  Cell(pegState::peg), 
		Cell(pegState::peg), Cell(pegState::peg),  Cell(pegState::peg), Cell(pegState::peg),   Cell(pegState::peg),   Cell(pegState::peg)},
		{ Cell(pegState::wall),  Cell(pegState::wall), Cell(pegState::wall), 
		Cell(pegState::peg), Cell(pegState::peg),  Cell(pegState::peg), Cell(pegState::wall),  Cell(pegState::wall),  Cell(pegState::wall)},
		{ Cell(pegState::wall),  Cell(pegState::wall), Cell(pegState::wall), 
		Cell(pegState::peg), Cell(pegState::peg),  Cell(pegState::peg), Cell(pegState::wall),  Cell(pegState::wall),  Cell(pegState::wall)},
		{ Cell(pegState::wall),  Cell(pegState::wall), Cell(pegState::wall), 
		Cell(pegState::peg), Cell(pegState::peg),  Cell(pegState::peg), Cell(pegState::wall),  Cell(pegState::wall),  Cell(pegState::wall)}
	};
	board = temp_board;
}//End of function.

void PegSolitaire::createAsymmetricalBoard(){

	vector<vector<Cell>> temp_board
	{
		{ Cell(pegState::wall), Cell(pegState::wall),  Cell(pegState::peg), 
		Cell(pegState::peg), 	Cell(pegState::peg),   Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::wall) },
		{ Cell(pegState::wall), Cell(pegState::wall),  Cell(pegState::peg), 
		Cell(pegState::peg), 	Cell(pegState::peg),   Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::wall) },
		{ Cell(pegState::wall), Cell(pegState::wall),  Cell(pegState::peg), 
		Cell(pegState::peg), 	Cell(pegState::peg),   Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::wall) },
		{ Cell(pegState::peg),  Cell(pegState::peg),   Cell(pegState::peg), 
		Cell(pegState::peg),   	Cell(pegState::peg),   Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::peg)  },  
		{ Cell(pegState::peg),  Cell(pegState::peg),   Cell(pegState::peg), 
		Cell(pegState::empty),  Cell(pegState::peg),   Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::peg)  },
		{ Cell(pegState::peg),  Cell(pegState::peg),   Cell(pegState::peg), 
		Cell(pegState::peg),   	Cell(pegState::peg),   Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::peg)  },
		{ Cell(pegState::wall), Cell(pegState::wall),  Cell(pegState::peg), 
		Cell(pegState::peg), 	Cell(pegState::peg),   Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::wall) },
		{ Cell(pegState::wall), Cell(pegState::wall),  Cell(pegState::peg), 
		Cell(pegState::peg), 	Cell(pegState::peg),   Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::wall) }	
	};

	board = temp_board;
}//End of function.

void PegSolitaire::createEnglishBoard(){
	vector<vector<Cell>> temp_board
	{

		{ Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::peg), 
		Cell(pegState::peg),    Cell(pegState::peg),  Cell(pegState::wall), Cell(pegState::wall)},
		{ Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::peg), 
		Cell(pegState::peg),    Cell(pegState::peg),  Cell(pegState::wall), Cell(pegState::wall)},
		{ Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::peg), 
		Cell(pegState::peg),    Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::peg)},
		{ Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::peg), 
		Cell(pegState::empty),  Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::peg)},
		{ Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::peg), 
		Cell(pegState::peg),    Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::peg)},
		{ Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::peg), 
		Cell(pegState::peg),    Cell(pegState::peg),  Cell(pegState::wall), Cell(pegState::wall)},
		{ Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::peg),
		Cell(pegState::peg),    Cell(pegState::peg),  Cell(pegState::wall), Cell(pegState::wall)}
	};

	board = temp_board;
}//End of function.

void PegSolitaire::createDiamondBoard(){
	vector<vector<Cell>> temp_board
	{
		{ Cell(pegState::wall),  Cell(pegState::wall),  Cell(pegState::wall), 
		Cell(pegState::wall), 	 Cell(pegState::peg), 	Cell(pegState::wall),  Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::wall)},
		{ Cell(pegState::wall),  Cell(pegState::wall),  Cell(pegState::wall), 
		Cell(pegState::peg), 	 Cell(pegState::peg), 	Cell(pegState::peg),   Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::wall)},
		{ Cell(pegState::wall),  Cell(pegState::wall),  Cell(pegState::peg), 
		Cell(pegState::peg), 	 Cell(pegState::peg), 	Cell(pegState::peg),   Cell(pegState::peg),  Cell(pegState::wall), Cell(pegState::wall)},
		{ Cell(pegState::wall),  Cell(pegState::peg),  	Cell(pegState::peg), 
		Cell(pegState::peg),   	 Cell(pegState::peg), 	Cell(pegState::peg),   Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::wall)},  
		{ Cell(pegState::peg),   Cell(pegState::peg),  	Cell(pegState::peg), 
		Cell(pegState::peg),   	 Cell(pegState::empty), Cell(pegState::peg),   Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::peg)},
		{ Cell(pegState::wall),  Cell(pegState::peg),  	Cell(pegState::peg), 
		Cell(pegState::peg),   	 Cell(pegState::peg), 	Cell(pegState::peg),   Cell(pegState::peg),  Cell(pegState::peg),  Cell(pegState::wall)},
		{ Cell(pegState::wall),  Cell(pegState::wall),  Cell(pegState::peg), 
		Cell(pegState::peg), 	 Cell(pegState::peg), 	Cell(pegState::peg),   Cell(pegState::peg),  Cell(pegState::wall), Cell(pegState::wall)},
		{ Cell(pegState::wall),  Cell(pegState::wall),  Cell(pegState::wall), 
		Cell(pegState::peg), 	 Cell(pegState::peg), 	Cell(pegState::peg),   Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::wall)},
		{ Cell(pegState::wall),  Cell(pegState::wall),  Cell(pegState::wall), 
		Cell(pegState::wall), 	 Cell(pegState::peg), 	Cell(pegState::wall),  Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::wall)}
	};

	board = temp_board;
}//End of function.

void PegSolitaire::createTriangularBoard(){
	vector<vector<Cell>> temp_board
	{	
		{Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::wall), 
		Cell(pegState::empty), Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::wall)},
		{Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::peg), 
		Cell(pegState::wall),  Cell(pegState::peg),  Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::wall)},
		{Cell(pegState::wall), Cell(pegState::wall), Cell(pegState::peg),  Cell(pegState::wall), 
		Cell(pegState::peg),   Cell(pegState::wall), Cell(pegState::peg),  Cell(pegState::wall), Cell(pegState::wall)},
		{Cell(pegState::wall), Cell(pegState::peg),  Cell(pegState::wall), Cell(pegState::peg), 
		Cell(pegState::wall),  Cell(pegState::peg),  Cell(pegState::wall), Cell(pegState::peg),  Cell(pegState::wall)},
		{Cell(pegState::peg),  Cell(pegState::wall), Cell(pegState::peg),  Cell(pegState::wall), 
		Cell(pegState::peg),   Cell(pegState::wall), Cell(pegState::peg),  Cell(pegState::wall), Cell(pegState::peg)}
	};

	board = temp_board;
}//End of function.

bool PegSolitaire::isEnd(){
	auto flag = true;

	for(int i = 0; static_cast<decltype(rowBound)>(i) < rowBound && flag; ++i){
		
		for(int j = 0; static_cast<decltype(rowBound)>(j) < colBound && flag; ++j){

			if(board[i][j].getState() == pegState::peg){
				
				if(boardType != 6){		// If board is not triangular make different checks.
					if(checkUp(j,i) || checkDown(j,i) || checkLeft(j, i) || checkRight(j, i))
						flag = false;
				}
				else{				// If board is triangular there are 6 checkings.
					if(checkTopLeft(j, i) || checkBottomLeft(j, i) ||  
					   checkTopRight(j, i) || checkBottomRight(j, i) ||
					   checkLeft(j, i) || checkRight(j, i)){
							flag = false;
					}
				}
			}	
		}
	}
	EndState = flag;
	return EndState;
}//End of function.

// x is colummn, y is row.
bool PegSolitaire::makeMove(const int& x,const int& y,const direction& dir){
	auto flag = false;

	if(static_cast<decltype(rowBound)>(y) < rowBound && static_cast<decltype(colBound)>(x) < colBound){// Checking the initial conditions.

		if(board[y][x].getState() == pegState::peg){			// Given indexes must be represent the peg.

			switch(dir){										// Selecting functions or making operations according to the direction.
				case direction::left:
					if(checkLeft(x, y)){
						putPegHorizontal(x, y, direction::left);
						flag = true;
					}
				
					break;
				case direction::right:
					if(checkRight(x, y)){
						putPegHorizontal(x, y, direction::right);	
						flag = true;
					}
					break;
				case direction::down:
					if(boardType != 6 && checkDown(x, y)){
						board[y][x].setState(pegState::empty);
						board[y+1][x].setState(pegState::empty);	
						board[y+2][x].setState(pegState::peg);
						flag = true;
					}
					else if(boardType == 6){		// If it is triangular board, make diagonal moves.
						
						auto flagBR = checkBottomRight(x, y);	// Check if bottom right move is valid. 
						auto flagBL = checkBottomLeft(x, y);

						if(flagBR && flagBL){									// If both flag is true than randomly choose one of them.
							int moveType = rand() % 2;
							flag = true;

							if(moveType == 1)
								putPegDiagonalDown(x, y, direction::right);
							else
								putPegDiagonalDown(x, y, direction::left);		
						} 
						else if(flagBR){										// If both of them is not true, chose valid one.
							putPegDiagonalDown(x, y, direction::right);
							flag = true;
						}
						else if(flagBL){
							putPegDiagonalDown(x, y, direction::left);
							flag = true;
						}
					}
					break;
				case direction::up:
					if(boardType != 6 && checkUp(x, y)){
						board[y][x].setState(pegState::empty);
						board[y-1][x].setState(pegState::empty);
						board[y-2][x].setState(pegState::peg);
						flag = true;
					}
					else if(boardType == 6){		// If it is triangular board, make diagonal moves.

						bool flagTR = checkTopRight(x, y);		// Check if top right movement is valid. 
						bool flagTL = checkTopLeft(x, y);

						if(flagTR && flagTL){									// If both flag is true than randomly choose one of them.
							int moveType = rand() % 2;	
							flag = true;

							if(moveType == 1)
								putPegDiagonalUp(x, y, direction::right);		
							else
								putPegDiagonalUp(x, y, direction::left);		
						}
						else if(flagTR){										// If both of them is not true, chose valid one.
							putPegDiagonalUp(x, y, direction::right);
							flag = true;
						}
						else if(flagTL){
							putPegDiagonalUp(x, y, direction::left);
							flag = true;
						}
					}
			}// End of selection.
		}
	}

	if(flag){
		--numOfPeg;
		++numOfEmptyCell;
		++numOfPegOut;
		isEnd();
	}
	return flag;
}//End of function.

bool PegSolitaire::checkLeft(const int& col,const int& row) const{	
	int step = 2;

	if(boardType == 6)			// If it is triangular, then there is a wall between each peg, so step must be twice as others.
		step = 4;

	if(col >= step && board[row][col-step].getState() == pegState::empty && board[row][col-step+step/2].getState() == pegState::peg)	// Checking validity.
		return true;
	return false;
}//End of function.


bool PegSolitaire::checkRight(const int& col, const int& row) const{	
	int step = 2;
	
	if(boardType == 6)			// If it is triangular, then there is a wall between each peg, so step must be twice as others.
		step = 4;

	if(static_cast<decltype(colBound)>(col+step) < colBound && board[row][col+step].getState() == pegState::empty && board[row][col+step-step/2].getState() == pegState::peg)	// Checking validity.
		return true;
	return false;
}//End of function.

bool PegSolitaire::checkDown(const int& col,const int& row) const{	
	if(static_cast<decltype(rowBound)>(row+2) < rowBound && board[row+2][col].getState() == pegState::empty && board[row+1][col].getState() == pegState::peg)
		return true;
	return false;
}//End of function.

bool PegSolitaire::checkUp(const int& col,const int& row) const{
	if(row >= 2 && board[row-2][col].getState() == pegState::empty && board[row-1][col].getState() == pegState::peg)	// Checking validity.
		return true;
	return false;
}//End of function.

bool PegSolitaire::checkTopLeft(const int& col,const int& row) const{
	if(col >= 2 && row >= 2 && board[row-2][col-2].getState() == pegState::empty && board[row-1][col-1].getState() == pegState::peg)
		return true;
	return false;
}//End of function.

bool PegSolitaire::checkTopRight(const int& col,const int& row) const{	
	if(static_cast<decltype(colBound)>(col+2) < colBound && row >= 2 && board[row-2][col+2].getState() == pegState::empty && board[row-1][col+1].getState() == pegState::peg)
		return true;
	return false;
}//End of function.

bool PegSolitaire::checkBottomLeft(const int& col,const int& row) const{ 
	if(col >= 2 && static_cast<decltype(rowBound)>(row+2) < rowBound && board[row+2][col-2].getState() == pegState::empty && board[row+1][col-1].getState() == pegState::peg) // Checking validity.
		return true;
	return false;
}//End of function.

bool PegSolitaire::checkBottomRight(const int& col,const int& row) const{
	if(static_cast<decltype(colBound)>(col+2) < colBound && static_cast<decltype(rowBound)>(row+2) < rowBound && board[row+2][col+2].getState() == pegState::empty && board[row+1][col+1].getState() == pegState::peg) // Checking validity.
		return true;
	return false;
}//End of function.

// Function makes horizontal operations on board.
void PegSolitaire::putPegHorizontal(const int& col,const int& row,const direction& dir){
	int step = 2;
	if(boardType == 6)				// If board is triangular, step must be twice as bigger.
		step = 4;

	if(dir == direction::left){
		board[row][col-step+(step/2)].setState(pegState::empty);
		board[row][col].setState(pegState::empty);		// Making the swap operation.
		board[row][col-step].setState(pegState::peg);
	}
	else{
		board[row][col+step-(step/2)].setState(pegState::empty);
		board[row][col].setState(pegState::empty);		// Making the swap operation.
		board[row][col+step].setState(pegState::peg);		
	}
}//End of function.

// Function makes upper diagonal movements.
void PegSolitaire::putPegDiagonalUp(const int& col, const int& row, const direction& dir){ 
	int step = 2;

	if(dir == direction::left){
		board[row-1][col-step+step/2].setState(pegState::empty);
		board[row][col].setState(pegState::empty);					// Making the swap operation.
		board[row-2][col-step].setState(pegState::peg);
	}
	else if(dir == direction::right){

		board[row-1][col+step-step/2].setState(pegState::empty);
		board[row][col].setState(pegState::empty);					// Making the swap operation.
		board[row-2][col+step].setState(pegState::peg);
	}
}//End of function.

// Function makes upper diagonal movements.
void PegSolitaire::putPegDiagonalDown(const int& col, const int& row, const direction& dir){	
	int step = 2;

	if(dir == direction::left){
		board[row+1][col-step+step/2].setState(pegState::empty);
		board[row][col].setState(pegState::empty);					// Making the swap operation.
		board[row+2][col-step].setState(pegState::peg);
	}
	else if(dir == direction::right){
		board[row+1][col+step-step/2].setState(pegState::empty);
		board[row][col].setState(pegState::empty);					// Making the swap operation.
		board[row+2][col+step].setState(pegState::peg);
	}
}//End of function.

// Function decrypts string input to usable variables. Returns as a reference.
bool PegSolitaire::decryptString(string userMove, int& col, int& row, direction& dir) const{	
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

bool PegSolitaire::readIntFromLine(string line, string name, int& givenType) const{
	auto flag = false;

	auto lenLine = line.length();	// Taking the boundaries.
	auto lenName = name.length();

	if(lenLine >= lenName + 1 && line.compare(0, lenName , name) == 0){

		string numStr = line.substr(lenName, lenLine-1);	// Taking the integer string.
		flag = convertAssignStr(numStr, givenType);			// Function converts string to integer.
	}
	return flag;
}//End of function.

// Function converts string to integer.
bool PegSolitaire::convertAssignStr(string numStr, int& givenType) const{
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

// Function checks and removes from CR character from end of the given string.
void PegSolitaire::correctCR(string& buffer) const{
	if(buffer.length() > 0){
		if(buffer[buffer.length()-1] == '\r')
			buffer.pop_back();
	}
}//End of function.


bool PegSolitaire::readBoardFromFile(vector<vector<Cell>>& temp_board, ifstream& inFile, const size_t& tempColBound, const size_t& tempRowBound) const{
	string line;
	auto ans = true;

	for(decltype(rowBound) i = 0; ans && i < tempRowBound; ++i){	// Read according to the boundaries.

		if(getline(inFile, line)){

			correctCR(line);

			auto lenLine = line.length();
			if(lenLine > tempColBound)
				ans = false;
			for(decltype(lenLine) j = 0; ans && j < lenLine; ++j){

				switch(line[j]){	// Take pegState according to the character written.
					case 'P':
					case 'p':
						temp_board[i][j].setState(pegState::peg);
						break;
					case '.':
						temp_board[i][j].setState(pegState::empty);
						break;
					case ' ':
						temp_board[i][j].setState(pegState::wall);
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