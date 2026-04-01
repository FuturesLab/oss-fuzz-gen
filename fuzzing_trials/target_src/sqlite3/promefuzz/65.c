// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_sleep at sqlite3.c:175133:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_error_offset at sqlite3.c:173770:16 in sqlite3.h
// sqlite3_busy_timeout at sqlite3.c:172853:16 in sqlite3.h
// sqlite3_changes at sqlite3.c:172160:16 in sqlite3.h
// sqlite3_db_cacheflush at sqlite3.c:171939:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static sqlite3* initialize_database() {
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return NULL;
    }
    return db;
}

static void cleanup_database(sqlite3 *db) {
    if (db) {
        sqlite3_close(db);
    }
}

int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size) {
    // Prepare a buffer for string operations
    char *buffer = (char *)malloc(Size + 1);
    if (!buffer) {
        return 0;
    }
    memcpy(buffer, Data, Size);
    buffer[Size] = '\0';

    // 1. Fuzzing sqlite3_sleep
    int sleep_duration = (Size > 0) ? (int)Data[0] : 0;
    sqlite3_sleep(sleep_duration);

    // 2. Fuzzing sqlite3_error_offset
    sqlite3 *db = initialize_database();
    if (db) {
        sqlite3_exec(db, buffer, 0, 0, 0);
        sqlite3_error_offset(db);

        // 3. Fuzzing sqlite3_busy_timeout
        int timeout_duration = (Size > 1) ? (int)Data[1] : 0;
        sqlite3_busy_timeout(db, timeout_duration);

        // 4. Fuzzing sqlite3_changes
        sqlite3_changes(db);

        // 5. Fuzzing sqlite3_db_cacheflush
        sqlite3_db_cacheflush(db);

        // 6. Fuzzing sqlite3_setlk_timeout
        int flags = (Size > 2) ? (int)Data[2] : 0;
#ifdef SQLITE_ENABLE_SETLK_TIMEOUT
        sqlite3_setlk_timeout(db, timeout_duration, flags);
#endif

        cleanup_database(db);
    }

    free(buffer);
    return 0;
}