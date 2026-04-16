#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>

// Define a custom destructor function as a placeholder
void custom_destructor_552(void *param) {
    // Custom cleanup logic can be added here if needed
    (void)param; // To avoid unused parameter warning
}

// Custom SQLite function to provide a valid context
static void custom_sqlite_function(sqlite3_context *context, int argc, sqlite3_value **argv) {
    const void *text = sqlite3_value_blob(argv[0]);
    int text_size = sqlite3_value_bytes(argv[0]);
    sqlite3_result_text16be(context, text, text_size, custom_destructor_552);
}

int LLVMFuzzerTestOneInput_552(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *errMsg = NULL;

    // Initialize SQLite3 and create an in-memory database
    if (sqlite3_initialize() != SQLITE_OK) {
        return 0; // Initialization failed, exit early
    }

    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        sqlite3_shutdown();
        return 0; // Failed to open database, exit early
    }

    // Create a custom SQL function
    if (sqlite3_create_function(db, "custom_function", 1, SQLITE_UTF8, NULL, custom_sqlite_function, NULL, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        sqlite3_shutdown();
        return 0; // Failed to create custom function, exit early
    }

    // Prepare a dummy SQL statement that uses the custom function
    if (sqlite3_prepare_v2(db, "SELECT custom_function(?)", -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        sqlite3_shutdown();
        return 0; // Failed to prepare statement, exit early
    }

    // Bind the input data to the statement
    if (sqlite3_bind_blob(stmt, 1, data, (int)size, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        sqlite3_shutdown();
        return 0; // Failed to bind data, exit early
    }

    // Execute the statement to trigger the custom function
    sqlite3_step(stmt);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    sqlite3_shutdown();

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

    LLVMFuzzerTestOneInput_552(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
