#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "/src/janet/src/include/janet.h"

// Dummy callback function for JanetCallback
void dummy_callback(JanetEVGenericMessage message) {
    // Do nothing
}

int LLVMFuzzerTestOneInput_93(const uint8_t *data, size_t size) {
    // Initialize Janet
    janet_init();

    // Create a dummy JanetCallback
    JanetCallback callback = dummy_callback;

    // Create a JanetEVGenericMessage from the input data
    JanetEVGenericMessage message;
    if (size >= sizeof(JanetEVGenericMessage)) {
        message = *(JanetEVGenericMessage *)data;
    } else {
        // If the size is not sufficient, fill the message with zeros
        message = (JanetEVGenericMessage){0};
    }

    // Call the function-under-test
    janet_ev_post_event(NULL, callback, message);

    // Clean up
    janet_deinit();

    return 0;
}