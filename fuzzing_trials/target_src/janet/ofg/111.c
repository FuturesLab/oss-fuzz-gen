#include <stdint.h>
#include <stddef.h>
#include <janet.h>

// Assuming JanetAtomicInt is a type defined in the Janet library
// and janet_atomic_dec is a function provided by the library.

extern JanetAtomicInt janet_atomic_dec(volatile JanetAtomicInt *);

// Fuzzing harness for janet_atomic_dec
int LLVMFuzzerTestOneInput_111(const uint8_t *data, size_t size) {
    // Ensure we have enough data to initialize a JanetAtomicInt
    if (size < sizeof(JanetAtomicInt)) {
        return 0;
    }

    // Initialize a JanetAtomicInt using the input data
    JanetAtomicInt atomicInt;
    memcpy(&atomicInt, data, sizeof(JanetAtomicInt));

    // Call the function-under-test
    JanetAtomicInt result = janet_atomic_dec(&atomicInt);

    // Optionally, you can add checks or further operations on 'result'
    // to verify correctness or trigger more code paths.

    return 0;
}