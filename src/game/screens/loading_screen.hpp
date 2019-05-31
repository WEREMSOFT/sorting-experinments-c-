//
// Created by Pablo Weremczuk on 2019-05-31.
//

#pragma once

Context &load_screen(Context &context) {
    {
        LoadScreen::Struct loadScreen(context);
        LoadScreen::utils::loadResources(loadScreen);
        LoadScreen::utils::run(loadScreen);
    }
    return context;
}
