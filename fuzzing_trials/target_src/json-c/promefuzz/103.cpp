// This fuzz driver is generated for library json-c, aiming to fuzz the following functions:
// lh_table_new at linkhash.c:499:18 in linkhash.h
// lh_table_free at linkhash.c:568:6 in linkhash.h
// lh_get_hash at linkhash.h:365:33 in linkhash.h
// lh_table_insert_w_hash at linkhash.c:580:5 in linkhash.h
// lh_table_lookup_entry_w_hash at linkhash.c:628:18 in linkhash.h
// lh_table_insert at linkhash.c:623:5 in linkhash.h
// lh_table_lookup_entry at linkhash.c:647:18 in linkhash.h
// lh_table_head at linkhash.h:349:36 in linkhash.h
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
#include <cstring>

static lh_table* create_table() {
    return lh_table_new(16, NULL, NULL, NULL);
}

static void destroy_table(lh_table* table) {
    lh_table_free(table);
}

extern "C" int LLVMFuzzerTestOneInput_103(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a hash table
    lh_table* table = create_table();
    if (!table) return 0;

    // Ensure the table has a valid hash function
    if (!table->hash_fn) {
        destroy_table(table);
        return 0;
    }

    // Prepare key and value
    const void* key = Data;
    const void* value = Data;

    // Calculate hash using lh_get_hash
    unsigned long hash = lh_get_hash(table, key);

    // Insert with lh_table_insert_w_hash
    int insert_result = lh_table_insert_w_hash(table, key, value, hash, 0);

    // Lookup with lh_table_lookup_entry_w_hash
    struct lh_entry* entry = lh_table_lookup_entry_w_hash(table, key, hash);

    // Insert with lh_table_insert
    int insert_result2 = lh_table_insert(table, key, value);

    // Lookup with lh_table_lookup_entry
    struct lh_entry* entry2 = lh_table_lookup_entry(table, key);

    // Get the head of the table
    struct lh_entry* head = lh_table_head(table);

    // Cleanup
    destroy_table(table);

    return 0;
}