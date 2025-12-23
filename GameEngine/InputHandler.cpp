#include "InputHandler.h"

InputHandler::InputHandler() 
{
	for (int i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(i);
		canPressKey[key] = true;
		keyPressed[key] = false;
	}
	for (int i = 0; i < sf::Mouse::ButtonCount; i++)
	{
		sf::Mouse::Button button = static_cast<sf::Mouse::Button>(i);
		canPressButton[button] = true;
		buttonPressed[button] = false;
	}
}

InputHandler& InputHandler::instance() 
{
	static InputHandler instance;
	return instance;
}

void InputHandler::update() 
{
	//Keyboard Update
	for (auto& [key, canPress] : canPressKey)
		if (sf::Keyboard::isKeyPressed(key))
			if (canPress)
			{
				keyPressed[key] = true;
				canPress = false;
			}
			else
				keyPressed[key] = false;
		else 
		{
			canPress = true;
			keyPressed[key] = false;
		}

	//Mouse Update
	for (auto& [button, canPress] : canPressButton)
		if (sf::Mouse::isButtonPressed(button))
			if (canPress) {
				buttonPressed[button] = true;
				canPress = false;
			}
			else
				buttonPressed[button] = false;
		else {
			canPress = true;
			buttonPressed[button] = false;
		}
}

bool InputHandler::is_key_pressed(sf::Keyboard::Key key) const 
{
	auto it = keyPressed.find(key);
	return it != keyPressed.end() && it->second;
}

bool InputHandler::is_key_held(sf::Keyboard::Key key) const 
{
	return sf::Keyboard::isKeyPressed(key);
}

bool InputHandler::is_button_pressed(sf::Mouse::Button button) const 
{
	auto it = buttonPressed.find(button);
	return it != buttonPressed.end() && it->second;
}

bool InputHandler::is_button_held(sf::Mouse::Button button) const 
{
	return sf::Mouse::isButtonPressed(button);
}

FVector InputHandler::get_mouse_pos() const
{
	return GAME_WINDOW.get_mouse_pos();
}