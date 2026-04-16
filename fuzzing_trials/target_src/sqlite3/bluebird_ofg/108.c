#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "sqlite3.h"

// Function to execute a SQL command
static void execute_sql(sqlite3 *db, const char *sql) {
    char *errMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
    }
}

int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;

    // Open a new in-memory database
    const char lwzpauru[1024] = "zducm";
    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_open
    rc = sqlite3_open(lwzpauru, &db);
    // End mutation: Producer.REPLACE_ARG_MUTATOR
    if (rc != SQLITE_OK) {
        return 0; // If opening the database failed, return immediately
    }

    // Ensure the database pointer is not NULL
    if (db != NULL) {
        // Attempt to execute the input data as SQL command
        char *sql = (char *)malloc(size + 1);
        if (sql != NULL) {
            memcpy(sql, data, size);
            sql[size] = '\0'; // Null-terminate the input data
            execute_sql(db, sql);
            free(sql);
        }

        // Close the database
        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_close with sqlite3_changes
        sqlite3_changes(db);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_open to sqlite3_wal_checkpoint_v2
    int npqtyoma = 1;
    int ret_sqlite3_wal_checkpoint_v2_rdvuo = sqlite3_wal_checkpoint_v2(db, (const char *)"r", 0, NULL, &npqtyoma);
    if (ret_sqlite3_wal_checkpoint_v2_rdvuo < 0){
    	return 0;
    }
    // End mutation: Producer.APPEND_MUTATOR
    
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

    LLVMFuzzerTestOneInput_108(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
