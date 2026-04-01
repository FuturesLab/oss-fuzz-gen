// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_compileoption_used at sqlite3.c:176156:16 in sqlite3.h
// sqlite3_open_v2 at sqlite3.c:174702:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>

static int check_compile_option(const char *opt) {
    return sqlite3_compileoption_used(opt);
}

static int open_database(const char *filename, sqlite3 **db, int flags, const char *vfs) {
    return sqlite3_open_v2(filename, db, flags, vfs);
}

static int close_database(sqlite3 *db) {
    return sqlite3_close(db);
}

int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare compile option string
    char compile_option[256];
    snprintf(compile_option, sizeof(compile_option), "SQLITE_ENABLE_%c", Data[0]);

    // Check if compile option is used
    int option_used = check_compile_option(compile_option);

    // Prepare filename for database
    const char *filename = "./dummy_file";

    // Write dummy data to file if necessary
    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }

    // Open database
    sqlite3 *db = NULL;
    int flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
    const char *vfs = NULL; // Use default VFS
    int rc = open_database(filename, &db, flags, vfs);
    if (rc != SQLITE_OK) {
        return 0; // If open fails, exit early
    }

    // Close database
    rc = close_database(db);
    if (rc != SQLITE_OK) {
        return 0; // If close fails, exit early
    }

    return 0;
}