#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

string chooseWord();
void renderGame(string&, int&);
char readAGuess();
bool contain(string, char);
string update(string&, string, char);

const int MAX_BAD_GUESSES = 7;
vector<string> FILE_LIST;

int main()
{
    srand(time(0)); //sinh tu ngau nhien

    //lay tu tu file
    ifstream wordlist;
    wordlist.open("HangmanWords.txt");

    string fileword;
    while(getline(wordlist,fileword))
    {
        FILE_LIST.push_back(fileword);
        //cout << fileword << endl;
    }
    wordlist.close();

    /*for (int i = 0; i < FILE_LIST.size(); i++)
    {
        cout << FILE_LIST[i] << endl;
    }*/
    string word = chooseWord(); //khoi tao tu de doan
    string guessedWord = string(word.length(),'-'); //tu da doan khoi tao bang so tu cua tu can doan
    int badguesscount = 0;// dem so lan doan sai
    cout << "The secret word contains " << word.length() << " letters.\n";
    do
    {
        renderGame(guessedWord, badguesscount);//hien thi tinh trang cua game: tu da doan duoc va so lan doan sai
        char guess = readAGuess();// lay ki tu nguoi choi doan
        if(contain(word,guess)) //neu ki tu do co chua trong tu bi mat thi update tu da doan
        {
            guessedWord = update(guessedWord, word, guess);
        }
        else badguesscount++;//neu khong thi tang so lan doan sai
    }
    while(badguesscount < MAX_BAD_GUESSES && guessedWord != word);

	renderGame(guessedWord, badguesscount);

	if(badguesscount < MAX_BAD_GUESSES)
    {
        cout << "Congratulation. You win! ^_^";
    }
    else
    {
        cout << "You lost. The correct word is " << word;
    }
    return 0;
}

const string FIGURE[] = {
        "   -------------    \n"
        "   |                \n"
        "   |                \n"
        "   |                \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |                \n"
        "   |                \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |                \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |           |    \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|    \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|\\  \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|\\  \n"
        "   |          /     \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|\\  \n"
        "   |          / \\  \n"
        "   |     \n"
        " -----   \n"
    };

string chooseWord()
{
    int index = rand() % FILE_LIST.size();//random ra chi so cua tu trong danh sach
    return FILE_LIST[index];//tra ve tu ngau nhien
}

void renderGame(string &guessedWord, int &badguesscount)
{
    cout << guessedWord << endl;
    cout << FIGURE[badguesscount] << endl;
    cout << "Number of wrong guesses: " << badguesscount << endl;
}

bool contain(string word, char guess)
{
    for (int i = 0; i < word.length(); i++)
    {
        if(word[i] == guess)
        {
            return true;
        }
    }
    return false;
}

string update(string &guessedWord, string word, char guess)
{
    for(int i = 0; i < word.length(); i++)
    {
        if(word[i] == guess)
        {
            guessedWord[i] = guess;
        }
    }
    return guessedWord;
}

char readAGuess()
{
    char c;
    cout << "Your guess: ";
    cin >> c;
    return c;
}


