// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_column_count at sqlite3.c:79599:16 in sqlite3.h
// sqlite3_column_type at sqlite3.c:79770:16 in sqlite3.h
// sqlite3_column_name at sqlite3.c:79883:24 in sqlite3.h
// sqlite3_column_text at sqlite3.c:79749:33 in sqlite3.h
// sqlite3_column_bytes at sqlite3.c:79724:16 in sqlite3.h
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

static sqlite3 *initialize_database() {
    sqlite3 *db;
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return NULL;
    }
    return db;
}

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    sqlite3 *db = initialize_database();
    if (!db) {
        return 0;
    }

    write_dummy_file(Data, Size);

    sqlite3_stmt *stmt = NULL;
    const char *sql = "SELECT * FROM sqlite_master";
    const char *pzTail = NULL;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &pzTail);
    if (rc != SQLITE_OK) {
        const char *errmsg = sqlite3_errmsg(db);
        (void)errmsg; // Silence unused variable warning
        sqlite3_close(db);
        return 0;
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
        const char *errmsg = sqlite3_errmsg(db);
        (void)errmsg; // Silence unused variable warning
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
        const char *errmsg = sqlite3_errmsg(db);
        (void)errmsg; // Silence unused variable warning
    }

    int column_count = sqlite3_column_count(stmt);
    for (int i = 0; i < column_count; i++) {
        int type = sqlite3_column_type(stmt, i);
        const char *name = sqlite3_column_name(stmt, i);
        const unsigned char *text = sqlite3_column_text(stmt, i);
        int bytes = sqlite3_column_bytes(stmt, i);
        (void)type; // Silence unused variable warning
        (void)name; // Silence unused variable warning
        (void)text; // Silence unused variable warning
        (void)bytes; // Silence unused variable warning
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}