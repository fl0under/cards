#include "cli_player.h"
#include <iostream>
#include <string>

using namespace std;

Card* CliPlayer::get_proposed_move(Card* top_card, int pickup_num) {
  // Print out , should remove from here
  string line = "*********************";
  cout << '\n' << line << '\n';
  cout << "\n " << name << "'s turn\n\n";

  // Print pretty things
  cout << "Card on top of pile:\n";
  cout << line << '\n';
  int spaces = ((line.size() - top_card->as_string().size()) - 2) / 2;
  cout << "*";
  for (int i{0}; i < spaces; ++i) cout << " ";
  cout << top_card->as_string();
  for (int i{0}; i < spaces; ++i) cout << " ";
  cout << "*\n";
  cout << line << '\n';

  // Players cards
  cout << "\n\n";
  cout << "Your cards\n";
  cout << line << '\n';
  for (int i{0}; i < cards.size(); ++i)
    cout << i+1 << ": " << cards[i]->as_string() << '\n';
  cout << "0: Pickup " << pickup_num << ((pickup_num > 1) ? " cards" : " card") << '\n';
  int choice;
  // what about letters?? cctype isdigit
  while (true) {
    cout << "\nWhich card would you like to play?: ";
    string input;
    getline(cin, input);
    try {
      choice = stoi(input);
    } catch (...) {choice = -1;}
    if (choice < 0 || choice > cards.size())
      cout << "Error. Please choose from one of the cards shown.\n";
    else break;
  }
  if (choice == 0)
    proposed = nullptr;
  else {
    proposed_index = choice-1;
    proposed = view_card(proposed_index);
  }
  return proposed;
}

unique_ptr<Card> CliPlayer::accept_move() {
  return get_card(proposed_index);
}

void CliPlayer::notify_invalid_move(Invalid& move) {
  if (move == Invalid::invalid_card) {
    cout << "\nMove Invalid. Please choose again.\n";
  }
}

Suit CliPlayer::ask_suit() {
  cout << "Which suit would you like?\n";
  vector<Suit> suits {Suit::clubs, Suit::hearts, Suit::spades, Suit::diamonds};
  cout << 1 << ": " << "Clubs\n";
  cout << 2 << ": " << "Hearts\n";
  cout << 3 << ": " << "Spades\n";
  cout << 4 << ": " << "Diamonds\n";

  int choice;
  while (true) {
    string input;
    getline(cin, input);
    try {
      choice = stoi(input);
    } catch (...) {choice = -1;}
    if (choice < 0 || choice > suits.size())
      cout << "Error. Please choose from one of the suits shown.\n";
    else break;
  }

  return suits.at(choice);
}
