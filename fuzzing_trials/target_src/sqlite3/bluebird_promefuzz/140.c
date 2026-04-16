#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "sqlite3.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

static void prepare_dummy_db(sqlite3 **db) {
    if (sqlite3_open(":memory:", db) != SQLITE_OK) {
        *db = NULL;
    }
}

static void prepare_stmt(sqlite3 *db, const char *sql, sqlite3_stmt **stmt) {
    if (db && sql && sqlite3_prepare_v2(db, sql, -1, stmt, NULL) != SQLITE_OK) {
        *stmt = NULL;
    }
}

int LLVMFuzzerTestOneInput_140(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt1 = NULL, *stmt2 = NULL;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value TEXT);";

    prepare_dummy_db(&db);
    if (!db) return 0;

    prepare_stmt(db, sql, &stmt1);
    if (!stmt1) {
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement to create table
    sqlite3_step(stmt1);
    sqlite3_reset(stmt1);

    // Prepare a statement to insert data
    sql = "INSERT INTO test (value) VALUES (?);";
    prepare_stmt(db, sql, &stmt2);
    if (!stmt2) {
        sqlite3_finalize(stmt1);
        sqlite3_close(db);
        return 0;
    }

    // Bind input data to the statement
    if (Size > 0) {
        sqlite3_bind_text(stmt2, 1, (const char *)Data, Size, SQLITE_TRANSIENT);
    }

    // Execute the statement
    sqlite3_step(stmt2);

    // Fuzzing target functions
    sqlite3_stmt_busy(stmt1);
    sqlite3_stmt_status(stmt1, SQLITE_STMTSTATUS_FULLSCAN_STEP, 0);
    sqlite3_transfer_bindings(stmt1, stmt2);
    sqlite3_expired(stmt1);
    sqlite3_stmt_explain(stmt1, 0);

    // Cleanup
    sqlite3_finalize(stmt1);
    sqlite3_finalize(stmt2);
    sqlite3_close(db);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_140(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
