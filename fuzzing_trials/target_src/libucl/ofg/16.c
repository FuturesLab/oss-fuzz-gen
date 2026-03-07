#include <stdint.h>
#include <stddef.h>
#include <ucl.h>

// Dummy destructor function
void dummy_dtor(void *data) {
    // Do nothing
}

// Dummy emitter function
void dummy_emitter(void *data) {
    // Do nothing
}

int LLVMFuzzerTestOneInput_16(const uint8_t *data, size_t size) {
    // Ensure that the data is not NULL
    if (data == NULL || size == 0) {
        return 0;
    }

    // Use the first byte of data as a dummy pointer value
    void *user_data = (void *)(uintptr_t)data[0];

    // Call the function-under-test
    ucl_object_t *obj = ucl_object_new_userdata(dummy_dtor, dummy_emitter, user_data);

    // Clean up
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}