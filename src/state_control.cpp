/**
 * @file state_control.cpp
 * @brief Implementation of the StateControl class for managing boolean states.
 * @author ATphonOS 
 * @version v1.1.0
 * @date 2024
 * @license MIT
 */

#include "state_control.h"
#include <avr/pgmspace.h>

static const char NOT_INDEX[] PROGMEM = "- unassigned";  // for debug
static const char INDEX[] PROGMEM = " assigned";         // for debug

StateControl::StateControl(uint8_t size)
  : def_size(size > 0 ? size : 1), array(nullptr), trueIndex(-1), savedState(nullptr), savedTrueIndex(-1) {
  if (def_size > 254) def_size = 254;
  array = new bool[def_size]();
  if (!array) {
    def_size = 0;
    return;
  }
  savedState = new bool[def_size]();
  if (!savedState) {
    delete[] array;
    array = nullptr;
    def_size = 0;
    return;
  }
}

StateControl::~StateControl() {
  delete[] array;
  delete[] savedState;
}

void StateControl::setState(uint8_t index, bool exclusive) {
  if (!isValidIndex(index)) return;
  array[index] = true;
  trueIndex = index;
  if (exclusive) clearOthers(index);
}

void StateControl::setState(uint8_t index, bool state, bool exclusive) {
  if (!isValidIndex(index)) return;
  array[index] = state;
  if (state) {
    trueIndex = index;
    if (exclusive) clearOthers(index);
  } else if (index == trueIndex) {
    trueIndex = -1;
  }
}

void StateControl::saveState() {
  if (!array || !savedState || def_size == 0) return;
  for (uint8_t i = 0; i < def_size; i++) {
    savedState[i] = array[i];
  }
  savedTrueIndex = trueIndex;
}

void StateControl::restoreSavedState() {
  if (!array || !savedState || def_size == 0) return;
  for (uint8_t i = 0; i < def_size; i++) {
    array[i] = savedState[i];
  }
  trueIndex = savedTrueIndex;
}

void StateControl::toggleState(uint8_t index) {
  if (!isValidIndex(index)) return;
  array[index] = !array[index];
  if (array[index]) {
    trueIndex = index;
    clearOthers(index);
  } else if (index == trueIndex) {
    trueIndex = -1;
  }
}

void StateControl::resetArray() {
  if (!array || def_size == 0) return;
  for (uint8_t i = 0; i < def_size; i++) {
    array[i] = false;
  }
  trueIndex = -1;
}

void StateControl::setAllStates(bool state) {
  if (!array || def_size == 0) return;
  for (uint8_t i = 0; i < def_size; i++) {
    array[i] = state;
  }
  trueIndex = state ? 0 : -1;
}

void StateControl::setDefaultIndex() {
  if (!array || def_size == 0) return;
  for (uint8_t i = 0; i < def_size; i++) {
    array[i] = (i == 0);
  }
  trueIndex = 0;
}

bool StateControl::getState(uint8_t index) const {
  return isValidIndex(index) ? array[index] : false;
}

int8_t StateControl::getFirstTrueIndex() const {
  if (!array) return -1;
  for (uint8_t i = 0; i < def_size; i++) {
    if (array[i]) return i;
  }
  return -1;
}

uint8_t* StateControl::getAllTrueIndices(uint8_t& count) const {
  if (!array || def_size == 0) {
    count = 0;
    return nullptr;
  }
  count = countTrueStates();
  if (count == 0) return nullptr;

  uint8_t* indices = new uint8_t[count];
  if (!indices) {
    count = 0;
    return nullptr;
  }

  uint8_t pos = 0;
  for (uint8_t i = 0; i < def_size; i++) {
    if (array[i]) indices[pos++] = i;
  }
  return indices;
}

// Returns the true index directly
int8_t StateControl::getIndex() const {
  return trueIndex;
}

void StateControl::getIndex(char* buffer, uint8_t bufSize) const {
  if (!buffer || bufSize == 0) return;
  if (trueIndex >= 0) {
    snprintf_P(buffer, bufSize, PSTR("%d%s"), trueIndex, INDEX);
  } else {
    strncpy_P(buffer, NOT_INDEX, bufSize);
  }
  buffer[bufSize - 1] = '\0';  // Ensure null termination
}

int8_t StateControl::findState(bool state) const {
  if (!array) return -1;
  for (uint8_t i = 0; i < def_size; i++) {
    if (array[i] == state) return i;
  }
  return -1;
}

uint8_t StateControl::serializeStatesSize() const {
  return def_size + 1;  // def_size chars + null terminator
}

void StateControl::setRangeStates(uint8_t start, uint8_t end, bool state) {
  if (!array || start >= def_size) return;
  end = min(end, def_size - 1);
  resetArray();  //
  for (uint8_t i = start; i <= end; i++) {
    array[i] = state;
    if (state && trueIndex == -1) trueIndex = i;
  }
}

bool StateControl::isAssignedIndex() const {
  return getFirstTrueIndex() != -1;
}

uint8_t StateControl::countTrueStates() const {
  if (!array || def_size == 0) return 0;
  uint8_t count = 0;
  for (uint8_t i = 0; i < def_size; i++) {
    if (array[i]) count++;
  }
  return count;
}

void StateControl::invertStates() {
  if (!array || def_size == 0) return;
  for (uint8_t i = 0; i < def_size; i++) {
    array[i] = !array[i];
  }
  trueIndex = array[trueIndex] ? trueIndex : findState(true);
}

bool StateControl::validateSingleState() const {
  return countTrueStates() == 1;
}

bool StateControl::isValidIndex(uint8_t index) const {
  return (array && index < def_size);
}

bool StateControl::copyStatesFrom(const StateControl& source) {
  if (!array || !source.array || def_size != source.def_size) return false;
  for (uint8_t i = 0; i < def_size; i++) {
    array[i] = source.array[i];
  }
  trueIndex = source.trueIndex;
  return true;
}

void StateControl::serializeStates(char* buffer, uint8_t bufSize) const {
  if (!array || def_size == 0 || !buffer || bufSize == 0) {
    if (bufSize > 0) buffer[0] = '\0';
    return;
  }
  uint8_t len = min(def_size, bufSize - 1);  // Leave room for null terminator
  for (uint8_t i = 0; i < len; i++) {
    buffer[i] = array[i] ? '1' : '0';
  }
  buffer[len] = '\0';
}

void StateControl::clearOthers(uint8_t index) {
  if (!array || def_size == 0) return;
  for (uint8_t i = 0; i < def_size; i++) {
    if (i != index) array[i] = false;
  }
}