//provides the implementation of 
#include"Led.h"
#include<iostream>
#include"Command.h"
#include<string>
#include <fstream>

Led::Led()									//Default constructor
{
	cout << "?   [New File]" << endl;
}
Led::Led(const string & file)			//Conversion constructor
{
	if (file == "")						//if filename not entered
	{
		Led();
	}
	else
	{
		string line;
		filename = file;
		ifstream myfile;
		myfile.open(filename);
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				buffer.push_back(line);			//file content copied into buffer
				count++;
			}
			cout << "\"" << filename << "\" " << count << "lines" << endl;
		}

		else
		{
			cout << "unable to open the file " << filename << endl;
			cout << " \"" << filename << "\"    [New File]" << endl;
		}
		myfile.close();
		
		}
}
void Led::run()							//run function
{
	i_first = buffer.begin();
	i_current = buffer.end();
	i_last = buffer.end();
	int distance = std::distance(i_first, i_last);
	current_line = distance; last_line = distance;
	string command_line;
	cout << "entering command mode" << endl;
	Command cmd;																									
	do
	{
		cout<< ":";
		getline(cin, command_line);									   // read a command line
		cmd.parse(command_line, current_line, last_line);			  // parse the command line
		int start = cmd.getstart();
		int end = cmd.getend();
		char command = cmd.getcmd();
		
		if (start <0 || end <0 || command == '\0')
		{			cout << "Invalid command"<<endl;
			run();
		}
		execute(cmd);							// execute the command
		} while (cmd.getcmd() != 'q');
}

void Led::execute(Command command)					//execute function calls the required function
{
	if (command.getcmd() == 'i'||command.getcmd() == 'I')
		insert(command);
	else if (command.getcmd() == 'p' || command.getcmd() == 'P')
		print(command);
	else if (command.getcmd() == 'n' || command.getcmd() == 'N')
		line_number(command);
	else if (command.getcmd() == 'a' || command.getcmd() == 'A')
		append(command);
	else if (command.getcmd() == 'w' || command.getcmd() == 'W')
		write(command);
	else if (command.getcmd() == 'c' || command.getcmd() == 'C')
		change(command);
	else if (command.getcmd() == '=')
		equal_to(command);
	else if (command.getcmd() == 'e'||command.getcmd() == 'E')
		enter(command);
	else if (command.getcmd() == 'u'|| command.getcmd() == 'U')
		up(command);
	else if (command.getcmd() == 'd'|| command.getcmd() == 'D')
		down(command);
	else if (command.getcmd() == 'r'||command.getcmd() == 'R')
		remove(command);
	else if (command.getcmd() == 'q'|| command.getcmd() == 'Q')
		quit(command);
	else
	{
		cout << "Invalid Command "<<endl;
		return;
	}
}


