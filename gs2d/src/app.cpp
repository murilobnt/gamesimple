#include "gs2d_engine/app_cycle/app.hpp"

namespace gs {

App::App() {
}

App::App(int app_width, int app_height,
         std::string app_title, float framerate)
        : app_frequency(sf::seconds(1.f / framerate)),
        app_title(app_title),
        app_width(app_width),
        app_height(app_height){

}

App::~App(){
        delete app_window;
}

void App::app_start(Scene *first_scene, bool vsync) {

        app_window = new sf::RenderWindow(sf::VideoMode(app_width, app_height), app_title);
        app_window->setVerticalSyncEnabled(vsync);

        first_scene->set_scene_proxy(&scene_proxy);
        first_scene->set_app_window(app_window);

        scene_proxy.set_scene(first_scene);

        while (app_window->isOpen()) {
                handle_time_actions();
                clear_and_draw();

                clock_handler.restart_clock();
                clock_handler.restart_time_handler(&app_frequency);
                scene_proxy.reset_time_handlers(clock_handler);
        }
}

void App::handle_time_actions() {
        if (app_frequency.time_to_update()) {
                process_events();
                scene_proxy.update();
        }
}

void App::process_events() {
        sf::Event event;

        while (app_window->pollEvent(event)) {
                scene_proxy.handle_event(event);
        }
}

void App::clear_and_draw() {
        app_window->clear();
        scene_proxy.draw_entities();
        app_window->display();
}

int App::get_app_width() const {
        return app_width;
}

int App::get_app_height() const {
        return app_height;
}

}