#ifndef JESTUREPIPE_ACTIONS_ACTION_H
#define JESTUREPIPE_ACTIONS_ACTION_H

#include "absl/types/variant.h"
#include "actions/action.h"

namespace jesturepipe {

using ActionType = actions::Action;

typedef enum CursorControl { None, Grab, Release, Toggle } CursorControl;

typedef struct Action {
    ActionType type;
    CursorControl cursor_control = None;
} Action;

}  // namespace jesturepipe

#endif  // JESTUREPIPE_ACTIONS_ACTION_H