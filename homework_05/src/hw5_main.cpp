/*
** hw5_main.cpp:
**
** The test/driver program.
**
** Burak Kocausta 1901042605
** 
*/

#include "boardgame2d.h"
#include "pegsolitaire.h"
#include "eightpuzzle.h"
#include "klotski.h"

#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

void testMenu1 ( );		// displays a menu for testing playUser() and all the other functions.
void test1 ( );			// test for PegSolitaire game.
void test2 ( );			// test for EightPuzzle game.
void test3 ( );			// test for Klotski game.
void test4 ( );			// it tests static playVector() function.
void writeToFile ( );	// test function for indicating << operator works fine for writing to a file.(call this in main if you want to test)

void test_sleepGame (int num) {

	std::this_thread::sleep_for(std::chrono::nanoseconds(10));
	std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(num));		
}

int main ( ) {

	test1();
	test2();
	test3();
//  test4();
	testMenu1();
	writeToFile();
	return 0;
}

void testMenu1 ( ) {
	std::vector <GameGTU::BoardGame2D *> boardGame(6);
	
	GameGTU::PegSolitaire pegGame1,pegGame2;
	GameGTU::EightPuzzle eightGame1,eightGame2;
	GameGTU::Klotski klotskiGame1,klotskiGame2;

	boardGame[0] = new GameGTU::PegSolitaire;
	boardGame[1] = &eightGame1; 
	boardGame[2] = &klotskiGame1; 
	boardGame[3] = &pegGame2; 
	boardGame[4] = &eightGame2; 
	boardGame[5] = &klotskiGame2;

	auto numOfGame = boardGame.size();
	decltype(numOfGame) i = 0;
	auto flag = true;
	
	while (flag) 
	{
		std::cout << *boardGame[i];
		//boardGame[i]->print();
		std::string userCommand;
		std::cout << "There are " << numOfGame << " active game." << std::endl
				  << "1- Go to next game.\n" << "2- Let computer to play current game till the end.\n"
				  << "3- Let computer make one move.\n" << "4- Play the game.\n" << "5- Initialize the board.\n"
				  << "6- Finish all games automatically and exit.\n" << "7- Exit\n" << "Input(1-7) = ";
		getline(std::cin, userCommand);
		if(userCommand.length() > 0)
			if(userCommand[userCommand.length()-1] == '\r')
				userCommand.pop_back();
		
		if (userCommand == "1")
		{
			++i;
			if (i >= numOfGame) i = 0;
		}
		else if (userCommand == "2")
		{
			boardGame[i]->playAutoAll();
			++i;
			if(i >= numOfGame) i = 0;
		}
		else if (userCommand == "3")
		{
			boardGame[i]->playAuto();
		}
		else if (userCommand == "4")
		{
			boardGame[i]->playUser();
			++i;
			if (i >= numOfGame) i = 0;
		}
		else if (userCommand == "5")
		{
			boardGame[i]->initialize();
		}
		else if (userCommand == "6") 
		{
			GameGTU::BoardGame2D::playVector(boardGame); 
			flag = false;
		}
		else if (userCommand == "7")
		{
			flag = false;
		}
		else
		{
			std::cerr << "Wrong input is entered! Please enter numbers between 1 and 7.\n";
			test_sleepGame(1);				
		}
	}
	delete boardGame[0];
	
}
void test1 ( ) {
	using GameGTU::PegSolitaire;
	using GameGTU::BoardGame2D;

	PegSolitaire PegGame;
	

	std::cout << "\033[H\033[J";
	std::cout << "<< operator will be tested.\n";
	test_sleepGame(2);
	BoardGame2D *game1 = &PegGame;
	std::cout << *game1 << std::endl
			  << "____<< operator works fine for PegSolitaire.\n";
	test_sleepGame(2);
	std::cout << "G5 LEFT command will be sent to playUser() function.\n";

	test_sleepGame(2);	
	game1->playUser("G5 LEFT");
	game1->print();
	if(game1->endGame())
		std::cout << "\nGame is ended!\n";
	else
		std::cout << "\nGame is not ended!\n";
	std::cout << "____playUser() function which takes string argument, works fine for Pegsolitaire.\n"
	          << "____Also print() and endGame() works fine for PegSolitaire class.\n";
	
	test_sleepGame(3);
	std::cout << "Two random move will be made by computer.\n";
	
	test_sleepGame(2);

	game1->playAuto();
	game1->print();
	std::cout << "Score is(less is better) = " << game1->boardScore() << std::endl;
	test_sleepGame(1);
	game1->playAuto();
	game1->print();
	std::cout << "Score is(less is better) = " << game1->boardScore() << std::endl;
	std::cout << "____playAuto() and  boardScore() functions work fine for PegSolitaire class.\n";

	test_sleepGame(3);
	std::cout << "initialize() function will be called\n";

	test_sleepGame(3);	

	game1->initialize();
	std::cout << *game1;
	std::cout << "____initialize() function works fine for PegSolitaire class.\n";

	test_sleepGame(3);

	std::cout << "playAutoAll() function will be called.\n";

	test_sleepGame(3);	
	game1->playAutoAll();
	std::cout << "____PlayAutoAll() and endGame() functions works fine for PegSolitaire class.\n";

	test_sleepGame(2);
}

