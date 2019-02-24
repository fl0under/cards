#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <string>
#include "card_container.h"
#include "deck.h"
#include "player.h"
#include "rules.h"

class GameManager {
  public:
    GameManager(Player& _player1, Player& _player2, 
        Deck& _stock, CardContainer& _discard)
      : player1{_player1}, player2{_player2},
        stock{_stock}, discard{_discard} {}

    void start() { init(); game_loop(); }

  private:
    void init();
    void game_loop();
    void do_player_turn(Player& player, std::string name);
    void player_pickup(Player& player);
    Player& player1;
    Player& player2;
    Deck& stock;
    CardContainer& discard;
    Rules rules{};
};

#endif
