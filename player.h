#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>
#include "card_container.h"
#include "card.h"
#include "actions.h"

class Player : public CardContainer {
  public:
    Player(std::string _name) : name{_name} {}
    // Given the top card of discard pile, what is player action?
    // Return the card to put down or empty ptr for pickup.
    virtual std::unique_ptr<Card> accept_move() = 0;
    virtual Card* get_proposed_move(Card* top_card, int pickup_num) = 0;
    virtual void notify_invalid_move(Invalid& move) = 0;
    virtual Suit ask_suit() = 0;
  protected:
    std::string name;
};

#endif
