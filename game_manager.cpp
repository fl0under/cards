#include "game_manager.h"
#include <iostream>

using namespace std;

void GameManager::init() {
    stock.shuffle();

    // Deal 7 cards to the players
    for (int i{0}; i < 7; ++i) {
      player1.add_card(stock.get_card());
      player2.add_card(stock.get_card());
    }

    // Deal 1 card to the discard pile
    discard.add_card(stock.get_card());
}

void GameManager::game_loop() {
  while (true) {
    do_player_turn(player1, "1");
    do_player_turn(player2, "2");
  }
}

void GameManager::do_player_turn(Player& player, string name) {
  string line = "*********************";
  cout << '\n' << line << '\n';
  cout << "\nPlayer " << name << "'s turn\n\n";
  Card* discard_card = discard.view_card(discard.size()-1);
  Card* card = player.get_proposed_move(discard_card);
  if (card) {
    // Check if valid etc.
    Action action = rules.check_move(card, discard_card);
    player.notify(action);
    if (action.type == ActionType::skip) {
      discard.add_card(move(player.accept_move()));
      do_player_turn(player, name); // Recursive
    } else if (action.type == ActionType::invalid_move)
      do_player_turn(player, name); // Recursive
    else
      discard.add_card(move(player.accept_move()));
  } else {
    // Pickup a card
    // Notify rules that player picked up
    int num_to_pickup = rules.notify_pickup();
    for (int i{0}; i < num_to_pickup; ++i) 
      player_pickup(player);
  }
}

void GameManager::player_pickup(Player& player) {
  auto pickup = stock.get_card();
  if (pickup) {
    player.add_card(move(pickup));
  } else { // No cards left in stock
    // Move all cards except top from discard pile to stock pile
    int num_of_cards = discard.size() - 2;
    for (int i{num_of_cards}; i >= 0; --i)
      stock.add_card(move(discard.get_card(i)));
    stock.shuffle();
    // Then the player can pick one up
    pickup = stock.get_card();
    player.add_card(move(pickup));
  }
}
