/**
 * @file NeuStorage.cpp
 * @author Ulywae (@neufa)
 * @brief Implementation of the NeuStorage NVS wrapper.
 */

#include "NeuStorage.h"

namespace Neu
{

    /**
     * @brief Constructor stores the namespace name for later use in begin().
     */
    Storage::Storage(const char *ns) : _ns(ns), _is_open(false) {}

    /**
     * @brief Handles low-level flash initialization and error recovery.
     * This is idempotent and will only run once.
     */
    esp_err_t Storage::init()
    {
        static bool is_init = false;
        if (is_init)
            return ESP_OK;

        esp_err_t ret = nvs_flash_init();
        if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
        {
            // Erase partition and retry if flash is full or format is incompatible
            nvs_flash_erase();
            ret = nvs_flash_init();
        }

        if (ret == ESP_OK)
            is_init = true;
        return ret;
    }

    /**
     * @brief Ensures NVS hardware is ready and opens the specific namespace.
     */
    bool Storage::begin()
    {
        if (init() != ESP_OK)
            return false;
        return (_is_open = (nvs_open(_ns, NVS_READWRITE, &_handle) == ESP_OK));
    }

    /**
     * @brief Checks key existence by attempting to get blob size.
     */
    bool Storage::isExists(const char *key)
    {
        if (!_is_open)
            return false;
        size_t s;
        return (nvs_get_blob(_handle, key, NULL, &s) != ESP_ERR_NVS_NOT_FOUND);
    }

    /**
     * @brief Removes a single key-value pair.
     */
    bool Storage::remove(const char *key)
    {
        if (!_is_open)
            return false;
        return (nvs_erase_key(_handle, key) == ESP_OK);
    }

    /**
     * @brief Erases the entire namespace.
     */
    bool Storage::clear()
    {
        if (!_is_open)
            return false;
        return (nvs_erase_all(_handle) == ESP_OK);
    }

    /**
     * @brief Commits pending changes to flash and releases the NVS handle.
     */
    void Storage::end()
    {
        if (_is_open)
        {
            nvs_commit(_handle);
            nvs_close(_handle);
            _is_open = false;
        }
    }

} // namespace Neu

/**
 * @brief Pre-instantiated global object for the default 'neu' namespace.
 */
Neu::Storage NeuStorage("neu");
