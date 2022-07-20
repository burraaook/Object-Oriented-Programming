/*
** eightpuzzle.h:
**
** The header file is created for class interface.
**
** Burak Kocausta	1901042605
*/

#ifndef EIGHTPUZZLE_H
#define EIGHTPUZZLE_H

#include <vector>
#include <string>
#include "boardgame2d.h"

enum class directionE {up,down,left,right};

namespace GameGTU 
{
	class EightPuzzle : public BoardGame2D
	{
	public:
		// No parameter constructor
		EightPuzzle();

		std::vector<std::vector<int>> getBoard( ) const { return board_; }		// getters
		int getBoardSize() const { return boardSize_; }

  		virtual void print() const;

  		// Makes one random move.
		virtual void playAuto();

		// Takes input from user and performs the given command.
		virtual void playUser(const std::string& command);

		// Returns true if game is ended.
		virtual bool endGame();

		// Returns a score according to the goodness of user's game.
		virtual int boardScore() const;

		// Initializes the board.
		virtual void initialize();

  		virtual ~EightPuzzle();		

	private:
		std::vector<std::vector<int>> board_;
		bool endState_;
		int boardSize_;

	protected:
		virtual std::ostream& print (std::ostream& outs) const;	
	};
}

#endif // EIGHTPUZZLE_H