void Led::append(Command c)								//appends the entered data 
{
	
	int position= c.getstart();
	string input;
	getline(cin,input);
	list<string>::iterator i_firstcopy=i_first;
	if (position >= 1)
	{
		advance(i_firstcopy, position);
	}

	while (input != ".")						//till input is not . takes input from user
	{
		buffer.insert(i_firstcopy, input);
		position++;
		getline(cin, input);
	}

	i_current = --i_firstcopy;
	current_line = position;
	i_first = buffer.begin();
	i_last = buffer.end();
	last_line = distance(i_first, i_last);
	saved = false;
}
void Led::change(Command c)				//change the entered string by user to replacement string
{
	list<string>::iterator i_firstcopy = buffer.begin();
	int startline = c.getstart();
	int endline = c.getend();
	int diff = endline - startline;
	string from, to;
	int len;
	cout << "change what?:";
	getline(cin, from);
	len = from.length();
	cout << "change to:";
	getline(cin, to);
	if (startline == endline)
	{
		advance(i_firstcopy, startline - 1);
		int pos = (*i_firstcopy).find(from, 0);
		if (pos < 0)
		{
			cout << "String not found" << endl;
		}
		while (pos >= 0)
		{
			(*i_firstcopy).replace(pos, len, to);
			pos = (*i_firstcopy).find(from, pos + len);
		}
	}
	else
	{
		list<string>::iterator i_lastcopy = buffer.begin();
		advance(i_lastcopy, endline);
		bool found = false;
		while (i_firstcopy != i_lastcopy)
		{
			int pos = (*i_firstcopy).find(from, 0);
			while (pos >= 0)
			{
				found = true;
				(*i_firstcopy).replace(pos, len, to);
				pos = (*i_firstcopy).find(from, pos + len);
			}
			++i_firstcopy,current_line++;
		}
		if (!found)
			cout << "string not found" << endl;
	}
	i_current = i_firstcopy;
	current_line = endline;
	saved = false;
}
void Led::enter(Command c)						//moves the current line down by one
{
	int moves = 1;
	if (i_current == --buffer.end())
	{
		cout << "EOF Reached" << endl;
	}
	else
	{
		++i_current;
		++current_line;
	}
}
void Led::remove(Command c)				//removes the mentioned lines from buffer
{
	int a = c.getstart();
	int b = c.getend();
	list<string>::iterator i_firstcopy = i_first;
	list<string>::iterator i_firstcopy2 = i_first;
	if(!buffer.empty())
	{
	advance(i_firstcopy, a - 1);
	advance(i_firstcopy2, b);
	list<string>::iterator i_current;
	buffer.erase(i_firstcopy, i_firstcopy2);
	i_first = buffer.begin();
	i_last = buffer.end();
	int dist = distance(i_first, i_last);
	current_line = distance(i_first,i_firstcopy2);
	if (current_line == 0)
		current_line++;
	last_line = dist;
	if (i_firstcopy2 != buffer.end())
	{
		i_current = i_firstcopy2;
	}
	else
	{
		if (i_first != buffer.end())
		{
			i_firstcopy = i_first;
			advance(i_firstcopy, dist - 1);
			i_current = i_firstcopy;
		}
	}
	}
	saved = false;

}
void Led::write(Command c)					//writes the contents of buffer into file
{
	int count=0;
	if (filename == "")
	{
		cout << "enter the filename:" << endl;
		cin >> filename;
	}
	ofstream out;
	out.open(filename);
	
	current_line = 0;
	last_line = 0;
	for (std::list<string>::iterator it =buffer.begin(); it != buffer.end(); ++it)
	{
		++current_line, ++last_line;
		out << *it<<endl;
		count++;
	}
	i_current = --buffer.end();
	i_last = --buffer.end();
	saved = true;
	out.close();
	cout << "\"" << filename << "\"   " << count << "lines written"<<endl;
}

void Led::up(Command c)					//moves the currentline up by number of mentioned lines
{
	bool bof = false;
	int a = c.getstart();
	list<string>::iterator i_firstcopy = buffer.begin();
	
	int dist = distance(i_firstcopy,i_current);
	if(dist==0)
	{
		cout << "BOF Reached"<<endl;
	}
	else
	{
		while (a > 0&&bof==false)
		{
			if (i_current == buffer.begin())
			{
				cout << "BOF Reached"<<endl;
				bof = true;
			}
			else
			{
			--i_current;
			--current_line;
			a--;
			}
		}
	}
	cout << *i_current<<endl;
}
void Led::down(Command c)			//moves the current line down by mentioned number of lines
{
	bool eof = false;
	int moves = c.getstart();
	if (i_current == --buffer.end())
	{
		cout << "EOF Reached"<<endl;
	}
	else
	{
		while (moves > 0 && i_current != buffer.end()&&eof==false)
		{
			if (i_current == --buffer.end())
			{
				eof = true;
				cout << "EOF Reached"<<endl;
			}
			else
			{
				++i_current;
				++current_line;
				moves--;
			}
		}
	}
	cout << *i_current<<endl;
	}

