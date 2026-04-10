#include <stdint.h>
#include <stddef.h>
#include <janet.h> // Assuming this is the correct header file for JanetAtomicInt

// Define the volatile type for JanetAtomicInt
typedef volatile JanetAtomicInt DW_TAG_volatile_typeJanetAtomicInt;

int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    // Ensure there is enough data to initialize a JanetAtomicInt
    if (size < sizeof(JanetAtomicInt)) {
        return 0;
    }

    // Initialize a JanetAtomicInt with data from the fuzzing input
    JanetAtomicInt atomicInt = *(const JanetAtomicInt *)data;

    // Cast to the volatile type
    DW_TAG_volatile_typeJanetAtomicInt *volatileAtomicInt = (DW_TAG_volatile_typeJanetAtomicInt *)&atomicInt;

    // Call the function-under-test
    JanetAtomicInt result = janet_atomic_inc(volatileAtomicInt);

    // Use the result to prevent compiler optimizations
    (void)result;

    return 0;
}