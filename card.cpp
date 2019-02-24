#include "card.h"

using namespace std;

string Card::suit_string() {
  switch (_suit) {
    case (Suit::clubs):
      return "clubs";
    case (Suit::hearts):
      return "hearts";
    case (Suit::spades):
      return "spades";
    case (Suit::diamonds):
      return "diamonds";
  }
}

string Card::rank_string() {
  switch (_rank) {
    case (Rank::ace):
      return "ace";
    case (Rank::two):
      return "two";
    case (Rank::three):
      return "three";
    case (Rank::four):
      return "four";
    case (Rank::five):
      return "five";
    case (Rank::six):
      return "six";
    case (Rank::seven):
      return "seven";
    case (Rank::eight):
      return "eight";
    case (Rank::nine):
      return "nine";
    case (Rank::ten):
      return "ten";
    case (Rank::jack):
      return "jack";
    case (Rank::queen):
      return "queen";
    case (Rank::king):
      return "king";
  }
}

string Card::as_string() {
  return rank_string() + " of " + suit_string();
}
