// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_error_offset at sqlite3.c:173770:16 in sqlite3.h
// sqlite3_keyword_check at sqlite3.c:169872:16 in sqlite3.h
// sqlite3_column_blob at sqlite3.c:79714:24 in sqlite3.h
// sqlite3_column_type at sqlite3.c:79770:16 in sqlite3.h
// sqlite3_keyword_name at sqlite3.c:169864:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_keyword_count at sqlite3.c:169871:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

static void fuzz_sqlite3_error_offset(sqlite3 *db) {
    int offset = sqlite3_error_offset(db);
    (void)offset; // Suppress unused variable warning
}

static void fuzz_sqlite3_keyword_check(const uint8_t *Data, size_t Size) {
    if (Size > 0) {
        int isKeyword = sqlite3_keyword_check((const char *)Data, (int)Size);
        (void)isKeyword; // Suppress unused variable warning
    }
}

static void fuzz_sqlite3_column_blob(sqlite3_stmt *stmt, int iCol) {
    const void *blob = sqlite3_column_blob(stmt, iCol);
    (void)blob; // Suppress unused variable warning
}

static void fuzz_sqlite3_column_type(sqlite3_stmt *stmt, int iCol) {
    int colType = sqlite3_column_type(stmt, iCol);
    (void)colType; // Suppress unused variable warning
}

static void fuzz_sqlite3_keyword_name(int index) {
    const char *keyword;
    int length;
    int result = sqlite3_keyword_name(index, &keyword, &length);
    (void)result; // Suppress unused variable warning
    (void)keyword;
    (void)length;
}

int LLVMFuzzerTestOneInput_71(const uint8_t *Data, size_t Size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    // Open a temporary in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare a dummy SQL statement
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value BLOB);";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    // Fuzz various functions
    fuzz_sqlite3_error_offset(db);
    fuzz_sqlite3_keyword_check(Data, Size);

    // Prepare another statement for column functions
    sql = "SELECT * FROM test;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            fuzz_sqlite3_column_blob(stmt, 1);
            fuzz_sqlite3_column_type(stmt, 1);
        }
        sqlite3_finalize(stmt);
    }

    // Fuzz keyword name function with a simple loop
    int keywordCount = sqlite3_keyword_count();
    for (int i = 0; i < keywordCount; ++i) {
        fuzz_sqlite3_keyword_name(i);
    }

    // Close the database connection
    sqlite3_close(db);

    return 0;
}