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
#include <stdlib.h>
#include <sys/stat.h>

static void prepare_database(sqlite3 **db) {
    int rc = sqlite3_open(":memory:", db);
    if (rc != SQLITE_OK) {
        *db = NULL;
    }
}

static sqlite3_blob* prepare_blob(sqlite3 *db) {
    sqlite3_blob *blob = NULL;
    char *errMsg = 0;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, data BLOB);"
                      "INSERT INTO test (data) VALUES (zeroblob(10));";
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc == SQLITE_OK) {
        rc = sqlite3_blob_open(db, "main", "test", "data", 1, 1, &blob);
    }
    if (rc != SQLITE_OK && blob) {
        sqlite3_blob_close(blob);
        blob = NULL;
    }
    return blob;
}

int LLVMFuzzerTestOneInput_131(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    prepare_database(&db);
    if (!db) {
        return 0;
    }

    // sqlite3_errmsg
    const char *errmsg = sqlite3_errmsg(db);

    // sqlite3_blob_reopen
    sqlite3_blob *blob = prepare_blob(db);
    if (blob) {
        sqlite3_int64 rowid = 1;
        if (Size >= sizeof(sqlite3_int64)) {
            memcpy(&rowid, Data, sizeof(sqlite3_int64));
        }
        sqlite3_blob_reopen(blob, rowid);
    }

    // sqlite3_blob_bytes
    if (blob) {
        int blob_size = sqlite3_blob_bytes(blob);
    }

    // sqlite3_realloc64
    void *pOld = sqlite3_malloc(100);
    if (pOld) {
        sqlite3_uint64 newSize = 100;
        if (Size >= sizeof(sqlite3_uint64)) {
            memcpy(&newSize, Data, sizeof(sqlite3_uint64));
        }
        void *pNew = sqlite3_realloc64(pOld, newSize);
        if (pNew) {
            sqlite3_free(pNew);
        } else {
            sqlite3_free(pOld);
        }
    
        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_realloc64 to sqlite3_uri_int64
        char* ret_sqlite3_str_finish_weiob = sqlite3_str_finish(NULL);
        if (ret_sqlite3_str_finish_weiob == NULL){
        	return 0;
        }
        sqlite3_int64 ret_sqlite3_uri_int64_stjyg = sqlite3_uri_int64(ret_sqlite3_str_finish_weiob, (const char *)pNew, 0);
        // End mutation: Producer.APPEND_MUTATOR
        
}

    // sqlite3_randomness
    if (Size > 0) {
        void *randomBuffer = sqlite3_malloc(Size);
        if (randomBuffer) {
            sqlite3_randomness((int)Size, randomBuffer);
            sqlite3_free(randomBuffer);
        }
    }

    if (blob) {
        sqlite3_blob_close(blob);
    }
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

    LLVMFuzzerTestOneInput_131(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
