#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "sqlite3.h"

// Define SQLITE_N_LIMIT if not defined
#ifndef SQLITE_N_LIMIT
#define SQLITE_N_LIMIT 16
#endif

static int dummy_progress_handler(void *unused) {
    return 0; // Return 0 to continue operation
}

int LLVMFuzzerTestOneInput_376(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize SQLite
    if (sqlite3_initialize() != SQLITE_OK) {
        return 0;
    }

    sqlite3 *db = NULL;
    int flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
    const char *vfs = NULL;

    // Open database connection
    if (sqlite3_open_v2("./dummy_file", &db, flags, vfs) != SQLITE_OK) {
        sqlite3_shutdown();
        return 0;
    }

    // Set a progress handler
    sqlite3_progress_handler(db, 1000, dummy_progress_handler, NULL);

    // Set various limits
    int limit_id = Data[0] % SQLITE_N_LIMIT;
    int new_limit_value = (Size > 1) ? Data[1] : -1;
    sqlite3_limit(db, limit_id, new_limit_value);
    sqlite3_limit(db, limit_id, new_limit_value);
    
    // Set a hard heap limit
    sqlite3_int64 new_heap_limit = 0;
    if (Size >= 10) {
        memcpy(&new_heap_limit, Data + 2, sizeof(sqlite3_int64));
    }
    sqlite3_hard_heap_limit64(new_heap_limit);

    // Set another limit
    sqlite3_limit(db, limit_id, new_limit_value);

    // Configure the database
    int db_config_op = SQLITE_DBCONFIG_LOOKASIDE;
    int lookaside_size = 128;
    int lookaside_count = 500;

    if (sqlite3_db_config(db, db_config_op, NULL, lookaside_size, lookaside_count) != SQLITE_OK) {
        sqlite3_close(db);
        sqlite3_shutdown();
        return 0;
    }

    // Cleanup
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

    LLVMFuzzerTestOneInput_376(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
