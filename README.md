This documentation is also available in **[Spanish](./README_es.md)**.

# 🔁 StateControl
## Summary
`StateControl` is a C++ library designed to manage arrays of boolean states on Arduino-compatible microcontrollers, providing logic akin to a finite state machine. It enables setting, toggling, querying, serialising, and restoring states, with support for exclusive or shared states. Ideal for applications such as menu navigation, user interface control, or module state management (e.g., GSM), it optimises memory usage and offers robust methods for state manipulation.

Designed as a library for use in Arduino environments.

---

## ⚙️ Features

- Management of a boolean array to track and control states.
- Support for exclusive states (single active state) or shared states (multiple active states).
- Methods to set, toggle, invert, reset, and serialise states.
- Functionality to save and restore previous states.
- Support for custom enumerations via templates (`setStateByEnum`, `Option`).
- Querying of active indices, counting true states, and validating single states.
- Robust error handling, including index validation and dynamic memory management.
- Optimised for resource-constrained environments, with efficient storage and memory cleanup.

> The library simplifies the implementation of state machine logic in Arduino, offering a flexible interface for managing states in embedded applications.

### 📌 Compatible Microcontrollers

Compatible with 8-bit AVR, 32-bit ARM Cortex-M, and Xtensa architectures, provided they are supported by the Arduino IDE and allow dynamic memory allocation (`new`/`delete`).

---

## 📦 Installation

**Option 1: Copy Files and Include**

1. Copy the following files into your Arduino project directory:
   - `state_control.h`
   - `state_control.cpp`
   - `state_control_enums.h`

2. Include the header in your source file:
   ```cpp
   #include "state_control.h"
   ```

**Option 2: Install Library and Include**

1. Download the repository as a ZIP file.
2. Open the Arduino IDE.
3. Navigate to **Sketch > Include Library > Add .ZIP Library** in the menu.
4. Select the library’s ZIP file.
5. Import the library:

To use the library in your sketch, go to **Sketch > Include Library** and select `StateControl` from the list to add its `#include` directive to your code.
```cpp
#include <state_control.h>
```

---

## 📚 Library: `StateControl`

### Key Definitions and Structures

```cpp
enum class OptionsView : uint8_t { MAIN = 0, MENU, SUB_MENU_1, SUB_MENU_2, SUB_MENU_3, SUB_MENU_4, FUNCT, INVALID_OPTION, MAX };
enum class OptionsShow : uint8_t { NOT_SHOW_ARROW = 0, SHOW_ARROW, OFF_DISPLAY, MAX };
enum class OptionsGSM : uint8_t { GSM_ON = 0, INCOMINGCALL, CALLINPROGRESS, MAX };
```

| Definition | Description |
|------------|-------------|
| `OptionsView` | Enumeration for interface view options (e.g., `MAIN`, `MENU`, `SUB_MENU_1`). |
| `OptionsShow` | Enumeration for display options (e.g., `SHOW_ARROW`, `OFF_DISPLAY`). |
| `OptionsGSM` | Enumeration for GSM module states (e.g., `GSM_ON`, `INCOMINGCALL`). |
| `countEnumElements<EnumType>()` | Template function to count elements in an enumeration. |

---

## 🔓 Public Functions

### Initialisation and Memory Management

```cpp
StateControl(uint8_t size);
~StateControl();
```

| Function | Description | Parameters | Return |
|----------|-------------|------------|--------|
| `StateControl(uint8_t size)` | Constructs a `StateControl` object with the specified size. | `size (uint8_t)`: Number of states (minimum 1, maximum 254). | None |
| `~StateControl()` | Destroys the object and frees allocated memory. | None | None |

### State Configuration

```cpp
void setState(uint8_t index, bool exclusive = true);
void setState(uint8_t index, bool state, bool exclusive = true);
void toggleState(uint8_t index);
void setAllStates(bool state);
void setDefaultIndex();
void setRangeStates(uint8_t start, uint8_t end, bool state);
void invertStates();
```

