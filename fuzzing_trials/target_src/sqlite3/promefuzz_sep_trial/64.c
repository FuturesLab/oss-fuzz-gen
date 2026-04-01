// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_null at sqlite3.c:80129:16 in sqlite3.h
// sqlite3_bind_zeroblob at sqlite3.c:80227:16 in sqlite3.h
// sqlite3_column_value at sqlite3.c:79754:27 in sqlite3.h
// sqlite3_bind_value at sqlite3.c:80193:16 in sqlite3.h
// sqlite3_bind_blob at sqlite3.c:80082:16 in sqlite3.h
// sqlite3_bind_text16 at sqlite3.c:80183:16 in sqlite3.h
// sqlite3_bind_blob64 at sqlite3.c:80094:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

static void prepareDummyDatabase(sqlite3 **db, sqlite3_stmt **stmt) {
    int rc = sqlite3_open(":memory:", db);
    if (rc != SQLITE_OK) {
        return;
    }

    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, data BLOB);";
    rc = sqlite3_exec(*db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(*db);
        *db = NULL;
        return;
    }

    sql = "INSERT INTO test (data) VALUES (?);";
    rc = sqlite3_prepare_v2(*db, sql, -1, stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(*db);
        *db = NULL;
        return;
    }
}

static void cleanup(sqlite3 *db, sqlite3_stmt *stmt) {
    if (stmt) {
        sqlite3_finalize(stmt);
    }
    if (db) {
        sqlite3_close(db);
    }
}

int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    prepareDummyDatabase(&db, &stmt);
    if (!db || !stmt) {
        return 0;
    }

    int index = 1; // Using parameter index 1 for simplicity

    // Fuzzing sqlite3_bind_null
    sqlite3_bind_null(stmt, index);

    // Fuzzing sqlite3_bind_zeroblob
    if (Size > 0) {
        int blobSize = Data[0] % 256; // Limit blob size for testing
        sqlite3_bind_zeroblob(stmt, index, blobSize);
    }

    // Fuzzing sqlite3_bind_value
    // Since sqlite3_value_new is not available, using a workaround
    sqlite3_value *val = sqlite3_column_value(stmt, 0); // Get a value from the current row
    if (val) {
        sqlite3_bind_value(stmt, index, val);
    }

    // Fuzzing sqlite3_bind_blob
    if (Size > 0) {
        sqlite3_bind_blob(stmt, index, Data, Size, SQLITE_TRANSIENT);
    }

    // Fuzzing sqlite3_bind_text16
    if (Size > 0) {
        sqlite3_bind_text16(stmt, index, Data, Size, SQLITE_TRANSIENT);
    }

    // Fuzzing sqlite3_bind_blob64
    if (Size > 0) {
        sqlite3_bind_blob64(stmt, index, Data, (sqlite3_uint64)Size, SQLITE_TRANSIENT);
    }

    cleanup(db, stmt);
    return 0;
}