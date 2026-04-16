#include <stdint.h>
#include <stddef.h>

// Assuming the definitions for JanetAtomicInt and DW_TAG_volatile_typeJanetAtomicInt
typedef int32_t JanetAtomicInt;
typedef volatile JanetAtomicInt DW_TAG_volatile_typeJanetAtomicInt;

// Function-under-test declaration
JanetAtomicInt janet_atomic_load_relaxed(DW_TAG_volatile_typeJanetAtomicInt *atomicInt);

int LLVMFuzzerTestOneInput_214(const uint8_t *data, size_t size) {
    // Ensure there is enough data to initialize the atomic integer
    if (size < sizeof(JanetAtomicInt)) {
        return 0;
    }

    // Initialize a volatile atomic integer using the provided data
    DW_TAG_volatile_typeJanetAtomicInt atomicInt;
    atomicInt = *((JanetAtomicInt *)data);

    // Call the function-under-test
    JanetAtomicInt result = janet_atomic_load_relaxed(&atomicInt);

    // Use the result to prevent any compiler optimizations that might eliminate the call
    volatile JanetAtomicInt use_result = result;
    (void)use_result;

    return 0;
}