// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_serialize at sqlite3.c:41164:27 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_backup_init at sqlite3.c:69968:28 in sqlite3.h
// sqlite3_backup_finish at sqlite3.c:70399:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_deserialize at sqlite3.c:41253:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_exec at sqlite3.c:126811:16 in sqlite3.h
// sqlite3_free at sqlite3.c:17452:17 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int exec_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

static void fuzz_sqlite3_open(const uint8_t *Data, size_t Size) {
    if (Size == 0) return;

    char *filename = malloc(Size + 1);
    if (!filename) return;
    memcpy(filename, Data, Size);
    filename[Size] = '\0';

    sqlite3 *db = NULL;
    if (sqlite3_open(filename, &db) == SQLITE_OK) {
        sqlite3_close(db);
    }

    free(filename);
}

static void fuzz_sqlite3_backup_init(const uint8_t *Data, size_t Size) {
    if (Size < 2) return;

    size_t halfSize = Size / 2;
    char *sourceName = malloc(halfSize + 1);
    char *destName = malloc(halfSize + 1);
    if (!sourceName || !destName) {
        free(sourceName);
        free(destName);
        return;
    }

    memcpy(sourceName, Data, halfSize);
    memcpy(destName, Data + halfSize, halfSize);
    sourceName[halfSize] = '\0';
    destName[halfSize] = '\0';

    sqlite3 *sourceDb = NULL;
    sqlite3 *destDb = NULL;
    if (sqlite3_open(":memory:", &sourceDb) == SQLITE_OK &&
        sqlite3_open(":memory:", &destDb) == SQLITE_OK) {
        sqlite3_backup *backup = sqlite3_backup_init(destDb, destName, sourceDb, sourceName);
        if (backup) {
            sqlite3_backup_finish(backup);
        }
        sqlite3_close(sourceDb);
        sqlite3_close(destDb);
    }

    free(sourceName);
    free(destName);
}

static void fuzz_sqlite3_deserialize(const uint8_t *Data, size_t Size) {
    if (Size < 8) return;

    sqlite3 *db = NULL;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) return;

    unsigned char *pData = malloc(Size);
    if (!pData) {
        sqlite3_close(db);
        return;
    }
    memcpy(pData, Data, Size);

    sqlite3_deserialize(db, "main", pData, Size, Size, SQLITE_DESERIALIZE_FREEONCLOSE);
    sqlite3_close(db);
}

static void fuzz_sqlite3_exec(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) return;

    char *sql = malloc(Size + 1);
    if (!sql) {
        sqlite3_close(db);
        return;
    }
    memcpy(sql, Data, Size);
    sql[Size] = '\0';

    char *errmsg = NULL;
    sqlite3_exec(db, sql, exec_callback, 0, &errmsg);
    if (errmsg) {
        sqlite3_free(errmsg);
    }

    sqlite3_close(db);
    free(sql);
}

static void fuzz_sqlite3_serialize(const uint8_t *Data, size_t Size) {
    sqlite3 *db = NULL;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) return;

    unsigned char *serializedData = sqlite3_serialize(db, "main", NULL, 0);
    if (serializedData) {
        sqlite3_free(serializedData);
    }

    sqlite3_close(db);
}

int LLVMFuzzerTestOneInput_96(const uint8_t *Data, size_t Size) {
    fuzz_sqlite3_open(Data, Size);
    fuzz_sqlite3_backup_init(Data, Size);
    fuzz_sqlite3_deserialize(Data, Size);
    fuzz_sqlite3_exec(Data, Size);
    fuzz_sqlite3_serialize(Data, Size);
    return 0;
}