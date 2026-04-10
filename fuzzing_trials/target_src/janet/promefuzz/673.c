// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_nanbox_from_double at janet.c:37710:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_table at janet.c:33121:13 in janet.h
// janet_table_put at janet.c:33237:6 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
// janet_next at value.c:126:7 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_in at value.c:453:7 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_table_put at janet.c:33237:6 in janet.h
// janet_nanbox_from_pointer at janet.c:37686:7 in janet.h
// janet_put at value.c:764:6 in janet.h
// janet_table_remove at janet.c:33222:7 in janet.h
// janet_table_get at janet.c:33179:7 in janet.h
// janet_table_clear at janet.c:33278:6 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <janet.h>
#include <stdint.h>
#include <stddef.h>

static Janet random_janet_value(const uint8_t *Data, size_t Size, size_t *Index) {
    if (*Index + sizeof(uint64_t) <= Size) {
        uint64_t u64 = *((uint64_t *)(Data + *Index));
        *Index += sizeof(uint64_t);
        return janet_wrap_integer(u64);
    }
    return janet_wrap_nil();
}

static JanetTable *random_janet_table(const uint8_t *Data, size_t Size, size_t *Index) {
    if (*Index + sizeof(JanetTable) <= Size) {
        JanetTable *table = janet_table(0);
        size_t num_entries = (Size - *Index) / (sizeof(JanetKV));
        for (size_t i = 0; i < num_entries; i++) {
            Janet key = random_janet_value(Data, Size, Index);
            Janet value = random_janet_value(Data, Size, Index);
            janet_table_put(table, key, value);
        }
        return table;
    }
    return NULL;
}

int LLVMFuzzerTestOneInput_673(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(JanetTable)) return 0;

    janet_init();  // Initialize the Janet environment

    size_t index = 0;

    JanetTable *table = random_janet_table(Data, Size, &index);
    if (!table) {
        janet_deinit();  // Deinitialize Janet environment
        return 0;
    }

    Janet key = random_janet_value(Data, Size, &index);

    // Fuzz janet_next
    Janet next_val = janet_next(janet_wrap_table(table), key);

    // Fuzz janet_in
    Janet in_val = janet_in(janet_wrap_table(table), key);

    // Fuzz janet_table_put
    Janet value = random_janet_value(Data, Size, &index);
    janet_table_put(table, key, value);

    // Fuzz janet_put
    janet_put(janet_wrap_table(table), key, value);

    // Fuzz janet_table_remove
    Janet removed_val = janet_table_remove(table, key);

    // Fuzz janet_table_get
    Janet get_val = janet_table_get(table, key);

    // Cleanup
    janet_table_clear(table);

    janet_deinit();  // Deinitialize Janet environment

    return 0;
}