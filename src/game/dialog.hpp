//
// Created by Pablo Weremczuk on 2019-06-22.
//

#pragma once


namespace dialog {

    struct Struct {
        int offsetY = 0;
        std::string text;
        dialog::Struct* next;
        std::vector<dialog::Struct> children;
        void (* callback)() ;

        Struct(std::string pText) : text(pText){}
    };

    void draw(dialog::Struct& dialog, sf::RenderWindow& window, sf::Font& font){
        sf::Text dialogText;
        dialogText.setFont(font);
        dialogText.setFillColor(sf::Color::White);
        dialogText.setOutlineThickness(3);
        dialogText.setOutlineColor(sf::Color::Black);
        dialogText.setCharacterSize(30);
        dialogText.setString("OOOOOOOO");
        const int lineHeight = dialogText.getLocalBounds().height;
        int line = 0;
        const int padding = 10;

        for(Struct child: dialog.children){
            dialogText.setString(child.text);
            text_center_origin(dialogText);
            text_center_on_screen(dialogText, window);
            dialogText.move(0, ( lineHeight + padding )  * line  + dialog.offsetY);
            window.draw(dialogText);
            line++;
        }

    }
};


