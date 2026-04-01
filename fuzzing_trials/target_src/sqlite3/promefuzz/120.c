// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open_v2 at sqlite3.c:174702:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_vfs_find at sqlite3.c:13246:25 in sqlite3.h
// sqlite3_open_v2 at sqlite3.c:174702:16 in sqlite3.h
// sqlite3_db_config at sqlite3.c:171968:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_vfs_register at sqlite3.c:13292:16 in sqlite3.h
// sqlite3_initialize at sqlite3.c:171208:16 in sqlite3.h
// sqlite3_open_v2 at sqlite3.c:174702:16 in sqlite3.h
// sqlite3_file_control at sqlite3.c:175162:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

static int fuzz_sqlite3_open_v2(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0; // Ensure there is enough data for flags
    char filename[] = "./dummy_file";
    sqlite3 *db = NULL;
    int flags = *(int*)Data;
    const char *zVfs = NULL;

    int rc = sqlite3_open_v2(filename, &db, flags, zVfs);
    if (rc == SQLITE_OK && db != NULL) {
        sqlite3_close(db);
    }
    return 0;
}

static int fuzz_sqlite3_vfs_find(const uint8_t *Data, size_t Size) {
    char vfsName[256];
    if (Size < sizeof(vfsName)) return 0;
    memcpy(vfsName, Data, sizeof(vfsName) - 1);
    vfsName[sizeof(vfsName) - 1] = '\0'; // Ensure null-termination

    sqlite3_vfs *vfs = sqlite3_vfs_find(vfsName);
    (void)vfs; // Use vfs to avoid unused variable warning

    return 0;
}

static int fuzz_sqlite3_db_config(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;
    sqlite3 *db = NULL;
    int op = *(int*)Data;

    int rc = sqlite3_open_v2("./dummy_file", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (rc == SQLITE_OK && db != NULL) {
        sqlite3_db_config(db, op);
        sqlite3_close(db);
    }
    return 0;
}

static int fuzz_sqlite3_vfs_register(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(sqlite3_vfs)) return 0;
    sqlite3_vfs vfs;
    memcpy(&vfs, Data, sizeof(vfs));
    vfs.zName = "dummy_vfs";

    int makeDflt = 0;
    int rc = sqlite3_vfs_register(&vfs, makeDflt);
    (void)rc; // Use rc to avoid unused variable warning

    return 0;
}

static int fuzz_sqlite3_initialize(const uint8_t *Data, size_t Size) {
    (void)Data; // Data not used for this function
    (void)Size; // Size not used for this function

    int rc = sqlite3_initialize();
    (void)rc; // Use rc to avoid unused variable warning

    return 0;
}

static int fuzz_sqlite3_file_control(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;
    sqlite3 *db = NULL;
    int op = *(int*)Data;
    void *pArg = malloc(128); // Allocate memory for pArg to avoid NULL dereference

    int rc = sqlite3_open_v2("./dummy_file", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    if (rc == SQLITE_OK && db != NULL) {
        if (sqlite3_file_control(db, "main", op, pArg) == SQLITE_OK) {
            // Handle any specific operations if needed
        }
        sqlite3_close(db);
    }
    free(pArg); // Free allocated memory
    return 0;
}

int LLVMFuzzerTestOneInput_120(const uint8_t *Data, size_t Size) {
    fuzz_sqlite3_open_v2(Data, Size);
    fuzz_sqlite3_vfs_find(Data, Size);
    fuzz_sqlite3_db_config(Data, Size);
    fuzz_sqlite3_vfs_register(Data, Size);
    fuzz_sqlite3_initialize(Data, Size);
    fuzz_sqlite3_file_control(Data, Size);
    return 0;
}