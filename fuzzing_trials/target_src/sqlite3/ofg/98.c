#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    // Ensure the input data is large enough to extract the required parameters
    if (size < sizeof(int) + 2 * sizeof(sqlite3_int64) + sizeof(int)) {
        return 0;
    }

    // Extract parameters from the input data
    int op = *(const int *)data;
    data += sizeof(int);
    size -= sizeof(int);

    sqlite3_int64 current = *(const sqlite3_int64 *)data;
    data += sizeof(sqlite3_int64);
    size -= sizeof(sqlite3_int64);

    sqlite3_int64 highwater = *(const sqlite3_int64 *)data;
    data += sizeof(sqlite3_int64);
    size -= sizeof(sqlite3_int64);

    int resetFlag = *(const int *)data;
    data += sizeof(int);
    size -= sizeof(int);

    // Call the function-under-test
    sqlite3_status64(op, &current, &highwater, resetFlag);

    return 0;
}