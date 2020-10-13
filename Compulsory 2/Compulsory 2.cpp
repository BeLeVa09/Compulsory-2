#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <conio.h>

using namespace std;

// Initializing functions
void createDeck();
void game();
void drawCard();

// Setting ascii values for card suits
const char hearts = 3;
const char diamonds = 4;
const char clubs = 5;
const char spades = 6;

// Creating an object for every unique card
struct Card {
    int number{ 0 };
    char suit{ ' ' };
    int value{ 0 };
    bool drawn{ false };
    bool isAce{ false };
    char name{ ' ' };
};

vector <Card> deck(52);

int main()
{
    srand(time(NULL));

    bool quit{ false };

    do {
        createDeck();
        system("cls");

        cout << "\t\t\t______ _            _      ___            _\n";
        cout << "\t\t\t| ___ \\ |          | |    |_  |          | |\n";
        cout << "\t\t\t| |_/ / | __ _  ___| | __   | | __ _  ___| | __\n";
        cout << "\t\t\t| ___ \\ |/ _` |/ __| |/ /   | |/ _` |/ __| |/ /\n";
        cout << "\t\t\t| |_/ / | (_| | (__|   </\\__/ / (_| | (__|   <\n";
        cout << "\t\t\t\\____/|_|\\__,_|\\___|_|\\_\\____/\\___,_|\\___|_|\\_\\\n\n";

        cout << "\t\t\t\t\t    1. Play\n";
        cout << "\t\t\t\t\t    2. Rules\n";
        cout << "\t\t\t\t\t    3. Exit\n";

        char input = _getch();

        switch (input) {
        case '1':
            game();
            break;

        case '2':
            break;

        case '3':
            quit = true;
    
            break;

        default:
            break;
        }

    } while (!quit);
}

void game() {
    system("cls");

    int playerMoney{ 100 };
    int houseMoney{ 100 };
    bool hold{ false };
    vector <int>
    
    cout << ".--------.\n";
    cout << "|   __   |\n";
    cout << "|  |  |  |\n";
    cout << "|    /   |\n";
    cout << "|    .   |\n";
    cout << ":--------:\n";
    cout << "'--------'\n\n";

    cout << "(D) to draw a card\n";
    cout << "(H) to hold your hand\n";

    do {
        char input = _getch();
        switch (toupper(input)) {
        case 'D':
            drawCard();
            break;

        case 'H':
            hold = true;
            break;

        default:
            break;
        }
    } while (!hold);
}

void drawCard() {
    string cardTop{ ".--------." };
    string cardBottom{ "'--------'" };
    string fillTop{ ".--.  |" };
    string fillBottom{ "|  '--'" };
    int chosenCard{ 0 };

    do {
        chosenCard = rand() % 52;
    } while (deck[chosenCard].drawn == true);

    deck[chosenCard].drawn = true;

    cout << cardTop << '\n';
    cout << "|" << deck[chosenCard].name << deck[chosenCard].suit << fillTop << '\n';

    if (deck[chosenCard].suit == hearts) {
        cout << "|  (\\/)  |\n";
        cout << "|  :\\/:  |\n";
    }
    else if (deck[chosenCard].suit == diamonds) {
        cout << "|  :/\\:  |\n";
        cout << "|  :\\/:  |\n";
    }
    else if (deck[chosenCard].suit == clubs) {
        cout << "|  :():  |\n";
        cout << "|  ()()  |\n";
    }
    else if (deck[chosenCard].suit == spades) {
        cout << "|  :/\\:  |\n";
        cout << "|  (__)  |\n";
    }
    cout << fillBottom << deck[chosenCard].name << deck[chosenCard].suit << "|\n";
    cout << cardBottom << '\n';
}

void createDeck() {
    char suit{ 3 };

    // Initializing every card in order of Hearts, Diamonds, Clubs & Spades; Ace to King
    for (int i{ 0 }; i < 52; ++i) {
        deck[i].number = i % 13 + 1;
        deck[i].suit = suit;
        deck[i].value = i % 13 + 1;
        deck[i].name = i % 13 + 49;
        deck[i].drawn = false;

        if (deck[i].name == ':') {
            deck[i].name = 'T';
        }
        else if (deck[i].name == ';') {
            deck[i].name = 'J';
        }
        else if (deck[i].name == '<') {
            deck[i].name = 'Q';
        }
        else if (deck[i].name == '=') {
            deck[i].name = 'K';
        }

        if ((i % 13 + 1) == 1) {
            deck[i].isAce = true;
            deck[i].name = 'A';
        }

        if ((i % 13) > 9) {
            deck[i].value = 10;
        }

        if (i % 13 == 12) {
            suit++;
        }
    }
}