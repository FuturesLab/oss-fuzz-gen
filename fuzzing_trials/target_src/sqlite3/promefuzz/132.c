// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_bind_blob at sqlite3.c:80082:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_column_value at sqlite3.c:79754:27 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_value_pointer at sqlite3.c:78547:18 in sqlite3.h
// sqlite3_value_dup at sqlite3.c:78678:27 in sqlite3.h
// sqlite3_value_free at sqlite3.c:78704:17 in sqlite3.h
// sqlite3_value_text16 at sqlite3.c:78564:24 in sqlite3.h
// sqlite3_value_text16le at sqlite3.c:78570:24 in sqlite3.h
// sqlite3_value_text16be at sqlite3.c:78567:24 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

static sqlite3_value* create_random_sqlite3_value(sqlite3* db, const uint8_t* data, size_t size) {
    sqlite3_value* val = NULL;
    
    if (size > 0) {
        sqlite3_stmt *stmt;
        sqlite3_prepare_v2(db, "SELECT ?", -1, &stmt, 0);
        sqlite3_bind_blob(stmt, 1, data, size, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            val = (sqlite3_value*)sqlite3_column_value(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    
    return val;
}

int LLVMFuzzerTestOneInput_132(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Create a random sqlite3_value
    sqlite3_value* original_value = create_random_sqlite3_value(db, Data, Size);
    if (!original_value) {
        sqlite3_close(db);
        return 0;
    }

    // Fuzz sqlite3_value_pointer
    const char* type_str = "test_type";
    void* pointer = sqlite3_value_pointer(original_value, type_str);

    // Fuzz sqlite3_value_dup
    sqlite3_value* duplicate_value = sqlite3_value_dup(original_value);
    if (duplicate_value) {
        // Fuzz sqlite3_value_free
        sqlite3_value_free(duplicate_value);
    }

    // Fuzz sqlite3_value_text16
    const void* text16 = sqlite3_value_text16(original_value);

    // Fuzz sqlite3_value_text16le
    const void* text16le = sqlite3_value_text16le(original_value);

    // Fuzz sqlite3_value_text16be
    const void* text16be = sqlite3_value_text16be(original_value);

    sqlite3_close(db);
    return 0;
}