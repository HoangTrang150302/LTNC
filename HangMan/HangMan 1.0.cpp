#include<iostream>
#include<string>
using namespace std;

string chooseword();
string updateword(string&, string, char);
bool contain(char, string);

int main()
{
	string secretWord = chooseword();
	string guessedword = string(secretWord.length(), '-');
	int count = 0;
	do
	{
		char guess;
		cout << "Enter a character: ";
		cin >> guess;
		if(contain(guess, secretWord))
		{
			guessedword = updateword(guessedword, secretWord, guess);
			cout << guessedword << endl;
		}
		else
		{
			cout << "You've enter a wrong answer!\n";
			cout << ++count << endl;
		}
	}
	while (count != 7 && secretWord != guessedword);
	if(count < 7) cout << "Congratulations! You win!";
	else cout << "You lost the correct word is " << secretWord;
	return 0;
}

string chooseword()
{
	return "programming";
}

bool contain(char guess, string secretWord)
{
	for (int i = 0; i < secretWord.length(); i++)
	{
		if(guess == secretWord[i])
		return true;
	}
	return false;
}
string updateword(string &guessedword, string secretWord, char guess)
{
	for (int i = 0; i < secretWord.length(); i++)
	{
		if(guess == secretWord[i])
		{
			guessedword[i] = secretWord[i];
		}
	}
	return guessedword;
}



