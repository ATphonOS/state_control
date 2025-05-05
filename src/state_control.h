/**
 * @file state_control.h
 * @brief Implements a state machine–like system using a boolean array for managing states.
 * @details StateControl manages a boolean array for state tracking, enabling exclusive or shared active states. 
 * It includes methods for setting, toggling, inverting, serializing, resetting states and querying active indices. 
 * @author ATphonOS
 * @version v1.1.0
 * @date 2024
 * @license MIT
 */

#ifndef STATE_CONTROL_H
#define STATE_CONTROL_H

#include <stdint.h>
#include <Arduino.h>
#include "state_control_enums.h"

class StateControl {
public:
  /**
   * @brief Constructs a StateControl object with the specified size.
   * @param size The number of states to manage (minimum 1).
   */
  StateControl(uint8_t size);

  /**
   * @brief Destructor to free allocated memory.
   */
  ~StateControl();

  /**
   * @brief Sets a state to true, optionally clearing all other states.
   * @param index The index of the state to set.
   * @param exclusive If true, clears all other states.
   */
  void setState(uint8_t index, bool exclusive = true);

  /**
   * @brief Sets a state to a specific value, optionally clearing all other states.
   * @param index The index of the state to set.
   * @param state The value to set (true or false).
   * @param exclusive If true, clears all other states when setting to true.
   */
  void setState(uint8_t index, bool state, bool exclusive = true);

  /**
   * @brief Toggles the state at the specified index.
   * @param index The index of the state to toggle.
   */
  void toggleState(uint8_t index);

  /**
   * @brief Resets all states to false.
   */
  void resetArray();

  /**
   * @brief Sets all states to a specific value.
   * @param state The value to set for all states.
   */
  void setAllStates(bool state);

  /**
   * @brief Sets the default state (index 0) to true and all others to false.
   */
  void setDefaultIndex();

  /**
   * @brief Retrieves the state at a specific index.
   * @param index The index to query.
   * @return The state value (true or false), or false if the index is invalid.
   */
  bool getState(uint8_t index) const;

  /**
   * @brief Finds the first index with a true state.
   * @return The first true index, or -1 if none are true.
   */
  int8_t getFirstTrueIndex() const;

  /**
   * @brief Retrieves all indices with true states.
   * @param count Output parameter for the number of true states found.
   * @return A dynamically allocated array of true indices (caller must free), or nullptr if none.
   */
  uint8_t* getAllTrueIndices(uint8_t& count) const;

  /**
     * @brief Gets the current true index directly.
     * @return Index of the first true state, or -1 if none.
     */
  int8_t getIndex() const;

  /**
   * @brief Writes the current true index as a string into a buffer.
   * @param buffer The buffer to write the string into.
   * @param bufSize The size of the buffer.
   */
  void getIndex(char* buffer, uint8_t bufSize) const;

  /**
   * @brief Calculates the required buffer size for serializing states.
   * @return The minimum size needed (including null terminator).
   */
  uint8_t serializeStatesSize() const;

  /**
   * @brief Serializes all states into a binary string (e.g., "0100").
   * @param buffer The buffer to write the string into.
   * @param bufSize The size of the buffer.
   */
  void serializeStates(char* buffer, uint8_t bufSize) const;

  /**
   * @brief Finds the first index with a specific state.
   * @param state The state to search for (true or false).
   * @return The first matching index, or -1 if none found.
   */
  int8_t findState(bool state) const;

  /**
   * @brief Sets a range of states to a specific value.
   * @param start The starting index of the range.
   * @param end The ending index of the range.
   * @param state The value to set for the range.
   */
  void setRangeStates(uint8_t start, uint8_t end, bool state);

  /**
   * @brief Checks if any state is true.
   * @return True if at least one state is true, false otherwise.
   */
  bool isAssignedIndex() const;

  /**
   * @brief Counts the number of true states.
   * @return The number of states currently set to true.
   */
  uint8_t countTrueStates() const;

  /**
   * @brief Inverts all states (true becomes false, false becomes true).
   */
  void invertStates();

  /**
   * @brief Checks if exactly one state is true.
   * @return True if only one state is true, false otherwise.
   */
  bool validateSingleState() const;

  /**
   * @brief Validates if an index is within bounds.
   * @param index The index to check.
   * @return True if the index is valid, false otherwise.
   */
  bool isValidIndex(uint8_t index) const;

  /**
   * @brief Copies states from another StateControl instance.
   * @param source The source StateControl object to copy from.
   * @return True if the copy was successful, false otherwise.
   */
  bool copyStatesFrom(const StateControl& source);

  /**
   * @brief Saves the current state of the array and trueIndex internally.
   *
   * Copies the current state of the array and trueIndex into internal storage
   * for later restoration with restoreSavedState().
   */
  void saveState();

  /**
   * @brief Restores the previously saved state of the array and trueIndex.
   *
   * Restores the state saved by saveState() into the current array and trueIndex.
   */
  void restoreSavedState();


  /**
   * @brief Sets a state by enum value, optionally clearing others.
   * @param option The enum value representing the state index.
   * @param state The value to set (true or false).
   * @param exclusive If true, clears all other states when setting to true.
   */
  template<typename T>
  void setStateByEnum(T option, bool state, bool exclusive = true) {
    uint8_t index = static_cast<uint8_t>(option);
    if (isValidIndex(index)) setState(index, state, exclusive);
  }

  /**
   * @brief Checks if an enum-specified state is active and matches the true index.
   * @param option The enum value representing the state index.
   * @return True if the state is true and matches the active index, false otherwise.
   */
  template<typename T>
  bool Option(T option) const {
    uint8_t index = static_cast<uint8_t>(option);
    return (index < def_size && index == trueIndex && array[index]);
  }

private:
  bool* array;            /**< Pointer to the state array. */
  uint8_t def_size;       /**< Size of the state array. */
  int8_t trueIndex;       /**< Index of the currently active state (-1 if none). */
  bool* savedState;       ///< Internal storage for the saved state array.
  int8_t savedTrueIndex;  ///< Internal storage for the saved trueIndex.

  /**
   * @brief Clears all states except the specified index.
   * @param index The index to preserve.
   */
  void clearOthers(uint8_t index);
};

#endif  // STATE_CONTROL_H