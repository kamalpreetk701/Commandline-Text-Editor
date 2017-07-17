
#include<string>
#include"Command.h"
#include"iostream"
#include"Led.h"
using namespace std;



	int main(int argc, char * argv[])
		 {
		 string filename; // an empty line
		
			
			switch (argc)
			 {
			 case 1: // no file name
			 break; // spelling error
				
			case 2: // read from argument string
			filename = argv[1]; // initialize filename
			break;
						
			 default:
			 cout << "too many arguments - all discarded " <<endl;
			 break;
			}
		Led led(filename);
		led.run();
		
		return 0; 
		 

}