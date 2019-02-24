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
  Player* player;
  Valid turn;
  // Chose player to go first
  player = &player1;
  while (true) {
    do {
      turn = do_player_turn(*player);
    } while (turn == Valid::same_player);
    player = (player == &player1) ? &player2 : &player1;
  }
}

// To make other things eaiser
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

Valid GameManager::do_player_turn(Player& player) {

  Card* discard_card = discard.view_card(discard.size()-1);
  int pickup_num = rules.get_pickup_num();
  Card* card = player.get_proposed_move(discard_card, pickup_num);
  Valid turn; // whose turn next?

  if (card) {
    std::variant<Valid, Invalid, Incomplete> result = rules.check_move(card, discard_card);

    std::visit(overloaded {
        [&](Valid arg) {
          turn = arg; 
          discard.add_card(move(player.accept_move()));
        },
        [&](Invalid arg) { 
          player.notify_invalid_move(arg);
          turn = Valid::same_player; // Not really valid of course
        },
        [&](Incomplete arg) {
          rules.set_suit(player.ask_suit());
          turn = Valid::other_player;
        }
    }, result);

  } else {
    // Pickup a card
    // Notify rules that player picked up
    int num_to_pickup = rules.notify_pickup();
    for (int i{0}; i < num_to_pickup; ++i) 
      player_pickup(player);
    turn = Valid::other_player;
  }

  return turn;
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
