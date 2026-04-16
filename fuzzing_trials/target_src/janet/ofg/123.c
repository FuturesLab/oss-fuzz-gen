#include <stdint.h>
#include <stddef.h>

// Assuming JanetAtomicInt is a typedef for a specific integer type
typedef int JanetAtomicInt;

// Assuming DW_TAG_volatile_typeJanetAtomicInt is a typedef for a volatile JanetAtomicInt
typedef volatile JanetAtomicInt DW_TAG_volatile_typeJanetAtomicInt;

// Function-under-test
JanetAtomicInt janet_atomic_inc(DW_TAG_volatile_typeJanetAtomicInt *atomicInt);

int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    // Initialize a volatile atomic integer
    DW_TAG_volatile_typeJanetAtomicInt atomicInt = 0;

    // Call the function-under-test
    janet_atomic_inc(&atomicInt);

    return 0;
}