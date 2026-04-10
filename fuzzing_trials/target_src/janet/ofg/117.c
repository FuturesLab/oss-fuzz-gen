#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

// Define the JanetOSRWLock structure as required by the function
typedef struct {
    // Placeholder for the actual structure fields
    int dummy_field;
} JanetOSRWLock;

// Function signature from the task
void janet_os_rwlock_init(JanetOSRWLock *);

// Fuzzing harness
int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    if (size < sizeof(JanetOSRWLock)) {
        return 0; // Not enough data to initialize the structure
    }

    // Allocate memory for the JanetOSRWLock structure
    JanetOSRWLock *lock = (JanetOSRWLock *)malloc(sizeof(JanetOSRWLock));
    if (lock == NULL) {
        return 0; // Memory allocation failed
    }

    // Use the input data to initialize the lock
    memcpy(lock, data, sizeof(JanetOSRWLock));

    // Call the function-under-test
    janet_os_rwlock_init(lock);

    // Free the allocated memory
    free(lock);

    return 0;
}