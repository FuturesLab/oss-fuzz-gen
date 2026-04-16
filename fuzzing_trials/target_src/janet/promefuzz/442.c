// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_init at vm.c:1652:5 in janet.h
// janet_table_clone at janet.c:33287:13 in janet.h
// janet_table_merge_table at janet.c:33313:6 in janet.h
// janet_table_merge_table at janet.c:33313:6 in janet.h
// janet_table_deinit at janet.c:33111:6 in janet.h
// janet_scalloc at gc.c:725:7 in janet.h
// janet_sfree at gc.c:759:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

// Initialize the Janet runtime
static void initialize_janet() {
    static int initialized = 0;
    if (!initialized) {
        janet_init();
        initialized = 1;
    }
}

static JanetTable *create_random_table(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(JanetTable)) return NULL;
    JanetTable *table = (JanetTable *)malloc(sizeof(JanetTable));
    if (!table) return NULL;
    memcpy(table, Data, sizeof(JanetTable));
    table->data = (JanetKV *)malloc(sizeof(JanetKV) * table->capacity);
    if (!table->data) {
        free(table);
        return NULL;
    }
    for (int32_t i = 0; i < table->capacity; i++) {
        table->data[i].key = (Janet){};
        table->data[i].value = (Janet){};
    }
    return table;
}

static void free_table(JanetTable *table) {
    if (table) {
        free(table->data);
        free(table);
    }
}

int LLVMFuzzerTestOneInput_442(const uint8_t *Data, size_t Size) {
    initialize_janet();

    if (Size < sizeof(JanetTable)) return 0;

    // Create a random table
    JanetTable *table1 = create_random_table(Data, Size);
    if (!table1) return 0;

    // Clone the table
    JanetTable *cloned_table = janet_table_clone(table1);
    if (cloned_table) {
        // Merge cloned table back into original
        janet_table_merge_table(table1, cloned_table);
    }

    // Create another random table for merging
    JanetTable *table2 = create_random_table(Data, Size);
    if (table2) {
        janet_table_merge_table(table1, table2);
        free_table(table2);
    }

    // Deinitialize the original table
    janet_table_deinit(table1);
    free_table(table1);

    // Allocate and free scratch memory
    void *scratch = janet_scalloc(10, sizeof(JanetKV));
    if (scratch) {
        janet_sfree(scratch);
    }

    return 0;
}