| Function | Description | Parameters | Return |
|----------|-------------|------------|--------|
| `void setState(uint8_t index, bool exclusive)` | Sets a state to `true`, optionally exclusive. | `index (uint8_t)`: State index<br>`exclusive (bool)`: Clear other states | `void` |
| `void setState(uint8_t index, bool state, bool exclusive)` | Sets a state to a specific value, optionally exclusive. | `index (uint8_t)`: Index<br>`state (bool)`: Value<br>`exclusive (bool)`: Clear other states if `true` | `void` |
| `void toggleState(uint8_t index)` | Toggles the state at the specified index. | `index (uint8_t)`: Index | `void` |
| `void setAllStates(bool state)` | Sets all states to a value. | `state (bool)`: Value for all states | `void` |
| `void setDefaultIndex()` | Sets index 0 to `true` and others to `false`. | None | `void` |
| `void setRangeStates(uint8_t start, uint8_t end, bool state)` | Sets a range of states to a value. | `start (uint8_t)`: Start index<br>`end (uint8_t)`: End index<br>`state (bool)`: Value | `void` |
| `void invertStates()` | Inverts all states (`true` to `false`, `false` to `true`). | None | `void` |

### State Querying

```cpp
bool getState(uint8_t index) const;
int8_t getFirstTrueIndex() const;
uint8_t* getAllTrueIndices(uint8_t& count) const;
int8_t getIndex() const;
void getIndex(char* buffer, uint8_t bufSize) const;
int8_t findState(bool state) const;
bool isAssignedIndex() const;
uint8_t countTrueStates() const;
bool validateSingleState() const;
bool isValidIndex(uint8_t index) const;
```

| Function | Description | Parameters | Return |
|----------|-------------|------------|--------|
| `bool getState(uint8_t index)` | Gets the state at an index. | `index (uint8_t)`: Index | `bool`: State or `false` if invalid |
| `int8_t getFirstTrueIndex()` | Finds the first `true` index. | None | `int8_t`: Index or -1 |
| `uint8_t* getAllTrueIndices(uint8_t& count)` | Gets all `true` indices. | `count (uint8_t&)`: Number of `true` states | `uint8_t*`: Dynamic array (free with `delete[]`) or `nullptr` |
| `int8_t getIndex()` | Gets the current active index. | None | `int8_t`: Index or -1 |
| `void getIndex(char* buffer, uint8_t bufSize)` | Writes the active index as a string. | `buffer (char*)`: Buffer<br>`bufSize (uint8_t)`: Size | `void` |
| `int8_t findState(bool state)` | Finds the first index with a state. | `state (bool)`: State to search | `int8_t`: Index or -1 |
| `bool isAssignedIndex()` | Checks if any state is `true`. | None | `bool`: `true` if any state is active |
| `uint8_t countTrueStates()` | Counts `true` states. | None | `uint8_t`: Number of `true` states |
| `bool validateSingleState()` | Checks if only one state is `true`. | None | `bool`: `true` if single state active |
| `bool isValidIndex(uint8_t index)` | Validates if an index is valid. | `index (uint8_t)`: Index | `bool`: `true` if valid |

### Management and Serialisation

```cpp
void resetArray();
void saveState();
void restoreSavedState();
bool copyStatesFrom(const StateControl& source);
uint8_t serializeStatesSize() const;
void serializeStates(char* buffer, uint8_t bufSize) const;
```

| Function | Description | Parameters | Return |
|----------|-------------|------------|--------|
| `void resetArray()` | Resets all states to `false`. | None | `void` |
| `void saveState()` | Saves the current state array and active index. | None | `void` |
| `void restoreSavedState()` | Restores the previously saved state. | None | `void` |
| `bool copyStatesFrom(const StateControl& source)` | Copies states from another instance. | `source (const StateControl&)`: Source instance | `bool`: `true` if successful |
| `uint8_t serializeStatesSize()` | Calculates the size needed to serialise states. | None | `uint8_t`: Size (includes null terminator) |
| `void serializeStates(char* buffer, uint8_t bufSize)` | Serialises states as a binary string (e.g., "0100"). | `buffer (char*)`: Buffer<br>`bufSize (uint8_t)`: Size | `void` |

