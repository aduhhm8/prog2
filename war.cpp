// Author: Adam Cobian
// CECS 325-01 
// Prog 2
// Due: 8/28/26
//
//I certify that this program is my own original work. I did not copy any part of this program from
//any other source including inappropriate AI use. I did not share this program with anyone. I
//further certify that I typed each and every line of code in this program.

// Author: Adam Cobian
// CECS 325-01 Prog 2
// Due: see Canvas
// War is a simple game of chance
#include <iostream>     // library for cin, cout
#include <string>       // library for string
#include <vector>       // library for vector
#include <cstdlib>      // library for rand, srand
#include <ctime>        // library for time
using namespace std;
struct Player
{
    string name;
    int win;
    int lose;
    int tie;
};

class Card
{
    private:
        char suit;
        char rank;

    public:
        Card(char s, char r)
        {
            suit = s;
            rank = r;
        }

        void display()
        {
            if (rank == 'T')
            {
                cout << "10" << suit;
            }
            else
            {
                cout << rank << suit;
            }
        }

        int compare(Card other)
        {
            char ranks[] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
            int myindex = -1;
            int otherindex = -1;

            for (int i = 0; i < 13; i++)
            {
                if (rank == ranks[i])
                {
                    myindex = i;
                }
                if (other.rank == ranks[i])
                {
                    otherindex = i;
                }
            }
            if (myindex > otherindex)
            {
                return 1;
            }
            else if (myindex < otherindex)
            {
                return -1;
            }
            else
            {
                return 0;
            }
        }
};

 class Deck
{
    private:
        vector<Card> cards;
        int nextcard;
        bool mix;

    public:
        Deck()
        {
            char suits[] = {'C','S','D','H'};
            char ranks[] = {'A','2','3','4','5','6','7','8','9','T','J','Q','K'};
            for (int s = 0; s < 4; s++)
            {
                for (int r = 0; r < 13; r++)
                {
                    cards.push_back(Card(suits[s], ranks[r]));
                }
            }
            nextcard = 0;
            mix = false;
        }

        bool isEmpty()
        {
            if (nextcard >= cards.size())
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        void display()
        {
            for (int i = 0; i < 52; i++)
            {
                cards[i].display();
                if (i == 12 || i == 25 || i == 38 || i == 51)
                {
                    cout << endl;
                }
                else
                {
                    cout << ",";
                }
            }
        }

        void shuffle()
        {
            for (int i = 0; i < 52; i++)
            {
                int j = rand() % 52;

                Card temp = cards[i];
                cards[i] = cards[j];
                cards[j] = temp;
            }
            mix = true;
        }

        Card deal()
        {
            if (isEmpty())
            {
                throw string("Error - Deck is empty");
            }
            Card c = cards[nextcard];
            nextcard = nextcard + 1;
            return c;
        }
};

int main()
{
    srand(time(0));
    Deck d;

    Player p1;
    Player p2;

    p1.win = 0;
    p1.lose = 0;
    p1.tie = 0;
    p2.win = 0;
    p2.lose = 0;
    p2.tie = 0;

    cout << "Enter the name of the first player: ";
    cin >> p1.name;
    cout << "Enter the name of the second player: ";
    cin >> p2.name;

    int games;
    cout << "How many games will they play? ";
    cin >> games;
    cout << endl << " Original Deck" << endl;
    d.display();

    d.shuffle();
    cout << endl << " Shuffled Deck" << endl;
    d.display();

    try
    {
        for (int i = 0; i < games; i++)
        {
            Card c1 = d.deal();
            Card c2 = d.deal();

	    cout << endl << "Game " << (i + 1) << endl;
	    cout << "--------" << endl;

            cout << "\t" << p1.name << "=>";
            c1.display();
            cout << endl;
            cout << "\t" << p2.name << "=>";
            c2.display();
            cout << endl;

            int result = c1.compare(c2);

            if (result == 1)
            {
                cout << p1.name << "=> Winner" << endl;
                p1.win = p1.win + 1;
                p2.lose = p2.lose + 1;
            }
            else if (result == -1)
            {
                cout << p2.name << "=> Winner" << endl;
                p2.win = p2.win + 1;
                p1.lose = p1.lose + 1;
            }
            else
            {
                cout << "Tie game" << endl;
                p1.tie = p1.tie + 1;
                p2.tie = p2.tie + 1;
            }
        }
    }

    catch (string msg)

    {
        cout << msg << endl;
    }

    cout << "------Final Stats-------" << endl;
    cout << "\t" << p1.name << " vs. " << p2.name << endl;
    cout << "Wins\t" << p1.win << "\t" << p2.win << endl;
    cout << "Losses\t" << p1.lose << "\t" << p2.lose << endl;
    cout << "Ties\t" << p1.tie << "\t" << p2.tie << endl;

    return 0;
}

