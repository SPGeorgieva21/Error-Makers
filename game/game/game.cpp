#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <string>

using namespace std;

struct hangman {

	/*PICKS RANDOM WORD FROM WORDLIST*/

	string pickStr() {
		srand(time(0));
		int temp = rand() % wordlist.size();
		return wordlist[temp];
	}

	/*RESET THE WORD / MAKE IT BLANK*/

	void clearWordGuessed() {
		for (size_t i = 0; i < wordGuessed.length(); i++) {
			if (wordGuessed[i] != ' ') {
				wordGuessed[i] = '_';
			}
			else {
				wordGuessed[i] = ' ';
			}
		}
	}

	/*OUTPUTS LETTERS OF A STRING WITH EQUAL INTERVALS OF TIME BETWEEN EVERY LETTER*/

		void typePrint(string str, float time /*SECONDS*/) {
		for (size_t i = 0; i < str.size(); i++) {
			cout << str[i];
			Sleep((time * 1000) / str.size());
		}
	}

	/*	FUNCTION USED FOR DEBUGGING*/

	void printWordGuessed() {
		for (size_t i = 0; i < wordGuessed.length(); i++) {
			cout << wordGuessed[i];
		}
	}

	/*FUNCTION USED TO INPUT LETTERS*/

	char choseLetter(bool first /*BOOL FOR RECURSION*/) {
		if (first == true) {
			typePrint("Guess a letter: ", 0.5);
		}
		char input;
		cin >> input;
		bool flag = false;
		for (size_t i = 0; i < lettersGuessed.size(); i++) {
			if (input == lettersGuessed[i]) flag = true;
		}
		if (flag == true) {
			typePrint("Please chose a letter you haven't chosen before: ", 1);
			choseLetter(false);
			return 0;
		}
		else {
			lettersGuessed.insert(lettersGuessed.end(), input);
			return input;
		}
	}

	/*FUNCTION ASKS PLAYER IF THEY WANT TO RESTART/PLAY AGAIN*/

	void restart(bool first /*BOOL FOR RECURSION*/) {
		if (first == true) {
			typePrint("Do you want to restart the game? (Y/N)", 1);
			cout << '\n';
		}
		char input;
		cin >> input;
		if (input != 'Y' && input != 'N') {
			typePrint("Please use a valid input (Y/N): ", 1);
			restart(false);
		}
		if (input == 'Y') {
			system("CLS");
			startGame();
		}
		if (input == 'N') {
			exit(0);
		}
	}

	/*FUNCTION STARTS THE GUESSING PROCESS*/

	void startGuessing() {
		if (wordGuessed == word) {
			system("CLS");
			cout << "You won!" << '\n' << "The word was '" << word << "'!" << '\n' << "Lives Remaining: " << lives;
			cout << '\n';
			restart(true);
		}
		else {
			cout << wordGuessed << '\n' << '\n';
			cout << "Lives Remaining: " << lives << '\n';
			if (lettersGuessed.size() != 0) {
				cout << "Letters Guessed: ";
				for (size_t i = 0; i < lettersGuessed.size(); i++) {
					cout << lettersGuessed[i] << " ";
				}
				cout << '\n';
			}
			Sleep(500);
			newTurn();

		}
	}

	/*FUNCTION STARTS A NEW TURN FOR THE PLAYER TO GUESS*/

	void newTurn() {
		char str = choseLetter(true);
		system("CLS");
		bool flag = false; /*BOOLEAN FOR WHETHER OR NOT LETTER IS FOUND IN WORD*/
		for (size_t i = 0; i < wordGuessed.length(); i++) {
			if (str == word[i]) {
				wordGuessed[i] = word[i];
				flag = true;
			}
		}
		if (flag == true) {
			typePrint("You guessed correctly!", 0.5);
			cout << '\n';
			Sleep(500);
			startGuessing();
		}
		if (flag == false) {
			lives--;
			if (lives > 0) {
				typePrint("You guessed incorrectly!", 1);
				cout << '\n';
				startGuessing();
			}
			else {
				typePrint("You guessed incorrectly and lost the game!", 1);
				cout << '\n';
				typePrint("The word was '" + word + "'", 1);
				cout << '\n';
				restart(true);
			}
		}
	}

	/*FUNCTION STARTS THE GAME*/

	void startGame() {
		lettersGuessed.clear(); /*CLEARS ANY LETTERS FROM PREVIOUS PLAYTHROUGHS*/
		clearWordGuessed();
		typePrint("Please chose one of the following difficulties:", 1);
		Sleep(300);
		cout << '\n';
		for (size_t i = 0; i < dif.size(); i++) {
			//string livesHearts = "";
			//for (int j = 0; j < dif[i]; j++) {
			//	livesHearts += "";
			//}
			cout << difName[i] << " (" << i + 1 << "): " << dif[i] << " lives" << '\n';
		}
		Sleep(500);
		choseDif(true);
		startGuessing();

	}

	/*CHOSE DIFFICULTY*/

	void choseDif(bool first /*BOOL FOR RECURSION*/) {
		if (first == true) { 
			typePrint("Which difficulty do you chose? (1-" + to_string(dif.size()) + "): ", 1);
		}
		int temp;
		cin >> temp;
		if (temp > 0 && temp <= dif.size()) {
			difficulty = temp;
			lives = dif[temp - 1];
			typePrint("You have chosen [" + difName[difficulty - 1] + " Difficulty] with " + to_string(lives) + " lives." + '\n' + "Game will now commence.", 2);
			Sleep(2000);
			system("CLS");
		}
		else {
			typePrint("Please chose a valid difficulty (1-" + to_string(dif.size()) + "): ", 1);
			choseDif(false);
		}
	}

	string* wordPtr = &word;

private:
	vector<string> wordlist = /*ADD WORDS HERE*/ { "test1", "test12", "test123", "test1234", "test12345" };
	vector<int> dif = /*NUMBER OF DIFFICULTIES AND LIVES PER DIFFICULTY*/{ 9,7,5,3,1 };
	vector<string> difName = /*INDEX OF NAME CORESPONDS TO INDEX OF LIVES PER DIFFICULTY*/{ "Easy", "Standard", "Hard", "Insane", "Perfect" };
	vector<char> lettersGuessed; /*DONT ADD ANYTHING HERE*/

	string word = pickStr();
	string wordGuessed = word; 
	int difficulty; /*DIFFICULTY REPRESENTED BY INDEX*/
	int lives;
};

int main()
{
	hangman game; /*CREATING OBJECT OF STRUCTURE HANGMAN*/
	game.startGame(); /*CALLING FUNCTION FROM OBJECT GAME*/
}
