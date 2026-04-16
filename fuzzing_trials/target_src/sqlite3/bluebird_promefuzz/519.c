#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include "sqlite3.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

static void prepare_dummy_db(sqlite3 **db) {
    if (sqlite3_open(":memory:", db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db));
        exit(1);
    }
    char *errMsg = NULL;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value TEXT);";
    if (sqlite3_exec(*db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(*db);
        exit(1);
    }
}

int LLVMFuzzerTestOneInput_519(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    sqlite3_str *strAccum = NULL;
    char *formattedStr = NULL;
    const unsigned char *textResult = NULL;
    int rc;

    prepare_dummy_db(&db);

    // Prepare SQL statement
    rc = sqlite3_prepare_v2(db, (const char *)Data, (int)Size, &stmt, NULL);
    if (rc != SQLITE_OK) {
        goto cleanup;
    }

    // Execute the statement
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        // Retrieve text from the first column
        textResult = sqlite3_column_text(stmt, 0);
        if (textResult) {
            // Use sqlite3_mprintf to format a string
            formattedStr = sqlite3_mprintf("Row data: %s", textResult);
            if (formattedStr) {
                // Create a new sqlite3_str object
                strAccum = sqlite3_str_new(db);

                // Append formatted string twice
                sqlite3_str_appendf(strAccum, "%s", formattedStr);
                sqlite3_str_appendf(strAccum, "%s", formattedStr);

                // Free the formatted string
                sqlite3_free(formattedStr);
            }
        }
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_prepare_v2 to sqlite3_complete16
    int ret_sqlite3_complete16_pnqil = sqlite3_complete16((const void *)db);
    if (ret_sqlite3_complete16_pnqil < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
cleanup:
    if (strAccum) {
        sqlite3_str_finish(strAccum);
    }
    if (stmt) {
        sqlite3_finalize(stmt);
    }
    if (db) {
        sqlite3_close(db);
    }
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

    LLVMFuzzerTestOneInput_519(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
