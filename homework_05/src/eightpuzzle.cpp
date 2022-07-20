/*
** eightpuzzle.cpp:
**
** The implementation file is created for implementing EightPuzzle class functions.
**
** Burak Kocausta 1901042605
** 
*/

#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <iostream>

#include "eightpuzzle.h"

namespace // Unnamed namespace for some helper functions.
{
	bool decryptString(std::string userMove, int& num, directionE& dir) 
	{
		auto flag = false;
		auto strLen = userMove.length();				// Taking the length of string input.
		auto dirVar = '-';
		if (strLen > 0)
		{
			if (userMove[0] >= '0' && userMove[0] <= '9')
			{
				num = static_cast<int>(userMove[0]) - static_cast<int>('0');
				flag = true;
			}
		}

		if(flag)
		{
			if(strLen >= 3)		// check all possible direction inputs.
			{
				std::string temp = userMove.substr(2,strLen-1);
				if(temp == "UP" || temp == "DOWN" || temp == "LEFT" || temp == "RIGHT" ||
				   temp == "up" || temp == "down" || temp == "left" || temp == "right" ||
				   temp == "U"  || temp == "D"    || temp == "L"    || temp == "R"     ||
				   temp == "u"  || temp == "d"    || temp == "l"    || temp == "r"     ) 
				{
					dirVar = userMove[2];
				}
				else 
					flag = false;	
			}
			else
				flag = false;
			if(flag)
			{
				switch(dirVar)
				{
					case 'R':
					case 'r':
						dir = directionE::right;
						break;
					case 'L':
					case 'l':
						dir = directionE::left;
						break;
					case 'U':
					case 'u':
						dir = directionE::up;
						break;
					case 'D':
					case 'd':
						dir = directionE::down;
						break;
				}// End of selection.		
			}		
		}
		return flag;
	}
	void swapPuzzleBlock (int& num1, int& num2)
	{
		int temp;
		temp = num1;
		num1 = num2;
		num2 = temp;
	}
	void findBlank (const std::vector<std::vector<int>>& board, int& col, int& row) 
	{
		auto boardLen = board.size();
		col = -1; row = -1;
		for (decltype(boardLen) i = 0; i < boardLen; ++i)
		{
			for(decltype(i) j = 0; j < boardLen; ++j)
			{
				if(board[i][j] == 0)
				{
					col = j;
					row = i;
					return;
				}
			}
		}
	}
	bool makeMove (std::vector<std::vector<int>>& board, int col, int row, directionE dir)
	{	
		auto ans = false;

		if (col >= 0 && row >= 0 && col < board.size() && row < board[0].size() && board[row][col] != 0)
		{
			int blankCol, blankRow;
			findBlank(board, blankCol, blankRow);		// find blank's location.
			switch(dir)
			{

				case directionE::left:
					if (col > blankCol && row == blankRow)
					{
						ans = true;
						swapPuzzleBlock(board[blankRow][blankCol],board[row][col]);		// Swap blank and chosen number. 
						for (int i = 1, j = 0; i < col - blankCol; i++, j++)
							swapPuzzleBlock(board[blankRow][blankCol + i], board[blankRow][blankCol+j]);
					}
					break;
				case directionE::right:
					if (col < blankCol && row == blankRow)
					{
						ans = true;
						swapPuzzleBlock(board[blankRow][blankCol], board[row][col]);		// Swap blank and chosen number. 	
						for (int i = 1,j = 0; i < blankCol - col; i++,j++)
							swapPuzzleBlock(board[blankRow][blankCol - i], board[blankRow][blankCol-j]);	
					}
					break;
				case directionE::up:
					if (row > blankRow && col == blankCol)
					{
						ans = true;
						swapPuzzleBlock(board[blankRow][blankCol], board[row][col]);		// Swap blank and chosen number. 
						for(int i = 1, j = 0; i < row - blankRow; i++, j++)
							swapPuzzleBlock(board[blankRow + i][blankCol], board[blankRow + j][blankCol]);
					}
					break;
				case directionE::down:
					if (row < blankRow && col == blankCol)
					{
						ans = true;
						swapPuzzleBlock(board[blankRow][blankCol], board[row][col]);		// Swap blank and chosen number.						
						for (int i = 1, j = 0; i < blankRow - row; i++, j++)
							swapPuzzleBlock(board[blankRow-i][blankCol], board[blankRow - j][blankCol]);
					}
					break;
			}
		}
		return ans;
	}
	bool isPrecede(int col, int row, int otherCol, int otherRow)	// checks which is closest to 0,0
	{
		if (row < otherRow) 
			return true;

		else if (row == otherRow)
		{
			if(col < otherCol) 
				return true;
			else 
				return false;
		}

		return false;
	}
	int countInversion(const std::vector<std::vector<int>>& board)
	{
		auto boardLen = board.size();
		int invCounter = 0;
		for (decltype(boardLen) i = 0; i < boardLen; ++i) 
		{
			for (decltype(i) j = 0; j < boardLen; ++j) 
			{
				for (decltype(j) k = 0; k < boardLen; ++k)
					for(decltype(k) m = 0; m < boardLen; ++m)
						if (isPrecede(j,i,m,k) && (board[i][j] != 0 && board[k][m] != 0) && board[i][j] > board[k][m])
							invCounter++;			
			}
		}
		return invCounter;
	}
	bool isSolvable (const std::vector<std::vector<int>>& board)
	{
		if ((countInversion(board) % 2) == 1)
			return false;
		return true;
	}
}//End of unnamed namespace.


