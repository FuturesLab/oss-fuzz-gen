// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_mprintf at sqlite3.c:19329:18 in sqlite3.h
// sqlite3_config at sqlite3.c:171444:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_db_status at sqlite3.c:11036:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_status at sqlite3.c:10769:16 in sqlite3.h
// sqlite3_mprintf at sqlite3.c:19329:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_mprintf at sqlite3.c:19329:18 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_mprintf at sqlite3.c:19329:18 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int dummy_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    (void)NotUsed;
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db = NULL;
    char *errMsg = NULL;
    int rc;
    int current, highwater;
    char *sql = sqlite3_mprintf("%.*s", (int)Size, Data);

    // Step 1: sqlite3_config
    sqlite3_config(SQLITE_CONFIG_LOG, NULL, NULL);

    // Step 2: sqlite3_open
    rc = sqlite3_open("./dummy_file", &db);
    if (rc != SQLITE_OK) {
        sqlite3_free(sql);
        return 0;
    }

    // Step 3: sqlite3_errmsg
    const char *errmsg = sqlite3_errmsg(db);
    if (errmsg) {
        printf("Error: %s\n", errmsg);
    }

    // Step 4: sqlite3_exec
    if (sql != NULL) {
        rc = sqlite3_exec(db, sql, dummy_callback, 0, &errMsg);
        if (rc != SQLITE_OK && errMsg != NULL) {
            printf("SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
        }
    }

    // Step 5: sqlite3_free
    sqlite3_free(sql);

    // Step 6-14: sqlite3_db_status
    for (int i = 0; i < 9; ++i) {
        sqlite3_db_status(db, SQLITE_DBSTATUS_LOOKASIDE_USED, &current, &highwater, 0);
    }

    // Step 15: sqlite3_close
    sqlite3_close(db);

    // Step 16-20: sqlite3_status
    for (int i = 0; i < 5; ++i) {
        sqlite3_status(SQLITE_STATUS_MEMORY_USED, &current, &highwater, 0);
    }

    // Step 21: sqlite3_mprintf
    char *formatted = sqlite3_mprintf("Formatted: %.*s", (int)Size, Data);

    // Step 22: sqlite3_free
    sqlite3_free(formatted);

    // Step 23: sqlite3_mprintf
    formatted = sqlite3_mprintf("Another: %.*s", (int)Size, Data);

    // Step 24: sqlite3_free
    sqlite3_free(formatted);

    // Repeat Steps 2-5
    rc = sqlite3_open("./dummy_file", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    errmsg = sqlite3_errmsg(db);
    if (errmsg) {
        printf("Error: %s\n", errmsg);
    }

    sql = sqlite3_mprintf("%.*s", (int)Size, Data);
    if (sql != NULL) {
        rc = sqlite3_exec(db, sql, dummy_callback, 0, &errMsg);
        if (rc != SQLITE_OK && errMsg != NULL) {
            printf("SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
        }

        rc = sqlite3_exec(db, sql, dummy_callback, 0, &errMsg);
        if (rc != SQLITE_OK && errMsg != NULL) {
            printf("SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
        }

        rc = sqlite3_exec(db, sql, dummy_callback, 0, &errMsg);
        if (rc != SQLITE_OK && errMsg != NULL) {
            printf("SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
        }

        sqlite3_free(sql);
    }

    // Final Step: sqlite3_close
    sqlite3_close(db);

    return 0;
}