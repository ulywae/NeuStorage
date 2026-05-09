/**
 * @file ResetStorage.ino
 * @author Ulywae (@neufa)
 * @brief Maintenance example: How to remove specific keys or wipe all data.
 *
 * USE WITH CAUTION: This example demonstrates data deletion.
 */

#include <Arduino.h>
#include <NeuStorage.h>

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n--- NeuStorage Maintenance Mode ---");

    if (NeuStorage.begin())
    {

        // --- SCENARIO 1: REMOVE A SPECIFIC KEY ---
        // Useful for clearing a specific setting like a WiFi password.
        const char *targetKey = "old_setting";

        if (NeuStorage.isExists(targetKey))
        {
            if (NeuStorage.remove(targetKey))
            {
                Serial.printf("Success: Key '%s' has been removed.\n", targetKey);
            }
        }
        else
        {
            Serial.printf("Notice: Key '%s' does not exist, nothing to remove.\n", targetKey);
        }

        // --- SCENARIO 2: CLEAR ALL DATA (FACTORY RESET) ---
        // This will erase EVERYTHING in the current namespace.
        Serial.println("Performing Factory Reset in 3 seconds...");
        delay(3000);

        if (NeuStorage.clear())
        {
            Serial.println("SUCCESS: All data in this namespace has been cleared!");
        }
        else
        {
            Serial.println("ERROR: Failed to clear storage.");
        }

        // IMPORTANT: Always call end() to finalize the deletion in Flash memory.
        NeuStorage.end();
        Serial.println("Maintenance complete. Storage closed.");
    }
    else
    {
        Serial.println("Failed to open storage!");
    }
}

void loop()
{
    // Nothing to do
}
