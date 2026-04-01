#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Initialize SQLite database connection
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Ensure the data size is sufficient for creating strings
    if (size < 2) {
        sqlite3_close(db);
        return 0;
    }

    // Create a null-terminated string for the extension name
    size_t extNameLen = data[0] % (size - 1) + 1; // Ensure extNameLen < size
    char *extensionName = (char *)malloc(extNameLen + 1);
    if (!extensionName) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(extensionName, data + 1, extNameLen);
    extensionName[extNameLen] = '\0';

    // Create a null-terminated string for the entry point
    size_t entryPointLen = data[1] % (size - extNameLen - 1) + 1; // Ensure entryPointLen < remaining size
    char *entryPoint = (char *)malloc(entryPointLen + 1);
    if (!entryPoint) {
        free(extensionName);
        sqlite3_close(db);
        return 0;
    }
    memcpy(entryPoint, data + extNameLen + 1, entryPointLen);
    entryPoint[entryPointLen] = '\0';

    // Prepare error message pointer
    char *errorMsg = NULL;

    // Call the function-under-test
    sqlite3_load_extension(db, extensionName, entryPoint, &errorMsg);

    // Clean up
    free(extensionName);
    free(entryPoint);
    if (errorMsg) {
        sqlite3_free(errorMsg);
    }
    sqlite3_close(db);

    return 0;
}