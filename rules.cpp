#include "rules.h"
#include <iostream>
#include <string>

using namespace std;

Action Rules::check_move(Card* player_card, Card* discard_card) {
  Action action;

  // prev_action keeps track of ongoing +2's or 3's,
  // cannot put any other rank down (must pick up).
  if (prev_action.type == ActionType::pickup_two || 
      prev_action.type == ActionType::pickup_three) {
    if (discard_card->rank() != player_card->rank()) {
      action.type = ActionType::invalid_move;
      return action;
    }
  }

  // Check for special cases first
  if (player_card->rank() == Rank::ace) {
    action.type = ActionType::change_suit;
  } else if (player_card->rank() == Rank::two) {
    action.type = ActionType::pickup_two;
    if (prev_action.type == action.type)
      action.repeat++;
  } else if (player_card->rank() == Rank::three) {
    action.type = ActionType::pickup_three;
    if (prev_action.type == action.type)
      action.repeat++;
  } else if (player_card->rank() == Rank::jack) {
    action.type = ActionType::skip;
  }

  // Check for either same suit or rank
  if (player_card->suit() != discard_card->suit()) {
    if (player_card->rank() != discard_card->rank())
      action.type = ActionType::invalid_move;
  }

  if (action.type != ActionType::invalid_move)
    prev_action = action;
  return action;
}

int Rules::notify_pickup() {
  int pickup{1};
  
  if (prev_action.type == ActionType::pickup_two)
    pickup = 2 * prev_action.repeat;
  else if (prev_action.type == ActionType::pickup_three)
    pickup = 3 * prev_action.repeat;

  prev_action.type = ActionType::none;
  prev_action.repeat = 1;

  return pickup;
}
