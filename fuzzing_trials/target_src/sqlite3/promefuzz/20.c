// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_column_text at sqlite3.c:79749:33 in sqlite3.h
// sqlite3_mprintf at sqlite3.c:19329:18 in sqlite3.h
// sqlite3_str_new at sqlite3.c:19257:25 in sqlite3.h
// sqlite3_str_appendf at sqlite3.c:19465:17 in sqlite3.h
// sqlite3_str_appendf at sqlite3.c:19465:17 in sqlite3.h
// sqlite3_str_finish at sqlite3.c:19172:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

static void prepare_database(sqlite3 **db) {
    int rc = sqlite3_open(":memory:", db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db));
        sqlite3_close(*db);
        *db = NULL;
    }
}

static int execute_sql(sqlite3 *db, const char *sql) {
    char *errMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
    }
    return rc;
}

static sqlite3_stmt* prepare_statement(sqlite3 *db, const char *sql) {
    sqlite3_stmt *stmt = NULL;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        return NULL;
    }
    return stmt;
}

int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    char *formattedStr = NULL;
    sqlite3_str *strAccum = NULL;

    // Prepare database
    prepare_database(&db);
    if (!db) return 0;

    // Create dummy table
    execute_sql(db, "CREATE TABLE dummy (id INTEGER PRIMARY KEY, value TEXT);");

    // Prepare statement
    stmt = prepare_statement(db, "INSERT INTO dummy (value) VALUES ('test');");
    if (!stmt) goto cleanup;

    // Step through statement
    sqlite3_step(stmt);

    // Retrieve text from column
    const unsigned char *text = sqlite3_column_text(stmt, 0);

    // Use sqlite3_mprintf
    formattedStr = sqlite3_mprintf("Column text: %s", text ? text : "NULL");
    if (!formattedStr) goto cleanup;

    // Use sqlite3_str_appendf
    strAccum = sqlite3_str_new(db);
    if (strAccum) {
        sqlite3_str_appendf(strAccum, "Formatted: %s", formattedStr);
        sqlite3_str_appendf(strAccum, " Additional: %d", 42);
        char *finalStr = sqlite3_str_finish(strAccum);
        if (finalStr) {
            sqlite3_free(finalStr);
        }
    }

cleanup:
    // Free resources
    if (formattedStr) sqlite3_free(formattedStr);
    if (stmt) sqlite3_finalize(stmt);
    if (db) sqlite3_close(db);

    return 0;
}