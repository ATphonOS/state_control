Esta documentación también está disponible en **[Inglés](./README.md)**.

# ⚙️➡️📜 StateControl
## Resumen
`StateControl` es una biblioteca C++ diseñada para gestionar arreglos de estados booleanos en microcontroladores compatibles con Arduino, proporcionando una lógica similar a una máquina de estados. Permite configurar, alternar, consultar, serializar y restaurar estados, con soporte para estados exclusivos o compartidos. Para aplicaciones como navegación de menús, control de interfaces de usuario, o gestión de estados de módulos.

Diseñada como una biblioteca para su uso en entornos Arduino.

---

## ⚙️ Características

- Gestión de un arreglo booleano para rastrear y controlar estados.
- Soporte para estados exclusivos (un solo estado activo) o compartidos (múltiples estados activos).
- Métodos para configurar, alternar, invertir, restablecer y serializar estados.
- Funcionalidad para guardar y restaurar estados previos.
- Soporte para enumeraciones personalizadas mediante plantillas (`setStateByEnum`, `Option`).
- Consulta de índices activos, conteo de estados verdaderos y validación de estados únicos.
- Manejo robusto de errores, incluyendo validación de índices y gestión de memoria dinámica.
- Optimización para entornos con recursos limitados, con almacenamiento eficiente y limpieza de memoria.

> La biblioteca simplifica la implementación de lógica de máquinas de estados en Arduino, ofreciendo una interfaz flexible para gestionar estados en aplicaciones embebidas.

### 📌 Microcontroladores Compatibles

Compatible con arquitecturas AVR de 8 bits, ARM Cortex-M de 32 bits y Xtensa, siempre que sean compatibles con el IDE de Arduino y soporten la asignación dinámica de memoria (`new`/`delete`).

---

## 📦 Instalación

**Opción 1: Copiar los archivos e incluirlos**

1. Copia los siguientes archivos en tu proyecto Arduino:
   - `state_control.h`
   - `state_control.cpp`
   - `state_control_enums.h`

2. Incluye el encabezado en tu archivo fuente:
   ```cpp
   #include "state_control.h"
   ```

**Opción 2: Instalar la biblioteca e incluirla**

1. Descarga el repositorio como un archivo ZIP.
2. Abre el IDE de Arduino.
3. Ve a **Sketch > Incluir Biblioteca > Añadir biblioteca ZIP** en el menú.
4. Selecciona el archivo ZIP de la biblioteca.
5. Importa la biblioteca:

Para usar la biblioteca en tu sketch, ve a **Sketch > Incluir Biblioteca** y selecciona `StateControl` de la lista para añadir su directiva `#include` a tu código.
```cpp
#include <state_control.h>
```

---

## 📚 Biblioteca: `StateControl`

### Definiciones y Estructuras Clave

```cpp
enum class OptionsView : uint8_t { MAIN = 0, MENU, SUB_MENU_1, SUB_MENU_2, SUB_MENU_3, SUB_MENU_4, FUNCT, INVALID_OPTION, MAX };
enum class OptionsShow : uint8_t { NOT_SHOW_ARROW = 0, SHOW_ARROW, OFF_DISPLAY, MAX };
enum class OptionsGSM : uint8_t { GSM_ON = 0, INCOMINGCALL, CALLINPROGRESS, MAX };
```

| Definición | Descripción |
|------------|-------------|
| `OptionsView` | Enumeración para opciones de vistas de interfaz (por ejemplo, `MAIN`, `MENU`, `SUB_MENU_1`). |
| `OptionsShow` | Enumeración para opciones de visualización (por ejemplo, `SHOW_ARROW`, `OFF_DISPLAY`). |
| `OptionsGSM` | Enumeración para estados de módulos GSM (por ejemplo, `GSM_ON`, `INCOMINGCALL`). |
| `countEnumElements<EnumType>()` | Función plantilla para contar elementos en una enumeración. |

---

## 🔓 Funciones Públicas

### Inicialización y Gestión de Memoria

```cpp
StateControl(uint8_t size);
~StateControl();
```

| Función | Descripción | Parámetros | Retorno |
|---------|-------------|------------|---------|
| `StateControl(uint8_t size)` | Construye un objeto `StateControl` con el tamaño especificado. | `size (uint8_t)`: Número de estados (mínimo 1, máximo 254). | Ninguno |
| `~StateControl()` | Destruye el objeto y libera la memoria asignada. | Ninguno | Ninguno |

### Configuración de Estados

```cpp
void setState(uint8_t index, bool exclusive = true);
void setState(uint8_t index, bool state, bool exclusive = true);
void toggleState(uint8_t index);
void setAllStates(bool state);
void setDefaultIndex();
void setRangeStates(uint8_t start, uint8_t end, bool state);
void invertStates();
```

