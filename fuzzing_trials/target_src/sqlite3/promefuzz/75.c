// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_clear_bindings at sqlite3.c:78482:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_double at sqlite3.c:80104:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_blob at sqlite3.c:80082:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_null at sqlite3.c:80129:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_zeroblob64 at sqlite3.c:80242:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_blob64 at sqlite3.c:80094:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void prepare_dummy_file() {
    FILE *file = fopen("./dummy_file", "w");
    if (file) {
        fputs("dummy data", file);
        fclose(file);
    }
}

static sqlite3_stmt* prepare_statement(sqlite3 *db) {
    const char *sql = "SELECT * FROM dummy_table WHERE column1 = ?";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }
    return stmt;
}

int LLVMFuzzerTestOneInput_75(const uint8_t *Data, size_t Size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    prepare_dummy_file();

    if (sqlite3_open("./dummy_file", &db) != SQLITE_OK) {
        return 0;
    }

    stmt = prepare_statement(db);
    if (!stmt) {
        sqlite3_close(db);
        return 0;
    }

    // Fuzzing sqlite3_clear_bindings
    rc = sqlite3_clear_bindings(stmt);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Fuzzing sqlite3_bind_double
    if (Size >= sizeof(double)) {
        double value;
        memcpy(&value, Data, sizeof(double));
        rc = sqlite3_bind_double(stmt, 1, value);
        if (rc != SQLITE_OK) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return 0;
        }
    }

    // Fuzzing sqlite3_bind_blob
    if (Size > sizeof(double)) {
        rc = sqlite3_bind_blob(stmt, 1, Data, Size, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return 0;
        }
    }

    // Fuzzing sqlite3_bind_null
    rc = sqlite3_bind_null(stmt, 1);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Fuzzing sqlite3_bind_zeroblob64
    if (Size >= sizeof(sqlite3_uint64)) {
        sqlite3_uint64 zeroblob_size;
        memcpy(&zeroblob_size, Data, sizeof(sqlite3_uint64));
        rc = sqlite3_bind_zeroblob64(stmt, 1, zeroblob_size);
        if (rc != SQLITE_OK) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return 0;
        }
    }

    // Fuzzing sqlite3_bind_blob64
    if (Size > sizeof(sqlite3_uint64)) {
        rc = sqlite3_bind_blob64(stmt, 1, Data, Size, SQLITE_STATIC);
        if (rc != SQLITE_OK) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return 0;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}