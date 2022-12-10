#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

struct hangman{
private:
	vector<string> wordlist = { "test1", "test12", "test123", "test1234", "test12345" };
	string word;
	string wordGuessed = word;
};

int main()
{
	hangman game;
}
