#include <iostream>
#include <stdexcept>
#include "deck.h"
#include "cli_player.h"
#include "card_container.h"
#include "game_manager.h"

int main() {
  using namespace std;

  try {
    Deck deck; 
    CliPlayer player1;
    CliPlayer player2;
    CardContainer discard;

    GameManager game_manager{player1, player2, deck, discard};
    game_manager.start();


  } catch (const exception& e) {
      cout << "main(): " << e.what() << '\n';
  }

}
