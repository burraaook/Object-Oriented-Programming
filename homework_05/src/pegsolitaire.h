/*
** pegsolitaire.h:
**
** The header file is created for class interface.
**
** Burak Kocausta	1901042605
*/

#ifndef PEGSOLITAIRE_H
#define PEGSOLITAIRE_H

#include "boardgame2d.h"
#include <iostream>
#include <vector>

enum class pegState {empty,peg,wall};
enum class direction {up,down,left,right};

namespace GameGTU 
{
	class PegSolitaire : public BoardGame2D
	{
	public:

		// This inner class holds each cells information.
		class Cell
		{
		public:
		    /* Constructors */
		    Cell(pegState pegValue ,char columnValue, int rowValue) : pstate_(pegValue), colPos_(columnValue), rowPos_(rowValue) {}    
		    Cell(pegState pegValue, char columnValue) :  pstate_(pegValue), colPos_(columnValue) {}
		    Cell(pegState pegValue) : pstate_(pegValue) {}
		    Cell() : pstate_(pegState::peg), colPos_('-'), rowPos_(1) {}

		    void setCell(char columnValue, int rowValue, pegState pegValue)  /* Inlined Mutator functions. */
		                                                     {colPos_ = columnValue; rowPos_ = rowValue; pstate_ = pegValue;}

		    void setPosition(char columnValue, int rowValue) {colPos_ = columnValue; rowPos_ = rowValue;}
		                                                     
		    void setState(pegState pegValue)                 {pstate_ = pegValue;}
		    
		    int getRow() const {return rowPos_;}                             /* Accessor function. */  
		    char getColumn() const {return colPos_;}                                                   
		    pegState getState() const {return pstate_;}
		private:
			pegState pstate_;
    		char colPos_;
    		int rowPos_;
		};

	  	// Default constructor creates a default game.
  		PegSolitaire();
  		virtual ~PegSolitaire();
        // Accessors. All of them are inlined.
		int getNumOfPeg() const       {return numOfPeg_;}
		bool getEndState() const      {return EndState_;}
		std::vector<std::vector<Cell>> getBoardVector() const{return board_;}
	
  		virtual void print() const;

  		// Makes one random move.
		virtual void playAuto();

		using BoardGame2D::playUser; // call from base class
		
		// Takes input from user and performs the given command.
		virtual void playUser(const std::string& command);

		// Returns true if game is ended.
		virtual bool endGame();

		// Returns a score according to the goodness of user's game.
		virtual int boardScore() const;

		// Initializes the board.
		virtual void initialize();
	private:
		std::vector<std::vector<Cell>> board_;
		int numOfPeg_;
		bool EndState_;
	protected:
		virtual std::ostream& print (std::ostream& outs) const;
	};
}

#endif // PEGSOLITAIRE_H