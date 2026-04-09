#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "janet.h"

static Janet generate_random_janet(const uint8_t *Data, size_t Size, size_t *offset) {
    if (*offset + sizeof(Janet) > Size) return (Janet){.u64 = 0};
    Janet janet;
    memcpy(&janet, Data + *offset, sizeof(Janet));
    *offset += sizeof(Janet);
    return janet;
}

static JanetTable* generate_random_janet_table(const uint8_t *Data, size_t Size, size_t *offset) {
    if (*offset + sizeof(JanetTable) > Size) return NULL;
    JanetTable *table = (JanetTable *)malloc(sizeof(JanetTable));
    memcpy(table, Data + *offset, sizeof(JanetTable));
    *offset += sizeof(JanetTable);

    if (table->capacity > 0) {
        table->data = (JanetKV *)malloc(sizeof(JanetKV) * table->capacity);
        if (*offset + sizeof(JanetKV) * table->capacity <= Size) {
            memcpy(table->data, Data + *offset, sizeof(JanetKV) * table->capacity);
            *offset += sizeof(JanetKV) * table->capacity;
        } else {
            free(table->data);
            table->data = NULL;
            table->capacity = 0; // Set capacity to 0 to avoid out-of-bounds access
        }
    } else {
        table->data = NULL;
    }
    return table;
}

static JanetKV* generate_random_janet_kv(const uint8_t *Data, size_t Size, size_t *offset, int32_t cap) {
    if (cap <= 0 || *offset + sizeof(JanetKV) * cap > Size) return NULL;
    JanetKV *kv = (JanetKV *)malloc(sizeof(JanetKV) * cap);
    memcpy(kv, Data + *offset, sizeof(JanetKV) * cap);
    *offset += sizeof(JanetKV) * cap;
    return kv;
}

int LLVMFuzzerTestOneInput_1505(const uint8_t *Data, size_t Size) {
    size_t offset = 0;

    // Fuzz janet_table_get_ex
    JanetTable *table = generate_random_janet_table(Data, Size, &offset);
    Janet key = generate_random_janet(Data, Size, &offset);
    JanetTable *which = NULL;
    if (table && table->data && table->capacity > 0) {
        Janet result = janet_table_get_ex(table, key, &which);
        (void)result; // Use result to prevent unused variable warning
    }

    // Fuzz janet_dictionary_next
    int32_t cap = 10; // Example capacity
    JanetKV *kvs = generate_random_janet_kv(Data, Size, &offset, cap);
    if (kvs) {
        const JanetKV *next_kv = janet_dictionary_next(kvs, cap, NULL);
        (void)next_kv;
    }

    // Fuzz janet_sorted_keys
    int32_t *index_buffer = (int32_t *)malloc(sizeof(int32_t) * cap);
    if (kvs && index_buffer) {
        int32_t sorted_count = janet_sorted_keys(kvs, cap, index_buffer);
        (void)sorted_count;
    }

    // Fuzz janet_dictionary_view
    if (table) {
        const JanetKV *data;
        int32_t len, cap_view;
        int view_result = janet_dictionary_view((Janet){.pointer = table}, &data, &len, &cap_view);
        (void)view_result;
    }

    // Fuzz janet_dictionary_get
    if (kvs) {
        Janet value = janet_dictionary_get(kvs, cap, key);
        (void)value;
    }

    // Cleanup
    if (table) {
        if (table->data) free(table->data);
        free(table);
    }
    free(kvs);
    free(index_buffer);

    return 0;
}