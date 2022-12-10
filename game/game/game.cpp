#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

struct hangman{
	string pickStr() {
		srand(time(0));
		int temp = rand() % wordlist.size();
		return wordlist[temp];
	}

private:
	vector<string> wordlist = { "test1", "test12", "test123", "test1234", "test12345" };
	string word = pickStr();
	string wordGuessed = word;
};

int main()
{
	hangman game;
}
