/*
** hw3_main.cpp:
**
** The test/driver program.
**
** Burak Kocausta 1901042605
** 
*/

#include "hw3_lib.h"

int main(){		// A program with user interaction which uses the class created in hw3_lib files. 

	// 4 type of constructor is used below.
	PegSolitaire game;	// default constructor.		
	vector<PegSolitaire> games {game, PegSolitaire(3), PegSolitaire(4), PegSolitaire(5), PegSolitaire(6),PegSolitaire(7,7)};

	PegSolitaire game_1(PegSolitaire(2).getBoardVector());	// Any valid board(user created or not) vector can be passed as an argument to a constructor.
	games.push_back(game_1);
	
	auto canPlay = true;
	decltype(games.size()) i = 0;

	for(auto j = i; j < games.size(); ++j)			// Total peg number in all games is calculated.
		games[j].addPegToTotal();
	
	do{
		if(games[i].getEndState()){
			cout << "\nGame " << i+1 << " is finished. Other Games are being checked..." << endl;
			i = 0;

			while(i < games.size() && games[i].getEndState())
				++i;
			if(i == games.size()){
				cout << "All games are finished! Program is terminated..." << endl;
				break;
			}
			else
				cout << "\nGAME " << i+1 << " is the new current game." << endl; 
		}
		
		do{
			cout << "==============================================================\n"
				 << "\n" << games.size() << " game(s) are running currently." << endl
				 << "Total number of pegs in all " << games.size() << " games = " << PegSolitaire::getTotalNumber() << endl << endl;
			games[i].displayBoard();
			cout << "___CURRENT GAME STATS___(GAME " << i+1 << ")" << endl
				 << "Number of pegs in this board = " << games[i].getNumOfPeg() << endl
				 << "Number of empty cell in this board = " << games[i].getNumOfEmptyCell() << endl
				 << "Number of the pegs taken out from the board = " << games[i].getNumOfPegOut() << endl << endl << endl;

			cout << "___LIST OF COMMANDS___" << endl
				 << "1- Change the board(Command = 1)\n2- Start a computer game with different board(Command = 2)"
				 << "\n3- Let computer to play continuously this board.(Command = 3)\n" 
				 << "4- Let computer to make one move(Command = 4)\n5- Switch the game(Command = 5)\n6- Create a new Game(Command = 6)\n"
				 << "7- Compare peg number with other games.(Command = 7)\n"
				 << "->You can enter a movement command(Example = B4-R)\n->You can LOAD a game from your file(Example = LOAD FILE.TXT)" << endl
				 << "->You can SAVE current game to a file(Example = SAVE FILE.TXT)\n\n>>Your Command = ";
			
			string command;
			getline(cin,command);
			
			if(command.length() > 0){
				if(command[command.length()-1] == '\r')
					command.pop_back();
			}

			if(command.length() == 1){
				if(command == "1"){
					if(games[i].boardTypeInput())
						cout << "\nBoard and stats are updated!" << endl << endl;

					else
						cerr << "Board cannot be loaded!" << endl;
				}

				else if(command == "2") games[i].playGame();
					
				else if(command == "3")	games[i].playCurrentGame();
					
				else if(command == "4")	games[i].play();
					
				else if(command == "5"){
					
					cout << "___GAMES LIST___ " << endl << endl;
					auto totalGames = games.size();
					cout << " GAME NUMBER" << "    BOARD TYPE" << endl;
					for(decltype(totalGames) j = 0; j < totalGames; ++j){

							cout << "     " << j+1 << "          ";
							switch(games[j].getBoardType()){
								case 1: cout << "European\n"; 		break;
								case 2: cout << "Germany\n"; 		break;
								case 3: cout << "Asymmetrical\n"; 	break;
								case 4: cout << "Standart\n"; 		break;
								case 5: cout << "Diamond\n"; 		break;
								case 6: cout << "Triangular\n";		break;
								case 7: cout << "Square(nxn)\n";	break;
								default: cout << "Arbitrary\n";		break;
							
						}
					}
					auto inputFlag = false;
					while(!inputFlag){
						int gameInput;	
						cout << "\nWhich game do you want to continue?\n"
							 << "Input(please enter the GAME NUMBER) = ";
						cin >> gameInput;

						if(cin.good())
							inputFlag = true;

						cin.clear();
						cin.ignore(500,'\n');

						if(inputFlag){
							if(gameInput > 0 && static_cast<decltype(totalGames)>(gameInput) < totalGames+1)
								i = gameInput-1;
							else{				
								inputFlag = false;
								cerr << "Wrong number is entered! Please enter one of the game number given.";
							}
						}
						else
							cerr << "Wrong input is entered! Please enter one of the game number!\n" << endl;
					}
				}

				else if(command == "6"){
					cout << "\nDefault game is created you can change board from option 1 in the game menu." << endl;
					games.push_back(PegSolitaire(2));
					i = games.size() - 1;
					games[i].addPegToTotal();
				}

				else if(command == "7"){
					if(games.size() > 1){
						for(decltype(i) j = 0; j < games.size(); ++j){
							if(j != i){
								auto compareFlag = games[i].compareGames(games[j]);
								if(compareFlag){
									cout << "GAME " << i+1 << " has more or equal number of pegs than GAME " << j+1 << ".\n"
										 << "GAME " << i+1 << "'s peg number is " << games[i].getNumOfPeg() << "." <<  endl
										 << "GAME " << j+1 << "'s peg number is " << games[j].getNumOfPeg() << "." <<  endl << endl;
 								}
 								else{
									cout << "GAME " << i+1 << " has less number of pegs than GAME " << j+1 << ".\n"
										 << "GAME " << i+1 << "'s peg number is " << games[i].getNumOfPeg() << "." <<  endl
										 << "GAME " << j+1 << "'s peg number is " << games[j].getNumOfPeg() << "." <<  endl << endl;
 								}
							}
						}
					}
					else
						cerr << "There are no other game to compare currently! Please create games to compare." << endl;
				}
			}
			else if(command.length() > 5){
				
				if(command.compare(0,5,"LOAD ") == 0 || command.compare(0,5,"load ") == 0){
					auto fileFlag = games[i].loadFile(command);
					if(fileFlag)
						cout << "File successfully loaded!" << endl;
					else
						cerr << "FILE cannot be loaded! File format might be wrong or given filename does not exist!" << endl;
				}
				else if(command.compare(0,5,"SAVE ") == 0 || command.compare(0,5,"save ") == 0){
					auto fileFlag = games[i].saveFile(command);

					if(!fileFlag)
						cerr << "File cannot be saved some error occured!";
					else
						cout << "File successfully saved!" << endl;
				}

				else
					cerr << "Command format is wrong! Please look at the examples above." << endl;
			}
			else{
				auto flag = games[i].play(command);
				if(!flag)
					cerr << "Command format is wrong! Please look at the examples above." << endl;
			}
	
		}while(!(games[i].getEndState()));

		if(games[i].getEndState()){
			games[i].displayBoard();
			if(games[i].getNumOfPeg() == 1)
		 		cout << "Congratulation! Maximum score is achieved with " << games[i].getNumOfPegOut() << " moves." << endl;
		 	else
		 		cout << "Total number of remaining pegs is " << games[i].getNumOfPeg() << " with " << games[i].getNumOfPegOut() << " successful moves." << endl;
		}

		decltype(i) finishedGameCounter = 0;

		for(decltype(i) j = 0; j < games.size(); ++j){
			
			if(games[j].getEndState() == false)
				++finishedGameCounter;
		}
		if(finishedGameCounter == games.size()){
			cout << "Congragulations! All games are finished!" << endl;
			canPlay = false;
		}

	}while(canPlay);

	return 0;
}// End of main