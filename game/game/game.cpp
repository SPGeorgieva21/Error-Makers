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
	string pickStr() {
		srand(time(0));
		int temp = rand() % wordlist.size();
		return wordlist[temp];
	}

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

	void printWordGuessed() {
		for (size_t i = 0; i < wordGuessed.length(); i++) {
			cout << wordGuessed[i];
		}
	}

	//void checkLetter(char str) {
	//	bool flag = false;
	//	for (size_t i = 0; i < wordGuessed.length(); i++) {
	//		if (str == word[i]) {
	//			wordGuessed[i] = word[i];
	//			flag = true;
	//		}
	//	}
	//	if (flag == false) {

	//	}
	//}

	void typePrint(string str, int time /*SECONDS*/) {
		for (size_t i = 0; i < str.size(); i++) {
			cout << str[i];
			Sleep((time * 1000) / str.size());
		}
	}

	void choseDif() {
		int temp;
		typePrint("Please chose one of the following difficulties:", 1);
		Sleep(300);
		cout << '\n';
		for (size_t i = 0; i < dif.size(); i++) {
			//string livesHearts = "";
			//for (int j = 0; j < dif[i]; j++) {
			//	livesHearts += "";
			//}
			cout << difName[i] << " (" << i+1 << "): " << dif[i] << " lives" << '\n';
		}
		Sleep(500);
		typePrint("Which difficulty do you chose? (1-" + to_string(dif.size() + 1) + "): ", 1);
		cin >> temp;
		difficulty = temp;
		lives = dif[temp];
		for (size_t i = 0; i < dif.size(); i++) {

		}
	}

	string* wordPtr = &word;

private:
	vector<string> wordlist = { "test1", "test12", "test123", "test1234", "test12345" };
	vector<int> dif = /*NUMBER OF DIFFICULTIES AND LIVES PER DIFFICULTY*/{ 9,7,5,3,1 };
	vector<string> difName = /*INDEX OF NAME CORESPONDS TO INDEX OF LIVES PER DIFFICULTY*/{ "Easy", "Standard", "Hard", "Insane", "Perfect" };

	string word = pickStr();
	string wordGuessed = word;
	int difficulty;
	int lives;
};

int main()
{
	;
	hangman game;
	//game.clearWordGuessed();
	//game.printWordGuessed();
	game.choseDif();
}
