#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <conio.h>

using namespace std;

// Initializing functions
void createDeck();
void game();
void drawCard(int offset, int chosenCard);

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
vector <vector <char>> cardPrint(6, vector <char>(200));

int main()
{
    srand(time(NULL));

    bool quit{ false };

    do {
        for (int i{ 0 }; i < 6; ++i) {
            for (int j{ 0 }; j < 100; ++j) {
                cardPrint[i][j] = ' ';
            }
        }
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
    int chosenCard{ 0 };
    int cardsDrawn{ 0 };

    do {
        system("cls");
        bool validInput{ false };

        cout << ".--------.\n";
        cout << "|   __   |\n";
        cout << "|  |  |  |\n";
        cout << "|    /   |\n";
        cout << "|    .   |\n";
        cout << "|________|\n";
        cout << "'--------'\n\n";

        cout << "(D) to draw a card\n";
        cout << "(H) to hold your hand\n";

        if (cardsDrawn != 0) {
            drawCard(cardsDrawn, chosenCard);
        }

        do {
            char input = _getch();
            switch (toupper(input)) {
            case 'D':
                ++cardsDrawn;
                validInput = true;
                do {
                    chosenCard = rand() % 52;
                } while (deck[chosenCard].drawn == true);
                break;

            case 'H':
                hold = true;
                validInput = true;
                break;

            default:
                break;
            }
        } while (!validInput);
    } while (!hold);
}

void drawCard(int offset, int chosenCard) {
    string cardTop{ ".--------." };
    string cardBottom{ "'--------'" };
    string fillTop{ ".--.  |" };
    string fillBottom{ "|  '--'" };
    vector <int> playerCards(10);
    vector <int> houseCards(10);
    ostringstream line1;
    ostringstream line2;
    ostringstream line3;
    ostringstream line4;
    --offset;
    offset *= 5;

    deck[chosenCard].drawn = true;

    line1 << "|" << deck[chosenCard].name << deck[chosenCard].suit << fillTop;
    line4 << fillBottom << deck[chosenCard].name << deck[chosenCard].suit << "|";

    if (deck[chosenCard].suit == hearts) {
        line2 << "|  (\\/)  |";
        line3 << "|  :\\/:  |";
    }
    else if (deck[chosenCard].suit == diamonds) {
        line2 << "|  :/\\:  |";
        line3 << "|  :\\/:  |";
    }
    else if (deck[chosenCard].suit == clubs) {
        line2 << "|  :():  |";
        line3 << "|  ()()  |";
    }
    else if (deck[chosenCard].suit == spades) {
        line2 << "|  :/\\:  |";
        line3 << "|  (__)  |";
    }

    for (int j{ 0 }; j < 10; ++j) {
        cardPrint[0][offset + j] = cardTop[j];
        cardPrint[1][offset + j] = line1.str()[j];
        cardPrint[2][offset + j] = line2.str()[j];
        cardPrint[3][offset + j] = line3.str()[j];
        cardPrint[4][offset + j] = line4.str()[j];
        cardPrint[5][offset + j] = cardBottom[j];
    }

    for (int i{ 0 }; i < 6; ++i) {
        for (int j{ 0 }; j < 100; ++j) {
            cout << cardPrint[i][j];
        }
        cout << '\n';
    }
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