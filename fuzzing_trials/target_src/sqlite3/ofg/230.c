#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>

typedef int (*collation_callback)(void*, int, const void*, int, const void*);
typedef void (*destroy_callback)(void*);

int sample_collation_callback(void* pArg, int len1, const void* str1, int len2, const void* str2) {
    // A simple collation function that compares strings
    return sqlite3_strnicmp((const char*)str1, (const char*)str2, len1 < len2 ? len1 : len2);
}

void sample_destroy_callback(void* pArg) {
    // Sample destroy callback
}

int LLVMFuzzerTestOneInput_230(const uint8_t *data, size_t size) {
    if (size < 2) {
        return 0; // Not enough data to form two strings
    }

    sqlite3 *db;
    int rc;
    const char *collationName = "sample_collation";
    void *pArg = NULL;

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a collation using the sample callback
    sqlite3_create_collation_v2(
        db,
        collationName,
        SQLITE_UTF8,
        pArg,
        sample_collation_callback,
        sample_destroy_callback
    );

    // Prepare two strings from the input data
    int len1 = data[0] % size;
    int len2 = size - len1 - 1;
    const char *str1 = (const char*)&data[1];
    const char *str2 = (const char*)&data[1 + len1];

    // Use the collation function
    sqlite3_create_collation_v2(
        db,
        collationName,
        SQLITE_UTF8,
        pArg,
        sample_collation_callback,
        sample_destroy_callback
    );

    // Execute a simple query that uses the collation
    char *errMsg = 0;
    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT 'a' COLLATE %s;", collationName);
    sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (errMsg) {
        sqlite3_free(errMsg);
    }

    // Close the SQLite database
    sqlite3_close(db);

    return 0;
}