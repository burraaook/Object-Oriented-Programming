/*
** boardgame2d.h:
**
** The header file is created for class interface.
**
** Burak Kocausta	1901042605
*/

#ifndef BOARDGAME2D_H
#define BOARDGAME2D_H

#include <iostream>
#include <string>
#include <vector>

namespace GameGTU 
{
	// This is an abstract boardGame class.
	class BoardGame2D 
	{
	public:
		
		// Takes input from user and performs the given command.
		virtual void playUser(const std::string& command) = 0;

		// Takes input from user and plays the game till it ends.
		virtual void playUser ( ) final;

		// Makes one random move.
		virtual void playAuto ( ) = 0;

		// Automatically plays the game till the end.
		virtual void playAutoAll() final;

		// Prints the board at top left of the terminal.
		virtual void print ( ) const = 0;

		// print() functions operator overloaded version.
		friend std::ostream& operator <<(std::ostream& outs,const BoardGame2D& boardGame);
		
		// Returns true if game is ended.
		virtual bool endGame ( ) = 0;
		
		// Returns a score according to the goodness of user's game.
		virtual int boardScore ( ) const = 0;

		// Initializes the board.
		virtual void initialize ( ) = 0;

		virtual ~BoardGame2D ( );

		// Plays different games.
		static void playVector (std::vector<BoardGame2D *> boardGame);

	protected:
		// Use this for overriding << operator indirectly.
		virtual std::ostream& print (std::ostream& outs) const = 0;
	};
}


#endif // BOARDGAME2D_H