// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_busy_timeout at sqlite3.c:172853:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sqlite3.h>

static void execute_sql(sqlite3 *db, const char *sql) {
    char *errMsg = 0;
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        sqlite3_free(errMsg);
    }
}

int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    if (Size < 4) return 0;

    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc;
    const char *filename = "./dummy_file";
    char *sql = "CREATE TABLE IF NOT EXISTS fuzz_table (id INTEGER PRIMARY KEY, value INTEGER);";

    // Open database
    rc = sqlite3_open(filename, &db);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Set busy timeout
    int timeout = Data[0] * 100; // Some arbitrary conversion
    sqlite3_busy_timeout(db, timeout);

    // Execute SQL to create table
    execute_sql(db, sql);

    // Prepare an INSERT statement
    sql = "INSERT INTO fuzz_table (value) VALUES (?);";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Bind the first byte of Data as an integer
    sqlite3_bind_int(stmt, 1, Data[1]);

    // Execute the statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Prepare a SELECT statement
    sql = "SELECT value FROM fuzz_table WHERE id = 1;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the SELECT statement
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        // Retrieve the integer from the first column
        int value = sqlite3_column_int(stmt, 0);
        (void)value; // Suppress unused variable warning
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Sleep for a duration based on the third byte of Data
    sqlite3_sleep(Data[2] * 100);

    // Close the database connection
    sqlite3_close(db);

    return 0;
}