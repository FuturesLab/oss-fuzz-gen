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

static void update_callback(void *pArg, int op, const char *zDb, const char *zTbl, sqlite3_int64 rowid) {
    // Simple update callback function
}

int LLVMFuzzerTestOneInput_190(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    const char *tail = NULL;
    int rc;

    // Open a SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare a statement
    rc = sqlite3_prepare_v3(db, (const char *)Data, Size, 0, &stmt, &tail);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Test sqlite3_db_handle
    sqlite3 *db_handle = sqlite3_db_handle(stmt);

    // Test sqlite3_stmt_readonly
    int is_readonly = sqlite3_stmt_readonly(stmt);

    // Register an update hook
    sqlite3_update_hook(db, update_callback, NULL);

    // Clean up
    sqlite3_finalize(stmt);
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

    LLVMFuzzerTestOneInput_190(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
