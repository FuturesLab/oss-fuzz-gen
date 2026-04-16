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

static void execute_sqlite_fuzzing(sqlite3 *db, const char *sql) {
    sqlite3_stmt *stmt = NULL;
    const char *pzTail = NULL;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &pzTail);
    if (rc != SQLITE_OK) {
        const char *errmsg = sqlite3_errmsg(db);
        (void)errmsg;  // Suppress unused variable warning
        return;
    }

    rc = sqlite3_step(stmt);
    rc = sqlite3_step(stmt);  // Call sqlite3_step twice as required

    int column_count = sqlite3_column_count(stmt);
    for (int i = 0; i < column_count; i++) {
        int col_type = sqlite3_column_type(stmt, i);
        const char *col_name = sqlite3_column_name(stmt, i);
        const unsigned char *col_text = sqlite3_column_text(stmt, i);
        int col_bytes = sqlite3_column_bytes(stmt, i);

        (void)col_type;  // Suppress unused variable warning
        (void)col_name;
        (void)col_text;
        (void)col_bytes;
    }

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_finalize with sqlite3_bind_parameter_count
    sqlite3_bind_parameter_count(stmt);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR
}

int LLVMFuzzerTestOneInput_221(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Initialize SQLite
    sqlite3 *db;
    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_open
    int rc = sqlite3_open((const char *)"w", &db);
    // End mutation: Producer.REPLACE_ARG_MUTATOR
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Copy input data to a null-terminated string

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_open to sqlite3_wal_autocheckpoint
    int ret_sqlite3_wal_autocheckpoint_jxilc = sqlite3_wal_autocheckpoint(db, 64);
    if (ret_sqlite3_wal_autocheckpoint_jxilc < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
    char *sql = (char *)malloc(Size + 1);
    if (!sql) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, Data, Size);
    sql[Size] = '\0';

    // Execute fuzzing with the given SQL
    execute_sqlite_fuzzing(db, sql);

    // Cleanup
    free(sql);
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

    LLVMFuzzerTestOneInput_221(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
