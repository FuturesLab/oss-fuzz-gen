#include <stdint.h>
#include "sqlite3.h"
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int LLVMFuzzerTestOneInput_667(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient to create a valid UTF-16 string
    if (size < 2) {
        return 0;
    }

    // Calculate the number of UTF-16 characters (each character is 2 bytes)
    size_t utf16_size = size & ~1; // Ensure it's even

    // Allocate memory for the UTF-16 string
    uint16_t *utf16_string = (uint16_t *)malloc(utf16_size + 2); // Allocate extra space for null-termination
    if (!utf16_string) {
        return 0; // Allocation failed
    }

    // Copy the input data to the allocated buffer
    memcpy(utf16_string, data, utf16_size);

    // Ensure the UTF-16 string is null-terminated
    utf16_string[utf16_size / 2] = 0;

    sqlite3 *db = NULL;

    // Call the function-under-test
    int result = sqlite3_open16((const void *)utf16_string, &db);

    // If the database was opened successfully, close it
    if (result == SQLITE_OK && db != NULL) {
        sqlite3_close(db);
    }

    // Free the allocated memory
    free(utf16_string);

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

    LLVMFuzzerTestOneInput_667(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
