#ifndef JESTUREPIPE_ACTIONS_MAPPER_H
#define JESTUREPIPE_ACTIONS_MAPPER_H

#include <shared_mutex>

#include "absl/container/flat_hash_map.h"
#include "actions/action.h"

namespace jesturepipe {
typedef struct ActionMapper {
    std::shared_mutex mutex;
    absl::flat_hash_map<int, actions::Action> mapping;
} ActionMapper;
}  // namespace jesturepipe

#endif  // JESTUREPIPE_ACTIONS_MAPPER_H