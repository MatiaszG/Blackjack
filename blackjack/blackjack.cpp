#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <random>

using namespace std;

void initialize_deck(vector<int> &deck, int decks_number)
{
    deck.clear();
    for (int i = 2; i <= 11; i++)
    {
        for (int j = 0; j < 4 * decks_number; j++)
        {
            deck.push_back(i);
        }
    }
    for (int i = 0; i < 12 * decks_number; i++)
    {
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

void play_dealer(vector<int> &deck, vector<int> &user_cards, vector<int> &dealer_cards, int &games_won, int &games_lost, int &games_draw, int current_sum_player)
{
    int soft_sum_dealer, hard_sum_dealer, current_sum_dealer;

    soft_sum_dealer = count_soft_sum(dealer_cards);
    hard_sum_dealer = sum_cards_value(dealer_cards);
    current_sum_dealer = count_current_sum(hard_sum_dealer, soft_sum_dealer);

    while (current_sum_dealer < 17)
    {
        dealer_cards.push_back(deck.back());
        deck.pop_back();
        hard_sum_dealer = sum_cards_value(dealer_cards);
        soft_sum_dealer = count_soft_sum(dealer_cards);
        current_sum_dealer = count_current_sum(hard_sum_dealer, soft_sum_dealer);
    }
    if (current_sum_dealer <= 21 && current_sum_dealer > current_sum_player)
    {
        games_lost++;
    }
    else if (current_sum_dealer == current_sum_player)
    {
        games_draw++;
    }
    else
    {
        games_won++;
    }
}

void play(vector<int> &deck, vector<int> &user_cards, vector<int> &dealer_cards)
{
    int soft_sum_player;
    int hard_sum_player;
    int current_sum_player;
    int choice = 1;

    cout << "Your cards' values:\n";
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

        cout << "Dealer's cards' values:\n";
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
        if (current_sum_dealer <= 21 && current_sum_dealer > current_sum_player)
        {
            cout << "You lost";
        }
        else if (current_sum_dealer == current_sum_player)
        {
            cout << "Draw";
        }
        else
        {
            cout << "You won";
        }
    }
}

void choose_game_mode(int &game_mode)
{
    cout << "Press:\n";
    cout << "1 to play on your own\n";
    cout << "2 to simulate games played with never bust strategy\n";
    cin >> game_mode;
}

void choose_parameters(int &number_of_decks, float &deck_penetration, int &number_of_games)
{
    cout << "Insert number of decks in game:\n";
    cin >> number_of_decks;
    cout << "\n"
         << "Insert percentage deck penetration\n";
    cin >> deck_penetration;
    cout << "\n"
         << "Insert number of games to simulate\n";
    cin >> number_of_games;
}

void play_never_bust(vector<int> &deck, vector<int> &user_cards, vector<int> &dealer_cards, int number_of_decks, float deck_penetration, int number_of_games)
{
    int hard_sum_player, soft_sum_player, current_sum_player;
    int games_won = 0;
    int games_lost = 0;
    int games_draw = 0;

    for (int i = 0; i < number_of_games; i++)
    {
        if ((float)deck.size() * number_of_decks / (52.0 * number_of_decks) < deck_penetration / 100)
        {
            initialize_deck(deck, number_of_decks);
            shuffle_deck(deck);
        }

        deal(deck, user_cards, dealer_cards);
        hard_sum_player = sum_cards_value(user_cards);
        soft_sum_player = count_soft_sum(user_cards);
        current_sum_player = count_current_sum(hard_sum_player, soft_sum_player);

        while (current_sum_player <= 11)
        {
            user_cards.push_back(deck.back());
            deck.pop_back();
            hard_sum_player = sum_cards_value(user_cards);
            soft_sum_player = count_soft_sum(user_cards);
            current_sum_player = count_current_sum(hard_sum_player, soft_sum_player);
        }
        play_dealer(deck, user_cards, dealer_cards, games_won, games_lost, games_draw, current_sum_player);

        user_cards.clear();
        dealer_cards.clear();
    }
    cout << "Games lost: " << games_lost << "\n";
    cout << "Games won: " << games_won << "\n";
    cout << "Games draw: " << games_draw << "\n";
}

int main()
{
    int game_mode;
    int number_of_decks;
    int number_of_games;
    float deck_penetration;
    vector<int> deck;
    vector<int> user_cards;
    vector<int> dealer_cards;

    choose_game_mode(game_mode);
    switch (game_mode)
    {
    case 1:
        initialize_deck(deck, 1);
        shuffle_deck(deck);
        deal(deck, user_cards, dealer_cards);
        play(deck, user_cards, dealer_cards);
        break;
    case 2:
        choose_parameters(number_of_decks, deck_penetration, number_of_games);
        initialize_deck(deck, number_of_decks);
        shuffle_deck(deck);
        play_never_bust(deck, user_cards, dealer_cards, number_of_decks, deck_penetration, number_of_games);
        break;
    default:
        cout << "Wrong number";
    }
    return 0;
}
