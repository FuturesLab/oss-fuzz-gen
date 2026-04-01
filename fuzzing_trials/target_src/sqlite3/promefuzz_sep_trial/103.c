// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close_v2 at sqlite3.c:172362:16 in sqlite3.h
// sqlite3_backup_init at sqlite3.c:69968:28 in sqlite3.h
// sqlite3_backup_step at sqlite3.c:70142:16 in sqlite3.h
// sqlite3_backup_remaining at sqlite3.c:70453:16 in sqlite3.h
// sqlite3_backup_pagecount at sqlite3.c:70467:16 in sqlite3.h
// sqlite3_backup_finish at sqlite3.c:70399:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static sqlite3* open_database(const char* filename) {
    sqlite3 *db = NULL;
    if (sqlite3_open(filename, &db) != SQLITE_OK) {
        return NULL;
    }
    return db;
}

static void close_database(sqlite3* db) {
    if (db) {
        sqlite3_close_v2(db);
    }
}

static sqlite3_backup* init_backup(sqlite3* pDest, sqlite3* pSource) {
    return sqlite3_backup_init(pDest, "main", pSource, "main");
}

int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare dummy database files
    FILE *f = fopen("./dummy_source.db", "wb");
    if (f) {
        fwrite(Data, 1, Size, f);
        fclose(f);
    }

    f = fopen("./dummy_dest.db", "wb");
    if (f) {
        fwrite(Data, 1, Size, f);
        fclose(f);
    }

    // Open source and destination databases
    sqlite3 *sourceDb = open_database("./dummy_source.db");
    sqlite3 *destDb = open_database("./dummy_dest.db");

    if (!sourceDb || !destDb) {
        close_database(sourceDb);
        close_database(destDb);
        return 0;
    }

    // Initialize backup
    sqlite3_backup *backup = init_backup(destDb, sourceDb);
    if (backup) {
        // Backup steps
        sqlite3_backup_step(backup, -1);
        sqlite3_backup_remaining(backup);
        sqlite3_backup_pagecount(backup);
        sqlite3_backup_finish(backup);
    }

    // Close databases
    close_database(sourceDb);
    close_database(destDb);

    return 0;
}