#include "headers.hpp"

int main() {

    sf::RenderWindow window(sf::VideoMode(SCREEN_WITH, SCREEN_HEIGHT), "Purfectly Safe", sf::Style::Default);
    sf::View view;

    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(window.getSize().x/2, window.getSize().y/2);
    window.setView(view);

    sf::Clock clock;
    TextureHolder textureHolder;
    FontHolder fontHolder;

    Context context(window, textureHolder, fontHolder, Screens::TITLE);
    context = load_screen(context);


    while (gameIsRunning) {
        switch (context.currentGameScreen) {
            case Screens::MENU:
                town_screen::loop(context);
                break;
            case Screens::TITLE:
                title_screen::loop(context);
                break;
            case Screens::FIGHT:
                fight_screen::game_loop(context);
                break;
            case Screens::GAME:
                screen_house::game_loop(context);
                break;
        }
    }


    window.close();
    return 0;
}



