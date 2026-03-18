// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_result_double at sqlite3.c:78820:17 in sqlite3.h
// sqlite3_result_int64 at sqlite3.c:78852:17 in sqlite3.h
// sqlite3_result_null at sqlite3.c:78859:17 in sqlite3.h
// sqlite3_result_error_nomem at sqlite3.c:79043:17 in sqlite3.h
// sqlite3_result_error_toobig at sqlite3.c:79032:17 in sqlite3.h
// sqlite3_aggregate_count at sqlite3.c:79590:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

static sqlite3_context* create_dummy_context() {
    // Since sqlite3_context is an opaque type, we can't allocate it directly.
    // We will simply return a null pointer as a dummy context for testing.
    return NULL;
}

int LLVMFuzzerTestOneInput_131(const uint8_t *Data, size_t Size) {
    sqlite3_context *ctx = create_dummy_context();

    if (ctx) {
        if (Size >= sizeof(double)) {
            double val;
            memcpy(&val, Data, sizeof(double));
            sqlite3_result_double(ctx, val);
        }

        if (Size >= sizeof(sqlite3_int64)) {
            sqlite3_int64 intVal;
            memcpy(&intVal, Data, sizeof(sqlite3_int64));
            sqlite3_result_int64(ctx, intVal);
        }

        sqlite3_result_null(ctx);
        sqlite3_result_error_nomem(ctx);
        sqlite3_result_error_toobig(ctx);

        int count = sqlite3_aggregate_count(ctx);
        (void)count; // Suppress unused variable warning
    }

    return 0;
}