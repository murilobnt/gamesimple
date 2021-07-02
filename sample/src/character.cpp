#include "character.hpp"

Character::Character(sf::Texture const &texture, sf::Vector2f position)
    : fox::MainObject::MainObject(texture, sf::IntRect(0, 0, 16, 32), 5),
    falling(false),
    jump_height(32),
    z_movement(0) {
  setPosition(position);
  player_position = sf::Vector3f(position.x, position.y, 0);
  current_facing_pos = DOWN;
  collision_offset_down = 0;
  collision_offset_up = 22;
  collision_offset_right = 2;
  collision_offset_left = 2;
}

Character::Character() {}

void Character::jump(const float &delta_time){
  z_movement = sqrt(2 * 32 * delta_time * jump_height);
  movement.y = -z_movement;
  player_position.z += z_movement;
  player_position.y = getPosition().y;
}

void Character::control_entity(float delta_time) {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !falling){
    falling = true;
    jump(delta_time);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    moving_left = true;
    current_facing_pos = LEFT;
  } else
    moving_left = false;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    moving_right = true;
    current_facing_pos = RIGHT;
  } else
    moving_right = false;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    moving_down = true;
    current_facing_pos = DOWN;
  } else
    moving_down = false;

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    moving_up = true;
    current_facing_pos = UP;
  } else
    moving_up = false;

  if (moving_left)
    movement.x = round(-100 * delta_time);
  if (moving_down)
    movement.y = round(100 * delta_time);
  if (moving_right)
    movement.x = round(100 * delta_time);
  if (moving_up)
    movement.y = round(-100 * delta_time);

  if ((moving_up || moving_down || moving_left || moving_right) &&
      !do_animate) {
    do_animate = true;
    reset_last_update();
    set_animation_loop_state(1);
    ready_to_update();
  }
}

void Character::move(float delta_time) {
  if(falling){
    z_movement -= 32 * delta_time;
    if(player_position.z + z_movement <= 0){
      z_movement = -player_position.z;
      falling = false;
    }
    player_position.z += z_movement;
    movement.y += -z_movement;
  }
  sf::Sprite::move(movement);
  current_movement = movement;
  movement.x = 0;
  movement.y = 0;
}

void Character::move() {
}

void Character::animate() {
  if (movement.x == 0.f && movement.y == 0.f) {
    do_animate = false;
    switch (current_facing_pos) {
    case UP:
      setTextureRect(0, 64);
      break;
    case DOWN:
      setTextureRect(0, 0);
      break;
    case LEFT:
      setTextureRect(0, 96);
      break;
    case RIGHT:
      setTextureRect(0, 32);
      break;
    }
    return;
  }

  switch (current_facing_pos) {
  case LEFT:
    apply_animation_on_row(this, sf::Vector2i(0, 64), 96);
    break;
  case RIGHT:
    apply_animation_on_row(this, sf::Vector2i(0, 64), 32);
    break;
  case DOWN:
    apply_animation_on_row(this, sf::Vector2i(0, 64), 0);
    break;
  case UP:
    apply_animation_on_row(this, sf::Vector2i(0, 64), 64);
    break;
  }
}
