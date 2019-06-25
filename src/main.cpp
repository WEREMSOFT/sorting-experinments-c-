#include "headers.hpp"


int main() {

    Screen* screens[SCREEN_COUNT] = {0};

    sf::RenderWindow window(sf::VideoMode(SCREEN_WITH, SCREEN_HEIGHT), "Purfectly Safe", sf::Style::Default);
    sf::View view;

    window.setFramerateLimit(60);

    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(window.getSize().x/2, window.getSize().y/2);
    window.setView(view);

    sf::Clock clock;
    TextureHolder textureHolder;
    FontHolder fontHolder;

    // Set the initial screen
    Context context(window, textureHolder, fontHolder, MAIN_MENU);
    context = load_screen(context);

    MainMenu mainMenu(context);
    Town town(context);

    screens[MAIN_MENU] = &mainMenu;
    screens[TOWN] = &town;


    context.currentGameScreen = MAIN_MENU;

    sf::Event event;
    float dt = 0;
    while(window.isOpen()){
        dt = clock.restart().asSeconds();

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            window.close();
        }

        screens[context.currentGameScreen]->update(dt);

        window.clear();
        window.draw(*screens[context.currentGameScreen]);
        window.display();

    }

    window.close();
    return 0;
}