void test2 ( ) {
	using GameGTU::EightPuzzle;
	using GameGTU::BoardGame2D;

	EightPuzzle eightGame;
	
	std::cout << "\033[H\033[J";
	std::cout << "<< operator will be tested.\n";

	test_sleepGame(2);

	BoardGame2D *game1 = &eightGame;
	std::cout << *game1 << std::endl
			  << "____<< operator works fine for EightPuzzle.\n";

	test_sleepGame(3);

	std::cout <<"\n2 UP command sent to playUser() function"
			  << "\n(command format is valid but move might not be made, because board initialized randomly.)\n";

	test_sleepGame(3);

	std::cout << "\n\n\n";
	
	game1->playUser("2 UP");
	game1->print();
	
	if (game1->endGame())
		std::cout << "Game is ended!\n";
	else
		std::cout << "Game is not ended!\n";
		
		std::cout << "\n____playUser() function which takes string argument, works fine for EightPuzzle.\n"
	          << "____Also print() and endGame() works fine for EightPuzzle class.\n";

	test_sleepGame(5);         

	std::cout << "\nTwo random move will be made by computer.\n";

	test_sleepGame(3);

	game1->playAuto();
	game1->print();
	std::cout << "Score is(less is better) = " << game1->boardScore() << std::endl;

	test_sleepGame(3);

	game1->playAuto();
	game1->print();
	std::cout << "Score is(less is better) = " << game1->boardScore() << std::endl;
	std::cout << "____playAuto() and  boardScore() functions work fine for EightPuzzle class.\n";

	test_sleepGame(4);


	std::cout << "\ninitialize() function will be called\n";

	test_sleepGame(3);

	game1->initialize();
	std::cout << *game1;
	std::cout << "____initialize() function works fine for EightPuzzle class.\n";

	test_sleepGame(3);

	std::cout << "\nplayAutoAll() function will be called.\n"
	<< "It might be take a little long time but it will not print board for each step after 100 successful moves, It will print finished board.\n";

	test_sleepGame(5);

	game1->playAutoAll();
	std::cout << "____PlayAutoAll() and endGame() functions works fine for EightPuzzle class.\n";

	test_sleepGame(3);
}

void test3 ( ) {
	using GameGTU::Klotski;
	using GameGTU::BoardGame2D;

	Klotski KlotskiGame;
	
	std::cout << "\033[H\033[J";
	std::cout << "<< operator will be tested.\n";

	test_sleepGame(2);

	BoardGame2D *game1 = &KlotskiGame;
	std::cout << *game1 << std::endl
			  << "____<< operator works fine for Klotski class.\n";

	test_sleepGame(3);	

	std::cout << "\nX DOWN command sent to playUser() function.\n";

	test_sleepGame(3);

	game1->playUser("X DOWN");
	game1->print();
	if(game1->endGame())
		std::cout << "Game is ended!\n";
	else
		std::cout << "Game is not ended!\n";
	
	std::cout << "\n____playUser() function which takes string argument, works fine for Klotski.\n"
	          << "____Also print() and endGame() works fine for Klotski class.\n";

	test_sleepGame(4);

	std::cout << "Two random move will be made by computer.\n";


	test_sleepGame(3);

	game1->playAuto();
	game1->print();
	std::cout << "Score is(less is better) = " << game1->boardScore() << std::endl;

	test_sleepGame(3);

	game1->playAuto();
	game1->print();
	std::cout << "Score is(less is better) = " << game1->boardScore() << std::endl;
	std::cout << "____playAuto() and  boardScore() functions work fine for Klotski class.\n";

	test_sleepGame(4);

	std::cout << "initialize() function will be called\n";

	test_sleepGame(3);


	game1->initialize();
	std::cout << *game1;
	std::cout << "\n____initialize() function works fine for Klotski class.\n";

	test_sleepGame(3);

	std::cout << "playAutoAll() function will be called.\n"
	<< "It might be take a little long time but it will not print board for each step after 100 successful moves, It will print finished board.\n";

	test_sleepGame(6);

	game1->playAutoAll();
	std::cout << "PlayAutoAll() and endGame() functions works fine for Klotski class.\n";

	test_sleepGame(3);
}

void test4( ) {
	std::cout << "\033[H\033[J";
	std::vector <GameGTU::BoardGame2D *> boardGame(6);
	GameGTU::PegSolitaire pegGame1,pegGame2;
	GameGTU::EightPuzzle eightGame1,eightGame2;
	GameGTU::Klotski klotskiGame1,klotskiGame2;

	boardGame[0] = &pegGame1;
	boardGame[1] = &eightGame1; 
	boardGame[2] = &klotskiGame1; 
	boardGame[3] = &pegGame2; 
	boardGame[4] = &eightGame2; 
	boardGame[5] = &klotskiGame2;

	
	std::cout << "Static playVector() function will be tested.\nThere are 6 boards(2 boards of each type).\n";
	test_sleepGame(4);

	GameGTU::BoardGame2D::playVector(boardGame);

	std::cout << "____Static playVector() function works fine.\n\n";
	test_sleepGame(2);
}
void writeToFile ( ) {		
	using GameGTU::PegSolitaire;
	using GameGTU::EightPuzzle;
	using GameGTU::Klotski;
	using GameGTU::BoardGame2D;
	
	PegSolitaire pegGame1;
	EightPuzzle eightGame1;
	Klotski klotskiGame1;

	BoardGame2D *game1 = &pegGame1;
	BoardGame2D *game2 = &eightGame1;
	BoardGame2D *game3 = &klotskiGame1;

	std::ofstream outFile;

	outFile.open("boards.txt");

	if(outFile.is_open()) {
		
		outFile << *game1 << std::endl
				<< *game2 << std::endl
				<< *game3 << std::endl;

		outFile.close();
	}	
}