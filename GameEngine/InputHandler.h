#pragma once

#include "EngineUtils.h"
#include "GameWindow.h"

#define INPUT InputHandler::instance()

class InputHandler 
{
private:
    std::unordered_map<sf::Keyboard::Key, bool> canPressKey;
    std::unordered_map<sf::Keyboard::Key, bool> keyPressed;
    std::unordered_map<sf::Mouse::Button, bool> canPressButton;
    std::unordered_map<sf::Mouse::Button, bool> buttonPressed;
    InputHandler();
    InputHandler(const InputHandler&) = delete;
    InputHandler& operator=(const InputHandler&) = delete;
public:
    static InputHandler& instance();
    void update();
    bool is_key_pressed(sf::Keyboard::Key key) const;
    bool is_key_held(sf::Keyboard::Key key) const;
    bool is_button_pressed(sf::Mouse::Button button) const;
    bool is_button_held(sf::Mouse::Button button) const;
    FVector get_mouse_pos() const;
};
