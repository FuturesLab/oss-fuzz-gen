#include <stdint.h>
#include "sqlite3.h"
#include <string.h>

// Dummy comparison function
static int dummy_compare(void *unused, int len1, const void *str1, int len2, const void *str2) {
    (void)unused; // Unused parameter
    return strncmp((const char *)str1, (const char *)str2, len1 < len2 ? len1 : len2);
}

int LLVMFuzzerTestOneInput_796(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the data is not empty and has a valid size for a collation name
    if (size == 0 || size > 255) {
        sqlite3_close(db);
        return 0;
    }

    // Use the input data as the collation name
    // Ensure null-termination for the collation name
    char collationName[256];
    memcpy(collationName, data, size);
    collationName[size] = '\0';

    int textEncoding = SQLITE_UTF16;

    // Call the function-under-test
    rc = sqlite3_create_collation16(db, collationName, textEncoding, NULL, dummy_compare);

    // Close the database
    sqlite3_close(db);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_796(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