void Led::line_number(Command c)			//prints the buffer with number line
{
	
		int startline = c.getstart();
		int endline = c.getend();

		list<string>::iterator i_firstcopy = buffer.begin();
		list<string>::iterator i_lastcopy = buffer.end();

		list<string>::iterator i_current;
		if (i_firstcopy == i_lastcopy)
		{
			cout << "No data in the file"<<endl;
		}
		else
		{
		if (startline == endline)
		{
			advance(i_firstcopy, startline - 1);
			cout << startline << "  " << *i_firstcopy << endl;
			i_current = i_firstcopy;
		}
		else
		{
			int diff = endline - startline + 1;
			advance(i_firstcopy, startline - 1);

			while ((distance(i_firstcopy, i_lastcopy)) != diff)
			{
				--i_lastcopy;
			}
			while (i_firstcopy != i_lastcopy)
			{
				std::cout << startline << "   " << *i_firstcopy << endl;
				i_firstcopy++;
				startline++;
			}
			i_current = --i_firstcopy;
		}		
	}
}
void Led::equal_to(Command c)			//prints the number of current line
{
	int startline = c.getstart();
	cout << startline<<endl;
	}

void Led::quit(Command c)				//saves the file before quitting
{
	int count=0;
	string response;
	if (saved == false)
	{
		cout << "File not saved.Would you like to save?(Press y||n)";
		cin >> response;
	label:	if (response == "y" || response == "Y")
	{
		if (filename == "")
		{
			cout << "enter the filename:";
			cin >> filename;
		}
		ofstream out;
		out.open(filename);
		for (std::list<string>::iterator it = buffer.begin(); it != buffer.end(); ++it)
		{
			out << *it << endl;
			count++;
		}
		cout << "\"" << filename << "\"   " << count << "lines written" << endl;
		out.close();
		}
			else if(response=="N"||response=="n")
			{
			}
			else
			{
				cout << "invalid response.."<<endl<<"Press y or n"<<endl;
				goto label;
			}

		}
	
		cout << "Quiting led!!..bye..."<<endl;
		
}
void Led::insert(Command c)						//insert  the content entered to a given line in buffer
{
	int startline= c.getstart();
	int endline = c.getend();
	if (startline == 0)
	{++startline; }
	string input;
	getline(cin, input);
	list<string>::iterator i_firstcopy = i_first;
	
		advance(i_firstcopy, startline-1);
	
	while (input != ".")
	{
		buffer.insert(i_firstcopy, input);
		startline++;
		getline(cin, input);
	}

	i_current = --i_firstcopy;
	current_line = startline-1;
	i_first = buffer.begin();
	i_last = buffer.end();
	last_line = distance(i_first, i_last);
	saved = false;
}

void Led::print(Command c)			//print the buffer from a given line
{
	int startline = c.getstart();
	int endline = c.getend();

	list<string>::iterator i_firstcopy = i_first;
	list<string>::iterator i_lastcopy = i_last;
	list<string>::iterator i_currentcopy = i_current;
	if (i_firstcopy == i_lastcopy)
	{
		cout << "No data in the file"<<endl;}
	else
	{
		if (startline == endline)
		{
			advance(i_firstcopy, startline - 1);
			cout << *i_firstcopy << endl;
			current_line = distance(i_first, i_firstcopy) + 1;
			i_current = i_firstcopy;
		}
		else
		{
			int c = endline - startline + 1;
			advance(i_firstcopy, startline - 1);
			while ((distance(i_firstcopy, i_lastcopy)) != c)
			{
				--i_lastcopy;
			}

			while (i_firstcopy != i_lastcopy)
			{
				std::cout << ' ' << *i_firstcopy << endl;
				i_firstcopy++;
			}
			current_line = distance(i_first, i_firstcopy);
			i_current = --i_firstcopy;
		}
		
	}
}

