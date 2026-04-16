#include <stdint.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

// Function to convert UTF-8 to UTF-16
static uint16_t* utf8_to_utf16(const uint8_t* data, size_t size, size_t* out_size) {
    if (size == 0) {
        *out_size = 0;
        return NULL;
    }

    // Allocate memory for UTF-16 string (worst case scenario: each UTF-8 byte becomes one UTF-16 word)
    uint16_t* utf16 = (uint16_t*)malloc((size + 1) * sizeof(uint16_t));
    if (!utf16) {
        *out_size = 0;
        return NULL;
    }

    size_t i = 0, j = 0;
    while (i < size) {
        utf16[j++] = data[i++];
    }
    utf16[j] = 0; // Null-terminate the UTF-16 string
    *out_size = j * sizeof(uint16_t);
    return utf16;
}

int LLVMFuzzerTestOneInput_414(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt = NULL;
    const void *tail = NULL;
    int rc;

    // Initialize a database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the data is not empty
    if (size > 0) {
        // Convert input data to UTF-16
        size_t utf16_size;
        uint16_t* utf16_data = utf8_to_utf16(data, size, &utf16_size);
        if (utf16_data == NULL) {
            sqlite3_close(db);
            return 0;
        }

        // Prepare the SQL statement using the function-under-test
        rc = sqlite3_prepare16_v3(db, utf16_data, (int)utf16_size, 0, &stmt, &tail);

        // Finalize the statement if it was prepared successfully
        if (stmt != NULL) {
            sqlite3_finalize(stmt);
        }

        // Free the allocated UTF-16 data
        free(utf16_data);
    }

    // Close the database connection
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

    LLVMFuzzerTestOneInput_414(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
