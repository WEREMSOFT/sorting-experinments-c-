#include "headers.hpp"

struct Tile: GameObject {
    Tile(Context& context): GameObject(context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE)){}

    void update(float dt) override {
        GameObject::update(dt);
        sprite.rotate(90 * dt);
    }

};



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

    sf::Event event;

    Tile go(context);
    Tile go1(context);

    go1.setPosition(32, 32);

    go.setPosition(100, 100);
    go.addChild(&go1);

    GameObject world(context.textureHolder->get(Textures::BACKGROUND_DIALOG));

    world.addChild(&go);

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

        world.update(dt);

        window.clear();
        window.draw(world);
        window.display();

    }

    window.close();
    return 0;
}



