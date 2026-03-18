#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

// Dummy comparison function
static int dummyCompare(void *pArg, int len1, const void *str1, int len2, const void *str2) {
    return strncmp((const char *)str1, (const char *)str2, len1 < len2 ? len1 : len2);
}

// Dummy destructor_229 function
static void dummyDestructor(void *pArg) {
    // No operation
}

int LLVMFuzzerTestOneInput_229(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    if (size == 0) {
        return 0;
    }

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        return 0;
    }

    // Use the input data as the collation name
    char collationName[256];
    size_t collationNameLen = size < 255 ? size : 255;
    memcpy(collationName, data, collationNameLen);
    collationName[collationNameLen] = '\0';

    // Call the function-under-test
    sqlite3_create_collation_v2(
        db,
        collationName,
        SQLITE_UTF8,
        NULL,
        dummyCompare,
        dummyDestructor
    );

    // Close the database
    sqlite3_close(db);

    return 0;
}