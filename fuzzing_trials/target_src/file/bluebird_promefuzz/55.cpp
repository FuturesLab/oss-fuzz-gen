#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "magic.h"

extern "C" int LLVMFuzzerTestOneInput_55(const uint8_t *Data, size_t Size) {
    // Initialize magic_t object

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of magic_open
    magic_t cookie = magic_open(MAGIC_PARAM_ELF_PHNUM_MAX);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (cookie == NULL) {
        return 0;
    }

    // Prepare a dummy file if necessary
    FILE *dummy_file = fopen("./dummy_file", "wb");
    if (dummy_file != NULL) {
        fwrite(Data, 1, Size, dummy_file);
        fclose(dummy_file);
    }

    // Fuzz magic_load
    const char *filename = Size > 0 ? "./dummy_file" : NULL;
    magic_load(cookie, filename);

    // Fuzz magic_errno
    int err = magic_errno(cookie);

    // Fuzz magic_version
    int version = magic_version();

    // Fuzz magic_getparam
    int param_type = (Size > 0) ? Data[0] : 0;
    size_t param_value;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of magic_getparam
    magic_getparam(cookie, MAGIC_PARAM_INDIR_MAX, &param_value);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Fuzz magic_load_buffers
    void *buffers[] = { (void *)Data };
    size_t buffer_sizes[] = { Size };
    magic_load_buffers(cookie, buffers, buffer_sizes, 1);

    // Fuzz magic_setparam
    magic_setparam(cookie, param_type, &param_value);

    // Cleanup

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from magic_setparam to magic_load_buffers
    int ret_magic_getflags_eonoe = magic_getflags(cookie);
    if (ret_magic_getflags_eonoe < 0){
    	return 0;
    }
    size_t chjhltyv = 0;

    int ret_magic_load_buffers_xqoym = magic_load_buffers(cookie, (void **)&cookie, &chjhltyv, Size);
    if (ret_magic_load_buffers_xqoym < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    magic_close(cookie);

    return 0;
}