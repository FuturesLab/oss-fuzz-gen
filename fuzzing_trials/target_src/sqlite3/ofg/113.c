#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

// Dummy collation function for testing
int dummy_collation(void *pArg, int len1, const void *str1, int len2, const void *str2) {
    return strncmp((const char *)str1, (const char *)str2, len1 < len2 ? len1 : len2);
}

int LLVMFuzzerTestOneInput_113(const uint8_t *data, size_t size) {
    sqlite3 *db;
    const char *collationName = "test_collation";
    int textRep = SQLITE_UTF8;
    void *pArg = NULL; // No specific argument needed for dummy function

    // Initialize SQLite database in memory
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Ensure the data is null-terminated for use as a collation name
    char *collationNameInput = (char *)malloc(size + 1);
    if (collationNameInput == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(collationNameInput, data, size);
    collationNameInput[size] = '\0';

    // Call the function-under-test
    sqlite3_create_collation(db, collationNameInput, textRep, pArg, dummy_collation);

    // Clean up
    free(collationNameInput);
    sqlite3_close(db);

    return 0;
}