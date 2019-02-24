#ifndef CLI_PLAYER_H
#define CLI_PLAYER_H

#include "player.h"

class CliPlayer : public Player {
  public:
    std::unique_ptr<Card> accept_move();
    Card* get_proposed_move(Card* top_card);
    void notify(Action& action);
  private:
    Card* proposed = nullptr;
    int proposed_index{};
};

#endif
