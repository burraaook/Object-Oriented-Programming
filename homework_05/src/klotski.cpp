/*
** klotski.cpp:
**
** The implementation file is created for implementing Klotski class functions.
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
#include "klotski.h"

namespace	// unnamed namespace for some helper functions. 
{

	void swapKCell(GameGTU::Klotski::KlotskiCell& cell1, GameGTU::Klotski::KlotskiCell& cell2)
	{
		GameGTU::Klotski::KlotskiCell temp;
		temp = cell1;
		cell1 = cell2;
		cell2 = temp;
	}
	bool decryptString (const std::string& userMove,char& cellLabel,directionK& dir)
	{
		auto flag = false;
		auto strLen = userMove.length();				// Taking the length of string input.
		auto dirVar = '-';
		if (strLen > 0)
		{
			if (userMove[0] >= 'A' && userMove[0] <= 'Z')
			{
				cellLabel = userMove[0];
				flag = true;
			}
			else if(userMove[0] >= 'a' && userMove[0] <= 'z')
			{
				cellLabel = userMove[0] - ' ';
				flag = true;
			}
		}

		if(flag)
		{
			if(strLen >= 3)
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
						dir = directionK::right;
						break;
					case 'L':
					case 'l':
						dir = directionK::left;
						break;
					case 'U':
					case 'u':
						dir = directionK::up;
						break;
					case 'D':
					case 'd':
						dir = directionK::down;
						break;
				}// End of selection.		
			}			
		}
		return flag;
	}

	void findLeftBottomCell(const std::vector<std::vector<GameGTU::Klotski::KlotskiCell>>& board
							, char cellLabel, int& tCol, int& tRow, int colBound, int rowBound)
	{
		for (decltype(rowBound) i = 0; i < rowBound; ++i)
		{
			for (decltype(colBound) j = 0; j < colBound; ++j)
			{
				if (board[i][j].getLabel() == cellLabel)
				{
					tCol = j;
				//	std::cout << i << " " << j << " " << board[i][j].getLabel() << " " << cellLabel << std::endl; 
					
					if (i < rowBound - 1 && board[i+1][j].getLabel() == cellLabel)
						tRow = i+1;
					
					else
						tRow = i;

					return;
				}
			}
		}
	}

	void findGreatest(const std::vector<std::vector<GameGTU::Klotski::KlotskiCell>>& board, int& tCol, int& tRow, int colBound, int rowBound) 
	{

		for (decltype(rowBound) i = 0; i < rowBound; ++i)
		{
			for (decltype(colBound) j = 0; j < colBound; ++j)
			{
				if (board[i][j].getWidth() == 2 && board[i][j].getHeight() == 2)
				{
					if (i < rowBound - 1)
					{
						tRow = i+1;
						tCol = j;
						return;
					}
				}
			} 
		}
	}
	//assumes left bottom coordinates given for bigger shapes.
	bool makeMove (std::vector<std::vector<GameGTU::Klotski::KlotskiCell>>& board, int col, int row, directionK dir, int colBound, int rowBound)
	{
		auto flag = false;

		if (col >= 0 && row >= 0 && col < colBound && row < rowBound && board[row][col].getLabel() != '0')
		{
			int tHeight = board[row][col].getHeight();
			int tWidth = board[row][col].getWidth();
			switch (dir)
			{
				case directionK::left:
					if (col > 0 && board[row][col-1].getLabel() == '0')
					{
						if (tHeight == 2 && row > 0 && (board[row-1][col-1].getLabel() == '0'))
						{
							if (tWidth == 2 && col < colBound-1)
							{
								swapKCell(board[row][col-1], board[row][col+1]);
								swapKCell(board[row-1][col-1], board[row-1][col+1]);
								flag = true;
							}
							else if (tWidth == 1)
							{
								swapKCell(board[row][col-1], board[row][col]);
								swapKCell(board[row-1][col], board[row-1][col-1]);
								flag = true;
							}
						}
						else if (tHeight == 1)
						{
							if (tWidth == 2 && col < colBound - 1)
							{
								swapKCell(board[row][col-1], board[row][col+1]);
								flag = true;								
							}
							
							else if (tWidth == 1)
							{
								swapKCell(board[row][col-1], board[row][col]);
								flag = true;								
							}													
						}
					}
					break;
				case directionK::right:
					if (col < colBound - 1)
					{
						if (tWidth == 2 && col < colBound - 2 && (board[row][col+2].getLabel() == '0')) 
						{
							if (tHeight == 2 && row > 0 && (board[row-1][col+2].getLabel() == '0'))
							{
								swapKCell(board[row][col], board[row][col+2]);
								swapKCell(board[row-1][col], board[row-1][col+2]);
								flag = true;
							}

							else if (tHeight == 1)
							{
								swapKCell(board[row][col], board[row][col+2]);
								flag = true;
							}
						}
						else if (tWidth == 1 && (board[row][col+1].getLabel() == '0'))
						{
							if (tHeight == 2 && row > 0 && board[row-1][col+1].getLabel() == '0')
							{
								swapKCell(board[row][col], board[row][col+1]);
								swapKCell(board[row-1][col], board[row-1][col+1]);
								flag = true;
							}
							else if (tHeight == 1)
							{
								swapKCell(board[row][col], board[row][col+1]);
								flag = true;
							}
						}
					}
					break;

				case directionK::up:
					if (row > 0)
					{
						if (tHeight == 2 && row > 1 && board[row-2][col].getLabel() == '0')
						{
							if (tWidth == 2 && col < colBound-1)
							{
								if (board[row-2][col+1].getLabel() == '0')
								{
									swapKCell(board[row][col], board[row-2][col]);
									swapKCell(board[row][col+1], board[row-2][col+1]);
									flag = true;
								}
							}
							else if (tWidth == 1)
							{
								swapKCell(board[row][col], board[row-2][col]);
								flag = true;
							}
						}
						else if (tHeight == 1 && board[row-1][col].getLabel() == '0')
						{
							if (tWidth == 2 && col < colBound-1)
							{
								if (board[row-1][col+1].getLabel() == '0')
								{
									swapKCell(board[row][col], board[row-1][col]);
									swapKCell(board[row][col+1], board[row-1][col+1]);
									flag = true;
								}
							}
							else if (tWidth == 1)
							{
								swapKCell(board[row][col], board[row-1][col]);
								flag = true;
							}
						}
					}
					break;

				case directionK::down:
					if (row < rowBound-1 && board[row+1][col].getLabel() == '0')
					{
						if (tHeight == 2 && row > 0)
						{
							if (tWidth == 2 && col < colBound- 1 && board[row+1][col+1].getLabel() == '0')
							{
								swapKCell(board[row-1][col+1], board[row+1][col+1]);
								swapKCell(board[row-1][col], board[row+1][col]);
								flag = true;
							}
							else if (tWidth == 1)
							{
								swapKCell(board[row-1][col], board[row+1][col]);
								flag = true;
							}
						}

						else if (tHeight == 1)
						{
							if (tWidth == 2 && col < colBound - 1 && board[row+1][col+1].getLabel() == '0')
							{
								swapKCell(board[row][col], board[row+1][col]);
								swapKCell(board[row][col+1], board[row+1][col+1]);
								flag = true;
							}
							else if (tWidth == 1)
							{
								swapKCell(board[row][col], board[row+1][col]);
								flag = true;
							}
						}
					}
					break;
			}
		}
		return flag;
	}
}// End of unnamed namespace.

namespace GameGTU
{
	Klotski::Klotski ( ) : rowBound_(5), colBound_(4), endState_(false)
	{
		std::vector<std::vector<KlotskiCell>> tempBoard 
		{
			{KlotskiCell('A',1,2),KlotskiCell('B',2,2),KlotskiCell('B',2,2),KlotskiCell('C',1,2)},
			{KlotskiCell('A',1,2),KlotskiCell('B',2,2),KlotskiCell('B',2,2),KlotskiCell('C',1,2)},
			{KlotskiCell('K',1,2),KlotskiCell('M',2,1),KlotskiCell('M',2,1),KlotskiCell('Y',1,2)},
			{KlotskiCell('K',1,2),KlotskiCell('P'),KlotskiCell('X'),KlotskiCell('Y',1,2)},
			{KlotskiCell('W'),KlotskiCell(),KlotskiCell(),KlotskiCell('E')}
		};

		board_ = tempBoard;
	}

	void Klotski::print( ) const
	{
		std::cout << "\033[H\033[J";
		std::cout << "___________" << std::endl;
		for (decltype(rowBound_) i = 0; i < rowBound_; ++i) 
		{
			std::cout << "| ";
			for (decltype(colBound_) j = 0; j < colBound_; ++j)
			{
				if(board_[i][j].getLabel() == '0')
					std::cout << "  ";
				else
					std::cout << board_[i][j].getLabel() << " ";
			}
			std::cout << "|" << std::endl;
		}
		std::cout << "***********" << std::endl;
		std::cout << "\n_____Klotski Puzzle Game_____\n" << std::endl;
	}
	std::ostream& Klotski::print (std::ostream& outs) const
	{
		outs << "___________" << std::endl;
		for (decltype(rowBound_) i = 0; i < rowBound_; ++i) 
		{
			outs << "| ";
			for (decltype(colBound_) j = 0; j < colBound_; ++j)
			{
				if(board_[i][j].getLabel() == '0')
					outs << "  ";
				else
					outs << board_[i][j].getLabel() << " ";
			}
			outs << "|" << std::endl;
		}
		outs << "***********" << std::endl;
		outs << "\n_____Klotski Puzzle Game_____\n" << std::endl;
		return outs;
	}		
	// Makes one random move.
	void Klotski::playAuto()
	{
		auto flag = false;
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> row(0,4);
		std::uniform_int_distribution<std::mt19937::result_type> col(0,3);		
		endGame();
		while (!flag && !endState_)
		{
			for (int i = 0; i < 4 && !flag; ++i) 
			{
				directionK dir = static_cast<directionK>(i);
				int tRow = row(rng) ,tCol = col(rng);
				findLeftBottomCell(board_, board_[tRow][tCol].getLabel(), tCol, tRow, colBound_, rowBound_);
				flag = makeMove(board_, tCol, tRow, dir, colBound_, rowBound_);
			}
		}		
	}

	// Takes input from user and performs the given command.
	void Klotski::playUser(const std::string& command) 
	{
		directionK dir;
		int col,row;
		char cellLabel;
		if (decryptString(command, cellLabel, dir))
		{
			int tCol = -1 ,tRow = -1;

			findLeftBottomCell(board_, cellLabel, tCol, tRow, colBound_, rowBound_);
			if (cellLabel != '0' && tCol >= 0 && tRow >= 0)
			{
				if (makeMove(board_, tCol, tRow, dir, colBound_, rowBound_) == false)
				{
					std::cerr << "This move cannot be done!" << std::endl;					
					std::this_thread::sleep_for(std::chrono::nanoseconds(10));
	    			std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));	
				}
			}
			else
			{
				std::cerr << "There is no such label as " << cellLabel << " in the board!" << std::endl; 				
				std::this_thread::sleep_for(std::chrono::nanoseconds(10));
	    		std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));	
			}
		}
		else
		{
			std::cerr << "Invalid command format is entered! Sample Formats = (A UP, K LEFT)" << std::endl;			
			std::this_thread::sleep_for(std::chrono::nanoseconds(10));
	    	std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));			
		}
	}

	bool Klotski::endGame()
	{
		int tRow = 0, tCol = 0;
		findGreatest(board_, tCol, tRow, colBound_, rowBound_);
		if (tRow == rowBound_ - 1 && tCol == 1) 
			endState_ = true;
		return endState_;
	}

	// Returns a score according to the goodness of user's game.
	int Klotski::boardScore() const
	{
		int tRow = 0,tCol = 0;
		findGreatest(board_, tCol, tRow, colBound_, rowBound_);
		if(tCol == 1 && tRow == rowBound_ - 1)
			return 0;
		else
			return rowBound_ - tRow;
	}

	// Initializes the board.
	void Klotski::initialize()
	{
		std::vector<std::vector<KlotskiCell>> tempBoard 
		{
			{KlotskiCell('A',1,2),KlotskiCell('B',2,2),KlotskiCell('B',2,2),KlotskiCell('C',1,2)},
			{KlotskiCell('A',1,2),KlotskiCell('B',2,2),KlotskiCell('B',2,2),KlotskiCell('C',1,2)},
			{KlotskiCell('K',1,2),KlotskiCell('M',2,1),KlotskiCell('M',2,1),KlotskiCell('Y',1,2)},
			{KlotskiCell('K',1,2),KlotskiCell('P'),KlotskiCell('X'),KlotskiCell('Y',1,2)},
			{KlotskiCell('W'),KlotskiCell(),KlotskiCell(),KlotskiCell('E')}
		};
		board_ = tempBoard;
		endState_ = false;
	}

	Klotski::~Klotski()
	{
		// intentionally left empty.
	}		
}// End of GameGTU namespace.