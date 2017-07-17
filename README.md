# Commandline-Text-Editor
Course Assignment
It is a C++ based Line Editor(Led)
Project contains 5 Files:- Souce.cpp,Led.h,Led.cpp,Command.cpp,Command.h

Instructions to run the editor:-
1.Source.cpp containing main function, file is run to start the text editor and the file name (.txt) is passed as argument.
or 
led.exe is directly executed in command prompt with file name.
eg:led a.txt

If the file alread exits it opens if not then new text file opens.
Modes Supported:-
1.Input Mode :-commands a and i put led into input mode.
2.Command Mode-(default)-: symbol represents the command mode.Dot character(.) is entered to get back into command mode.

Commands Supported:-
All commands makes changes in buffer(copied file) not in the orignal text file .Changes are saved in file when write(w) command is executed.
1.n a - input mode-reads input line and append them after line number n and current line address saved as last line entered.
2.n i- input mode-reads input line and append them before line number n and current line address saved as last line entered.
3.x,y r- removes the lines from x,y from buffer and current line address saved as  line after y.
4.x,y p-prints the line range from x to y.
5.x,y n-prints the line range from x to y by adding line number in front of each line.
6.x,y c- prompts the user to enter the text to be changed by desired text and then change all the occurences of text to be changed in line         range x to y.
7.x a- moves the cursor up by x lines.
8. x d- moves the cursor down by  x lines.
9. '=' -equal to command prints the address of current line.
10. enter- enter key moves the cursor by one line.
11.w- write command writes the buffer into associated file.

if . is entered in command then it means current line eg:- .,10 p means print lines from current line to 10th line.
if $ is entered in command then it means last line eg:- 1,$ p means print lines from 1st line to last line.
if user dont enters the x and y with command  then they are taken as current line eg:- ,p or .p is entered as command then only current line is printed.
if user dont enter any command with x and y then default command is print .eg-1,3 -prints lines from 1 to 3.










