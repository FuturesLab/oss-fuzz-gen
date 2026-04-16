// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_table_init at janet.c:33101:13 in janet.h
// janet_table_weakv at janet.c:33131:13 in janet.h
// janet_table_weakk at janet.c:33126:13 in janet.h
// janet_table_init_raw at janet.c:33106:13 in janet.h
// janet_table at janet.c:33121:13 in janet.h
// janet_table_weakkv at janet.c:33136:13 in janet.h
// janet_init at vm.c:1652:5 in janet.h
// janet_deinit at vm.c:1732:6 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <janet.h>

static void fuzz_janet_table_init(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t capacity = *(int32_t *)Data;
    JanetTable table;
    janet_table_init(&table, capacity);
}

static void fuzz_janet_table_weakv(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t capacity = *(int32_t *)Data;
    janet_table_weakv(capacity);
}

static void fuzz_janet_table_weakk(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t capacity = *(int32_t *)Data;
    janet_table_weakk(capacity);
}

static void fuzz_janet_table_init_raw(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t capacity = *(int32_t *)Data;
    JanetTable table;
    janet_table_init_raw(&table, capacity);
}

static void fuzz_janet_table(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t capacity = *(int32_t *)Data;
    janet_table(capacity);
}

static void fuzz_janet_table_weakkv(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int32_t)) return;
    int32_t capacity = *(int32_t *)Data;
    janet_table_weakkv(capacity);
}

int LLVMFuzzerTestOneInput_146(const uint8_t *Data, size_t Size) {
    janet_init();

    fuzz_janet_table_init(Data, Size);
    fuzz_janet_table_weakv(Data, Size);
    fuzz_janet_table_weakk(Data, Size);
    fuzz_janet_table_init_raw(Data, Size);
    fuzz_janet_table(Data, Size);
    fuzz_janet_table_weakkv(Data, Size);

    janet_deinit();
    return 0;
}