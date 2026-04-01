// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_mprintf at sqlite3.c:19329:18 in sqlite3.h
// sqlite3_mprintf at sqlite3.c:19329:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_blob_open at sqlite3.c:90692:16 in sqlite3.h
// sqlite3_blob_close at sqlite3.c:90931:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

static int dummy_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    sqlite3 *db;
    sqlite3_stmt *stmt = NULL;
    sqlite3_blob *blob = NULL;
    char *errMsg = NULL;
    char *sql1 = NULL;
    char *sql2 = NULL;

    // Open a database connection
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Prepare a dummy statement and finalize it
    if (sqlite3_prepare_v2(db, "CREATE TABLE test (id INTEGER PRIMARY KEY, data BLOB);", -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_finalize(stmt);
    }

    // Execute a dummy SQL statement
    sqlite3_exec(db, "BEGIN; INSERT INTO test (data) VALUES (zeroblob(10)); COMMIT;", dummy_callback, 0, &errMsg);
    sqlite3_free(errMsg);

    // Check if Size is sufficient before accessing Data
    if (Size > 1) {
        // Use sqlite3_mprintf to format SQL strings
        sql1 = sqlite3_mprintf("SELECT * FROM test WHERE id=%d;", (int)Data[0]);
        sql2 = sqlite3_mprintf("SELECT * FROM test WHERE id=%d;", (int)Data[1]);

        // Free the formatted strings
        sqlite3_free(sql1);
        sqlite3_free(sql2);
    }

    // Attempt to open a BLOB
    sqlite3_blob_open(db, "main", "test", "data", 1, 0, &blob);
    if (blob) {
        sqlite3_blob_close(blob);
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}