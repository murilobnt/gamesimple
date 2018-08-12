#include <string>

#include "gs2d_engine/concrete/game.hpp"
#include "instance/menu_example.hpp"

int main() {
        Game game(800, 600, std::string("Tartaruga"));
        game.game_start(new MenuExample());
        return 0;
}