### Enumeration-Based Methods

```cpp
template<typename T> void setStateByEnum(T option, bool state, bool exclusive = true);
template<typename T> bool Option(T option) const;
```

| Function | Description | Parameters | Return |
|----------|-------------|------------|--------|
| `void setStateByEnum(T option, bool state, bool exclusive)` | Sets a state using an enumeration value. | `option (T)`: Enum value<br>`state (bool)`: Value<br>`exclusive (bool)`: Clear other states | `void` |
| `bool Option(T option)` | Checks if an enum-specified state is active and matches the index. | `option (T)`: Enum value | `bool`: `true` if active and matches |

---

## 🧪 Example Usage

**Example 1**: Demonstrates how to use the `StateControl` library to manage states for a user interface (views) and a GSM module. The code uses the `OptionsView` and `OptionsGSM` enumerations to set and query states.

```cpp
#include "state_control.h"
#include "state_control_enums.h"

// Create StateControl instances for managing UI views and GSM states
StateControl viewControl(OptionsViewLength); // For OptionsView (UI views)
StateControl gsmControl(OptionsGSMLength);   // For OptionsGSM (GSM states)

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  Serial.println(F("StateControl Example: Demonstrating key methods"));

  // 1. Initial state
  Serial.println(F("1. Initial state of viewControl"));
  printStates(viewControl);

  // 2. setState(uint8_t index, bool exclusive)
  Serial.println(F("\n2. Setting MAIN view (exclusive)"));
  viewControl.setState(static_cast<uint8_t>(OptionsView::MAIN));
  printStates(viewControl);

  // 3. setState(uint8_t index, bool state, bool exclusive)
  Serial.println(F("\n3. Setting MENU view to true (non-exclusive)"));
  viewControl.setState(static_cast<uint8_t>(OptionsView::MENU), true, false);
  printStates(viewControl);

  // 4. toggleState(uint8_t index)
  Serial.println(F("\n4. Toggling MENU view state"));
  viewControl.toggleState(static_cast<uint8_t>(OptionsView::MENU));
  printStates(viewControl);

  // 5. resetArray()
  Serial.println(F("\n5. Resetting all view states"));
  viewControl.resetArray();
  printStates(viewControl);

  // 6. setAllStates(bool state)
  Serial.println(F("\n6. Setting all view states to true"));
  viewControl.setAllStates(true);
  printStates(viewControl);

  // 7. setDefaultIndex()
  Serial.println(F("\n7. Setting default index (MAIN)"));
  viewControl.setDefaultIndex();
  printStates(viewControl);

  // 8. getState(uint8_t index)
  Serial.println(F("\n8. Checking state of SUB_MENU_1"));
  Serial.print(F("SUB_MENU_1 state: "));
  Serial.println(viewControl.getState(static_cast<uint8_t>(OptionsView::SUB_MENU_1)));

  // 9. getFirstTrueIndex()
  Serial.println(F("\n9. Getting first true index"));
  Serial.print(F("First true index: "));
  Serial.println(viewControl.getFirstTrueIndex());

  // 10. getAllTrueIndices(uint8_t& count)
  Serial.println(F("\n10. Getting all true indices"));
  uint8_t count;
  uint8_t* indices = viewControl.getAllTrueIndices(count);
  Serial.print(F("True indices (count=")); Serial.print(count); Serial.print(F("): "));
  for (uint8_t i = 0; i < count; i++) {
    Serial.print(indices[i]);
    if (i < count - 1) Serial.print(F(", "));
  }
  Serial.println();
  delete[] indices; // Free allocated memory

  // 11. getIndex()
  Serial.println(F("\n11. Getting current true index"));
  Serial.print(F("Current true index: "));
  Serial.println(viewControl.getIndex());

  // 12. getIndex(char* buffer, uint8_t bufSize)
  Serial.println(F("\n12. Getting true index as string"));
  char buffer[20];
  viewControl.getIndex(buffer, sizeof(buffer));
  Serial.print(F("True index string: "));
  Serial.println(buffer);

  // 13. serializeStatesSize()
  Serial.println(F("\n13. Getting serialized states size"));
  Serial.print(F("Serialized states size: "));
  Serial.println(viewControl.serializeStatesSize());

  // 14. serializeStates(char* buffer, uint8_t bufSize)
  Serial.println(F("\n14. Serializing states"));
  char stateBuffer[OptionsViewLength + 1];
  viewControl.serializeStates(stateBuffer, sizeof(stateBuffer));
  Serial.print(F("Serialized states: "));
  Serial.println(stateBuffer);

  // 15. findState(bool state)
  Serial.println(F("\n15. Finding first true state"));
  Serial.print(F("First true state index: "));
  Serial.println(viewControl.findState(true));

  // 16. setRangeStates(uint8_t start, uint8_t end, bool state)
  Serial.println(F("\n16. Setting range SUB_MENU_1 to SUB_MENU_3 to true"));
  viewControl.setRangeStates(static_cast<uint8_t>(OptionsView::SUB_MENU_1), 
                             static_cast<uint8_t>(OptionsView::SUB_MENU_3), true);
  printStates(viewControl);

  // 17. isAssignedIndex()
  Serial.println(F("\n17. Checking if any state is assigned"));
  Serial.print(F("Is any state assigned? "));
  Serial.println(viewControl.isAssignedIndex() ? F("Yes") : F("No"));

  // 18. countTrueStates()
  Serial.println(F("\n18. Counting true states"));
  Serial.print(F("Number of true states: "));
  Serial.println(viewControl.countTrueStates());

  // 19. invertStates()
  Serial.println(F("\n19. Inverting all states"));
  viewControl.invertStates();
  printStates(viewControl);

  // 20. validateSingleState()
  Serial.println(F("\n20. Validating single true state"));
  viewControl.setState(static_cast<uint8_t>(OptionsView::MENU));
  printStates(viewControl);

  // 21. isValidIndex(uint8_t index)
  Serial.println(F("\n21. Checking if index 10 is valid"));
  Serial.print(F("Is index 10 valid? "));
  Serial.println(viewControl.isValidIndex(10) ? F("Yes") : F("No"));

  // 22. copyStatesFrom(const StateControl& source)
  Serial.println(F("\n22. Copying states from gsmControl to viewControl"));
  gsmControl.setState(static_cast<uint8_t>(OptionsGSM::GSM_ON));
  viewControl.copyStatesFrom(gsmControl);
  printStates(viewControl);

  // 23. saveState() and restoreSavedState()
  Serial.println(F("\n23. Saving and restoring state"));
  viewControl.setState(static_cast<uint8_t>(OptionsView::SUB_MENU_2));
  viewControl.saveState();
  viewControl.setState(static_cast<uint8_t>(OptionsView::SUB_MENU_3));
  Serial.println(F("State before restore:"));
  printStates(viewControl);
  viewControl.restoreSavedState();
  Serial.println(F("State after restore:"));
  printStates(viewControl);

  // 24. setStateByEnum(T option, bool state, bool exclusive)
  Serial.println(F("\n24. Setting GSM state using enum"));
  gsmControl.setStateByEnum(OptionsGSM::INCOMINGCALL, true, true);
  printStates(gsmControl);

  // 25. Option(T option)
  Serial.println(F("\n25. Checking if INCOMINGCALL is active"));
  Serial.print(F("Is INCOMINGCALL active? "));
  Serial.println(gsmControl.Option(OptionsGSM::INCOMINGCALL) ? F("Yes") : F("No"));
}

void loop() {
  // Empty loop, example runs in setup()
}

// Helper function to print all states
void printStates(const StateControl& control) {
  char buffer[OptionsViewLength + 1];
  control.serializeStates(buffer, sizeof(buffer));
  Serial.print(F("States: "));
  Serial.println(buffer);
  Serial.print(F("True index: "));
  Serial.println(control.getIndex());
}
```

