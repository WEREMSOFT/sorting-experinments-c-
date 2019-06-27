#include "headers.hpp"


int main() {
    Screen* screens[SCREEN_COUNT] = {0};
    sf::Clock clock;
    TextureHolder textureHolder;
    FontHolder fontHolder;
    sf::View view;
    FPSCounter::Struct fpsCounter;

    FPSCounter::utils::initialize(fpsCounter);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WITH, SCREEN_HEIGHT), "Purfectly Safe", sf::Style::Default);

    window.setFramerateLimit(60);


    // Set the initial screen
    Context context(window, textureHolder, fontHolder, MAIN_MENU);

    context.screenSize.x = SCREEN_WITH;
    context.screenSize.y = SCREEN_HEIGHT;

    view.setSize(context.screenSize.x, context.screenSize.y);
    view.setCenter(context.screenSize.x/2, context.screenSize.y/2);
    window.setView(view);

    context = load_screen(context);




    MainMenu mainMenu(context);
    Town town(context);
    Dialog dialog(context);

    screens[MAIN_MENU] = &mainMenu;
    screens[TOWN] = &town;
    screens[DIALOG] = &dialog;

    fpsCounter.font = &context.fontHolder->get(Fonts::PRESS_START);

    context.currentGameScreen = MAIN_MENU;

    sf::Event event;
    float dt = 0;
    bool fullscreen = true;
    while(window.isOpen()){
        dt = clock.restart().asSeconds();

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == keys::F)) {
                fullscreen = !fullscreen;
                window.create(sf::VideoMode(SCREEN_WITH, SCREEN_HEIGHT), "Purflactlt Safe", (fullscreen ? sf::Style::Fullscreen : sf::Style::Default));
                window.setView(view);
                window.setFramerateLimit(60);
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            window.close();
        }

        screens[context.currentGameScreen]->update(dt);
        FPSCounter::utils::recalculateFPS(fpsCounter);
        FPSCounter::utils::calculateAVGFPS(fpsCounter);

        window.clear();
        window.draw(*screens[context.currentGameScreen]);
        FPSCounter::utils::draw(fpsCounter, window);
        window.display();

    }

    window.close();
    return 0;
}



