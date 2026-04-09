#include <stdint.h>
#include <stddef.h>
#include <janet.h>
#include <string.h> // Include for memory handling functions

int LLVMFuzzerTestOneInput_361(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for creating a JanetFuncDef
    if (size < sizeof(JanetFuncDef)) {
        return 0;
    }

    // Create a local copy of the JanetFuncDef from the input data
    JanetFuncDef func_def;
    memcpy(&func_def, data, sizeof(JanetFuncDef));

    // Ensure func_def has valid fields
    if (func_def.environments == NULL || func_def.bytecode == NULL) {
        return 0;
    }

    // Validate that environments and bytecode are within the bounds of the input data
    if ((uintptr_t)func_def.environments >= (uintptr_t)data + size ||
        (uintptr_t)func_def.bytecode >= (uintptr_t)data + size) {
        return 0;
    }

    // Call the function-under-test
    JanetFunction *result = janet_thunk(&func_def);

    // Optional: Use the result in some way to prevent compiler optimizations
    if (result != NULL) {
        // Do something with result, if needed
    }

    return 0;
}