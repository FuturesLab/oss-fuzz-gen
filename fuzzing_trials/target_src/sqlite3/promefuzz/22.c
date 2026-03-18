// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_bind_int64 at sqlite3.c:80118:16 in sqlite3.h
// sqlite3_bind_int at sqlite3.c:80115:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_libversion_number at sqlite3.c:171129:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static sqlite3_stmt* prepare_dummy_stmt(sqlite3** db) {
    sqlite3_stmt* stmt = NULL;
    if (sqlite3_open(":memory:", db) == SQLITE_OK) {
        const char* sql = "SELECT ?1, ?2, ?3, ?4, ?5, ?6, ?7, ?8, ?9, ?10, ?11, ?12, ?13, ?14, ?15, ?16, ?17, ?18, ?19, ?20, ?21, ?22, ?23, ?24, ?25, ?26, ?27, ?28, ?29, ?30, ?31, ?32, ?33, ?34, ?35;";
        sqlite3_prepare_v2(*db, sql, -1, &stmt, NULL);
    }
    return stmt;
}

int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    sqlite3* db = NULL;
    sqlite3_stmt* stmt = prepare_dummy_stmt(&db);
    if (!stmt || Size < 100) {
        if (db) {
            sqlite3_close(db);
        }
        return 0;
    }

    int offset = 0;
    int bind_index = 1;
    while (offset < Size && bind_index <= 35) {
        switch (bind_index) {
            case 1:
            case 5:
            case 9:
            case 18:
            case 24:
            case 25:
            case 26:
            case 27:
            case 28:
            case 29:
                // sqlite3_bind_int64
                if (Size - offset >= sizeof(sqlite3_int64)) {
                    sqlite3_int64 value;
                    memcpy(&value, &Data[offset], sizeof(sqlite3_int64));
                    sqlite3_bind_int64(stmt, bind_index, value);
                    offset += sizeof(sqlite3_int64);
                }
                break;
            case 2:
            case 4:
            case 7:
            case 10:
            case 11:
            case 15:
            case 16:
            case 17:
            case 20:
            case 21:
            case 22:
            case 23:
            case 30:
            case 31:
            case 33:
                // sqlite3_bind_int
                if (Size - offset >= sizeof(int)) {
                    int value;
                    memcpy(&value, &Data[offset], sizeof(int));
                    sqlite3_bind_int(stmt, bind_index, value);
                    offset += sizeof(int);
                }
                break;
            case 3:
            case 6:
            case 8:
            case 12:
            case 13:
            case 14:
            case 19:
            case 32:
            case 34:
            case 35:
                // sqlite3_bind_text
                if (Size - offset >= 1) {
                    int text_len = Data[offset] % (Size - offset);
                    sqlite3_bind_text(stmt, bind_index, (const char*)&Data[offset], text_len, SQLITE_TRANSIENT);
                    offset += text_len;
                }
                break;
        }
        bind_index++;
    }

    // Call sqlite3_libversion_number once after all bindings
    sqlite3_libversion_number();

    sqlite3_finalize(stmt);
    if (db) {
        sqlite3_close(db);
    }
    return 0;
}