| Función | Descripción | Parámetros | Retorno |
|---------|-------------|------------|---------|
| `void setState(uint8_t index, bool exclusive)` | Establece un estado a `true`, opcionalmente exclusivo. | `index (uint8_t)`: Índice del estado<br>`exclusive (bool)`: Limpiar otros estados | `void` |
| `void setState(uint8_t index, bool state, bool exclusive)` | Establece un estado a un valor específico, opcionalmente exclusivo. | `index (uint8_t)`: Índice<br>`state (bool)`: Valor<br>`exclusive (bool)`: Limpiar otros estados si `true` | `void` |
| `void toggleState(uint8_t index)` | Alterna el estado en el índice especificado. | `index (uint8_t)`: Índice | `void` |
| `void setAllStates(bool state)` | Establece todos los estados a un valor. | `state (bool)`: Valor para todos | `void` |
| `void setDefaultIndex()` | Establece el índice 0 a `true` y los demás a `false`. | Ninguno | `void` |
| `void setRangeStates(uint8_t start, uint8_t end, bool state)` | Establece un rango de estados a un valor. | `start (uint8_t)`: Índice inicial<br>`end (uint8_t)`: Índice final<br>`state (bool)`: Valor | `void` |
| `void invertStates()` | Invierte todos los estados (`true` a `false`, `false` a `true`). | Ninguno | `void` |

### Consulta de Estados

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

| Función | Descripción | Parámetros | Retorno |
|---------|-------------|------------|---------|
| `bool getState(uint8_t index)` | Obtiene el estado en un índice. | `index (uint8_t)`: Índice | `bool`: Estado o `false` si inválido |
| `int8_t getFirstTrueIndex()` | Encuentra el primer índice `true`. | Ninguno | `int8_t`: Índice o -1 |
| `uint8_t* getAllTrueIndices(uint8_t& count)` | Obtiene todos los índices `true`. | `count (uint8_t&)`: Número de estados `true` | `uint8_t*`: Arreglo dinámico (liberar con `delete[]`) o `nullptr` |
| `int8_t getIndex()` | Obtiene el índice activo actual. | Ninguno | `int8_t`: Índice o -1 |
| `void getIndex(char* buffer, uint8_t bufSize)` | Escribe el índice activo como cadena. | `buffer (char*)`: Búfer<br>`bufSize (uint8_t)`: Tamaño | `void` |
| `int8_t findState(bool state)` | Encuentra el primer índice con un estado. | `state (bool)`: Estado a buscar | `int8_t`: Índice o -1 |
| `bool isAssignedIndex()` | Verifica si hay algún estado `true`. | Ninguno | `bool`: `true` si hay estados activos |
| `uint8_t countTrueStates()` | Cuenta los estados `true`. | Ninguno | `uint8_t`: Número de estados `true` |
| `bool validateSingleState()` | Verifica si solo un estado es `true`. | Ninguno | `bool`: `true` si hay un solo estado activo |
| `bool isValidIndex(uint8_t index)` | Valida si un índice es válido. | `index (uint8_t)`: Índice | `bool`: `true` si válido |

### Gestión y Serialización

```cpp
void resetArray();
void saveState();
void restoreSavedState();
bool copyStatesFrom(const StateControl& source);
uint8_t serializeStatesSize() const;
void serializeStates(char* buffer, uint8_t bufSize) const;
```

| Función | Descripción | Parámetros | Retorno |
|---------|-------------|------------|---------|
| `void resetArray()` | Restablece todos los estados a `false`. | Ninguno | `void` |
| `void saveState()` | Guarda el estado actual del arreglo y el índice activo. | Ninguno | `void` |
| `void restoreSavedState()` | Restaura el estado guardado previamente. | Ninguno | `void` |
| `bool copyStatesFrom(const StateControl& source)` | Copia estados desde otra instancia. | `source (const StateControl&)`: Instancia fuente | `bool`: `true` si éxito |
| `uint8_t serializeStatesSize()` | Calcula el tamaño necesario para serializar estados. | Ninguno | `uint8_t`: Tamaño (incluye terminador nulo) |
| `void serializeStates(char* buffer, uint8_t bufSize)` | Serializa estados como cadena binaria (ej., "0100"). | `buffer (char*)`: Búfer<br>`bufSize (uint8_t)`: Tamaño | `void` |

### Métodos Basados en Enumeraciones

```cpp
template<typename T> void setStateByEnum(T option, bool state, bool exclusive = true);
template<typename T> bool Option(T option) const;
```

| Función | Descripción | Parámetros | Retorno |
|---------|-------------|------------|---------|
| `void setStateByEnum(T option, bool state, bool exclusive)` | Establece un estado usando un valor de enumeración. | `option (T)`: Valor de enumeración<br>`state (bool)`: Valor<br>`exclusive (bool)`: Limpiar otros estados | `void` |
| `bool Option(T option)` | Verifica si un estado de enumeración es activo y coincide con el índice. | `option (T)`: Valor de enumeración | `bool`: `true` si activo y coincide |

