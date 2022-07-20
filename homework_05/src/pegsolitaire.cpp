/*
** pegsolitaire.cpp:
**
** The implementation file is created for implementing PegSolitaire class functions.
**
** Burak Kocausta 1901042605
** 
*/

#include "pegsolitaire.h"
#include <random>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>

namespace // unnamed namespace for some helper functions used in implementation.
{
	int countNumOfPeg (const std::vector<std::vector<GameGTU::PegSolitaire::Cell>>& board) 
	{
		int counter = 0;
		auto rowBound = board.size( );
		auto colBound = board[0].size( );

		for (decltype(rowBound) i = 0; i < rowBound; ++i)
			for (decltype(colBound) j = 0; j < colBound; ++j)
				if (board[i][j].getState( ) == pegState::peg)
					++counter;

		return counter;	
	}
	void fillObjectPosition (std::vector<std::vector<GameGTU::PegSolitaire::Cell>>& board)
	{
		auto rowBound = board.size( );
		auto colBound = board[0].size( );
		for (decltype(rowBound) i = 0; i < rowBound; ++i)
		{
			for (decltype(colBound) j = 0; j < colBound; ++j)
			{
				if (j < 27)
					board[i][j].setPosition('A' + j, i+1);
				else
					board[i][j].setPosition('-', i+1);
			}
		}
	}//End of function.
	bool makeMove (std::vector<std::vector<GameGTU::PegSolitaire::Cell>>& board, int col, int row, direction dir)
	{
		auto rowBound = board.size( );
		auto colBound = board[0].size( );
		auto flag = false;

		if (row < rowBound && col < colBound){					// Check the initial conditions.

			if (board[row][col].getState() == pegState::peg)		// Given indexes must be represent the peg.
			{	
				switch(dir) 									// Select functions or make operations according to the direction.
				{									
				case direction::left:
					if (col >= 2 && board[row][col-2].getState() == pegState::empty && board[row][col-1].getState() == pegState::peg)
					{
						board[row][col-1].setState(pegState::empty);
						board[row][col].setState(pegState::empty);
						board[row][col-2].setState(pegState::peg);		
						flag = true;
					}		
					break;
				case direction::right:
					if (col+2 < colBound && board[row][col+2].getState() == pegState::empty && board[row][col+1].getState() == pegState::peg)
					{
						board[row][col+1].setState(pegState::empty);
						board[row][col].setState(pegState::empty);
						board[row][col+2].setState(pegState::peg);		
						flag = true;
					}
					break;
				case direction::down:
					if (row+2 < rowBound && board[row+2][col].getState() == pegState::empty && board[row+1][col].getState() == pegState::peg)
					{
						board[row][col].setState(pegState::empty);
						board[row+1][col].setState(pegState::empty);	
						board[row+2][col].setState(pegState::peg);
						flag = true;
					}
					break;
				case direction::up:
					if (row >= 2 && board[row-2][col].getState() == pegState::empty && board[row-1][col].getState() == pegState::peg)
					{
						board[row][col].setState(pegState::empty);
						board[row-1][col].setState(pegState::empty);
						board[row-2][col].setState(pegState::peg);
						flag = true;
					}
					break;
				}
			}		
		}
		return flag;
	}

	bool decryptString (std::string userMove, int& col, int& row, direction& dir) 
	{
		auto flag = false;
		auto strLen = userMove.length();				// Taking the length of string input.
		auto dirVar = '-';
		if (strLen > 0)
		{
			if (userMove[0] >= 'A' && userMove[0] <= 'Z')
			{
				col = static_cast<int>(userMove[0]) - static_cast<int>('A');
				flag = true;
			}
			else if (userMove[0] >= 'a' && userMove[0] <= 'z')
			{
				col = static_cast<int>(userMove[0]) - static_cast<int>('a');
				flag = true;
			}
		}

		if (flag)
		{
			if (strLen >= 4)	// check all possible direction commands.
			{
				std::string temp = userMove.substr(3,strLen-1);	
				if (temp == "UP" || temp == "DOWN" || temp == "LEFT" || temp == "RIGHT" ||
				   temp == "up" || temp == "down" || temp == "left" || temp == "right" ||
				   temp == "U"  || temp == "D"    || temp == "L"    || temp == "R"     ||
				   temp == "u"  || temp == "d"    || temp == "l"    || temp == "r"     ) 
				{
					dirVar = userMove[3];
				}
				else 
					flag = false;	
				
				if (userMove[1] >= '0' && userMove[1] <= '9')
				{
					row = static_cast<int>(userMove[1]) - static_cast<int>('0');
					row--;
				}

				else
					flag = false;
			}
			else
				flag = false;		
		}
		if (flag)
		{
			switch(dirVar)
			{
				case 'R':
				case 'r':
					dir = direction::right;
					break;
				case 'L':
				case 'l':
					dir = direction::left;
					break;
				case 'U':
				case 'u':
					dir = direction::up;
					break;
				case 'D':
				case 'd':
					dir = direction::down;
					break;
			}// End of selection.		
		}
		return flag;
	}
}// End of unnamed namespace.
namespace GameGTU 
{
	PegSolitaire::PegSolitaire( ) : EndState_(false)
	{
		std::vector<std::vector<Cell>> tempBoard
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

		board_ = tempBoard;
		auto rowBound = board_.size( );
		auto colBound = board_[0].size( );

		fillObjectPosition(board_);		// fill the informations of each cell.
		for (decltype(rowBound) i = 0; i < rowBound; ++i) 
		{
			for (decltype(colBound) j = 0;j < colBound; ++j) 
			{
				if (j < 27)
					board_[i][j].setPosition('A' + j, i+1);
				else
					board_[i][j].setPosition('-', i+1);
			}
		}
		numOfPeg_ = countNumOfPeg(board_);
	}/*End of Constructor.*/
	
