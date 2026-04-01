// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_blob at sqlite3.c:80082:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_value_dup at sqlite3.c:78678:27 in sqlite3.h
// sqlite3_column_value at sqlite3.c:79754:27 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_value_nochange at sqlite3.c:78667:16 in sqlite3.h
// sqlite3_value_encoding at sqlite3.c:78662:16 in sqlite3.h
// sqlite3_value_bytes at sqlite3.c:78528:16 in sqlite3.h
// sqlite3_value_type at sqlite3.c:78578:16 in sqlite3.h
// sqlite3_vtab_in_next at sqlite3.c:79428:16 in sqlite3.h
// sqlite3_value_frombind at sqlite3.c:78672:16 in sqlite3.h
// sqlite3_value_free at sqlite3.c:78704:17 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

static sqlite3_value* create_sqlite3_value(const uint8_t *Data, size_t Size, sqlite3 **db) {
    sqlite3_value *value = NULL;
    *db = NULL;

    if (sqlite3_open(":memory:", db) != SQLITE_OK) {
        return NULL;
    }

    sqlite3_stmt *stmt;
    const char *sql = "SELECT ?";

    if (sqlite3_prepare_v2(*db, sql, -1, &stmt, 0) != SQLITE_OK) {
        sqlite3_close(*db);
        *db = NULL;
        return NULL;
    }

    if (sqlite3_bind_blob(stmt, 1, Data, Size, SQLITE_TRANSIENT) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(*db);
        *db = NULL;
        return NULL;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        value = sqlite3_value_dup(sqlite3_column_value(stmt, 0));
    }

    sqlite3_finalize(stmt);
    return value;
}

int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db = NULL;
    sqlite3_value *value = create_sqlite3_value(Data, Size, &db);

    if (value) {
        // Test sqlite3_value_nochange
        int nochange = sqlite3_value_nochange(value);

        // Test sqlite3_value_encoding
        int encoding = sqlite3_value_encoding(value);

        // Test sqlite3_value_bytes
        int bytes = sqlite3_value_bytes(value);

        // Test sqlite3_value_type
        int type = sqlite3_value_type(value);

        // Test sqlite3_vtab_in_next
        sqlite3_value *nextValue = NULL;
        int in_next_status = sqlite3_vtab_in_next(value, &nextValue);

        // Test sqlite3_value_frombind
        int frombind = sqlite3_value_frombind(value);

        sqlite3_value_free(value);
    }

    if (db) {
        sqlite3_close(db);
    }

    return 0;
}