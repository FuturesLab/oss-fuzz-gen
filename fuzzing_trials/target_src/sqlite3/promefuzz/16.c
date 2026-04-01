// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_config at sqlite3.c:171444:16 in sqlite3.h
// sqlite3_config at sqlite3.c:171444:16 in sqlite3.h
// sqlite3_config at sqlite3.c:171444:16 in sqlite3.h
// sqlite3_config at sqlite3.c:171444:16 in sqlite3.h
// sqlite3_config at sqlite3.c:171444:16 in sqlite3.h
// sqlite3_config at sqlite3.c:171444:16 in sqlite3.h
// sqlite3_config at sqlite3.c:171444:16 in sqlite3.h
// sqlite3_libversion at sqlite3.c:171116:24 in sqlite3.h
// sqlite3_sourceid at sqlite3.c:252248:24 in sqlite3.h
// sqlite3_initialize at sqlite3.c:171208:16 in sqlite3.h
// sqlite3_vfs_find at sqlite3.c:13246:25 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>

static void invoke_sqlite3_config() {
    sqlite3_config(SQLITE_CONFIG_SINGLETHREAD);
    sqlite3_config(SQLITE_CONFIG_MULTITHREAD);
    sqlite3_config(SQLITE_CONFIG_SERIALIZED);
    sqlite3_config(SQLITE_CONFIG_MEMSTATUS, 1);
    sqlite3_config(SQLITE_CONFIG_SCRATCH, NULL, 0, 0);
    sqlite3_config(SQLITE_CONFIG_PAGECACHE, NULL, 0, 0);
    sqlite3_config(SQLITE_CONFIG_HEAP, NULL, 0, 0);
}

int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    // Step 1: Invoke sqlite3_libversion and sqlite3_sourceid
    const char *version = sqlite3_libversion();
    const char *sourceId = sqlite3_sourceid();

    // Step 2: Configure SQLite using sqlite3_config
    invoke_sqlite3_config();

    // Step 3: Initialize SQLite library
    int initResult = sqlite3_initialize();
    if (initResult != SQLITE_OK) {
        return 0; // Early exit if initialization fails
    }

    // Step 4: Find a VFS using sqlite3_vfs_find
    char *vfsName = NULL;
    if (Size > 0) {
        vfsName = (char *)malloc(Size + 1);
        if (vfsName == NULL) {
            return 0; // Early exit if memory allocation fails
        }
        memcpy(vfsName, Data, Size);
        vfsName[Size] = '\0'; // Null-terminate the string
    }
    sqlite3_vfs *vfs = sqlite3_vfs_find(vfsName);

    // Cleanup
    free(vfsName);
    // Normally, we'd call sqlite3_shutdown() here, but it's not thread-safe
    // and must be called from a single thread after all database connections are closed.

    return 0;
}