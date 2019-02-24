#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include "card_container.h"
#include "card.h"
#include "actions.h"

class Player : public CardContainer {
  public:
    // Given the top card of discard pile, what is player action?
    // Return the card to put down or empty ptr for pickup.
    virtual std::unique_ptr<Card> accept_move() = 0;
    virtual Card* get_proposed_move(Card* top_card) = 0;
    virtual void notify(Action& action) = 0;
};

#endif
