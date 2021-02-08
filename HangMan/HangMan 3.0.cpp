#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

string chooseWord();
void renderGame(string&, int&);
char readAGuess();
bool contain(string, char);
string update(string&, string, char);

const int MAX_BAD_GUESSES = 7;

int main()
{
	srand(time(0)); //sinh tu ngau nhien
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

const string WORD_LIST[] = {
		"angle", "ant", "apple", "arch", "arm", "army",
        "baby", "bag", "ball", "band", "basin", "basket", "bath", "bed", "bee", "bell", "berry",
        "bird", "blade", "board", "boat", "bone", "book", "boot", "bottle", "box", "boy",
        "brain", "brake", "branch", "brick", "bridge", "brush", "bucket", "bulb", "button",
        "cake", "camera", "card",  "cart", "carriage", "cat", "chain", "cheese", "chest",
        "chin", "church", "circle", "clock", "cloud", "coat", "collar", "comb", "cord",
        "cow", "cup", "curtain", "cushion",
        "dog", "door", "drain", "drawer", "dress", "drop", "ear", "egg", "engine", "eye",
        "face", "farm", "feather", "finger", "fish", "flag", "floor", "fly",
        "foot", "fork", "fowl", "frame",
        "garden", "girl", "glove", "goat", "gun",
        "hair", "hammer", "hand", "hat", "head", "heart", "hook", "horn", "horse",
        "hospital", "house",
        "island", "jewel",
        "kettle", "key", "knee", "knife", "knot",
        "leaf", "leg", "library", "line", "lip", "lock",
        "map", "match", "monkey", "moon", "mouth", "muscle",
        "nail", "neck", "needle", "nerve", "net", "nose", "nut",
        "office", "orange", "oven", "parcel", "pen", "pencil", "picture", "pig", "pin",
        "pipe", "plane", "plate", "plow", "pocket", "pot", "potato", "prison", "pump",
        "rail", "rat", "receipt", "ring", "rod", "roof", "root",
        "sail", "school", "scissors", "screw", "seed", "sheep", "shelf", "ship", "shirt",
        "shoe", "skin", "skirt", "snake", "sock", "spade", "sponge", "spoon", "spring",
        "square", "stamp", "star", "station", "stem", "stick", "stocking", "stomach",
        "store", "street", "sun",
        "table", "tail", "thread", "throat", "thumb", "ticket", "toe", "tongue", "tooth",
        "town", "train", "tray", "tree", "trousers",
        "umbrella",
        "wall", "watch", "wheel", "whip", "whistle", "window", "wire", "wing", "worm"}; //danh sach tu co dinh
const int WORD_COUNT = sizeof(WORD_LIST) / sizeof(string);//so luong tu cua danh sach

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
    int index = rand() % WORD_COUNT;//random ra chi so cua tu trong danh sach
    return WORD_LIST[index];//tra ve tu ngau nhien
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

