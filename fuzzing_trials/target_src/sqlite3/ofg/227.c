#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

// Dummy comparison function
int dummy_compare(void *pArg, int len1, const void *str1, int len2, const void *str2) {
    // For simplicity, let's just return 0
    return 0;
}

// Dummy destructor function
void dummy_destructor_227(void *pArg) {
    // Do nothing
}

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_227(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    const char *collationName = "test_collation";

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the data is not empty
    if (size == 0) {
        sqlite3_close(db);
        return 0;
    }

    // Use the first byte of data as collation encoding
    int encoding = data[0] % 4; // 0 to 3 are valid encoding values

    // Call the function-under-test
    rc = sqlite3_create_collation_v2(db, collationName, encoding, NULL, dummy_compare, dummy_destructor_227);

    // Close the database
    sqlite3_close(db);

    return 0;
}

#ifdef __cplusplus
}
#endif