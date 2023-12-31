#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include <unordered_map>

#include "EventKeyboard.h"
#include "EventMouse.h"
#include "Manager.h"
#include "SFML/Window.hpp"

#define IM df::InputManager::getInstance()

namespace df {
class InputManager : public Manager {
 private:
  InputManager();
  InputManager(InputManager const &);
  void operator=(InputManager const &);
  std::unordered_map<sf::Keyboard::Key, Keyboard::Key> m_keyboardEvent;
  std::unordered_map<sf::Mouse::Button, Mouse::Button> m_mouseEvent;
  Keyboard::Key fromSFMLKeyCode(sf::Keyboard::Key key) const;
  Mouse::Button fromSFMLMouseButton(sf::Mouse::Button btn) const;

 public:
  static InputManager &getInstance();
  int startUp() override;
  void shutDown() override;
  void getInput() const;
};
}  // namespace df

#endif