//
// Created by Pablo Weremczuk on 2019-05-31.
//

#pragma once

void cat_handle_states(Tables& tables, int id, AnimationVector& cat_animations){
    switch (tables[Entities::CAT].state) {
        case cat::States::IDLE:
            cat_state_process_idle(tables, Entities::CAT, cat_animations);
            break;
        case cat::States::WALKING:
            cat_state_process_walking(tables, Entities::CAT, cat_animations);
            break;
    }
}

void game_screen(Tables &tables, Context &context) {
    sf::RenderWindow &window = *context.window;
    sf::Clock clock;
    sf::Time sleepInterval = sf::seconds(.02f);

    // Build game objects;
    tables[Entities::BACKGROUND].sprite.setTexture(context.textureHolder->get(Textures::BACKGROUND));
    tables[Entities::HOUSE].sprite.setTexture(context.textureHolder->get(Textures::HOUSE));
    tables[Entities::TABLE].sprite.setTexture(context.textureHolder->get(Textures::TABLE));;
    tables[Entities::CAT].sprite.setTexture(context.textureHolder->get(Textures::CAT_1_ANIMATION));
    tables[Entities::MOTH].sprite.setTexture(context.textureHolder->get(Textures::MOTH));


    AnimationVector cat_animations(cat::Animations::ANIM_COUNT);
    cat_animations_init(cat_animations, context);
    cat_state_to_idle(tables, Entities::CAT, cat_animations);

    entity_set_position(tables, Entities::TABLE, sf::Vector2f(500, 446));
    tables[Entities::TABLE].zIndex = tables[Entities::TABLE].sprite.getPosition().y;

    entity_set_position(tables, Entities::MOTH, sf::Vector2f(100, 100));
    entity_set_child(tables, Entities::MOTH, Entities::CAT);

    FPSCounter::Struct fpsCounter;
    fpsCounter.font = &context.fontHolder->get(Fonts::PRESS_START);

    sf::Event event;
    while (gameIsRunning && context.currentGameScreen == Screens::GAME) {
        float dt = clock.restart().asSeconds();

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                gameIsRunning = false;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            gameIsRunning = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            context.currentGameScreen = Screens::TITLE;
        }

        sort_by_entity_type(tables);
        cat_keyboard_event_handler(tables, Entities::CAT, dt);
        entity_set_scale_based_on_flipped_flag(tables);

        cat_handle_states(tables, Entities::CAT, cat_animations);

        tables[Entities::CAT].zIndex = tables[Entities::CAT].sprite.getPosition().y;
        entity_recalculate_world_transforms(tables);
        entity_handle_animation(tables, Entities::CAT, dt);

        {
            int firstAnimated = sort_by_animated(tables);
            process_animations(tables, firstAnimated);
        }

        sort_by_z_index(tables);
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
