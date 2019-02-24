#ifndef RULES_H
#define RULES_H

#include <string>
#include <variant>
#include "card_container.h"
#include "deck.h"
#include "player.h"

class Rules {
  public:
    const std::variant<Valid, Invalid, Incomplete> check_move(Card* player_card, Card* discard_card);
    // Return how many cards player should pickup
    int notify_pickup();
    int get_pickup_num();
    void set_suit(Suit suit);
  private:
    Action prev_action;
    Suit ace_suit;
    bool ace_valid = false;
};

#endif
