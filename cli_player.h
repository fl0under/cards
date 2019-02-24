#ifndef CLI_PLAYER_H
#define CLI_PLAYER_H

#include "player.h"

class CliPlayer : public Player {
  public:
    CliPlayer(std::string _name) : Player(_name) {}
    std::unique_ptr<Card> accept_move();
    Card* get_proposed_move(Card* top_card, int pickup_num);
    void notify_invalid_move(Invalid& move);
    Suit ask_suit();
  private:
    Card* proposed = nullptr;
    int proposed_index{};
    //std::string name;
};

#endif
