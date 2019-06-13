#pragma once

#include "game_screen.hpp"

void game_screen_tile(Tables &tables, Context &context) {
    sf::RenderWindow &window = *context.window;

    sf::Clock clock;

    FPSCounter::Struct fpsCounter;
    fpsCounter.font = &context.fontHolder->get(Fonts::PRESS_START);


    // Build game objects;
    tables[Entities::BACKGROUND].sprite.setTexture(context.textureHolder->get(Textures::BACKGROUND));
    tables[Entities::MOTH].sprite.setTexture(context.textureHolder->get(Textures::MOTH));

    context.textureHolder->get(Textures::SCI_FI_TILES).setRepeated(true);

    tables[Entities::SCI_FI_TILES].sprite.setTexture(context.textureHolder->get(Textures::SCI_FI_TILES));
    tables[Entities::SCI_FI_TILES].sprite.setTextureRect(sf::IntRect(0, 0, window.getSize().x, 400));
    entity_move(tables, Entities::SCI_FI_TILES, sf::Vector2f(0, 400));



    tables[Entities::HOUSE].sprite.setTexture(context.textureHolder->get(Textures::HOUSE));
    tables[Entities::TABLE].sprite.setTexture(context.textureHolder->get(Textures::TABLE));;
    tables[Entities::CAT].sprite.setTexture(context.textureHolder->get(Textures::CAT_1_ANIMATION));
    tables[Entities::CAT].sprite.setScale(-1, 1);


    AnimationVector cat_animations(cat::Animations::ANIM_COUNT);
    cat_animations_init(cat_animations, context);

    cat_state_to_idle(tables, Entities::CAT, cat_animations);
    entity_move(tables, Entities::CAT, sf::Vector2f(78, 347));

    sf::Event event;
    while (gameIsRunning && context.currentGameScreen == Screens::GAME_TILE) {
        float dt = clock.restart().asSeconds();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                gameIsRunning = false;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
            gameIsRunning = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            context.currentGameScreen = Screens::TITLE;
        }

        sort_by_entity_type(tables);

        print_position(tables, Entities::CAT);

        tile_keyboard_event_handler(tables, Entities::CAT);

        switch (tables[Entities::CAT].state) {
            case cat::States::IDLE:
                cat_state_process_idle(tables, Entities::CAT, cat_animations);
                break;
            case cat::States::WALKING:
                cat_state_process_walking(tables, Entities::CAT, cat_animations);
                break;
        }

        entity_handle_animation(tables, Entities::CAT, dt);
        tables[Entities::CAT].zIndex = tables[Entities::CAT].sprite.getPosition().y;

        {
            int firstAnimated = sort_by_animated(tables);
            process_animations(tables, firstAnimated);
        }

        entity_recalculate_world_transforms(tables);

        // Draw routine
//        sort_by_z_index(tables);
        draw(tables, context, 0, Entities::ENTITIES_COUNT);

        FPSCounter::utils::recalculateFPS(fpsCounter);
        FPSCounter::utils::draw(fpsCounter, window);

        window.display();

        // If I updated too fast, then sleep for the rest of the frame (saves battery)
        sf::Time elapsedTime = clock.getElapsedTime();

        if (elapsedTime.asSeconds() < DELAY_UPDATE) {
            sf::sleep(sf::seconds(DELAY_UPDATE));
        }
    }

}


