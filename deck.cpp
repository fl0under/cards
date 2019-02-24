#include "deck.h"

using namespace std;

Deck::Deck() {
  // Create the deck of cards
  for (int i{0}; i < 4; ++i) {
    for (int j{0}; j < 13; ++j)
      cards.emplace_back(
            new Card(static_cast<Suit>(i), static_cast<Rank>(j))
          );
  }
}
