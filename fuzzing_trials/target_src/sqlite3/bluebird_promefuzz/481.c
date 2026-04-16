#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_481(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a new sqlite3_str object
    sqlite3_str *str = sqlite3_str_new(NULL);

    if (str == NULL) {
        return 0;
    }

    // Fuzz sqlite3_str_append
    sqlite3_str_append(str, (const char*)Data, (int)Size);

    // Fuzz sqlite3_str_appendchar
    if (Size > 1) {
        char C = (char)Data[0];
        int N = (int)Data[1];
        sqlite3_str_appendchar(str, N, C);
    }

    // Fuzz sqlite3_str_truncate
    if (Size > 2) {
        int N = (int)Data[2];
        sqlite3_str_truncate(str, N);
    }

    // Check the length of the string
    int length = sqlite3_str_length(str);

    // Check the error code
    int errcode = sqlite3_str_errcode(str);

    // Reset the string
    sqlite3_str_reset(str);

    // Clean up by finalizing the sqlite3_str object
    char *finalized_str = sqlite3_str_finish(str);
    if (finalized_str) {
        free(finalized_str);
    }

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

    LLVMFuzzerTestOneInput_481(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
