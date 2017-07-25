// MasterMind.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <ctime>

#include "Color.h"

#define MAX_TRIES 10
#define MAX_COLORS 4
#define MAX_POSITIONS 4
#define NUM_COLORS 7

using namespace std;

vector< char > colors = {
	
	'R', // RED
	'G', // GREEN
	'B', // BLUE
	'V', // VIOLET
	'T', // TEAL
	'Y', // YELLOW
	'O'	 // ORANGE
};

vector< int > positions = {

	1,
	2,
	3,
	4
};

string get_user_in(string uin);
bool correct_user_in_length(string gin);
bool correct_user_in_colors(string gin);


int main()
{

	cout << "Welcome inferior human to Mastermind" << endl;
	cout << "You will now be tested to show you how inferior you really are!" << endl;
	cout << "I will now choose 4 unique colors with a unique sequence" << endl;
	cout << "It is your test to find out what that sequence of colors is..." << endl;
	cout << "Are you up for that challenge?" << endl << endl;

	// CPU initilize its colors

	// Color Buffers
	Color cpu_colors[MAX_COLORS];
	Color human_colors[MAX_COLORS];
	string cpu_hint_colors;
	int correct_color_and_position = 0;

	srand(time(0));
	int randcolor;
	int randposition;

	// Choose unique colors with unique positions
	for (Color &c : cpu_colors) {

		randcolor = (rand() % colors.size());
		randposition = (rand() % positions.size());

		c.setColor(colors[randcolor]);
		c.setPosition(positions[randposition]);

		colors.erase(colors.begin() + randcolor);
		positions.erase(positions.begin() + randposition);
	}

	// Test code
	for (Color c : cpu_colors) {

		cout << "Color: " << c.getColor() << ", " << "Position: " << c.getPosition() << endl;
	}

	// Game starts
	string user_in;
	int num_tries = MAX_TRIES;

	while (1) {

		cout << endl;
		cout << "You have only " << num_tries << " tries left" << endl;
		cout << "Choose a sequence of 4 colors" << endl;
		cout << "Choices: R G B T Y V O" << endl << endl;
		cout << "Enter a color sequence: ";
		getline(cin, user_in);

		// Get user input
		string uin = get_user_in(user_in);

		// Verify user input
		if (!correct_user_in_length(uin)) {
			cout << endl;
			cout << "**************************" << endl;
			cout << "Please enter only 4 colors" << endl;
			cout << "**************************" << endl;
			continue;
		}

		if (!correct_user_in_colors(uin)) {
			cout << endl;
			cout << "**************************************************" << endl;
			cout << "Please enter only colors from the choices provided" << endl;
			cout << "**************************************************" << endl;
			continue;
		}

		int color_pos = 0;
		for (char c : uin) {
			human_colors[color_pos].setColor(c);
			human_colors[color_pos].setPosition(color_pos + 1);
			color_pos++;
		}



		// Compare user color sequence to computer color sequence
		cpu_hint_colors = "";
		correct_color_and_position = 0;
		for (Color hc : human_colors) {

			for (Color cc : cpu_colors) {
				if (hc.getColor() == cc.getColor()) {
					if (hc.getPosition() == cc.getPosition()) {
						cpu_hint_colors += "R";
						correct_color_and_position++;
					}
					else {
						cpu_hint_colors += "W";
					}
				}
			}
		}

		for (Color c : human_colors) {

			cout << c.getColor() << " ";
		}

		cout << "\t";

		sort(cpu_hint_colors.begin(), cpu_hint_colors.end());
		for (char c : cpu_hint_colors) {

			cout << c << " ";
		}
		cout << endl;
		
		if (correct_color_and_position == MAX_COLORS) {
			cout << endl;
			cout << "You got the sequence, maybe you are not so inferior after all" << endl;
			break;
		}

		num_tries--;
		if (num_tries <= 0) {
			cout << "You lost inferior human ahahah..." << endl;
			break;
		}

		cout << endl << endl;
	}


	// Test code
	for (Color c : cpu_colors) {

		cout << "Color: " << c.getColor() << ", " << "Position: " <<  c.getPosition() << endl;
	}

	int e = 0;
	while (e != 1) {
		cin >> e;
	}

    return 0;
}

string get_user_in(string uin) {

	// Grab all alphabetic characters the user entered
	string in;
	int user_in_length = uin.length();
	for (int idx = 0; idx < user_in_length; idx++) {
		
		if (isalpha(uin[idx])) {
			in += toupper(uin[idx]);
		}
	}

	return in;
}

bool correct_user_in_length(string gin) {
	
	if (gin.length() != MAX_COLORS ) {
		return false;
	}

	return true;
}

bool correct_user_in_colors(string gin) {

	string colors = "RGBTVYO";
	for (char c : gin) {
		
		if (colors.find(c) == string::npos) {
			return false;
		}
	}

	return true;
}


