// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_file_control at sqlite3.c:175162:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_db_name at sqlite3.c:175965:24 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>

static void perform_file_control(sqlite3 *db, const char *zDbName) {
    int op = SQLITE_FCNTL_DATA_VERSION;
    int result;
    int dataVersion = 0;

    result = sqlite3_file_control(db, zDbName, op, &dataVersion);
    if (result != SQLITE_OK) {
        fprintf(stderr, "sqlite3_file_control failed with error code: %d\n", result);
    }
}

int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    int rc;
    const char *filename = "./dummy_file";

    // Open the database
    rc = sqlite3_open(filename, &db);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Get the database name
    const char *dbName = sqlite3_db_name(db, 0);
    if (dbName != NULL) {
        // Perform file control operations
        perform_file_control(db, dbName);
        perform_file_control(db, dbName);
    }

    // Close the database
    rc = sqlite3_close(db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "sqlite3_close failed with error code: %d\n", rc);
        return 0;
    }

    // Reopen the database to explore different states
    rc = sqlite3_open(filename, &db);
    if (rc == SQLITE_OK) {
        sqlite3_close(db);
    }

    return 0;
}