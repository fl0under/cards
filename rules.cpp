#include "rules.h"
#include <iostream>
#include <string>

using namespace std;

const std::variant<Valid, Invalid, Incomplete> Rules::check_move(
    Card* player_card, Card* discard_card) {
  
  Action action;
  std::variant<Valid, Invalid, Incomplete> move_result;

  // prev_action keeps track of ongoing +2's or 3's,
  // cannot put any other rank down (must pick up).
  if (prev_action.type == ActionType::pickup_two) {
    if (discard_card->rank() != player_card->rank()) {
      action.type = ActionType::invalid_move;
      move_result = Invalid::invalid_card_plus2;
      return move_result;
    }
  } else if (prev_action.type == ActionType::pickup_three) {
    if (discard_card->rank() != player_card->rank()) {
      action.type = ActionType::invalid_move;
      move_result = Invalid::invalid_card_plus3;
      return move_result;
    }
  }

  // Check for special cases first
  if (player_card->rank() == Rank::ace) {
    action.type = ActionType::change_suit;
    move_result = Incomplete::ask_suit;
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
    move_result = Valid::same_player;
  }

  // Check for either same suit or rank
  Suit suit = (ace_valid) ? ace_suit : discard_card->suit();
  if (player_card->suit() != suit) {
    if (player_card->rank() != discard_card->rank()) {
      action.type = ActionType::invalid_move;
      move_result = Invalid::invalid_card;
    }
  }

  ace_valid = false;

  if (action.type != ActionType::invalid_move)
    prev_action = action;

  move_result = Valid::other_player;

  return move_result;
}

int Rules::notify_pickup() {
  int pickup = get_pickup_num();

  prev_action.type = ActionType::none;
  prev_action.repeat = 1;

  return pickup;
}

int Rules::get_pickup_num() {
  int pickup{1};
  
  if (prev_action.type == ActionType::pickup_two)
    pickup = 2 * prev_action.repeat;
  else if (prev_action.type == ActionType::pickup_three)
    pickup = 3 * prev_action.repeat;

  return pickup;
}

void Rules::set_suit(Suit suit) {
  ace_suit = suit;
  ace_valid = true;
}
