#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "sqlite3.h"
#include <string.h>

int LLVMFuzzerTestOneInput_820(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errmsg = 0;
    int rc;
    
    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        return 0;
    }

    // Ensure the input data is null-terminated for use as a string
    char *func_name = (char *)malloc(size + 1);
    if (func_name == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(func_name, data, size);
    func_name[size] = '\0';

    // Use a fixed number of arguments for the function overload
    int numArgs = 1;

    // Call the function-under-test
    sqlite3_overload_function(db, func_name, numArgs);

    // Clean up
    free(func_name);
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

    LLVMFuzzerTestOneInput_820(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
