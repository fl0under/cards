#ifndef CARD_H
#define CARD_H

#include <string>

enum class Suit { clubs, hearts, spades, diamonds };
enum class Rank { ace,two,three,four,five,six,seven,eight,nine,ten,jack,queen,king };

// Describes one playing card
class Card {
  public:
    Card(Suit s, Rank r) : _suit{s}, _rank{r} {}
    Card(Card&& c) : _suit{c._suit}, _rank{c._rank} {}
    Card& operator=(Card&& c) {
      _suit = c._suit;
      _rank = c._rank;
    }
    Suit suit() const {return _suit;}
    Rank rank() const {return _rank;}
    std::string suit_string();
    std::string rank_string();
    std::string as_string();
  private:
    Suit _suit;
    Rank _rank;
};

#endif
