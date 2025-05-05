#include "state_control.h" 

StateControl menuView(OptionsViewLength);
StateControl GSMStatus(OptionsGSMLength);

void setup() {
  Serial.begin(9600);

  menuView.setDefaultIndex();
  GSMStatus.setDefaultIndex();

  GSMStatus.setState(static_cast<uint8_t>(OptionsGSM::CALLINPROGRESS));
  menuView.setState(static_cast<uint8_t>(OptionsView::MENU));

  Serial.println("ATphonOS StateControl library example");
  Serial.println("** Index range [0-n]");
  Serial.println("** uint8_t = [0-255], uint16_t = [0-65535]");
  Serial.println("** FIRST element 0");
  Serial.println("** LAST  element 255 used for enum length");
  Serial.println("** Real range [0-254]");
  Serial.println("** [0 - n < = enum length < = 254]");
  Serial.println("** [0-254] assigned / -1 unassigned");
  Serial.println();
  Serial.println("---------------------------------------");
  Serial.print("Elements MENU_VIEW:        ");
  Serial.println(OptionsViewLength);

  // Buffer for menuView.getIndex()
  char menuIndexBuf[13]; // Max size from getIndexSize() = 13 (3 digits + " assigned" + null)
  menuView.getIndex(menuIndexBuf, sizeof(menuIndexBuf));
  Serial.print(" * INDEX MENU_VIEW:        ");
  Serial.println(menuIndexBuf);

  Serial.println("---------------------------------------");
  Serial.println("index    enum            state");
  Serial.print("  0      MAIN              ");
  Serial.println(menuView.Option(OptionsView::MAIN));
  Serial.print("  1      MENU              ");
  Serial.println(menuView.Option(OptionsView::MENU));
  Serial.print("  2      SUB1              ");
  Serial.println(menuView.Option(OptionsView::SUB_MENU_1));
  Serial.print("  3      SUB2              ");
  Serial.println(menuView.Option(OptionsView::SUB_MENU_2));
  Serial.print("  4      SUB3              ");
  Serial.println(menuView.Option(OptionsView::SUB_MENU_3));
  Serial.print("  5      SUB4              ");
  Serial.println(menuView.Option(OptionsView::SUB_MENU_4));
  Serial.print("  6      FUNCT             ");
  Serial.println(menuView.Option(OptionsView::FUNCT));
  Serial.print("  7      INVALID_OPTION    ");
  Serial.println(menuView.Option(OptionsView::INVALID_OPTION));
  Serial.println("---------------------------------------");
  Serial.print("Elements GSM_STATUS:       ");
  Serial.println(OptionsGSMLength);

  // Buffer for GSMStatus.getIndex()
  char gsmIndexBuf[13]; // Max size from getIndexSize() = 13
  GSMStatus.getIndex(gsmIndexBuf, sizeof(gsmIndexBuf));
  Serial.print(" * INDEX GSM_STATUS:       ");
  Serial.println(gsmIndexBuf);

  Serial.println("---------------------------------------");
  Serial.println("index    enum            state");
  Serial.print("  0      GSM_ON            ");
  Serial.println(GSMStatus.Option(OptionsGSM::GSM_ON));
  Serial.print("  1      INCOMINGCALL      ");
  Serial.println(GSMStatus.Option(OptionsGSM::INCOMINGCALL));
  Serial.print("  2      CALLINPROGRESS    ");
  Serial.println(GSMStatus.Option(OptionsGSM::CALLINPROGRESS));
  Serial.println("---------------------------------------");

  if (menuView.Option(OptionsView::MAIN)) {
    Serial.print("MAIN is active | ");
    Serial.print("enum/array index: ");
    Serial.println(menuView.findState(true));
  } else if (menuView.Option(OptionsView::MENU)) {
    Serial.print("MENU is active | ");
    Serial.print("enum/array index: ");
    Serial.println(menuView.findState(true));
  } else if (menuView.Option(OptionsView::SUB_MENU_1)) {
    Serial.print("SUB1 is active | ");
    Serial.print("enum/array index: ");
    Serial.println(menuView.findState(true));
  } else if (menuView.Option(OptionsView::SUB_MENU_2)) {
    Serial.print("SUB2 is active | ");
    Serial.print("enum/array index: ");
    Serial.println(menuView.findState(true));
  } else if (menuView.Option(OptionsView::FUNCT)) {
    Serial.print("FUNCT is active | ");
    Serial.print("enum/array index: ");
    Serial.println(menuView.findState(true));
  } else if (menuView.Option(OptionsView::INVALID_OPTION)) {
    Serial.print("INVALID_OPTION is active | ");
    Serial.print("enum/array index: ");
    Serial.println(menuView.findState(true));
  } else {
    Serial.print("WITHOUT STATE ");
    Serial.print(menuView.getFirstTrueIndex());
    Serial.print(menuIndexBuf); // Reuse buffer
    Serial.println();
  }

  if (GSMStatus.Option(OptionsGSM::GSM_ON)) {
    Serial.print("GSM_ON is active | ");
    Serial.print("enum/array index: ");
    Serial.println(GSMStatus.findState(true));
  } else if (GSMStatus.Option(OptionsGSM::INCOMINGCALL)) {
    Serial.print("INCOMINGCALL is active | ");
    Serial.print("enum/array index: ");
    Serial.println(GSMStatus.findState(true));
  } else if (GSMStatus.Option(OptionsGSM::CALLINPROGRESS)) {
    Serial.print("CALLINPROGRESS is active | ");
    Serial.print("enum/array index: ");
    Serial.println(GSMStatus.findState(true));
  } else {
    Serial.print("WITHOUT STATE ");
    Serial.print(GSMStatus.getFirstTrueIndex());
    Serial.print(gsmIndexBuf); // Reuse buffer
    Serial.println();
  }
  Serial.println();
  Serial.println("* * * * * *  End of program * * * * * *");
}

void loop() {
}