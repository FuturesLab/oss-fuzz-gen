// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_initialize at sqlite3.c:171208:16 in sqlite3.h
// sqlite3_config at sqlite3.c:171444:16 in sqlite3.h
// sqlite3_shutdown at sqlite3.c:171390:16 in sqlite3.h
// sqlite3_vfs_find at sqlite3.c:13246:25 in sqlite3.h
// sqlite3_vfs_register at sqlite3.c:13292:16 in sqlite3.h
// sqlite3_vfs_unregister at sqlite3.c:13320:16 in sqlite3.h
// sqlite3_initialize at sqlite3.c:171208:16 in sqlite3.h
// sqlite3_shutdown at sqlite3.c:171390:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

static void fuzz_sqlite3_config() {
    sqlite3_initialize();
    int config_options[] = {SQLITE_CONFIG_SINGLETHREAD, SQLITE_CONFIG_MULTITHREAD, SQLITE_CONFIG_SERIALIZED};
    for (int i = 0; i < 3; i++) {
        sqlite3_config(config_options[i]);
    }
    sqlite3_shutdown();
}

static void fuzz_sqlite3_vfs_find(const char *vfsName) {
    sqlite3_vfs *vfs = sqlite3_vfs_find(vfsName);
    (void)vfs;
}

static void fuzz_sqlite3_vfs_register() {
    sqlite3_vfs vfs = {
        3, // iVersion
        sizeof(sqlite3_file), // szOsFile
        1024, // mxPathname
        NULL, // pNext
        "test_vfs", // zName
        NULL, // pAppData
        NULL, // xOpen
        NULL, // xDelete
        NULL, // xAccess
        NULL, // xFullPathname
        NULL, // xDlOpen
        NULL, // xDlError
        NULL, // xDlSym
        NULL, // xDlClose
        NULL, // xRandomness
        NULL, // xSleep
        NULL, // xCurrentTime
        NULL, // xGetLastError
        NULL, // xCurrentTimeInt64
        NULL, // xSetSystemCall
        NULL, // xGetSystemCall
        NULL  // xNextSystemCall
    };
    sqlite3_vfs_register(&vfs, 0);
    sqlite3_vfs_unregister(&vfs);
}

static void fuzz_sqlite3_initialize_shutdown() {
    sqlite3_initialize();
    sqlite3_shutdown();
}

int LLVMFuzzerTestOneInput_119(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Fuzz sqlite3_config
    fuzz_sqlite3_config();

    // Fuzz sqlite3_vfs_find
    char vfsName[256];
    size_t vfsNameLen = Size < sizeof(vfsName) ? Size : sizeof(vfsName) - 1;
    memcpy(vfsName, Data, vfsNameLen);
    vfsName[vfsNameLen] = '\0';
    fuzz_sqlite3_vfs_find(vfsName);

    // Fuzz sqlite3_vfs_register and unregister
    fuzz_sqlite3_vfs_register();

    // Fuzz sqlite3_initialize and shutdown
    fuzz_sqlite3_initialize_shutdown();

    return 0;
}