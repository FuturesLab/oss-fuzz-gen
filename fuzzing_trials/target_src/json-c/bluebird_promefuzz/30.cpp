#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "/src/json-c/linkhash.h"
#include "json.h"

static unsigned long simple_hash_fn(const void *k) {
    // A simple hash function for demonstration purposes
    const char *str = static_cast<const char *>(k);
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

static int simple_equal_fn(const void *k1, const void *k2) {
    return strcmp(static_cast<const char *>(k1), static_cast<const char *>(k2)) == 0;
}

extern "C" int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(unsigned long) + sizeof(unsigned) + 1) {
        return 0;
    }

    struct lh_table *table = lh_table_new(16, NULL, simple_hash_fn, simple_equal_fn);
    if (!table) {
        return 0;
    }

    // Ensure null-terminated string for key
    size_t key_length = Size - sizeof(unsigned long) - sizeof(unsigned);
    std::string key_str(reinterpret_cast<const char*>(Data), key_length);
    const void *key = key_str.c_str();
    const void *value = key_str.c_str(); // Using key_str for both key and value for simplicity

    unsigned long hash = *reinterpret_cast<const unsigned long*>(Data + key_length);
    unsigned opts = *reinterpret_cast<const unsigned*>(Data + key_length + sizeof(unsigned long));

    // Fuzz lh_table_insert_w_hash
    lh_table_insert_w_hash(table, key, value, hash, opts);

    // Fuzz json_global_set_string_hash
    int hash_type = *reinterpret_cast<const int*>(Data);
    json_global_set_string_hash(hash_type);

    // Fuzz lh_table_lookup_ex
    void *retrieved_value = nullptr;
    lh_table_lookup_ex(table, key, &retrieved_value);

    // Fuzz lh_table_length
    int length = lh_table_length(table);

    // Fuzz lh_table_delete
    lh_table_delete(table, key);

    // Fuzz lh_table_insert
    lh_table_insert(table, key, value);

    lh_table_free(table);
    return 0;
}