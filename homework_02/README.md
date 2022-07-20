# FOR TXT FILES_____________  
- Files are formatted like given sample txt files(FILE.TXT,FILE_1.TXT,FILE_2.TXT).
- operationType indicates whether the shape of board is triangular or not. If it is 2, it means it is triangular, so diagonal movements can be made.
If it is 1, diagonal movements cannot be made.
- File can be prepared with or without carriage return character. Program handles both possibility.
- .txt and .TXT difference does matter in ubuntu but does not matter in windows. Call files in program as same as name of the file.
(if file name is FILE.TXT example command:LOAD FILE.TXT, if file name ise FILE.txt example command:LOAD FILE.txt)  

# FOR PROGRAM_______________  
- LOAD and SAVE commands can be used in program at any time during input taking.(cannot use save if there is no game).
- LOAD and SAVE commands must be written with uppercase letters.(load, save are not valid!)
- Computer Game can be load, but cannot be saved. Because, during computer game there is no user interaction.
- Function's detailed explanations are commented on the header file. Spesific explanations are inside of hw2_lib.cpp file.
- Program compiles with make command, and runs with ./hw2 command.
