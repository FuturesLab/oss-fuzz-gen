// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_int64 at sqlite3.c:80118:16 in sqlite3.h
// sqlite3_bind_double at sqlite3.c:80104:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_column_type at sqlite3.c:79770:16 in sqlite3.h
// sqlite3_column_double at sqlite3.c:79734:19 in sqlite3.h
// sqlite3_reset at sqlite3.c:78461:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static sqlite3 *db = NULL;
static sqlite3_stmt *stmt = NULL;

// Helper function to initialize the database and prepare a statement
static int initialize_db_and_prepare_stmt(const char *sql) {
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return rc;
    }
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    return rc;
}

// Helper function to clean up database resources
static void cleanup() {
    if (stmt) {
        sqlite3_finalize(stmt);
        stmt = NULL;
    }
    if (db) {
        sqlite3_close(db);
        db = NULL;
    }
}

int LLVMFuzzerTestOneInput_93(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(sqlite3_int64) + sizeof(double) + 1) return 0;

    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER, value REAL, text TEXT);"
                      "INSERT INTO test (id, value, text) VALUES (?, ?, ?);"
                      "SELECT * FROM test;";
    
    if (initialize_db_and_prepare_stmt(sql) != SQLITE_OK) {
        cleanup();
        return 0;
    }

    // Fuzz sqlite3_bind_int64
    sqlite3_int64 int_val = *(sqlite3_int64*)Data;
    sqlite3_bind_int64(stmt, 1, int_val);

    // Fuzz sqlite3_bind_double
    double double_val = *(double*)(Data + sizeof(sqlite3_int64));
    sqlite3_bind_double(stmt, 2, double_val);

    // Fuzz sqlite3_bind_text
    const char *text_val = (const char*)(Data + sizeof(sqlite3_int64) + sizeof(double));
    int text_len = (int)(Size - sizeof(sqlite3_int64) - sizeof(double));
    if (text_len > 0) {
        sqlite3_bind_text(stmt, 3, text_val, text_len, SQLITE_TRANSIENT);
    }

    // Execute the statement
    int rc = sqlite3_step(stmt);

    // Fuzz sqlite3_column_type
    if (rc == SQLITE_ROW) {
        for (int i = 0; i < 3; i++) {
            sqlite3_column_type(stmt, i);
        }
    }

    // Fuzz sqlite3_column_double
    if (rc == SQLITE_ROW) {
        sqlite3_column_double(stmt, 1);
    }

    // Reset the statement
    sqlite3_reset(stmt);

    cleanup();
    return 0;
}