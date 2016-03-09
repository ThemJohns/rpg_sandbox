#include <string>
#include <iostream>
#include <stdio.h>

#include "general_functions.h"
#include "character.h"
#include "battle_system.h"

using namespace std;

void main() {
	Player p;
	int s;
	bool exit;

	srand(time(NULL));
	//Title Screen
	cout << "________________________________________" << endl << endl;
	cout << "              RPG SANDBOX               " << endl;
	cout << "            A short project             " << endl;
	cout << "________________________________________" << endl << endl;
	PressEnter("Press ENTER to continue... ");

	//Main Menu
	do {
		cout << endl << "____________" << endl << " Main Menu " << endl << "____________" << endl;
		cout << "Choose an option:" << endl;
		cout << "1) Play Now" << endl;
		cout << "2) Manual" << endl;
		cout << "3) About" << endl;
		cout << "4) Exit" << endl;
		s = validNumber("Select an option:");
		switch(s){
			case 1:
				createPlayer();
				exit = false;
				break;
			case 2:
				cout << endl << "____________" << endl << "  Manual  " << endl << "____________" << endl;
				viewManual();
				cout << endl << "____________" << endl << " Main Menu " << endl << "____________" << endl;
					cout << "Choose an option:" << endl;
					cout << "1) Play Now" << endl;
					cout << "2) Manual" << endl;
					cout << "3) About" << endl;
					cout << "4) Exit" << endl;
				exit = false;
				break;
			case 3:
				cout << endl << "____________" << endl << "  About  " << endl << "____________" << endl;
				cout << "A 'small' RPG made by Calvin Kim." << endl;
				exit = false;
				break;
			case 4:
				exit = true;
				break;
			default:
				exit = false;
				break;
		}
	} while (!exit);

	return;
}