#include "gs2d/game/level/level_bundle.hpp"

namespace gs {

LevelBundle::LevelBundle() {}

LevelBundle::LevelBundle(LevelProxy *level_proxy,
                         SharedTextureHolder *shared_holder, Camera *camera) {
  this->level_proxy = level_proxy;
  this->shared_holder = shared_holder;
  this->camera = camera;
}

} // namespace gs
