#include <stdint.h>
#include <stddef.h>

// Define the structure for the atomic integer
typedef struct {
    volatile int value;
} DW_TAG_volatile_typeJanetAtomicInt;

// Define the type for the atomic integer
typedef int JanetAtomicInt;

// Function-under-test
JanetAtomicInt janet_atomic_dec(DW_TAG_volatile_typeJanetAtomicInt *atomicInt);

// Fuzzing entry point
int LLVMFuzzerTestOneInput_110(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        return 0; // Not enough data to initialize the atomic integer
    }

    // Initialize the atomic integer with data from the fuzzer input
    DW_TAG_volatile_typeJanetAtomicInt atomicInt;
    atomicInt.value = *(const int *)data;

    // Call the function-under-test
    JanetAtomicInt result = janet_atomic_dec(&atomicInt);

    // Use the result in some way to avoid compiler optimizations removing the call
    (void)result;

    return 0;
}