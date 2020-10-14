#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

// Initializing functions
void createDeck();
void game();
void drawCard(int offset, int chosenCard, int player, bool bank);

// Setting ascii values for card suits
const char hearts = 3;
const char diamonds = 4;
const char clubs = 5;
const char spades = 6;

// I know global variables are evil, but this is the only way I got the money system to work properly
int playerMoney{ 100 };
int houseMoney{ 100 };

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
vector <vector <char>> aiCardPrint(6, vector <char>(200));

int main()
{
    srand(time(NULL));

    bool quit{ false };

    do {
        for (int i{ 0 }; i < 6; ++i) {
            for (int j{ 0 }; j < 100; ++j) {
                cardPrint[i][j] = ' ';
                aiCardPrint[i][j] = ' ';
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
        cout << "\t\t\t\t\t    2. Exit\n";

        char input = _getch();

        switch (input) {
        case '1':
            game();
            break;

        case '2':
            quit = true;
            break;

        default:
            break;
        }

    } while (!quit);
}

void game() {

    bool hold{ false };
    int chosenCard{ 0 };
    int cardsDrawn{ 0 };
    int playerPoints{ 0 };
    int housePoints{ 0 };
    int bet{ 0 };
    int pot{ 0 };

    do {
        system("cls");
        cout << "Pay in starts at 10$\n";
        cout << "One cannot bet more than another player has\n";
        cout << "Your money: " << playerMoney << "$\n";
        cout << "House money: " << houseMoney << "$\n\n";

        cout << "Bet: ";
        cin >> bet;
    } while (bet > houseMoney && bet > playerMoney);

    playerMoney -= bet;
    houseMoney -= bet;

    pot = 2 * bet;

    system("cls");

    cout << ".--------.\n";
    cout << "|   __   |\n";
    cout << "|  |  |  |\n";
    cout << "|    /   |\n";
    cout << "|    .   |\n";
    cout << "'--------'\n";

    do { // ----------GAME LOOP----------
        bool validInput{ false };

        if (cardsDrawn != 0) {
            drawCard(cardsDrawn, chosenCard, 1, false);
        }
        cout << "Your Points: " << playerPoints;

        if (playerPoints > 21) {
            cout << "\n\nHouse wins!\n";
            cout << "You lost " << bet << "$\n";
            houseMoney += bet;
            _getch();
            return;
        }
        else {
            cout << "\n\n";
            cout << "The pot is: " << pot << "$\n";
            cout << "(D) to draw a card\n";
            cout << "(H) to hold your hand\n\n";
            cout << "House Points: " << housePoints << "\n";
            cout << ".--------.\n";
            cout << "|   __   |\n";
            cout << "|  |  |  |\n";
            cout << "|    /   |\n";
            cout << "|    .   |\n";
            cout << "'--------'\n";
        }

        do {
            char input = _getch();
            switch (toupper(input)) {
            case 'D':
                validInput = true;
                do {
                    chosenCard = rand() % 52;
                } while (deck[chosenCard].drawn == true);
                if (deck[chosenCard].isAce == true) {
                    cout << "Do you want the Ace to be of value 11 instead of 1?\n";
                    cout << "1. Yes\n";
                    cout << "2. No\n";
                    char input = _getch();
                    if (input == '1') {
                        playerPoints += 10;
                    }
                }
                playerPoints += deck[chosenCard].value;
                ++cardsDrawn;
                break;

            case 'H': // AI start---------------------------------------------------------------------------------------------------------------------------------
                hold = true;
                validInput = true;
                cardsDrawn = 0;

                do {
                    system("cls");
                    do {
                        chosenCard = rand() % 52;
                    } while (deck[chosenCard].drawn == true);
                    housePoints += deck[chosenCard].value;
                    ++cardsDrawn;

                    drawCard(cardsDrawn, chosenCard, 1, true);
                    cout << "Your Points: " << playerPoints << "\n\n";
                    cout << "The pot is: " << pot << "$\n";
                    cout << "(D) to draw a card\n";
                    cout << "(H) to hold your hand\n\n";
                    cout << "House Points: " << housePoints << "\n";
                    drawCard(cardsDrawn, chosenCard, 0, true);

                    Sleep(1250);
                } while (housePoints <= playerPoints);

                if (housePoints > 21) {
                    cout << "\nPlayer Wins!\n";
                    cout << "You won: " << pot << "$\n";
                    playerMoney += pot;
                }
                else {
                    cout << "House Wins!\n";
                    cout << "Better luck next time\n";
                    houseMoney += pot;
                }
                _getch();
                break; // AI End-----------------------------------------------------------------------------------------------------------------------------------

            default:
                break;
            }
        } while (!validInput);

        system("cls");
    } while (!hold);
}

void drawCard(int offset, int chosenCard, int player, bool bank) {
    string cardTop{ ".--------." };
    string cardBottom{ "'--------'" };
    ostringstream line1;
    ostringstream line2;
    ostringstream line3;
    ostringstream line4;
    --offset;
    offset *= 5;

    deck[chosenCard].drawn = true;

    line1 << "|" << deck[chosenCard].name << deck[chosenCard].suit << ".--.  |";
    line4 << "|  '--'" << deck[chosenCard].name << deck[chosenCard].suit << "|";

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

    if (bank == false) {
        for (int j{ 0 }; j < 10; ++j) {
            cardPrint[0][offset + j] = cardTop[j];
            cardPrint[1][offset + j] = line1.str()[j];
            cardPrint[2][offset + j] = line2.str()[j];
            cardPrint[3][offset + j] = line3.str()[j];
            cardPrint[4][offset + j] = line4.str()[j];
            cardPrint[5][offset + j] = cardBottom[j];
        }
    }
    else {
        for (int j{ 0 }; j < 10; ++j) {
            aiCardPrint[0][offset + j] = cardTop[j];
            aiCardPrint[1][offset + j] = line1.str()[j];
            aiCardPrint[2][offset + j] = line2.str()[j];
            aiCardPrint[3][offset + j] = line3.str()[j];
            aiCardPrint[4][offset + j] = line4.str()[j];
            aiCardPrint[5][offset + j] = cardBottom[j];
        }
    }

    for (int i{ 0 }; i < 6; ++i) {
        for (int j{ 0 }; j < 100; ++j) {
            if (player == 1) {
                cout << cardPrint[i][j];
            }
            else {
                cout << aiCardPrint[i][j];
            }
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