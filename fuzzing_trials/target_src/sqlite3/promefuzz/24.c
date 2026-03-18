// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_column_text at sqlite3.c:79749:33 in sqlite3.h
// sqlite3_mprintf at sqlite3.c:19329:18 in sqlite3.h
// sqlite3_str_new at sqlite3.c:19257:25 in sqlite3.h
// sqlite3_str_appendf at sqlite3.c:19465:17 in sqlite3.h
// sqlite3_str_appendf at sqlite3.c:19465:17 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_str_finish at sqlite3.c:19172:18 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void prepare_dummy_db(sqlite3 **db) {
    if (sqlite3_open(":memory:", db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db));
        exit(1);
    }
    char *errMsg = NULL;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value TEXT);";
    if (sqlite3_exec(*db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(*db);
        exit(1);
    }
}

int LLVMFuzzerTestOneInput_24(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    sqlite3_str *strAccum = NULL;
    char *formattedStr = NULL;
    const unsigned char *textResult = NULL;
    int rc;

    prepare_dummy_db(&db);

    // Prepare SQL statement
    rc = sqlite3_prepare_v2(db, (const char *)Data, (int)Size, &stmt, NULL);
    if (rc != SQLITE_OK) goto cleanup;

    // Execute the statement
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        // Retrieve text from the first column
        textResult = sqlite3_column_text(stmt, 0);
        if (textResult) {
            // Use sqlite3_mprintf to format a string
            formattedStr = sqlite3_mprintf("Row data: %s", textResult);
            if (formattedStr) {
                // Create a new sqlite3_str object
                strAccum = sqlite3_str_new(db);

                // Append formatted string twice
                sqlite3_str_appendf(strAccum, "%s", formattedStr);
                sqlite3_str_appendf(strAccum, "%s", formattedStr);

                // Free the formatted string
                sqlite3_free(formattedStr);
            }
        }
    }

cleanup:
    if (strAccum) sqlite3_str_finish(strAccum);
    if (stmt) sqlite3_finalize(stmt);
    if (db) sqlite3_close(db);
    return 0;
}