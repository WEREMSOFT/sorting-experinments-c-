#include "headers.hpp"


int main() {

    Screen* screens[SCREEN_COUNT] = {0};

    sf::RenderWindow window(sf::VideoMode(SCREEN_WITH, SCREEN_HEIGHT), "Purfectly Safe", sf::Style::Fullscreen);
    sf::View view;

    window.setFramerateLimit(60);

    sf::Clock clock;
    TextureHolder textureHolder;
    FontHolder fontHolder;

    // Set the initial screen
    Context context(window, textureHolder, fontHolder, MAIN_MENU);
    context = load_screen(context);

    context.screenSize.x = SCREEN_WITH;
    context.screenSize.y = SCREEN_HEIGHT;

    view.setSize(context.screenSize.x, context.screenSize.y);
    view.setCenter(context.screenSize.x/2, context.screenSize.y/2);
    window.setView(view);


    MainMenu mainMenu(context);
    Town town(context);
    Dialog dialog(context);

    screens[MAIN_MENU] = &mainMenu;
    screens[TOWN] = &town;
    screens[DIALOG] = &dialog;


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