---

## 🧪 Ejemplo de Uso

Ejemplo 1: Demuestra cómo usar la biblioteca `StateControl` para gestionar estados de una interfaz de usuario (vistas) y un módulo GSM. El código utiliza las enumeraciones `OptionsView` y `OptionsGSM` para configurar y consultar estados.

```cpp
#include "state_control.h"

// Crear instancias de StateControl para vistas de UI y estados GSM
StateControl viewControl(OptionsViewLength); // Para OptionsView (vistas UI)
StateControl gsmControl(OptionsGSMLength);   // Para OptionsGSM (estados GSM)

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Esperar conexión del puerto serial
  }
  Serial.println(F("Ejemplo de StateControl: Demostración de todos los métodos"));

  // 1. Estado inicial
  Serial.println(F("1. Estado inicial de viewControl"));
  printStates(viewControl);

  // 2. setState(uint8_t index, bool exclusive)
  Serial.println(F("\n2. Configurando vista MAIN (exclusiva)"));
  viewControl.setState(static_cast<uint8_t>(OptionsView::MAIN));
  printStates(viewControl);

  // 3. setState(uint8_t index, bool state, bool exclusive)
  Serial.println(F("\n3. Configurando vista MENU a true (no exclusiva)"));
  viewControl.setState(static_cast<uint8_t>(OptionsView::MENU), true, false);
  printStates(viewControl);

  // 4. toggleState(uint8_t index)
  Serial.println(F("\n4. Alternando estado de MENU"));
  viewControl.toggleState(static_cast<uint8_t>(OptionsView::MENU));
  printStates(viewControl);

  // 5. resetArray()
  Serial.println(F("\n5. Restableciendo todos los estados"));
  viewControl.resetArray();
  printStates(viewControl);

  // 6. setAllStates(bool state)
  Serial.println(F("\n6. Configurando todos los estados a true"));
  viewControl.setAllStates(true);
  printStates(viewControl);

  // 7. setDefaultIndex()
  Serial.println(F("\n7. Configurando índice predeterminado (MAIN)"));
  viewControl.setDefaultIndex();
  printStates(viewControl);

  // 8. getState(uint8_t index)
  Serial.println(F("\n8. Verificando estado de SUB_MENU_1"));
  Serial.print(F("Estado de SUB_MENU_1: "));
  Serial.println(viewControl.getState(static_cast<uint8_t>(OptionsView::SUB_MENU_1)));

  // 9. getFirstTrueIndex()
  Serial.println(F("\n9. Obteniendo primer índice true"));
  Serial.print(F("Primer índice true: "));
  Serial.println(viewControl.getFirstTrueIndex());

  // 10. getAllTrueIndices(uint8_t& count)
  Serial.println(F("\n10. Obteniendo todos los índices true"));
  uint8_t count;
  uint8_t* indices = viewControl.getAllTrueIndices(count);
  Serial.print(F("Índices true (count=")); Serial.print(count); Serial.print(F("): "));
  for (uint8_t i = 0; i < count; i++) {
    Serial.print(indices[i]);
    if (i < count - 1) Serial.print(F(", "));
  }
  Serial.println();
  delete[] indices; // Liberar memoria

  // 11. getIndex()
  Serial.println(F("\n11. Obteniendo índice true actual"));
  Serial.print(F("Índice true actual: "));
  Serial.println(viewControl.getIndex());

  // 12. getIndex(char* buffer, uint8_t bufSize)
  Serial.println(F("\n12. Obteniendo índice true como cadena"));
  char buffer[20];
  viewControl.getIndex(buffer, sizeof(buffer));
  Serial.print(F("Cadena de índice true: "));
  Serial.println(buffer);

  // 13. serializeStatesSize()
  Serial.println(F("\n13. Obteniendo tamaño de serialización"));
  Serial.print(F("Tamaño de serialización: "));
  Serial.println(viewControl.serializeStatesSize());

  // 14. serializeStates(char* buffer, uint8_t bufSize)
  Serial.println(F("\n14. Serializando estados"));
  char stateBuffer[OptionsViewLength + 1];
  viewControl.serializeStates(stateBuffer, sizeof(stateBuffer));
  Serial.print(F("Estados serializados: "));
  Serial.println(stateBuffer);

  // 15. findState(bool state)
  Serial.println(F("\n15. Buscando primer estado true"));
  Serial.print(F("Índice del primer estado true: "));
  Serial.println(viewControl.findState(true));

  // 16. setRangeStates(uint8_t start, uint8_t end, bool state)
  Serial.println(F("\n16. Configurando rango SUB_MENU_1 a SUB_MENU_3 a true"));
  viewControl.setRangeStates(static_cast<uint8_t>(OptionsView::SUB_MENU_1), 
                             static_cast<uint8_t>(OptionsView::SUB_MENU_3), true);
  printStates(viewControl);

  // 17. isAssignedIndex()
  Serial.println(F("\n17. Verificando si hay estados asignados"));
  Serial.print(F("¿Hay algún estado asignado? "));
  Serial.println(viewControl.isAssignedIndex() ? F("Sí") : F("No"));

  // 18. countTrueStates()
  Serial.println(F("\n18. Contando estados true"));
  Serial.print(F("Número de estados true: "));
  Serial.println(viewControl.countTrueStates());

  // 19. invertStates()
  Serial.println(F("\n19. Invirtiendo todos los estados"));
  viewControl.invertStates();
  printStates(viewControl);

  // 20. validateSingleState()
  Serial.println(F("\n20. Validando estado único true"));
  viewControl.setState(static_cast<uint8_t>(OptionsView::MENU));
  printStates(viewControl);

  // 21. isValidIndex(uint8_t index)
  Serial.println(F("\n21. Verificando si el índice 10 es válido"));
  Serial.print(F("¿Es válido el índice 10? "));
  Serial.println(viewControl.isValidIndex(10) ? F("Sí") : F("No"));

  // 22. copyStatesFrom(const StateControl& source)
  Serial.println(F("\n22. Copiando estados desde gsmControl a viewControl"));
  gsmControl.setState(static_cast<uint8_t>(OptionsGSM::GSM_ON));
  viewControl.copyStatesFrom(gsmControl);
  printStates(viewControl);

  // 23. saveState() y restoreSavedState()
  Serial.println(F("\n23. Guardando y restaurando estado"));
  viewControl.setState(static_cast<uint8_t>(OptionsView::SUB_MENU_2));
  viewControl.saveState();
  viewControl.setState(static_cast<uint8_t>(OptionsView::SUB_MENU_3));
  Serial.println(F("Estado antes de restaurar:"));
  printStates(viewControl);
  viewControl.restoreSavedState();
  Serial.println(F("Estado después de restaurar:"));
  printStates(viewControl);

  // 24. setStateByEnum(T option, bool state, bool exclusive)
  Serial.println(F("\n24. Configurando estado GSM usando enumeración"));
  gsmControl.setStateByEnum(OptionsGSM::INCOMINGCALL, true, true);
  printStates(gsmControl);

  // 25. Option(T option)
  Serial.println(F("\n25. Verificando si INCOMINGCALL está activo"));
  Serial.print(F("¿Está activo INCOMINGCALL? "));
  Serial.println(gsmControl.Option(OptionsGSM::INCOMINGCALL) ? F("Sí") : F("No"));
}

void loop() {
  // Bucle vacío, el ejemplo se ejecuta en setup()
}

// Función auxiliar para imprimir estados
void printStates(const StateControl& control) {
  char buffer[OptionsViewLength + 1];
  control.serializeStates(buffer, sizeof(buffer));
  Serial.print(F("Estados: "));
  Serial.println(buffer);
  Serial.print(F("Índice true: "));
  Serial.println(control.getIndex());
}
```


