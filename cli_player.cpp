#include "cli_player.h"
#include <iostream>
#include <string>

using namespace std;

Card* CliPlayer::get_proposed_move(Card* top_card) {
  // Print pretty things
  cout << "Card on top of pile:\n";
  string line = "*********************";
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
  cout << "0: Pickup a card\n";
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

void CliPlayer::notify(Action& action) {
  if (action.type == ActionType::invalid_move) {
    cout << "\nMove Invalid. Please choose again.\n";
  }
}
