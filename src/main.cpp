#include "headers.hpp"


int main() {

    sf::RenderWindow window(sf::VideoMode(SCREEN_WITH, SCREEN_HEIGHT), "Purfectly Safe", sf::Style::Default);
    sf::View view;

    window.setFramerateLimit(30);

    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(window.getSize().x/2, window.getSize().y/2);
    window.setView(view);

    sf::Clock clock;
    TextureHolder textureHolder;
    FontHolder fontHolder;

    Context context(window, textureHolder, fontHolder, Screens::TITLE);
    context = load_screen(context);

    MainMenu mainMenu(context);

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

        mainMenu.update(dt);

        window.clear();
        window.draw(mainMenu);
        window.display();

    }

    window.close();
    return 0;
}



