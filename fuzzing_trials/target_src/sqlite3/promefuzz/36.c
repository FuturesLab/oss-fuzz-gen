// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_compileoption_used at sqlite3.c:176156:16 in sqlite3.h
// sqlite3_open_v2 at sqlite3.c:174702:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

#define DUMMY_DB_FILE "./dummy_file"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen(DUMMY_DB_FILE, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Ensure null-terminated string for compile option
    char *compileOption = (char *)malloc(Size + 1);
    if (!compileOption) return 0;
    memcpy(compileOption, Data, Size);
    compileOption[Size] = '\0';

    // Step 1: Check compile option used
    int optionUsed = sqlite3_compileoption_used(compileOption);

    // Prepare a dummy database file
    write_dummy_file(Data, Size);

    // Step 2: Open a database connection
    sqlite3 *db = NULL;
    int flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
    const char *vfs = NULL; // Default VFS

    int rc = sqlite3_open_v2(DUMMY_DB_FILE, &db, flags, vfs);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        free(compileOption);
        return 0;
    }

    // Step 3: Close the database connection
    rc = sqlite3_close(db);
    if (rc != SQLITE_OK) {
        // Handle SQLITE_BUSY if needed
    }

    free(compileOption);
    return 0;
}