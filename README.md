⚠️ DEPRECATED: This library has been renamed to NeuKV. Please use NeuKV for the latest updates and features.

# NeuStorage

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform: Arduino](https://img.shields.io/badge/Platform-Arduino-00878F?logo=arduino&logoColor=white)](https://arduino.cc)
[![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32-blue?logo=espressif&logoColor=white)](https://espressif.com)

**NeuStorage** is a high-performance, lightweight NVS (Non-Volatile Storage) wrapper for ESP32. It is designed to be simple for beginners while providing advanced power for professionals by utilizing C++ templates and avoiding the overhead of the `String` class.

---

## Features

- **No String Overhead**: Completely avoids `String` class to prevent memory fragmentation.
- **Zero Dynamic Allocation**: Uses binary blobs for maximum speed and stability.
- **Type Safety**: Includes `static_assert` to prevent saving incompatible data types (like pointers).
- **Powerfull Templates**: Save and load entire `structs` or arrays in a single line.
- **Beginner Friendly**: Provides simple `putInt`, `putFloat`, and `putBool` shortcuts.
- **Auto-Initialization**: Automatically handles NVS flash initialization and error recovery.

---

## Installation

### Arduino Library Manager (Recommended)

1. In the Arduino IDE, go to **Sketch > Include Library > Manage Libraries...**
2. Search for **NeuStorage**
3. Click **Install**

### PlatformIO

```ini
lib_deps = ulywae/NeuStorage
```

### Manual Installation

1. Download the repository as `.zip`
2. Open Arduino IDE
3. Go to **Sketch > Include Library > Add .ZIP Library**
4. Select the downloaded file

---

## Quick Start

### Basic Usage (For Beginners)

```cpp
#include <NeuStorage.h>

void setup() {
    NeuStorage.begin();

    // Save data
    NeuStorage.putInt("boot_count", 10);

    // Get data with default value fallback
    int boots = NeuStorage.getInt("boot_count", 0);

    NeuStorage.end(); // Always call end() to commit changes
}
```

### Advanced Usage (Storing Structs)

```cpp
struct Config {
    float threshold;
    bool alarmEnabled;
};

void saveConfig() {
    NeuStorage.begin();

    Config myCfg = {25.5f, true};
    NeuStorage.put("sys_cfg", myCfg); // Saves the whole struct

    NeuStorage.end();
}
```

---

## API Reference

| Method                  | Description                                                                 |
| :---------------------- | :-------------------------------------------------------------------------- |
| `begin()`               | Opens the default namespace and initializes flash hardware.                 |
| `isExists(key)`         | Checks if a specific key exists in the current namespace.                   |
| `put<T>(key, val)`      | Stores any trivially copyable data (struct, int, float, etc).               |
| `get<T>(key, var)`      | Retrieves data. Returns `true` if found, variable remains unchanged if not. |
| `get<T>(key, var, def)` | Retrieves data with an automatic default value fallback.                    |
| `putInt(key, val)`      | Shortcut to store a 32-bit integer.                                         |
| `getInt(key, def)`      | Shortcut to get an integer with a default value.                            |
| `putFloat(key, val)`    | Shortcut to store a float.                                                  |
| `getFloat(key, def)`    | Shortcut to get a float with a default value.                               |
| `putBool(key, val)`     | Shortcut to store a boolean.                                                |
| `getBool(key, def)`     | Shortcut to get a boolean with a default value.                             |
| `remove(key)`           | Deletes a specific key-value pair.                                          |
| `clear()`               | Erases all keys within the current namespace.                               |
| `end()`                 | Commits pending changes and closes the NVS handle.                          |

---

## Limitations

To keep the library "pure" and high-performance, please note the following:

1. **No Pointers in Structs**: You cannot store structs that contain pointers (e.g., `char*`, `int*`) or dynamic containers (e.g., `std::vector`, `std::string`). Only "Trivially Copyable" data is allowed.
2. **Key Length**: NVS keys are limited to a maximum of **15 characters**.
3. **Namespace Length**: Namespace names are also limited to **15 characters**.
4. **No Strings**: This library intentionally does not support the Arduino `String` class to ensure memory stability. Use fixed-size char arrays (`char[32]`) inside your structs instead.
5. **Flash Wear**: Like all NVS operations, frequent writing in a tight loop can wear out your ESP32's flash memory. Always manage your write cycles responsibly.

---

## Author

Created by **Ulywae (@neufa)**
Part of the **NEU Ecosystem**

---

## License

This library is licensed under the MIT License.

---
