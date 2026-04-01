#include <stdint.h>
#include <stdlib.h>
#include <ucl.h>

typedef void (*ucl_userdata_dtor)(void *);

void sample_dtor(void *data) {
    // Sample destructor function
}

const char *sample_emitter(void *data) {
    // Sample emitter function
    return "sample";
}

extern int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    // Initialize variables
    ucl_userdata_dtor dtor = sample_dtor;
    ucl_userdata_emitter emitter = sample_emitter;
    
    // Ensure the data is not NULL
    void *user_data = (void *)data;

    // Call the function-under-test
    ucl_object_t *obj = ucl_object_new_userdata(dtor, emitter, user_data);

    // Clean up if necessary
    if (obj != NULL) {
        ucl_object_unref(obj);
    }

    return 0;
}