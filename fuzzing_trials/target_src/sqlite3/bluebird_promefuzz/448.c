#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include <stdlib.h>
#include "stdio.h"
#include "sqlite3.h"
#include "stdint.h"
#include "stddef.h"
#include "stdio.h"
#include "string.h"

static void prepare_database(sqlite3 **db, sqlite3_stmt **stmt) {
    sqlite3_open(":memory:", db);
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);"
                      "INSERT INTO test (value) VALUES ('Hello'), ('World');";
    sqlite3_exec(*db, sql, 0, 0, 0);
    sqlite3_prepare_v2(*db, "SELECT * FROM test;", -1, stmt, 0);
}

static void clean_up(sqlite3 *db, sqlite3_stmt *stmt) {
    if (stmt) sqlite3_finalize(stmt);
    if (db) sqlite3_close(db);
}

int LLVMFuzzerTestOneInput_448(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    prepare_database(&db, &stmt);

    if (!stmt) {
        clean_up(db, stmt);
        return 0;
    }

    int step_result = sqlite3_step(stmt);
    if (step_result == SQLITE_ROW) {
        int iCol = Data[0] % sqlite3_column_count(stmt);
        
        int intValue = sqlite3_column_int(stmt, iCol);
        const void *declType = sqlite3_column_decltype16(stmt, iCol);
        const void *textValue = sqlite3_column_text16(stmt, iCol);
        const void *colName = sqlite3_column_name16(stmt, iCol);
        int bytes16 = sqlite3_column_bytes16(stmt, iCol);
        int dataCount = sqlite3_data_count(stmt);

        (void)intValue;
        (void)declType;
        (void)textValue;
        (void)colName;
        (void)bytes16;
        (void)dataCount;
    }

    clean_up(db, stmt);
    return 0;
}