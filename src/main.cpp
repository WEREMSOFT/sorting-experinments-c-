#include "headers.hpp"

int main() {

    sf::RenderWindow window(sf::VideoMode(SCREEN_WITH, SCREEN_HEIGHT), "Purfectly Safe", sf::Style::Default);
    sf::View view;

    //        view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    view.setSize(window.getSize().x, window.getSize().y);
    view.setCenter(window.getSize().x/2, window.getSize().y/2);
    window.setView(view);

    sf::Clock clock;
    TextureHolder textureHolder;
    FontHolder fontHolder;
    Tables tables(MAX_ENTITIES);

    printf("Space in memory %lu\n", sizeof(tables));

    Context context(window, textureHolder, fontHolder, Screens::TITLE);
    context = load_screen(context);

    // Set entity_type = index for further reference
    entity_set_type_equals_index(tables);

    tables[Entities::CAT].flags |= Flags::ANIMATED;


    while (gameIsRunning) {
        switch (context.currentGameScreen) {
            case Screens::TITLE:
                title_screen(tables, context);
                break;
            case Screens::GAME:
                game_screen(tables, context);
                break;
        }
    }


    window.close();
    return 0;
}



