//
// Created by Pablo Weremczuk on 2019-05-31.
//

#pragma once

void thread_print_position(Tables &tables, int id) {
    while (gameIsRunning) {
        sf::Vector2f position = tables[id].sprite.getPosition();
        printf("Position %f, %f\n", position.x, position.y);
    }
}

