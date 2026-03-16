#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

// Dummy comparison function for collation
int dummy_collation(void *pArg, int len1, const void *str1, int len2, const void *str2) {
    return strncmp((const char *)str1, (const char *)str2, len1 < len2 ? len1 : len2);
}

// Dummy destructor function
void dummy_destructor_226(void *pArg) {
    // No operation destructor
}

int LLVMFuzzerTestOneInput_226(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    const char *collation_name = "custom_collation";

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the data is null-terminated for collation name
    char *collation_name_copy = (char *)malloc(size + 1);
    if (collation_name_copy == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(collation_name_copy, data, size);
    collation_name_copy[size] = '\0';

    // Call the function-under-test
    sqlite3_create_collation_v2(db, collation_name_copy, SQLITE_UTF8, NULL, dummy_collation, dummy_destructor_226);

    // Clean up
    free(collation_name_copy);
    sqlite3_close(db);

    return 0;
}