**Example 2**: Demonstrates the use of all methods in `StateControl`.

```cpp
#include "state_control.h"
#include "state_control_enums.h"

// Create StateControl instances for managing UI views and GSM states
StateControl viewControl(OptionsViewLength); // For OptionsView (UI views)
StateControl gsmControl(OptionsGSMLength);   // For OptionsGSM (GSM states)

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  Serial.println(F("StateControl Example: Demonstrating all methods"));

  // 1. Test constructor and initial state
  Serial.println(F("1. Initial state of viewControl"));
  printStates(viewControl);

  // 2. setState(uint8_t index, bool exclusive)
  Serial.println(F("\n2. Setting MAIN view (exclusive)"));
  viewControl.setState(static_cast<uint8_t>(OptionsView::MAIN));
  printStates(viewControl);

  // 3. setState(uint8_t index, bool state, bool exclusive)
  Serial.println(F("\n3. Setting MENU view to true (non-exclusive)"));
  viewControl.setState(static_cast<uint8_t>(OptionsView::MENU), true, false);
  printStates(viewControl);

  // 4. toggleState(uint8_t index)
  Serial.println(F("\n4. Toggling MENU view state"));
  viewControl.toggleState(static_cast<uint8_t>(OptionsView::MENU));
  printStates(viewControl);

  // 5. resetArray()
  Serial.println(F("\n5. Resetting all view states"));
  viewControl.resetArray();
  printStates(viewControl);

  // 6. setAllStates(bool state)
  Serial.println(F("\n6. Setting all view states to true"));
  viewControl.setAllStates(true);
  printStates(viewControl);

  // 7. setDefaultIndex()
  Serial.println(F("\n7. Setting default index (MAIN)"));
  viewControl.setDefaultIndex();
  printStates(viewControl);

  // 8. getState(uint8_t index)
  Serial.println(F("\n8. Checking state of SUB_MENU_1"));
  Serial.print(F("SUB_MENU_1 state: "));
  Serial.println(viewControl.getState(static_cast<uint8_t>(OptionsView::SUB_MENU_1)));

  // 9. getFirstTrueIndex()
  Serial.println(F("\n9. Getting first true index"));
  Serial.print(F("First true index: "));
  Serial.println(viewControl.getFirstTrueIndex());

  // 10. getAllTrueIndices(uint8_t& count)
  Serial.println(F("\n10. Getting all true indices"));
  uint8_t count;
  uint8_t* indices = viewControl.getAllTrueIndices(count);
  Serial.print(F("True indices (count=")); Serial.print(count); Serial.print(F("): "));
  for (uint8_t i = 0; i < count; i++) {
    Serial.print(indices[i]);
    if (i < count - 1) Serial.print(F(", "));
  }
  Serial.println();
  delete[] indices; // Free allocated memory

  // 11. getIndex()
  Serial.println(F("\n11. Getting current true index"));
  Serial.print(F("Current true index: "));
  Serial.println(viewControl.getIndex());

  // 12. getIndex(char* buffer, uint8_t bufSize)
  Serial.println(F("\n12. Getting true index as string"));
  char buffer[20];
  viewControl.getIndex(buffer, sizeof(buffer));
  Serial.print(F("True index string: "));
  Serial.println(buffer);

  // 13. serializeStatesSize()
  Serial.println(F("\n13. Getting serialized states size"));
  Serial.print(F("Serialized states size: "));
  Serial.println(viewControl.serializeStatesSize());

  // 14. serializeStates(char* buffer, uint8_t bufSize)
  Serial.println(F("\n14. Serializing states"));
  char stateBuffer[OptionsViewLength + 1];
  viewControl.serializeStates(stateBuffer, sizeof(stateBuffer));
  Serial.print(F("Serialized states: "));
  Serial.println(stateBuffer);

  // 15. findState(bool state)
  Serial.println(F("\n15. Finding first true state"));
  Serial.print(F("First true state index: "));
  Serial.println(viewControl.findState(true));

  // 16. setRangeStates(uint8_t start, uint8_t end, bool state)
  Serial.println(F("\n16. Setting range SUB_MENU_1 to SUB_MENU_3 to true"));
  viewControl.setRangeStates(static_cast<uint8_t>(OptionsView::SUB_MENU_1), 
                             static_cast<uint8_t>(OptionsView::SUB_MENU_3), true);
  printStates(viewControl);

  // 17. isAssignedIndex()
  Serial.println(F("\n17. Checking if any state is assigned"));
  Serial.print(F("Is any state assigned? "));
  Serial.println(viewControl.isAssignedIndex() ? F("Yes") : F("No"));

  // 18. countTrueStates()
  Serial.println(F("\n18. Counting true states"));
  Serial.print(F("Number of true states: "));
  Serial.println(viewControl.countTrueStates());

  // 19. invertStates()
  Serial.println(F("\n19. Inverting all states"));
  viewControl.invertStates();
  printStates(viewControl);

  // 20. validateSingleState()
  Serial.println(F("\n20. Validating single true state"));
  viewControl.setState(static_cast<uint8_t>(OptionsView::MENU));
  printStates(viewControl);

  // 21. isValidIndex(uint8_t index)
  Serial.println(F("\n21. Checking if index 10 is valid"));
  Serial.print(F("Is index 10 valid? "));
  Serial.println(viewControl.isValidIndex(10) ? F("Yes") : F("No"));

  // 22. copyStatesFrom(const StateControl& source)
  Serial.println(F("\n22. Copying states from gsmControl to viewControl"));
  gsmControl.setState(static_cast<uint8_t>(OptionsGSM::GSM_ON));
  viewControl.copyStatesFrom(gsmControl);
  printStates(viewControl);

  // 23. saveState() and restoreSavedState()
  Serial.println(F("\n23. Saving and restoring state"));
  viewControl.setState(static_cast<uint8_t>(OptionsView::SUB_MENU_2));
  viewControl.saveState();
  viewControl.setState(static_cast<uint8_t>(OptionsView::SUB_MENU_3));
  Serial.println(F("State before restore:"));
  printStates(viewControl);
  viewControl.restoreSavedState();
  Serial.println(F("State after restore:"));
  printStates(viewControl);

  // 24. setStateByEnum(T option, bool state, bool exclusive)
  Serial.println(F("\n24. Setting GSM state using enum"));
  gsmControl.setStateByEnum(OptionsGSM::INCOMINGCALL, true, true);
  printStates(gsmControl);

  // 25. Option(T option)
  Serial.println(F("\n25. Checking if INCOMINGCALL is active"));
  Serial.print(F("Is INCOMINGCALL active? "));
  Serial.println(gsmControl.Option(OptionsGSM::INCOMINGCALL) ? F("Yes") : F("No"));
}

void loop() {
  // Empty loop, example runs in setup()
}

// Helper function to print all states
void printStates(const StateControl& control) {
  char buffer[OptionsViewLength + 1];
  control.serializeStates(buffer, sizeof(buffer));
  Serial.print(F("States: "));
  Serial.println(buffer);
  Serial.print(F("True index: "));
  Serial.println(control.getIndex());
}
```

