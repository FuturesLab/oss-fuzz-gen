#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "janet.h"

// Function-under-test
void janet_os_rwlock_deinit(JanetOSRWLock *rwlock);

// Fuzzing harness
int LLVMFuzzerTestOneInput_1485(const uint8_t *data, size_t size) {
    // Since we cannot use sizeof(JanetOSRWLock) due to incomplete type,
    // we will assume a reasonable size for fuzzing purposes.
    const size_t rwlock_size = 8; // Assuming 8 bytes for fuzzing, adjust as needed

    // Ensure there is enough data to initialize the structure
    if (size < rwlock_size) {
        return 0;
    }

    // Initialize a buffer to hold the mock data for JanetOSRWLock
    uint8_t rwlock_buffer[rwlock_size];
    memcpy(rwlock_buffer, data, rwlock_size);

    // Cast the buffer to JanetOSRWLock pointer
    JanetOSRWLock *rwlock = (JanetOSRWLock *)rwlock_buffer;

    // Call the function-under-test
    janet_os_rwlock_deinit(rwlock);

    return 0;
}