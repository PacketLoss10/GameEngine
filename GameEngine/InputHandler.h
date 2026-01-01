#pragma once

#include "EngineUtils.h"
#include "GameWindow.h"

#define INPUT InputHandler::instance()

enum class Keyboard
{
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    Esc,
    Tab,
    LShift,
    RShift,
    LCtrl,
    RCtrl,
    LAlt,
    RAlt,
    Space,
    Up,
    Left,
    Down,
    Right,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,
    Num0
};

enum class Mouse
{
    M1,
    M2,
    M3,
    M4,
    M5
};

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
    sf::Keyboard::Key convert(Keyboard key) const;
    sf::Mouse::Button convert(Mouse button) const;
public:
    static InputHandler& instance();
    void update();
    bool is_key_pressed(Keyboard key) const;
    bool is_key_held(Keyboard key) const;
    bool is_button_pressed(Mouse button) const;
    bool is_button_held(Mouse button) const;
    FVector get_mouse_pos() const;
};