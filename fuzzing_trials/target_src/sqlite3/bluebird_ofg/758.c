#include <stdint.h>
#include "sqlite3.h"
#include <string.h>

// Dummy collation function
int collation_function(void *pArg, int len1, const void *str1, int len2, const void *str2) {
    // Simple comparison
    return memcmp(str1, str2, len1 < len2 ? len1 : len2);
}

int LLVMFuzzerTestOneInput_758(const uint8_t *data, size_t size) {
    if (size < 4) {
        return 0; // Not enough data to split into meaningful parts
    }

    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Failed to open the database
    }

    // Use part of the input data as the collation name
    const void *collationName = (const void *)data;
    int collationNameLength = size / 2;

    // Ensure collationName is null-terminated and within bounds
    char collationNameBuffer[256];
    if (collationNameLength >= sizeof(collationNameBuffer)) {
        collationNameLength = sizeof(collationNameBuffer) - 1;
    }
    memcpy(collationNameBuffer, collationName, collationNameLength);
    collationNameBuffer[collationNameLength] = '\0';

    // Use the rest of the data as the collation function argument
    void *pArg = (void *)(data + collationNameLength);
    int pArgLength = size - collationNameLength;
    if (pArgLength < 2) {
        sqlite3_close(db);
        return 0; // Not enough data for a valid collation function argument
    }

    // Ensure pArg is within bounds
    if (pArgLength > (int)(size - collationNameLength)) {
        pArgLength = (int)(size - collationNameLength);
    }

    int textRep = SQLITE_UTF8; // Use UTF8 as it's more common and less likely to cause issues

    // Call the function-under-test
    sqlite3_create_collation(db, collationNameBuffer, textRep, pArg, collation_function);

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

    LLVMFuzzerTestOneInput_758(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
