#include <stdint.h>
#include <stddef.h>
#include <ucl.h>

// Dummy destructor function
static void dummy_dtor(void *data) {
    // Do nothing
}

// Dummy emitter function
static int dummy_emitter(const ucl_object_t *obj, void *ud) {
    // Do nothing and return success
    return 1;
}

int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Ensure there is some data to use as user data
    if (size == 0) {
        return 0;
    }

    // Use the first byte of data as user data for the sake of this example
    void *user_data = (void *)&data[0];

    // Call the function-under-test
    ucl_object_t *obj = ucl_object_new_userdata(dummy_dtor, dummy_emitter, user_data);

    // Clean up if necessary
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}