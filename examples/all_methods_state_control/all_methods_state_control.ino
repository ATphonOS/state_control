
#include "state_control.h"

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
