#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "sqlite3.h"

// Define a callback function to be used with sqlite3_trace
static void traceCallback(void *unused, const char *sql) {
    (void)unused; // Avoid unused parameter warning
    // Just print the SQL statement being traced
    printf("SQL Trace: %s\n", sql);
}

int LLVMFuzzerTestOneInput_643(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    char *errMsg = 0;

    // Initialize SQLite database in-memory
    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_open
    rc = sqlite3_open((const char *)"w", &db);
    // End mutation: Producer.REPLACE_ARG_MUTATOR
    if (rc != SQLITE_OK) {
        return 0; // If opening the database fails, exit early
    }

    // Ensure data is null-terminated before using it as a SQL statement
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Set the trace callback
    sqlite3_trace(db, traceCallback, NULL);

    // Execute the SQL statement
    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of sqlite3_exec
    sqlite3_exec(db, (const char *)"w", 0, 0, &errMsg);
    // End mutation: Producer.REPLACE_ARG_MUTATOR

    // Clean up
    if (errMsg) {
        sqlite3_free(errMsg);
    }
    free(sql);
    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_close with sqlite3_changes
    sqlite3_changes(db);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR

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

    LLVMFuzzerTestOneInput_643(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
