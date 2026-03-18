#include <stdint.h>
#include <stddef.h>  // Include this to define size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_402(const uint8_t *data, size_t size) {
    int op;
    int current = 0;
    int highwater = 0;
    int resetFlag;

    // Ensure size is large enough to extract required inputs
    if (size < sizeof(int) * 2) {
        return 0;
    }

    // Extract values from data
    op = *((int*)data);
    resetFlag = *((int*)(data + sizeof(int)));

    // Call the function-under-test
    sqlite3_status(op, &current, &highwater, resetFlag);

    return 0;
}