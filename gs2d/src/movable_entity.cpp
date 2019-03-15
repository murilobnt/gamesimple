#include "gs2d/scene/components/object/movable_object.hpp"

namespace gs {

MovableObject::MovableObject()
    : moving_up(false), moving_down(false), moving_left(false),
      moving_right(false), collision_offset_up(0), collision_offset_down(0),
      collision_offset_left(0), collision_offset_right(0) {}

void MovableObject::nullfy_movement() { movement = sf::Vector2f(0, 0); }

void MovableObject::set_movement_x(float x) { movement.x = x; }
void MovableObject::set_movement_y(float y) { movement.y = y; }
void MovableObject::set_movement(sf::Vector2f movement) {
  this->movement = movement;
}

sf::Vector2f MovableObject::get_movement() const { return movement; }

} // namespace gs