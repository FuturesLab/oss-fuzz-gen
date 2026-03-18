#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

// Example collation function
int example_collation(void *notUsed, int len1, const void *str1, int len2, const void *str2) {
    return strncmp((const char *)str1, (const char *)str2, len1 < len2 ? len1 : len2);
}

int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    char *errMsg = 0;

    // Open a new in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        return 0;
    }

    // Ensure the data is null-terminated to safely use as a string
    char collationName[256];
    if (size > 255) {
        size = 255;
    }
    memcpy(collationName, data, size);
    collationName[size] = '\0';

    // Call the function-under-test
    rc = sqlite3_create_collation(db, collationName, SQLITE_UTF8, NULL, example_collation);

    // Close the database
    sqlite3_close(db);

    return 0;
}