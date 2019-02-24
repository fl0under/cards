#ifndef ACTIONS_H
#define ACTIONS_H

enum class ActionType { pickup_two, pickup_three, change_suit, skip, invalid_move, none };

struct Action {
  ActionType type{ActionType::none};
  int repeat{1};
  Suit suit;
};

enum class Valid { other_player, same_player };
enum class Invalid { invalid_card, invalid_card_plus2, invalid_card_plus3 };
enum class Incomplete { ask_suit };

#endif