namespace GameGTU 
{
	EightPuzzle::EightPuzzle ( ) : endState_(false), boardSize_(3)
	{
		auto maxNum = boardSize_*boardSize_ - 1;
		for (int i = 0; i < boardSize_; ++i) 
		{
			board_.push_back(std::vector<int>());
			for (int j = 0; j < boardSize_; ++j) 
			{
				board_[i].push_back(maxNum);
				maxNum--;
			}
		}		
		do {

			for(int i = 0; i < boardSize_; ++i)
			{
				for(decltype(i) j = 0; j < boardSize_; ++j)
				{
					std::random_device dev;
    				std::mt19937 rng(dev());
					std::uniform_int_distribution<std::mt19937::result_type> t_ind1(0,2);
					std::uniform_int_distribution<std::mt19937::result_type> t_ind2(0,2);
					swapPuzzleBlock(board_[i][j], board_[t_ind1(rng)][t_ind2(rng)]);
							
				}
			}
		}while(!isSolvable(board_));	// generate till solvable board comes.
	}

	void EightPuzzle::print( ) const
	{
		std::cout << "\033[H\033[J";
		for (decltype(boardSize_) i = 0; i < boardSize_; ++i)
		{
			std::cout << "**********\n";
			for (decltype(i) j = 0; j < boardSize_; ++j)
			{	
				if(board_[i][j] != 0)
					std::cout << "* " << board_[i][j];
				else
					std::cout << "*  ";
			}
			std::cout << "*" << std::endl;
		}
		std::cout << "**********\n";
		std::cout << "\n_____Eight Puzzle Game_____\n" << std::endl;		
		std::cout << std::endl;
	}
	std::ostream& EightPuzzle::print (std::ostream& outs) const
	{
		for (decltype(boardSize_) i = 0; i < boardSize_; ++i)
		{
			outs << "**********\n";
			for (decltype(i) j = 0; j < boardSize_; ++j)
			{	
				if(board_[i][j] != 0)
					outs << "* " << board_[i][j];
				else
					outs << "*  ";
			}
			outs << "*" << std::endl;
		}
		outs << "**********\n";
		outs << "\n_____Eight Puzzle Game_____\n" << std::endl;		
		outs << std::endl;
		return outs;
	}

	// Makes one random move.
	void EightPuzzle::playAuto( ) 
	{
		auto flag = false;
		endGame();
		while (!flag && !endState_)
		{
			std::random_device dev;
    		std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> row(0,2);
			std::uniform_int_distribution<std::mt19937::result_type> col(0,2);
			for(int i = 0; i < 4 && !flag; ++i) 
			{
				directionE dir = static_cast<directionE>(i);
				if(makeMove(board_, col(rng), row(rng), dir))
					flag = true;
			}
		}
	}

	// Takes input from user and performs the given command.
	void EightPuzzle::playUser(const std::string& command)
	{
		directionE dir;
		int col,row,num;
		if (decryptString(command, num, dir))
		{
			int tCol = -1 ,tRow = -1;
			for (int i = 0; i < boardSize_; ++i)
			{
				for (int j = 0; j < boardSize_; ++j)
				{
					if (board_[i][j] == num)
					{
						tCol = j;
						tRow = i;
					}
				}
			}
			if (num != 0 && tCol >= 0 && tRow >= 0)
			{
				if (makeMove(board_, tCol, tRow, dir) == false)
				{
					std::cerr << "This move cannot be done!" << std::endl;
					std::this_thread::sleep_for(std::chrono::nanoseconds(10));
	    			std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));						
				}
			}
			else
			{
				std::cerr << "There is no such number as " << num << " in the board!" << std::endl;
				std::this_thread::sleep_for(std::chrono::nanoseconds(10));
	    		std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));					 
			}
		}
		else
		{
			std::cerr << "Invalid command format is entered! Sample Formats = (3 UP, 4 LEFT)" << std::endl;
			std::this_thread::sleep_for(std::chrono::nanoseconds(10));
	    	std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));				
		}
	}

	bool EightPuzzle::endGame()
	{
		if (countInversion(board_) == 0)
			endState_ = true;
	
		return endState_;
	}

	// Returns a score according to the goodness of user's game.
	int EightPuzzle::boardScore() const
	{
		return countInversion(board_);
	}

	// Initializes the board.
	void EightPuzzle::initialize()
	{
		auto maxNum = boardSize_*boardSize_ - 1;
		std::vector<std::vector<int>> tempBoard;

		for (int i = 0; i < boardSize_; ++i) 
		{
			tempBoard.push_back(std::vector<int>());
			for (int j = 0; j < boardSize_; ++j) 
			{
				tempBoard[i].push_back(maxNum);
				maxNum--;
			}
		}		
		do{
			for(int i = 0; i < boardSize_; ++i)
			{
				for(decltype(i) j = 0; j < boardSize_; ++j)
				{
					std::random_device dev;
    				std::mt19937 rng(dev());
					std::uniform_int_distribution<std::mt19937::result_type> t_ind1(0,2);
					std::uniform_int_distribution<std::mt19937::result_type> t_ind2(0,2);
					swapPuzzleBlock(tempBoard[i][j], tempBoard[t_ind1(rng)][t_ind2(rng)]);				
				}
			}
		}while(!isSolvable(tempBoard));

		board_ = tempBoard;
		endState_ = false;
	}

	EightPuzzle::~EightPuzzle()
	{
		// intentionally left empty.
	}			
}// End of GameGTU namespace.