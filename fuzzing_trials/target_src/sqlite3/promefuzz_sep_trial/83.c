// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_column_count at sqlite3.c:79599:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_column_name16 at sqlite3.c:79887:24 in sqlite3.h
// sqlite3_column_text16 at sqlite3.c:79764:24 in sqlite3.h
// sqlite3_data_count at sqlite3.c:79609:16 in sqlite3.h
// sqlite3_column_blob at sqlite3.c:79714:24 in sqlite3.h
// sqlite3_column_int at sqlite3.c:79739:16 in sqlite3.h
// sqlite3_column_bytes16 at sqlite3.c:79729:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

static void prepare_dummy_db(sqlite3 **db, sqlite3_stmt **stmt) {
    sqlite3_open(":memory:", db);
    const char *sql = "CREATE TABLE test (id INTEGER, value TEXT); "
                      "INSERT INTO test VALUES (1, 'hello'), (2, 'world'); "
                      "SELECT * FROM test;";
    sqlite3_prepare_v2(*db, sql, -1, stmt, NULL);
}

int LLVMFuzzerTestOneInput_83(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;  // Ensure there is at least one byte to read

    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    prepare_dummy_db(&db, &stmt);

    // Step through the statement to ensure it's ready for column access
    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    int column_count = sqlite3_column_count(stmt);
    if (column_count == 0) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    int column_index = Data[0] % column_count;

    // Fuzzing target functions
    const void *name16 = sqlite3_column_name16(stmt, column_index);
    const void *text16 = sqlite3_column_text16(stmt, column_index);
    int data_count = sqlite3_data_count(stmt);
    const void *blob = sqlite3_column_blob(stmt, column_index);
    int int_val = sqlite3_column_int(stmt, column_index);
    int bytes16 = sqlite3_column_bytes16(stmt, column_index);

    // Use the results to prevent optimizations
    (void)name16;
    (void)text16;
    (void)data_count;
    (void)blob;
    (void)int_val;
    (void)bytes16;

    // Cleanup
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}