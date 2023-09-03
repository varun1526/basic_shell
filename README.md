# basic_shell
My project's aim is to show the basic working of the shell
Description:
Basic libraries included -> 
  1. stdio.h -> to perform input output operation
  2. readline/readline.h -> to take input of the string
  3. string.h -> to perform operations on the character array
  4. stdlib.h -> to give dynamic allocation
  5. unistd.h -> implementing specific functions
  6. sys/wait.h -> used for sleep function
  7. sys/types.h
Steps to interpret command
  1. It takes input through readline library.
  2. Then it parse space and save it in character array.
  3. It saves history in file.
  4. Then it check whether it is my own handler command.
  5. If it's my own handler command then it execute it.
  6. If not then check if contains pipe. If contains pipe then give error that piping is not allowed.
  7. If command is not in my own handler command then it will execute through excvp command.
Command in my command handler:-
  1. exit
  2. cd
  3. help
  4. hello
  5. history
  6. delHistory
  7. openHelp
My aim is to show how shell interpret the command.
