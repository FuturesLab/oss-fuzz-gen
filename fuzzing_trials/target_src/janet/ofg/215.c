#include <stdint.h>
#include <stddef.h>

// Assuming the JanetAtomicInt and DW_TAG_volatile_typeJanetAtomicInt are defined somewhere
// Here is a mock definition for the purpose of this example
typedef struct {
    int value;
} JanetAtomicInt;

typedef volatile JanetAtomicInt DW_TAG_volatile_typeJanetAtomicInt;

// Mock function for janet_atomic_load_relaxed
JanetAtomicInt janet_atomic_load_relaxed_215(DW_TAG_volatile_typeJanetAtomicInt *atomicInt) {
    return *atomicInt;
}

int LLVMFuzzerTestOneInput_215(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a JanetAtomicInt
    if (size < sizeof(JanetAtomicInt)) {
        return 0;
    }

    // Initialize a JanetAtomicInt from the input data
    JanetAtomicInt atomicInt;
    atomicInt.value = *((int*)data);

    // Call the function-under-test
    JanetAtomicInt result = janet_atomic_load_relaxed_215((DW_TAG_volatile_typeJanetAtomicInt *)&atomicInt);

    // Use result to prevent compiler optimizations from removing the function call
    volatile int prevent_optimization = result.value;

    return 0;
}