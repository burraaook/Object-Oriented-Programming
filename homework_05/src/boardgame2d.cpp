/*
** boardgame2d.cpp:
**
** The implementation file is created for implementing BoardGame2D class functions.
**
** Burak Kocausta 1901042605
** 
*/
#include "boardgame2d.h"

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

namespace GameGTU 
{	
	BoardGame2D::~BoardGame2D ( ) 
	{ 
		//intentionally empty
	}
	// Don't override this function.
	void BoardGame2D::playUser ( )
	{
		while(!endGame()) 
		{
			print( );
			std::cout << "Score is: " << boardScore( ) << std::endl;		// print score
			std::string userCommand;
			std::cout << "Enter 1 for computer to finish the game.\n"
					  << "Example Commands according to the game:" 
					  <<  "\"A2 UP\"(Peg Solitaire), \"3 DOWN\"(Eight Puzzle), \"A UP\"(Klotski)\n"
					  << "Command = ";
			getline(std::cin, userCommand);
			if(userCommand.length() > 0)							// check carriage return
				if(userCommand[userCommand.length()-1] == '\r')
					userCommand.pop_back();

			if (userCommand == "1")
			{
				playAutoAll( );
			}
			else
				playUser(userCommand);
		}
	}

	// Don't override this function.
	void BoardGame2D::playAutoAll ( )
	{
		int counter = 0;
		print( );

		if (endGame())
		{
			std::cout << "Game is already finished!\n";
			std::this_thread::sleep_for(std::chrono::nanoseconds(10));
			std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
			return;	
		}
		while(!endGame( )) 
		{
			playAuto( );
			if(counter < 100)
			{
				print( );
				std::cout << "Score is (less score is better): " << boardScore( ) << std::endl;
				std::this_thread::sleep_for(std::chrono::nanoseconds(10));
	    		std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(250));
			}
			else if (counter == 100) 
			{
				std::cout << "100 moves are already made. Rest of the moves will be made without printing one by one.\n" 
						  << "Computer is making moves...\n";
			}
			if(counter >= 2000000)	// limit is 2000000
				break;
			
			++counter;
		}
		print( );
		std::cout << "Game is ended with " << counter << " successful move." << std::endl
				  << "Score is(less score is better) = " << boardScore( ) << std::endl;
		std::this_thread::sleep_for(std::chrono::nanoseconds(10));
	    std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(3));	
	}

	//static function
	void BoardGame2D::playVector (std::vector<BoardGame2D *> boardGame)
	{
		auto numOfGame = boardGame.size();
		decltype(numOfGame) i = 0;
		while (i < numOfGame) 
		{
			boardGame[i]->playAutoAll();
			++i;
		}
	}
	std::ostream& operator << (std::ostream& outs,const BoardGame2D& boardGame)
	{
		std::cout << "\033[H\033[J";
		return boardGame.print(outs);
	}
}