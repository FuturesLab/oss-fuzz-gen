// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_busy_timeout at sqlite3.c:172853:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_column_int at sqlite3.c:79739:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_sleep at sqlite3.c:175133:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <string.h>

static int execute_sql(sqlite3 *db, const char *sql, sqlite3_stmt **stmt) {
    int rc = sqlite3_prepare_v2(db, sql, -1, stmt, NULL);
    if (rc != SQLITE_OK) {
        return rc;
    }
    return sqlite3_step(*stmt);
}

int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc;
    char *errMsg = 0;

    // Open database connection
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Set busy timeout
    sqlite3_busy_timeout(db, 100);

    // Prepare and execute a simple SQL statement
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value INTEGER);";
    rc = execute_sql(db, sql, &stmt);
    if (rc == SQLITE_ROW || rc == SQLITE_DONE) {
        sqlite3_finalize(stmt);
    }

    // Insert data using the fuzzer input
    sql = "INSERT INTO test (value) VALUES (?);";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, Data[0]);
        rc = sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    // Select data and retrieve integer value
    sql = "SELECT value FROM test WHERE id = 1;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            int value = sqlite3_column_int(stmt, 0);
            (void)value; // Use the value to avoid compiler warnings
        }
        sqlite3_finalize(stmt);
    }

    // Sleep for a random amount of time using fuzzer input
    sqlite3_sleep(Data[0] % 200);

    // Close the database connection
    sqlite3_close(db);

    return 0;
}