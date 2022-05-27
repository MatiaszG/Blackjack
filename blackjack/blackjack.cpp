#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <random>

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
    for(int i=0; i<12; i++) {
        deck.push_back(10);
    }
}

void shuffle_deck(vector<int> &deck)
{
    random_device rd;
    default_random_engine rng(rd());
    shuffle(deck.begin(), deck.end(), rng);
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

int sum_cards_value(vector<int> cards)
{
    int sum = 0;
    for (int i = 0; i < cards.size(); i++)
    {
        sum += cards[i];
    }
    return sum;
}

int count_soft_sum(vector<int> cards)
{
    int sum = 0;
    for (int i = 0; i < cards.size(); i++)
    {
        if (cards[i] == 11)
        {
            if (sum + 11 <= 21)
            {
                sum += 11;
            }
            else
            {
                sum += 1;
            }
        }
        else
        {
            sum += cards[i];
        }
    }
    return sum;
}

int count_current_sum(int hard_sum, int soft_sum)
{
    if (hard_sum > 21)
    {
        return soft_sum;
    }
    else
    {
        return hard_sum;
    }
}

void play(vector<int> &deck, vector<int> &user_cards, vector<int> &dealer_cards)
{
    int soft_sum_player;
    int hard_sum_player;
    int current_sum_player;
    int choice = 1;

    cout << "Your cards values:\n";
    cout << user_cards[0] << " " << user_cards[1] << "\n\n";

    while (choice == 1)
    {
        cout << "Press 1 to draw a card"
             << "\n"
             << "Press 2 to stop drawing\n";
        cin >> choice;
        if (choice == 1)
        {
            cout << "Your new card's value: " << deck.back() << "\n";
            user_cards.push_back(deck.back());
            deck.pop_back();
            hard_sum_player = sum_cards_value(user_cards);
            soft_sum_player = count_soft_sum(user_cards);
            current_sum_player = count_current_sum(hard_sum_player, soft_sum_player);

            cout << "Your new total value: " << current_sum_player << "\n";
            if (current_sum_player > 21)
            {
                cout << "You lost";
                break;
            }
        }
    }
    if (current_sum_player <= 21)
    {
        int soft_sum_dealer = count_soft_sum(dealer_cards);
        int hard_sum_dealer = sum_cards_value(dealer_cards);
        int current_sum_dealer = count_current_sum(hard_sum_dealer, soft_sum_dealer);

        cout << "Dealer's cards values:\n";
        cout << dealer_cards[0] << " " << dealer_cards[1] << "\n\n";

        while (current_sum_dealer < 17)
        {
            cout << "Dealer's new card's value: " << deck.back() << "\n";
            dealer_cards.push_back(deck.back());
            deck.pop_back();
            hard_sum_dealer = sum_cards_value(dealer_cards);
            soft_sum_dealer = count_soft_sum(dealer_cards);
            current_sum_dealer = count_current_sum(hard_sum_dealer, soft_sum_dealer);
            cout << "Dealer's new total value: " << current_sum_dealer << "\n";
        }
        if (current_sum_dealer < 21 && current_sum_dealer > current_sum_player)
        {
            cout << "You lost";
        }
        else
        {
            cout << "You won";
        }
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
    play(deck, user_cards, dealer_cards);

    return 0;
}
