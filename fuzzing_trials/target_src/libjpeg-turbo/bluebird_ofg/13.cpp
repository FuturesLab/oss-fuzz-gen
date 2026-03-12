#include <stdint.h>
#include <stddef.h>

extern "C" {
    #include "/src/libjpeg-turbo.main/src/turbojpeg.h"
    #include "/src/libjpeg-turbo.dev/src/turbojpeg.h"
    #include "../src/turbojpeg.h"
}

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function tjInitCompress with tjInitTransform
    tjhandle handle = tjInitTransform();
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    int param1 = 0;
    int param2 = 0;

    if (size >= 2) {
        param1 = data[0];
        param2 = data[1];
    }

    // Call the function-under-test
    tj3Set(handle, param1, param2);

    tjDestroy(handle);
    return 0;
}