	PegSolitaire::~PegSolitaire( ) 
	{
		// intentionally empty
	}

	void PegSolitaire::print( ) const 
	{
		std::cout << "\033[H\033[J";
		auto rowBound = board_.size( );
		auto colBound = board_[0].size( );
		
		std::cout << "   ";
		for (decltype(colBound) j = 0; j < colBound; ++j)		// Printing Alphabets for cols.
			std::cout << board_[0][j].getColumn( ) << " ";

		std::cout << std::endl;
		for (decltype(rowBound) i = 0; i < rowBound; ++i){		// Printing the rest of the board.
			std::cout << board_[i][0].getRow( ) << " ";

			for (decltype(rowBound) j = 0; j < colBound; ++j){
				std::cout << " ";
				switch(board_[i][j].getState( )){					// Print single block peg or empty(P,.).
					case pegState::peg:
						std::cout << "P";
						break;
					case pegState::empty:
						std::cout << ".";
						break;
					default:
						std::cout << " ";
				}//End of selection.						
			}
			std::cout << std::endl;
		}
		std::cout << "\n_____Peg Solitaire Game_____\n" << std::endl;
		std::cout << std::endl;			
	}

	std::ostream& PegSolitaire::print (std::ostream& outs) const
	{
		auto rowBound = board_.size( );
		auto colBound = board_[0].size( );
		
		outs << "   ";
		for (decltype(colBound) j = 0; j < colBound; ++j)		// Printing Alphabets for cols.
			outs << board_[0][j].getColumn( ) << " ";

		outs << std::endl;
		for (decltype(rowBound) i = 0; i < rowBound; ++i){		// Printing the rest of the board.
			outs << board_[i][0].getRow( ) << " ";

			for (decltype(rowBound) j = 0; j < colBound; ++j){
				outs << " ";
				switch(board_[i][j].getState( )){					// Print single block peg or empty(P,.).
					case pegState::peg:
						outs << "P";
						break;
					case pegState::empty:
						outs << ".";
						break;
					default:
						outs << " ";
				}//End of selection.						
			}
			outs << std::endl;
		}
		outs << "\n_____Peg Solitaire Game_____\n" << std::endl;
		outs << std::endl;
		return outs;		
	}
	void PegSolitaire::playAuto( ) 
	{
		auto rowBound = board_.size( );
		auto colBound = board_[0].size( );

		auto flag = false;
		direction dir;
		int gRow, gCol;			// i is row j is col.

		endGame();
		while(!flag && !EndState_)
		{															// Iterate till valid command is generated.
			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> gRow(0,rowBound-1);
			std::uniform_int_distribution<std::mt19937::result_type> gCol(0,colBound-1);
			
			for (int i = 0; i < 4 && !flag; ++i)
			{
				dir = static_cast<decltype(dir)>(i);
				flag = makeMove(board_, gCol(rng), gRow(rng), dir);			// Check if generated command is valid.
			}
		}
	}
	
	void PegSolitaire::playUser(const std::string& command) 
	{
		direction dir;
		int col,row;
		auto ans = false;
	
		if (decryptString(command, col, row, dir))
		{
			auto ans = makeMove(board_, col, row, dir);
			if (!ans)
			{
				std::cerr << "This move cannot be done!" << std::endl;				
				std::this_thread::sleep_for(std::chrono::nanoseconds(10));
	    		std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
			}
		}
		else
		{
			std::cerr << "Invalid command format is entered! Please check the correct format (Ex: A2 UP)." << std::endl;			
			std::this_thread::sleep_for(std::chrono::nanoseconds(10));
	    	std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));			
		}
	}

	bool PegSolitaire::endGame( ) 
	{
		auto rowBound = board_.size( );
		auto colBound = board_[0].size( );
		
		auto flag = true;
		for (decltype(rowBound) row = 0; row < rowBound && flag; ++row) 
		{
			for (decltype(colBound) col = 0; col < colBound && flag; ++col) 
			{

				if (board_[row][col].getState() == pegState::peg)
				{
					// check left
					if (col >= 2 && board_[row][col-2].getState() == pegState::empty && board_[row][col-1].getState() == pegState::peg)
						flag = false;
					
					// check right
					else if (col+2 < colBound && board_[row][col+2].getState() == pegState::empty && board_[row][col+1].getState() == pegState::peg)
						flag = false;
					
					// check up
					else if (row >= 2 && board_[row-2][col].getState() == pegState::empty && board_[row-1][col].getState() == pegState::peg)
						flag = false;
					
					// check down
					else if (row+2 < rowBound && board_[row+2][col].getState() == pegState::empty && board_[row+1][col].getState() == pegState::peg)
						flag = false;
				}

			}
		}
		
		EndState_ = flag;
		return flag;
	}
	int PegSolitaire::boardScore() const {
		int counter;
		counter = countNumOfPeg(board_);
		return counter;
	}
	void PegSolitaire::initialize() 
	{
		std::vector<std::vector<Cell>> tempBoard
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

		board_ = tempBoard;
		fillObjectPosition(board_);
		EndState_ = false;
		numOfPeg_ = countNumOfPeg(board_);
	}
}// End of GameGTU namespace.