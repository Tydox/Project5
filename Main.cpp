//#include <iostream>
//#include "DataFile.h"
//#include "Folder.h"
//#include <iostream>
//#include <typeinfo>
//using namespace std;
//void main() {
//	Folder* root = Folder::root;
//	root->mkDir("C:");
//	root->mkDir("D:");
//	Folder* curr = Folder::cd("C:");
//	bool quit = false; string path;
//	string command, p_command;
//	char echoStream[256];
//	do {
//		std::cout << curr->getFullPath().substr(5) << ">";//deletes Root Folder Name
//		cin.ignore(cin.rdbuf()->in_avail());
//		cin >> command;
//		try {
//			if (command == "cd") {
//				cin.ignore(1);
//				cin >> p_command;
//				curr = Folder::cd(p_command);
//				continue;
//			}
//			if (command == "mkdir") {
//				cin.ignore(1);
//				cin >> p_command;
//				curr->mkDir(p_command);
//				continue;
//			}
//			if (command == "dir") {
//				curr->dir();
//				continue;
//			}
//			if (command == "echo") {
//				cin.ignore(1);
//				std::cin.getline(echoStream, 256);
//				command = echoStream;
//				curr->mkfile(command.substr(command.find('<') + 2),
//					command.substr(0, command.find('<') - 1));
//				continue;
//			}
//			if (command == "FC") {
//				cin.ignore(1);
//				cin >> p_command;
//				cin.ignore(1);
//				cin >> command;
//				if (fc(*curr, p_command, command) == true)
//					cout << " equals\n";
//				else
//					cout << " not equals\n";
//				continue;
//			}
//		}
//		catch (const char* msg) { cout << msg << endl; }
//		catch (...) {
//			std::cout << "unhandeled eception";
//		};
//		break;
//	} while (!quit);


#include <iostream>

int main() {}