#include "card_container.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <stdexcept>

void CardContainer::add_card(std::unique_ptr<Card> card) {
  cards.push_back(std::move(card));
}

std::unique_ptr<Card> CardContainer::get_card() {
  if (cards.empty()) return nullptr;
  auto ptr = std::move(cards.back());
  cards.pop_back();
  return ptr;
}

std::unique_ptr<Card> CardContainer::get_card(int index) {
  if (cards.empty()) return nullptr;
  auto ptr = std::move(cards.at(index));
  cards.erase(cards.begin() + index);
  return ptr;
}

Card* CardContainer::view_card(int index) {
  if (cards.empty()) return nullptr;
  return cards.at(index).get();
}

void CardContainer::shuffle() {
  // obtain a time-based seed:
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

  auto rng = std::default_random_engine (seed);
  std::shuffle (begin(cards), end(cards), rng);
}

int CardContainer::size() {
  return cards.size();
}
