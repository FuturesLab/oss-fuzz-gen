// This fuzz driver is generated for library json-c, aiming to fuzz the following functions:
// lh_table_head at linkhash.h:349:36 in linkhash.h
// lh_entry_v at linkhash.h:408:25 in linkhash.h
// lh_entry_set_val at linkhash.h:417:24 in linkhash.h
// lh_entry_v at linkhash.h:408:25 in linkhash.h
// lh_entry_k at linkhash.h:387:25 in linkhash.h
// lh_entry_next at linkhash.h:427:36 in linkhash.h
// lh_entry_prev at linkhash.h:437:36 in linkhash.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
#include "linkhash.h"
}

#include <cstdint>
#include <cstdlib>
#include <cstring>

static lh_table* create_dummy_table() {
    lh_table* table = (lh_table*)malloc(sizeof(lh_table));
    if (table) {
        table->size = 1;
        table->head = (lh_entry*)malloc(sizeof(lh_entry));
        if (table->head) {
            table->head->k = strdup("key");
            table->head->v = strdup("value");
            table->head->next = nullptr;
            table->head->prev = nullptr;
        }
    }
    return table;
}

static void free_dummy_table(lh_table* table) {
    if (table) {
        if (table->head) {
            free((void*)table->head->k);
            free((void*)table->head->v);
            free(table->head);
        }
        free(table);
    }
}

extern "C" int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(void*)) return 0;

    lh_table* table = create_dummy_table();
    if (!table) return 0;

    lh_entry* entry = lh_table_head(table);
    if (entry) {
        // Fuzz lh_entry_set_val
        void* new_val = malloc(Size);
        memcpy(new_val, Data, Size);
        void* old_val = lh_entry_v(entry);
        lh_entry_set_val(entry, new_val);

        // Fuzz lh_entry_v
        void* val = lh_entry_v(entry);

        // Fuzz lh_entry_k
        void* key = lh_entry_k(entry);

        // Fuzz lh_entry_next and lh_entry_prev
        lh_entry* next_entry = lh_entry_next(entry);
        lh_entry* prev_entry = lh_entry_prev(entry);

        // Clean up the allocated values
        // Note: Do not free `val` or `key` as they point to internal structures
        free(old_val);
    }

    free_dummy_table(table);
    return 0;
}