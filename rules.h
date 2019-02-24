#ifndef RULES_H
#define RULES_H

#include <string>
#include "card_container.h"
#include "deck.h"
#include "player.h"

class Rules {
  public:
    Action check_move(Card* player_card, Card* discard_card);
    // Return how many cards player should pickup
    int notify_pickup();
  private:
    Action prev_action;
};

#endif
