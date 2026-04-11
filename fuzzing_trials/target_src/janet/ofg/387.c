#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

// Assuming JanetOSRWLock is a structure defined somewhere in the codebase
typedef struct {
    // Dummy fields for the sake of example
    int lock_state;
    int writer_count;
} JanetOSRWLock;

// Function prototype for the function-under-test
void janet_os_rwlock_wunlock(JanetOSRWLock *lock);

int LLVMFuzzerTestOneInput_387(const uint8_t *data, size_t size) {
    // Ensure there's enough data to initialize the lock structure
    if (size < sizeof(JanetOSRWLock)) {
        return 0;
    }

    // Initialize a JanetOSRWLock structure from the input data
    JanetOSRWLock lock;
    lock.lock_state = (int)data[0];
    lock.writer_count = (int)data[1];

    // Call the function-under-test
    janet_os_rwlock_wunlock(&lock);

    return 0;
}