# FOR PROGRAM_______________  
- In main, sample program written which uses the PegSolitaire class's functions and data.
- Program runs till there aren't any possible movement in all game objects.
- 7 objects are created beforehand to show different possible constructions in main, their number can be incremented during runtime.
And these objects can be active same time.
- In console program describes which commands can be entered.
- LOAD command overwrites the game, does not create a new game object. There is an option for to create a new object, It is said in the menu.
- LOAD and SAVE commands can be used in program at any time during input taking.
- Function's detailed explanations are commented on the header file. Spesific explanations are inside of hw3_lib.cpp file.
- Program compiles with make command, and runs with ./hw3 command.  

# FOR TXT FILES_____________  
- Files are formatted like given sample txt files(FILE.TXT,FILE_1.TXT,FILE_2.TXT).
- boardType indicates whether the shape of board is triangular or not. If it is 6, it means it is triangular, so diagonal movements can be made.
If it is 1-5, diagonal movements cannot be made. 7 represents square boards. 8 represents arbitrary boards. 7 and 8 are also cannot make diagonal movements.
- If userType equals 1, it means this is computer game. If userType equals 2, that means this is human game.
- File can be prepared with or without carriage return character. Program handles both possibility.
- .txt and .TXT difference does matter in ubuntu but does not matter in windows. Call files in program as same as name of the file.
(if file name is FILE.TXT example command:LOAD FILE.TXT, if file name ise FILE.txt example command:LOAD FILE.txt)

