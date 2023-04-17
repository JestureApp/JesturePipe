#ifndef JESTUREPIPE_ACTIONS_ACTION_H
#define JESTUREPIPE_ACTIONS_ACTION_H

#include "absl/types/variant.h"
#include "actions/action.h"

namespace jesturepipe {

typedef enum CursorControl { None, Grab, Release, Toggle } CursorControl;

using actions::Action;

typedef struct ActionList {
    std::vector<Action> actions;
    CursorControl cursor_control = None;
} ActionList;

}  // namespace jesturepipe

#endif  // JESTUREPIPE_ACTIONS_ACTION_H