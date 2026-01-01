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

sf::Keyboard::Key InputHandler::convert(Keyboard key) const
{
	switch (key)
	{
	case Keyboard::A:
		return sf::Keyboard::Key::A;
		break;
	case Keyboard::B:
		return sf::Keyboard::Key::B;
		break;
	case Keyboard::C:
		return sf::Keyboard::Key::C;
		break;
	case Keyboard::D:
		return sf::Keyboard::Key::D;
		break;
	case Keyboard::E:
		return sf::Keyboard::Key::E;
		break;
	case Keyboard::F:
		return sf::Keyboard::Key::F;
		break;
	case Keyboard::G:
		return sf::Keyboard::Key::G;
		break;
	case Keyboard::H:
		return sf::Keyboard::Key::H;
		break;
	case Keyboard::I:
		return sf::Keyboard::Key::I;
		break;
	case Keyboard::J:
		return sf::Keyboard::Key::J;
		break;
	case Keyboard::K:
		return sf::Keyboard::Key::K;
		break;
	case Keyboard::L:
		return sf::Keyboard::Key::L;
		break;
	case Keyboard::M:
		return sf::Keyboard::Key::M;
		break;
	case Keyboard::N:
		return sf::Keyboard::Key::N;
		break;
	case Keyboard::O:
		return sf::Keyboard::Key::O;
		break;
	case Keyboard::P:
		return sf::Keyboard::Key::P;
		break;
	case Keyboard::Q:
		return sf::Keyboard::Key::Q;
		break;
	case Keyboard::R:
		return sf::Keyboard::Key::R;
		break;
	case Keyboard::S:
		return sf::Keyboard::Key::S;
		break;
	case Keyboard::T:
		return sf::Keyboard::Key::T;
		break;
	case Keyboard::U:
		return sf::Keyboard::Key::U;
		break;
	case Keyboard::V:
		return sf::Keyboard::Key::V;
		break;
	case Keyboard::W:
		return sf::Keyboard::Key::W;
		break;
	case Keyboard::X:
		return sf::Keyboard::Key::X;
		break;
	case Keyboard::Y:
		return sf::Keyboard::Key::Y;
		break;
	case Keyboard::Z:
		return sf::Keyboard::Key::Z;
		break;
	case Keyboard::Esc:
		return sf::Keyboard::Key::Escape;
		break;
	case Keyboard::Tab:
		return sf::Keyboard::Key::Tab;
		break;
	case Keyboard::LShift:
		return sf::Keyboard::Key::LShift;
		break;
	case Keyboard::RShift:
		return sf::Keyboard::Key::RShift;
		break;
	case Keyboard::LCtrl:
		return sf::Keyboard::Key::LControl;
		break;
	case Keyboard::RCtrl:
		return sf::Keyboard::Key::RControl;
		break;
	case Keyboard::LAlt:
		return sf::Keyboard::Key::LAlt;
		break;
	case Keyboard::RAlt:
		return sf::Keyboard::Key::RAlt;
		break;
	case Keyboard::Space:
		return sf::Keyboard::Key::Space;
		break;
	case Keyboard::Up:
		return sf::Keyboard::Key::Up;
		break;
	case Keyboard::Left:
		return sf::Keyboard::Key::Left;
		break;
	case Keyboard::Down:
		return sf::Keyboard::Key::Down;
		break;
	case Keyboard::Right:
		return sf::Keyboard::Key::Right;
		break;
	case Keyboard::Num1:
		return sf::Keyboard::Key::Num1;
		break;
	case Keyboard::Num2:
		return sf::Keyboard::Key::Num2;
		break;
	case Keyboard::Num3:
		return sf::Keyboard::Key::Num3;
		break;
	case Keyboard::Num4:
		return sf::Keyboard::Key::Num4;
		break;
	case Keyboard::Num5:
		return sf::Keyboard::Key::Num5;
		break;
	case Keyboard::Num6:
		return sf::Keyboard::Key::Num6;
		break;
	case Keyboard::Num7:
		return sf::Keyboard::Key::Num7;
		break;
	case Keyboard::Num8:
		return sf::Keyboard::Key::Num8;
		break;
	case Keyboard::Num9:
		return sf::Keyboard::Key::Num9;
		break;
	case Keyboard::Num0:
		return sf::Keyboard::Key::Num0;
		break;
	default:
		return sf::Keyboard::Key::A;
	}
}

sf::Mouse::Button InputHandler::convert(Mouse button) const
{
	switch (button)
	{
	case Mouse::M1:
		return sf::Mouse::Button::Left;
		break;
	case Mouse::M2:
		return sf::Mouse::Button::Right;
		break;
	case Mouse::M3:
		return sf::Mouse::Button::Middle;
		break;
	case Mouse::M4:
		return sf::Mouse::Button::Extra1;
		break;
	case Mouse::M5:
		return sf::Mouse::Button::Extra2;
		break;
	default:
		return sf::Mouse::Button::Left;
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

bool InputHandler::is_key_pressed(Keyboard key) const 
{
	auto it = keyPressed.find(convert(key));
	return it != keyPressed.end() && it->second;
}

bool InputHandler::is_key_held(Keyboard key) const 
{
	return sf::Keyboard::isKeyPressed(convert(key));
}

bool InputHandler::is_button_pressed(Mouse button) const 
{
	auto it = buttonPressed.find(convert(button));
	return it != buttonPressed.end() && it->second;
}

bool InputHandler::is_button_held(Mouse button) const 
{
	return sf::Mouse::isButtonPressed(convert(button));
}

FVector InputHandler::get_mouse_pos() const
{
	return GAME_WINDOW.get_mouse_pos();
}