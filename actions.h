#ifndef ACTIONS_H
#define ACTIONS_H

enum class ActionType { pickup_two, pickup_three, change_suit, skip, invalid_move, none };

struct Action {
  ActionType type{ActionType::none};
  int repeat{1};
  Suit suit;
};

#endif
