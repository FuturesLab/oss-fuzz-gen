#include <stdint.h>
#include "sqlite3.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

// Dummy callback functions to be used as window function callbacks
void step_callback(sqlite3_context *context, int argc, sqlite3_value **argv) {
    // Dummy implementation
}

void final_callback(sqlite3_context *context) {
    // Dummy implementation
}

void value_callback(sqlite3_context *context) {
    // Dummy implementation
}

void inverse_callback(sqlite3_context *context, int argc, sqlite3_value **argv) {
    // Dummy implementation
}

void destroy_callback(void *p) {
    // Dummy implementation
}

int LLVMFuzzerTestOneInput_777(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;
    const char *zFunctionName = "test_window_func";

    // Initialize SQLite in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Ensure the function name is null-terminated
    char *functionName = (char *)malloc(size + 1);
    if (functionName == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(functionName, data, size);
    functionName[size] = '\0';

    // Fuzz the sqlite3_create_window_function
    sqlite3_create_window_function(
        db, 
        functionName, 
        1, 
        SQLITE_UTF8, 
        NULL, 
        step_callback, 
        final_callback, 
        value_callback, 
        inverse_callback, 
        destroy_callback
    );

    // Clean up
    free(functionName);
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

    LLVMFuzzerTestOneInput_777(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
