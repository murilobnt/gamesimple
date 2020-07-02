#include "foxer/components/fader.hpp"

namespace fox {

Fader::Fader() {}

Fader::Fader(const sf::RenderTexture *rt, const sf::Time &update_rate)
      : TimedEntity(update_rate),
      sf::Sprite(rt->getTexture()),
      alpha(0),
      state(COMPLETE) {
        sf::Sprite::setColor(sf::Color(0, 0, 0, 0));
      }

void Fader::fade_out(){
  state = FADE_OUT;
}

void Fader::fade_in(){
  state = FADE_IN;
}

bool Fader::is_complete(){
  return (state == COMPLETE);
}

void Fader::on_update_time() {
  if(state == FADE_IN)
    sf::Sprite::setColor(sf::Color(0, 0, 0, --alpha));

  if(state == FADE_OUT)
    sf::Sprite::setColor(sf::Color(0, 0, 0, ++alpha));

  if(state != COMPLETE && (alpha == 255 || alpha == 0))
    state = COMPLETE;
}

}