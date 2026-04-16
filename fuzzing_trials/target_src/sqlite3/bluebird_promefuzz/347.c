#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include "sqlite3.h"

static sqlite3 *open_database() {
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return NULL;
    }
    return db;
}

static void close_database(sqlite3 *db) {
    if (db) {
        sqlite3_close(db);
    }
}

int LLVMFuzzerTestOneInput_347(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) * 2) {
        return 0;
    }

    sqlite3 *db = open_database();
    if (!db) {
        return 0;
    }

    int op = *((int *)Data);
    int resetFlg = *((int *)(Data + sizeof(int)));
    int cur, hiwtr;

    // Fuzz sqlite3_db_status
    sqlite3_db_status(db, op, &cur, &hiwtr, resetFlg);

    // Fuzz sqlite3_error_offset
    sqlite3_error_offset(db);

    // Fuzz sqlite3_changes
    sqlite3_changes(db);

    // Fuzz sqlite3_extended_result_codes
    int onoff = Data[Size - 1] % 2; // Use last byte to decide on/off
    sqlite3_extended_result_codes(db, onoff);

    // Fuzz sqlite3_total_changes
    sqlite3_total_changes(db);

    // Fuzz sqlite3_errcode
    sqlite3_errcode(db);

    close_database(db);
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

    LLVMFuzzerTestOneInput_347(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
