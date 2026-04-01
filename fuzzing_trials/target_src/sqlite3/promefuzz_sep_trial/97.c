// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_value_dup at sqlite3.c:78678:27 in sqlite3.h
// sqlite3_column_value at sqlite3.c:79754:27 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_value_int64 at sqlite3.c:78540:25 in sqlite3.h
// sqlite3_value_double at sqlite3.c:78534:19 in sqlite3.h
// sqlite3_value_text at sqlite3.c:78560:33 in sqlite3.h
// sqlite3_value_text16 at sqlite3.c:78564:24 in sqlite3.h
// sqlite3_value_dup at sqlite3.c:78678:27 in sqlite3.h
// sqlite3_value_free at sqlite3.c:78704:17 in sqlite3.h
// sqlite3_value_free at sqlite3.c:78704:17 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

static sqlite3_value* create_sqlite3_value(const uint8_t *Data, size_t Size) {
    sqlite3_value *val = NULL;
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return NULL;
    }

    const char *sql = "SELECT ?;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return NULL;
    }

    if (sqlite3_bind_text(stmt, 1, (const char *)Data, Size, SQLITE_TRANSIENT) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return NULL;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        val = sqlite3_value_dup(sqlite3_column_value(stmt, 0));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return val;
}

int LLVMFuzzerTestOneInput_97(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3_value *val = create_sqlite3_value(Data, Size);
    if (!val) return 0;

    // Test sqlite3_value_int64
    sqlite3_int64 int64_val = sqlite3_value_int64(val);

    // Test sqlite3_value_double
    double double_val = sqlite3_value_double(val);

    // Test sqlite3_value_text
    const unsigned char *text_val = sqlite3_value_text(val);

    // Test sqlite3_value_text16
    const void *text16_val = sqlite3_value_text16(val);

    // Test sqlite3_value_dup and sqlite3_value_free
    sqlite3_value *val_dup = sqlite3_value_dup(val);
    if (val_dup) {
        sqlite3_value_free(val_dup);
    }

    // Clean up the original value
    sqlite3_value_free(val);

    return 0;
}