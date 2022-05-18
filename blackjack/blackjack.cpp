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

void deal(vector<int> &deck, vector<int> &user_cards, vector<int> &dealer_cards)
{
    for (int i = 0; i < 2; i++)
    {
        dealer_cards.push_back(deck.back());
        deck.pop_back();
        user_cards.push_back(deck.back());
        deck.pop_back();
    }
}

int main()
{
    vector<int> deck;
    vector<int> user_cards;
    vector<int> dealer_cards;
    initialize_deck(deck);
    shuffle_deck(deck);
    deal(deck, user_cards, dealer_cards);

    return 0;
}
