#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h> // Include stdlib.h for malloc and free

// A sample collation comparison function
static int sample_collation(void *pArg, int len1, const void *str1, int len2, const void *str2) {
    return strcmp((const char *)str1, (const char *)str2);
}

int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    const char *collationName = "sample_collation";
    int textRep = SQLITE_UTF8;
    void *pArg = NULL;

    // Open an in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the data is null-terminated for collation name
    char *nullTerminatedData = (char *)malloc(size + 1);
    if (nullTerminatedData == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(nullTerminatedData, data, size);
    nullTerminatedData[size] = '\0';

    // Call the function-under-test
    sqlite3_create_collation(db, nullTerminatedData, textRep, pArg, sample_collation);

    // Clean up
    free(nullTerminatedData);
    sqlite3_close(db);

    return 0;
}