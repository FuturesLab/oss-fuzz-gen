// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_table_init at janet.c:33101:13 in janet.h
// janet_table_init at janet.c:33101:13 in janet.h
// janet_table_clone at janet.c:33287:13 in janet.h
// janet_table_merge_table at janet.c:33313:6 in janet.h
// janet_table_merge_table at janet.c:33313:6 in janet.h
// janet_table_clear at janet.c:33278:6 in janet.h
// janet_table_deinit at janet.c:33111:6 in janet.h
// janet_table_deinit at janet.c:33111:6 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "janet.h"

#define MAX_CAPACITY 1024

static int32_t get_int32_from_data(const uint8_t *data, size_t size) {
    if (size < sizeof(int32_t)) {
        return 0;
    }
    int32_t value;
    memcpy(&value, data, sizeof(int32_t));
    return value;
}

int LLVMFuzzerTestOneInput_165(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) {
        return 0;
    }

    janet_init();

    JanetTable table1, table2;
    int32_t capacity1 = get_int32_from_data(Data, Size) % MAX_CAPACITY;
    int32_t capacity2 = get_int32_from_data(Data + sizeof(int32_t), Size - sizeof(int32_t)) % MAX_CAPACITY;

    JanetTable *initialized_table1 = janet_table_init(&table1, capacity1);
    JanetTable *initialized_table2 = janet_table_init(&table2, capacity2);

    if (initialized_table1 && initialized_table2) {
        JanetTable *cloned_table = janet_table_clone(initialized_table1);
        if (cloned_table) {
            janet_table_merge_table(initialized_table1, cloned_table);
            // Do not free cloned_table as it is managed by Janet GC
        }

        janet_table_merge_table(initialized_table1, initialized_table2);
        janet_table_clear(initialized_table1);
    }

    janet_table_deinit(initialized_table1);
    janet_table_deinit(initialized_table2);

    janet_deinit();

    return 0;
}