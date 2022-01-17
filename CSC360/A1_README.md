

 This program continuously prompts the user for commands and executes all commands in a child process. The prompt prints vsh%.
 My program accepts commands with up to 9 arguments. It searches for the command pathname in the .vshrc uses it to execute these commands. 
 If not found it prints a proper error message if no correct pathname was found. When exit is inputted as the only command vsh terminates.

If a file name is given with :: immediatly before the file name, the command output will display in the specified output file. Because I tokenize the input string the order of the file/commands/arguments wont matter. 

 If a file name is given with :: immediatly following the the command will read from this file (recieved as the input file). The order of the commands wont matter as the input string is tokenized to get each command/arguments 

 If ## is recieved than the program will print the wallclock time taken to execute the command again order wont matter.

If 2 files are inputted the ::filename is the output file filename:: is the input file. The input/output will be recieved/written to the correct files
