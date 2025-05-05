/**
 * @file state_control_enums.h
 * @brief Enumerations for various view options and GSM states.
 * @details This file contains three enumerations:
 * - OptionsView: Symbolic names for various view options.
 * - OptionsShow: Symbolic names for different display options.
 * - OptionsGSM: Symbolic names for different states of a GSM module.
 *
 * The OptionsView enumeration provides symbolic names for different screens or states within the UI.
 * The OptionsShow enumeration defines display options.
 * The OptionsGSM enumeration represents states related to GSM communication.
 *
 * The constants OptionsViewLength, OptionsShowLength, and OptionsGSMLength calculate the lengths of their
 * respective enumerations to provide an easy way to iterate over all possible options.
 *
 * @author ATphonOS 
 * @version v1.0.0
 * @date 2024
 * @license MIT 
 */

#ifndef STATE_CONTROL_ENUMS_H
#define STATE_CONTROL_ENUMS_H

#include <Arduino.h>

/**
 * @brief Template function to count the number of elements in an enumeration.
 * @tparam EnumType The enumeration type.
 * @return The number of elements in the enumeration.
 */

template<typename EnumType>
constexpr int countEnumElements() {
  return static_cast<int>(EnumType::MAX);
}

/**
 * @brief Enumeration representing various view options.
 */

enum class OptionsView : uint8_t {
  MAIN = 0,       /**< Main screen option. */
  MENU,           /**< Menu screen option. */
  SUB_MENU_1,     /**< Sub-menu 1 option. */
  SUB_MENU_2,     /**< Sub-menu 2 option. */
  SUB_MENU_3,     /**< Sub-menu 3 option. */
  SUB_MENU_4,     /**< Sub-menu 4 option. */
  FUNCT,          /**< Function screen option. */
  INVALID_OPTION, /**< Invalid option. */
  MAX             /**< Maximum value for iteration purposes. */
};

/**
 * @brief Enumeration representing different display options.
 */

enum class OptionsShow : uint8_t {
  NOT_SHOW_ARROW = 0, /**< Do not show arrow option. */
  SHOW_ARROW,         /**< Show arrow option. */
  OFF_DISPLAY,        /**< Turn off display option. */
  MAX                 /**< Maximum value for iteration purposes. */
};

/**
 * @brief Enumeration representing different states of a GSM module.
 */

enum class OptionsGSM : uint8_t {
  GSM_ON = 0,     /**< GSM module is on. */
  INCOMINGCALL,   /**< Incoming call. */
  CALLINPROGRESS, /**< Call in progress. */
  MAX             /**< Maximum value for iteration purposes. */
};

/**
 * @brief Length of the OptionsView enumeration.
 */

const uint8_t OptionsViewLength = countEnumElements<OptionsView>();

/**
 * @brief Length of the OptionsShow enumeration.
 */

const uint8_t OptionsGSMLength = countEnumElements<OptionsGSM>();

/**
 * @brief Length of the OptionsGSM enumeration.
 */

const uint8_t OptionsShowLength = countEnumElements<OptionsShow>();

#endif  // STATE_CONTROL_ENUMS_H