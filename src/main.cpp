#include "headers.hpp"



int main() {

    sf::RenderWindow window(sf::VideoMode(SCREEN_WITH, SCREEN_HEIGHT), "Purfectly Safe", sf::Style::Default);
    sf::View view;
    sf::Clock clock;
    TextureHolder textureHolder;
    FontHolder fontHolder;
    Tables tables(MAX_ENTITIES);

    printf("Space in memory %lu\n", sizeof(tables));

    Context context(window, textureHolder, fontHolder, Screens::TITLE);
    context = load_screen(context);

    // Build game objects;
    tables[Entities::BACKGROUND].sprite.setTexture(context.textureHolder->get(Textures::BACKGROUND));
    tables[Entities::HOUSE].sprite.setTexture(context.textureHolder->get(Textures::HOUSE));
    tables[Entities::TABLE].sprite.setTexture(context.textureHolder->get(Textures::TABLE));;
    tables[Entities::CAT].sprite.setTexture(context.textureHolder->get(Textures::CAT_1_ANIMATION));

    // Set type = index for further reference
    gameUtils::setTypeEqualsIndex(tables);

    tables[Entities::CAT].flags |= Flags::ANIMATED;


    while (gameIsRunning) {
        switch (context.currentGameScreen) {
            case Screens::GAME_TILE:
                game_screen_tile(tables, context);
                break;
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



