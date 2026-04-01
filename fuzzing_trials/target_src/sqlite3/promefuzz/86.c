// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_reset at sqlite3.c:78461:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_column_count at sqlite3.c:79599:16 in sqlite3.h
// sqlite3_bind_parameter_index at sqlite3.c:80290:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_column_decltype at sqlite3.c:79906:24 in sqlite3.h
// sqlite3_column_name at sqlite3.c:79883:24 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

// Helper function to create a prepared statement
static sqlite3_stmt* createPreparedStatement(sqlite3 *db, const char *sql) {
    sqlite3_stmt *stmt = NULL;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return NULL;
    }
    return stmt;
}

// Helper function to execute and reset a prepared statement
static void executeAndResetStatement(sqlite3_stmt *stmt) {
    sqlite3_step(stmt);
    sqlite3_reset(stmt);
}

// Fuzzing entry point
int LLVMFuzzerTestOneInput_86(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db = NULL;
    sqlite3_open(":memory:", &db);

    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);"
                      "INSERT INTO test (value) VALUES ('foo'), ('bar');"
                      "SELECT * FROM test;";
    sqlite3_stmt *stmt = createPreparedStatement(db, sql);
    if (!stmt) {
        sqlite3_close(db);
        return 0;
    }

    // Fuzz sqlite3_column_count
    int columnCount = sqlite3_column_count(stmt);

    // Ensure paramName is null-terminated by copying to a new buffer
    char *paramName = (char *)malloc(Size + 1);
    if (paramName) {
        memcpy(paramName, Data, Size);
        paramName[Size] = '\0';  // Null-terminate the string

        // Fuzz sqlite3_bind_parameter_index
        int paramIndex = sqlite3_bind_parameter_index(stmt, paramName);

        // Fuzz sqlite3_bind_text
        if (paramIndex > 0) {
            sqlite3_bind_text(stmt, paramIndex, paramName, Size, SQLITE_STATIC);
        }

        free(paramName);
    }

    // Fuzz sqlite3_column_decltype
    for (int i = 0; i < columnCount; i++) {
        const char *declType = sqlite3_column_decltype(stmt, i);
    }

    // Fuzz sqlite3_column_name
    for (int i = 0; i < columnCount; i++) {
        const char *columnName = sqlite3_column_name(stmt, i);
    }

    // Execute and reset the statement
    executeAndResetStatement(stmt);

    // Cleanup
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}