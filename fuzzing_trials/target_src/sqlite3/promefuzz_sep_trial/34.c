// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_bind_null at sqlite3.c:80129:16 in sqlite3.h
// sqlite3_stmt_status at sqlite3.c:80439:16 in sqlite3.h
// sqlite3_bind_parameter_name at sqlite3.c:80275:24 in sqlite3.h
// sqlite3_stmt_busy at sqlite3.c:80407:16 in sqlite3.h
// sqlite3_clear_bindings at sqlite3.c:78482:16 in sqlite3.h
// sqlite3_bind_parameter_count at sqlite3.c:80264:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <sqlite3.h>

static sqlite3_stmt* prepare_dummy_statement(sqlite3 *db) {
    const char *sql = "SELECT * FROM sqlite_master WHERE type='table'";
    sqlite3_stmt *stmt = NULL;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    return stmt;
}

int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    sqlite3_open(":memory:", &db);

    sqlite3_stmt *stmt = prepare_dummy_statement(db);

    if (stmt != NULL) {
        // Fuzzing sqlite3_bind_null
        int index = (Size > 0) ? Data[0] % 10 : 0;
        sqlite3_bind_null(stmt, index);

        // Fuzzing sqlite3_stmt_status
        int op = (Size > 1) ? Data[1] % 10 : 0;
        int resetFlg = (Size > 2) ? Data[2] % 2 : 0;
        sqlite3_stmt_status(stmt, op, resetFlg);

        // Fuzzing sqlite3_bind_parameter_name
        const char *paramName = sqlite3_bind_parameter_name(stmt, index);

        // Fuzzing sqlite3_stmt_busy
        int busy = sqlite3_stmt_busy(stmt);

        // Fuzzing sqlite3_clear_bindings
        sqlite3_clear_bindings(stmt);

        // Fuzzing sqlite3_bind_parameter_count
        int paramCount = sqlite3_bind_parameter_count(stmt);

        // Finalize the statement
        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
    return 0;
}