#include "headers.hpp"


int main() {

    sf::RenderWindow window(sf::VideoMode(SCREEN_WITH, SCREEN_HEIGHT), "Purfectly Safe", sf::Style::Default);
    sf::View view;
    sf::Clock clock;
    TextureHolder textureHolder;
    FontHolder fontHolder;
    Tables tables(MAX_ENTITIES);

    printf("Space in memory %lu\n", sizeof(tables));

    Context context(window, textureHolder, fontHolder, Screens::GAME);
    context = load_screen(context);

    // Build game objects;
    tables[Entities::BACKGROUND].sprite.setTexture(context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE));
    tables[Entities::HOUSE].sprite.setTexture(context.textureHolder->get(Textures::TITLE_BACKGROUND_TILE));
    tables[Entities::TABLE].sprite.setTexture(context.textureHolder->get(Textures::TABLE));;
    tables[Entities::CAT].sprite.setTexture(context.textureHolder->get(Textures::CAT_1_ANIMATION));

    // Set type = index for further reference
    gameUtils::setTypeEqualsIndex(tables);


    // Cat animations
    tables[Entities::CAT].animations.texture = &context.textureHolder->get(Textures::CAT_1_ANIMATION);
    tables[Entities::CAT].animations.maxFrames = 8;
    tables[Entities::CAT].animations.frameSize = {0, 767, 148, 193};
    tables[Entities::CAT].animations.textureRect = {0, 767, 148, 193};
    tables[Entities::CAT].animations.framesPerSeccond = 8;
    tables[Entities::CAT].animations.centered = true;
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



