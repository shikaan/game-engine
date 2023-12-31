#include "WorldManager.h"

#include "ObjectListIterator.h"

#define WM df::WorldManager::getInstance()

namespace df {

WorldManager::WorldManager() {}

WorldManager& WorldManager::getInstance() {
  static WorldManager instance;
  return instance;
}

int WorldManager::startUp() {
  setType("WorldManager");
  m_deletions = ObjectList();
  m_updates = ObjectList();

  return Manager::startUp();
}

void WorldManager::shutDown() {
  auto updates = m_updates;  // create a copy
  auto iterator = ObjectListIterator(&updates);
  for (iterator.first(); !iterator.isDone(); iterator.next()) {
    // This is not leaving a danglig null reference!
    // In the destructor of Object, we also remove it from the world
    delete iterator.currentObject();
  }

  m_updates.clear();

  Manager::shutDown();
}

int WorldManager::insertObject(Object* p_o) { return m_updates.insert(p_o); }

int WorldManager::removeObject(Object* p_o) { return m_updates.remove(p_o); }

ObjectList WorldManager::getAllObjects() const { return m_updates; }

ObjectList WorldManager::objectsOfType(std::string type) const {
  ObjectList result;
  df::ObjectListIterator* iterator = new ObjectListIterator(&m_updates);
  for (iterator->first(); !iterator->isDone(); iterator->next()) {
    if (iterator->currentObject()->getType() == type) {
      result.insert(iterator->currentObject());
    }
  }

  return result;
}

void WorldManager::update() {
  auto iterator = new ObjectListIterator(&m_deletions);
  for (iterator->first(); !iterator->isDone(); iterator->next()) {
    removeObject(iterator->currentObject());
    delete iterator->currentObject();
  }
  m_deletions.clear();
}

int WorldManager::markForDelete(Object* p_o) {
  // Prevents marking the same object for deletion twice
  auto iterator = new ObjectListIterator(&m_deletions);

  for (iterator->first(); !iterator->isDone(); iterator->next()) {
    if (iterator->currentObject() == p_o) {
      return 0;
    }
  }

  return m_deletions.insert(p_o);
}
}  // namespace df