#include <stdint.h>
#include <ucl.h>

// Dummy destructor function
void dummy_dtor(void *ud) {
    // No operation
}

// Dummy emitter function
void dummy_emitter(void *ud) {
    // No operation
}

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Ensure that the input data is not NULL and has a minimum size
    if (data == NULL || size < sizeof(void *)) {
        return 0;
    }

    // Use a portion of the data as a dummy user data
    void *user_data = (void *)data;

    // Call the function-under-test
    ucl_object_t *obj = ucl_object_new_userdata(dummy_dtor, dummy_emitter, user_data);

    // Clean up if necessary
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}