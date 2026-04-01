#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    struct lh_entry {
        struct lh_entry *next;
        struct lh_entry *prev;
        void *k;
        const void *v;
        unsigned k_is_constant:1;
    };

    struct lh_table {
        int size;
        int count;
        struct lh_entry *head;
        struct lh_entry *tail;
        struct lh_entry *table;
        void *free_fn;
        void *resize_fn;
        unsigned char *buckets;
    };

    int lh_table_length(struct lh_table *);
}

extern "C" int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    struct lh_table table;
    table.size = fuzzed_data.ConsumeIntegral<int>();
    table.count = fuzzed_data.ConsumeIntegral<int>();
    table.head = reinterpret_cast<struct lh_entry*>(fuzzed_data.ConsumeIntegral<uintptr_t>());
    table.tail = reinterpret_cast<struct lh_entry*>(fuzzed_data.ConsumeIntegral<uintptr_t>());
    table.table = reinterpret_cast<struct lh_entry*>(fuzzed_data.ConsumeIntegral<uintptr_t>());
    table.free_fn = reinterpret_cast<void*>(fuzzed_data.ConsumeIntegral<uintptr_t>());
    table.resize_fn = reinterpret_cast<void*>(fuzzed_data.ConsumeIntegral<uintptr_t>());
    table.buckets = reinterpret_cast<unsigned char*>(fuzzed_data.ConsumeIntegral<uintptr_t>());

    int length = lh_table_length(&table);

    return 0;
}