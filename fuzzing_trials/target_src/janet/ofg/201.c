#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

// Assuming JanetAtomicInt is defined as follows
typedef int JanetAtomicInt;

// Assuming DW_TAG_volatile_typeJanetAtomicInt is defined as follows
typedef volatile JanetAtomicInt DW_TAG_volatile_typeJanetAtomicInt;

// Function-under-test
JanetAtomicInt janet_atomic_load(DW_TAG_volatile_typeJanetAtomicInt *atomicInt);

int LLVMFuzzerTestOneInput_201(const uint8_t *data, size_t size) {
    // Ensure there is enough data to initialize a JanetAtomicInt
    if (size < sizeof(JanetAtomicInt)) {
        return 0;
    }

    // Initialize a DW_TAG_volatile_typeJanetAtomicInt with the input data
    DW_TAG_volatile_typeJanetAtomicInt atomicInt;
    atomicInt = *((JanetAtomicInt *)data);

    // Call the function-under-test
    JanetAtomicInt result = janet_atomic_load(&atomicInt);

    // Use the result in some way to avoid compiler optimizations removing the call
    printf("Loaded value: %d\n", result);

    return 0;
}