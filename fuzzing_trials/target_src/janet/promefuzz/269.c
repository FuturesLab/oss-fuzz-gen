// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_struct_put at janet.c:32598:6 in janet.h
// janet_struct_find at janet.c:32513:16 in janet.h
// janet_struct_rawget at janet.c:32626:7 in janet.h
// janet_struct_end at janet.c:32603:16 in janet.h
// janet_struct_get_ex at janet.c:32643:7 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "janet.h"

static JanetStruct create_dummy_struct() {
    static struct {
        JanetStructHead head;
        JanetKV data[2];
    } full_struct;

    full_struct.head.length = 2;
    full_struct.head.capacity = 2;
    full_struct.head.proto = full_struct.data;

    full_struct.data[0].key.u64 = 1;
    full_struct.data[0].value.u64 = 100;
    full_struct.data[1].key.u64 = 2;
    full_struct.data[1].value.u64 = 200;

    return (JanetStruct)&full_struct.head;
}

int LLVMFuzzerTestOneInput_269(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) * 2) return 0;

    JanetStruct st = create_dummy_struct();
    Janet key, value;
    memcpy(&key, Data, sizeof(Janet));
    memcpy(&value, Data + sizeof(Janet), sizeof(Janet));

    // Test janet_struct_head
    JanetStructHead *head = janet_struct_head(st);

    if (head && head->capacity > 0) {
        // Test janet_struct_put
        janet_struct_put((JanetKV *)st, key, value);

        // Test janet_struct_find
        const JanetKV *found = janet_struct_find(st, key);

        // Test janet_struct_rawget
        Janet raw_value = janet_struct_rawget(st, key);

        // Test janet_struct_end
        JanetStruct new_struct = janet_struct_end((JanetKV *)st);

        // Test janet_struct_get_ex
        JanetStruct which;
        Janet ex_value = janet_struct_get_ex(st, key, &which);
    }

    return 0;
}