Ejemplo 2: Uso de todos los métodos.

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

## 🧠 Notas de Diseño

- **Gestión Eficiente de Memoria**: Utiliza arreglos dinámicos (`new`/`delete`) para el arreglo de estados y el estado guardado, con un límite de 254 estados para evitar desbordamientos en microcontroladores con poca RAM. El destructor asegura la liberación de recursos.
- **Lógica de Máquina de Estados**: Soporta estados exclusivos (un solo estado `true`) y compartidos para implementar máquinas de estados finitas simples.
- **Índice Activo (`trueIndex`)**: Mantiene un índice activo para rastrear el último estado `true` configurado, optimizando consultas rápidas de estados activos sin recorrer el arreglo completo.
- **Soporte para Enumeraciones**: Los métodos basados en plantillas (`setStateByEnum`, `Option`) permiten usar enumeraciones personalizadas, mejorando la legibilidad y seguridad del código al trabajar con valores simbólicos.
- **Gestión de Errores**: Valida índices, maneja fallos de asignación de memoria, y asegura la integridad de los datos mediante comprobaciones en cada método.
- **Serialización de Estados**: Proporciona métodos para serializar estados como cadenas binarias (por ejemplo, "0100"), útiles para depuración, almacenamiento en memoria no volátil, o comunicación con otros dispositivos.
- **Flexibilidad de Configuración**: Permite configurar rangos de estados, invertir estados, copiar estados entre instancias, y guardar/restaurar estados.

---

## 🧾 Licencia
Este proyecto está licenciado bajo la Licencia MIT — consulta el archivo [LICENSE](https://github.com/ATphonOS/StateControl/blob/main/LICENSE.md) para más detalles.
