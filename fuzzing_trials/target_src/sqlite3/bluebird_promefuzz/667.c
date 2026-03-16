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

static void execute_sql(sqlite3 *db, const char *sql) {
    char *errMsg = 0;
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        sqlite3_free(errMsg);
    }
}

static void fuzz_sqlite3_total_changes64(sqlite3 *db) {
    sqlite3_int64 changes = sqlite3_total_changes64(db);
    (void)changes; // Suppress unused variable warning
}

static void fuzz_sqlite3_last_insert_rowid(sqlite3 *db) {
    sqlite3_int64 rowid = sqlite3_last_insert_rowid(db);
    (void)rowid; // Suppress unused variable warning
}

static void fuzz_sqlite3_changes(sqlite3 *db) {
    int changes = sqlite3_changes(db);
    (void)changes; // Suppress unused variable warning
}

static void fuzz_sqlite3_column_int64(sqlite3_stmt *stmt) {
    int column_count = sqlite3_column_count(stmt);
    for (int i = 0; i < column_count; i++) {
        sqlite3_int64 value = sqlite3_column_int64(stmt, i);
        (void)value; // Suppress unused variable warning
    }
}

static void fuzz_sqlite3_changes64(sqlite3 *db) {
    sqlite3_int64 changes = sqlite3_changes64(db);
    (void)changes; // Suppress unused variable warning
}

static void fuzz_sqlite3_errcode(sqlite3 *db) {
    int errcode = sqlite3_errcode(db);
    (void)errcode; // Suppress unused variable warning
}

int LLVMFuzzerTestOneInput_667(const uint8_t *Data, size_t Size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *sql = "./dummy_file";
    FILE *file = fopen(sql, "wb");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    fclose(file);

    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    execute_sql(db, "CREATE TABLE IF NOT EXISTS fuzz_table (id INTEGER PRIMARY KEY, data BLOB);");
    execute_sql(db, "BEGIN TRANSACTION;");
    execute_sql(db, "INSERT INTO fuzz_table (data) VALUES (zeroblob(1024));");
    execute_sql(db, "COMMIT;");

    if (sqlite3_prepare_v2(db, "SELECT * FROM fuzz_table;", -1, &stmt, 0) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            fuzz_sqlite3_column_int64(stmt);
        }
        sqlite3_finalize(stmt);
    }

    fuzz_sqlite3_total_changes64(db);
    fuzz_sqlite3_last_insert_rowid(db);
    fuzz_sqlite3_changes(db);
    fuzz_sqlite3_changes64(db);
    fuzz_sqlite3_errcode(db);

    sqlite3_close(db);
    return 0;
}