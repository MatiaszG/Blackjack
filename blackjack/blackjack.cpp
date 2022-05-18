#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void initialize_deck(vector<int> &deck)
{
    for (int i = 2; i <= 11; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            deck.push_back(i);
        }
    }
}

void shuffle_deck(vector<int> &deck)
{
    random_shuffle(deck.begin(), deck.end());
}

int main()
{
    vector<int> deck;
    initialize_deck(deck);
    shuffle_deck(deck);
    return 0;
}
