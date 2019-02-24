#ifndef CARD_CONTAINER_H
#define CARD_CONTAINER_H

#include <vector>
#include <memory>
#include <functional>
#include "card.h"

// Provides functionality to manage a group of Cards
class CardContainer {
  public:
    // Add a card to the deck
    void add_card(std::unique_ptr<Card> card);
    // Remove and return a card
    std::unique_ptr<Card> get_card();
    std::unique_ptr<Card> get_card(int index);
    // would be nice to use optional
    Card* view_card(int index);
    // Shuffle the order of the cards
    void shuffle();
    // Number of cards in the container
    int size();
  protected:
    std::vector<std::unique_ptr<Card>> cards;
};


#endif
