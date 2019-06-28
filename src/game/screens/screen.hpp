#pragma once


struct Shutters: GameObject{
    enum States {
        SHUTTERS_CLOSED,
        SHUTTERS_OPEN,
        SHUTTERS_OPENING,
        SHUTTERS_CLOSING,
        SHUTTERS_STATE_COUNT
    };

    const float shade_speed = 4000;
    sf::Vector2f size_screen;

    sf::RectangleShape shade_up;
    sf::RectangleShape shade_down;
    bool isOpen = false;

    Shutters(Context& context){
        sf::RenderWindow& window = *context.window;

        size_screen.y = context.screenSize.y;
        size_screen.x = context.screenSize.x;

        size_screen.y /= 2;

        shade_up.setSize(size_screen);
        shade_down.setSize(size_screen);

        shade_up.setFillColor(sf::Color::Black);
        shade_down.setFillColor(sf::Color::Black);

        passToStateOpen();
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        GameObject::draw(target, states);
        target.draw(shade_up, states);
        target.draw(shade_down, states);
    }


    void processShuttersClosing(float dt) {
        shade_down.move(0, -shade_speed * dt);
        shade_up.move(0, shade_speed * dt);

        if( shade_down.getPosition().y <= size_screen.y ){
            shade_down.setPosition( shade_down.getPosition().x, size_screen.y);
            passToStateClosed();
        }

    }

    void processShuttersOpening(float dt) {
        shade_down.move(0, shade_speed * dt);
        shade_up.move(0, -shade_speed * dt);

        if( shade_up.getPosition().y <= -size_screen.y ){
            passToStateOpen();
        }
    }

    void passToStateOpenning(){
        state = SHUTTERS_OPENING;
    }

    void passToStateClosing(){
        state = SHUTTERS_CLOSING;
    }

    void passToStateOpen(){
        state = SHUTTERS_OPEN;
        shade_up.setPosition(0, -size_screen.y);
        shade_down.setPosition(0, size_screen.y * 2);
    }

    void passToStateClosed(){
        state = SHUTTERS_CLOSED;
        shade_up.setPosition(0, 0);
        shade_down.setPosition(0, size_screen.y);
    }

    void update(float dt) override {
        GameObject::update(dt);

        switch (state){
            case SHUTTERS_OPENING:
                processShuttersOpening(dt);
                break;
            case SHUTTERS_CLOSING:
                processShuttersClosing(dt);
                break;
            case SHUTTERS_OPEN:
            case SHUTTERS_CLOSED:
                break;

        }
    }

};


struct Screen: GameObject {
    Shutters shutters;
    Context* context;
    int nextScreen = 0;

    enum Layers {
        LAYER_BACKGROUND,
        LAYER_MIDDLE,
        LAYER_FOREGROUND,
        LAYER_COUNT
    };

    GameObject layers[LAYER_COUNT];

    enum States {
        IDLE,
        TRANSITION_OUT,
        TRANSITION_IN
    };

    Screen(sf::Texture& texture, Context& pContext): GameObject(texture), shutters(pContext), context(&pContext){
        bool shade_is_closed = true;
        addChild(&layers[LAYER_BACKGROUND]);
        addChild(&layers[LAYER_MIDDLE]);
        addChild(&layers[LAYER_FOREGROUND]);

        layers[LAYER_FOREGROUND].addChild(&shutters);
        shutters.passToStateClosed();
        shutters.passToStateOpenning();
    }

    void passToStateIdle(){
        state = IDLE;
    }

    virtual void passToStateTransitionIn(){
        shutters.passToStateOpenning();
        state = TRANSITION_IN;

    }

    void processStateTransitionIn(){
        if(shutters.state == Shutters::SHUTTERS_OPEN){
            passToStateIdle();
        }
    }

    void passToStateTransitionOut(int pNextScreen){
        nextScreen = pNextScreen;
        shutters.passToStateClosing();
        state = TRANSITION_OUT;
    }

    void processStateTransitionOut(){
        if(shutters.state == Shutters::SHUTTERS_CLOSED){
            passToStateTransitionIn();
            context->currentGameScreen = nextScreen;
        }
    }

    void update(float dt){
        GameObject::update(dt);

        switch(state){
            case TRANSITION_IN:
                processStateTransitionIn();
                break;
            case TRANSITION_OUT:
                processStateTransitionOut();
                break;
            case IDLE:
                break;
        }
    }
};