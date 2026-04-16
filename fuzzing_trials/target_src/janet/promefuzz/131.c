// This fuzz driver is generated for library janet, aiming to fuzz the following functions:
// janet_sandbox_assert at vm.c:1725:6 in janet.h
// janet_sandbox at vm.c:1720:6 in janet.h
// janet_getflags at janet.c:4828:10 in janet.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "janet.h"

// Dummy implementation of janet.h functions for compilation
// In a real scenario, these would be linked from the janet library
void janet_sandbox_assert_131(uint32_t forbidden_flags) {}
void janet_sandbox_131(uint32_t flags) {}
uint64_t janet_getflags_131(const Janet *argv, int32_t n, const char *flags) { return 0; }

static void fuzz_janet_sandbox_assert_131(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) return;
    uint32_t forbidden_flags;
    memcpy(&forbidden_flags, Data, sizeof(uint32_t));
    janet_sandbox_assert_131(forbidden_flags);
}

static void fuzz_janet_sandbox_131(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(uint32_t)) return;
    uint32_t flags;
    memcpy(&flags, Data, sizeof(uint32_t));
    janet_sandbox_131(flags);
}

static void fuzz_janet_getflags_131(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(Janet) + sizeof(int32_t) + 1) return;
    
    size_t offset = 0;
    int32_t n;
    memcpy(&n, Data + offset, sizeof(int32_t));
    offset += sizeof(int32_t);

    const Janet *argv = (const Janet *)(Data + offset);
    offset += sizeof(Janet);

    const char *flags = (const char *)(Data + offset);
    if (Size - offset > 64) return; // Ensure flags string is not too long

    janet_getflags_131(argv, n, flags);
}

int LLVMFuzzerTestOneInput_131(const uint8_t *Data, size_t Size) {
    fuzz_janet_sandbox_assert_131(Data, Size);
    fuzz_janet_sandbox_131(Data, Size);
    fuzz_janet_getflags_131(Data, Size);
    return 0;
}