---

## 🧠 Design Notes

- **Efficient Memory Management**: Uses dynamic arrays (`new`/`delete`) for the state array and saved state, with a 254-state limit to prevent overflows on microcontrollers with limited RAM. The destructor ensures resource cleanup.
- **State Machine Logic**: Supports exclusive (single `true` state) and shared states, ideal for implementing simple finite state machines, such as menus or GSM module control.
- **Active Index (`trueIndex`)**: Maintains an active index to track the last `true` state set, optimising quick state queries without scanning the entire array.
- **Enumeration Support**: Template-based methods (`setStateByEnum`, `Option`) allow custom enumerations, enhancing code readability and safety when working with symbolic values.
- **Error Handling**: Validates indices, handles memory allocation failures, and ensures data integrity through checks in each method, ensuring robustness in embedded environments.
- **State Serialisation**: Provides methods to serialise states as binary strings (e.g., "0100"), useful for debugging, non-volatile storage, or communication with other devices.
- **Configuration Flexibility**: Allows setting state ranges, inverting states, copying states between instances, and saving/restoring states, offering versatility for various applications.

---

## 🧾 Licence
This project is licensed under the MIT Licence — see the [LICENSE](https://github.com/ATphonOS/StateControl/blob/main/LICENSE.md) file for details.
