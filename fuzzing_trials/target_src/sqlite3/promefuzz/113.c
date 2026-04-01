// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_column_count at sqlite3.c:79599:16 in sqlite3.h
// sqlite3_column_count at sqlite3.c:79599:16 in sqlite3.h
// sqlite3_column_type at sqlite3.c:79770:16 in sqlite3.h
// sqlite3_column_int at sqlite3.c:79739:16 in sqlite3.h
// sqlite3_column_int64 at sqlite3.c:79744:25 in sqlite3.h
// sqlite3_column_value at sqlite3.c:79754:27 in sqlite3.h
// sqlite3_value_type at sqlite3.c:78578:16 in sqlite3.h
// sqlite3_value_dup at sqlite3.c:78678:27 in sqlite3.h
// sqlite3_value_int64 at sqlite3.c:78540:25 in sqlite3.h
// sqlite3_bind_int64 at sqlite3.c:80118:16 in sqlite3.h
// sqlite3_value_free at sqlite3.c:78704:17 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>

static void prepare_dummy_db(sqlite3 **db, sqlite3_stmt **stmt) {
    sqlite3_open(":memory:", db);
    const char *create_table_sql = "CREATE TABLE test (id INTEGER, value TEXT);";
    sqlite3_exec(*db, create_table_sql, 0, 0, NULL);

    const char *insert_sql = "INSERT INTO test (id, value) VALUES (1, 'test');";
    sqlite3_exec(*db, insert_sql, 0, 0, NULL);

    const char *select_sql = "SELECT * FROM test;";
    sqlite3_prepare_v2(*db, select_sql, -1, stmt, NULL);
    sqlite3_step(*stmt);
}

int LLVMFuzzerTestOneInput_113(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;

    prepare_dummy_db(&db, &stmt);

    if (Size > 0) {
        int col_index = Data[0] % sqlite3_column_count(stmt);

        int column_count = sqlite3_column_count(stmt);
        int column_type = sqlite3_column_type(stmt, col_index);
        int column_int = sqlite3_column_int(stmt, col_index);
        sqlite3_int64 column_int64 = sqlite3_column_int64(stmt, col_index);

        sqlite3_value *val = sqlite3_column_value(stmt, col_index);
        if (val && sqlite3_value_type(val) != SQLITE_NULL) {
            sqlite3_value *protected_val = sqlite3_value_dup(val);
            sqlite3_int64 int64_val = sqlite3_value_int64(protected_val);
            sqlite3_bind_int64(stmt, col_index + 1, int64_val);
            sqlite3_value_free(protected_val);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}