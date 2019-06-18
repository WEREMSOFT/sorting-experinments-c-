//
// Created by Pablo Weremczuk on 2019-05-31.
//

#pragma once

namespace fight_screen {

    enum Entities {
        BACKGROUND,
        HENCHMAN,
        LITTLE_MAC,
        ENTITIES_COUNT,
    };

    void handle_window_events_and_screen_navigation(Context &context, sf::RenderWindow &window, sf::Event &event) {
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
            context.currentGameScreen = TITLE;
        }
    }

    void initialize_entities_state(Context &context, Tables &tables, anim::AnimationVector *animations) {
        tables[BACKGROUND].sprite.setTexture(context.textureHolder->get(Textures::BACKGROUND_FIGHT));

        little_mac::create(tables[LITTLE_MAC], context, animations[LITTLE_MAC]);
        henchman::create(tables[HENCHMAN], context, animations[HENCHMAN]);

//        tables[HENCHMAN].sprite.setTexture(context.textureHolder->get(Textures::HENCHMAN));

//        entity_center_on_screen(tables[HENCHMAN], *context.window);

//        entity_move(tables, HENCHMAN, sf::Vector2f(0, -70.f));

//        henchman::animations_init(animations[HENCHMAN], context);
//        henchman::state_to_idle(tables, HENCHMAN, animations[HENCHMAN]);

//        tables[HENCHMAN].sprite.setScale(3, 3);

//        entity_set_animated(tables[HENCHMAN]);
    }

    void game_loop(Context &context) {

        Tables tables(ENTITIES_COUNT);

        // Render
        sf::RenderWindow &window = *context.window;
        sf::Clock clock;
        sf::Time sleepInterval = sf::seconds(.02f);

        entity_set_type_equals_index(tables);

        anim::AnimationVector animations[ENTITIES_COUNT];

        animations[LITTLE_MAC] = anim::AnimationVector(little_mac::ANIM_COUNT);
        animations[HENCHMAN] = anim::AnimationVector(henchman::ANIM_COUNT);

        initialize_entities_state(context, tables, animations);

        FPSCounter::Struct fpsCounter;
        fpsCounter.font = &context.fontHolder->get(Fonts::PRESS_START);

        sf::Event event;
        // Metrics
        float averageRunningTime = 0;
        while (gameIsRunning && context.currentGameScreen == Screens::FIGHT) {
            float dt = clock.restart().asSeconds();

            handle_window_events_and_screen_navigation(context, window, event);

            // KEYBOARD
            sort_by_entity_type(tables);
            entity_set_scale_based_on_flipped_flag(tables);


            little_mac::handle_states(tables, Entities::LITTLE_MAC, animations[LITTLE_MAC]);
            henchman::handle_states(tables[Entities::HENCHMAN], animations[HENCHMAN]);

            entity_recalculate_world_transforms(tables);

            // ANIMATION UPDATE
            int firstAnimated = sort_by_animated(tables);
            process_animations(tables, firstAnimated, dt);

            sort_by_z_index(tables);
            draw(tables, context, 0, Entities::ENTITIES_COUNT);

            FPSCounter::utils::recalculateFPS(fpsCounter);
            FPSCounter::utils::draw(fpsCounter, window);

            window.display();

            // If I updated too fast, then sleep for the rest of the frame (saves battery)
            sf::Time elapsedTime = clock.getElapsedTime();

            if (elapsedTime.asSeconds() < DELAY_UPDATE) {
                if(averageRunningTime == 0) averageRunningTime = elapsedTime.asSeconds();

                averageRunningTime = (averageRunningTime + elapsedTime.asSeconds()) / 2;

                sf::sleep(sf::seconds(DELAY_UPDATE));
            }

        }

        printf("average running time: %f of an historical lowest of 0.001392 secs\n", averageRunningTime);


    }
}

