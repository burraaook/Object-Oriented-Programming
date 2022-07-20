/*
** klotski.h:
**
** The header file is created for class interface.
**
** Burak Kocausta	1901042605
*/

#ifndef KLOTSKI_H
#define KLOTSKI_H

#include "boardgame2d.h"
#include <vector>
#include <string>

enum class directionK {up,down,left,right};

namespace GameGTU
{
	class Klotski : public BoardGame2D 
	{
	public:
		// This inner class holds each cells information.
		class KlotskiCell
		{
		public:
			KlotskiCell ( ) : label_('0'), width_(1), height_(1) {}
			KlotskiCell (char labelVar) : label_(labelVar) , width_(1), height_(1) {}
			KlotskiCell (char labelVar, int widVar, int heightVar) : label_(labelVar), width_(widVar), height_(heightVar) {}
			char getLabel ( ) 	const  	{ return label_;}
			int getHeight ( ) 	const 	{return height_;}
			int getWidth ( )	const 	{return width_;}
		private:
			char label_;
			int width_;
			int height_;
		};

		// No parameter constructor
		Klotski ( );

		std::vector<std::vector<KlotskiCell>> getBoard( ) const { return board_; }
		
		int getBoardLength ( ) const { return rowBound_; }
		int getboardWidth ( ) const { return colBound_; }

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

  		virtual ~Klotski();		
	private:
		std::vector<std::vector<KlotskiCell>> board_;
		int rowBound_;
		int colBound_;
		bool endState_;
	protected:
		virtual std::ostream& print (std::ostream& outs) const;	
	};
}

#endif // KLOTSKI_H