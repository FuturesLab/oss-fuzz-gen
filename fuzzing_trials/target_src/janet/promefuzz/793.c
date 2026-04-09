// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_equals at value.c:249:5 in janet.h
// janet_getboolean at janet.c:4523:1 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_compare at value.c:371:5 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
// janet_nanbox_from_bits at janet.c:37716:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "janet.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

static Janet create_janet_from_data(const uint8_t *Data, size_t Size, size_t *offset) {
    Janet janet_value;
    if (*offset + sizeof(uint64_t) <= Size) {
        janet_value.u64 = *(const uint64_t *)(Data + *offset);
        *offset += sizeof(uint64_t);
    } else {
        janet_value.u64 = 0; // Default to a safe value
    }
    return janet_value;
}

int LLVMFuzzerTestOneInput_793(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) * 2 + sizeof(int32_t)) {
        return 0;
    }

    size_t offset = 0;

    // Prepare Janet values
    Janet x = create_janet_from_data(Data, Size, &offset);
    Janet y = create_janet_from_data(Data, Size, &offset);

    // Ensure there is enough data for argv and n
    if (offset + sizeof(int32_t) > Size) {
        return 0;
    }

    const Janet *argv = (const Janet *)(Data + offset);
    int32_t n = *(const int32_t *)(Data + offset);
    offset += sizeof(int32_t);

    // Fuzz janet_equals
    int equals_result = janet_equals(x, y);

    // Fuzz janet_getboolean
    int getboolean_result = 0;
    if (offset + sizeof(Janet) * (n + 1) <= Size && n >= 0) {
        getboolean_result = janet_getboolean(argv, n);
    }

    // Fuzz janet_wrap_true
    Janet true_value = janet_wrap_true();

    // Fuzz janet_compare
    int compare_result = janet_compare(x, y);

    // Fuzz janet_wrap_false
    Janet false_value = janet_wrap_false();

    // Fuzz janet_wrap_nil
    Janet nil_value = janet_wrap_nil();

    // Write to dummy file if needed for further testing
    write_dummy_file(Data, Size);

    // Cleanup and handle exceptions if necessary
    // (In this context, assuming janet functions handle their own exceptions)

    return 0;
}