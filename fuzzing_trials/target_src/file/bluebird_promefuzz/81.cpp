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

extern "C" int LLVMFuzzerTestOneInput_81(const uint8_t *Data, size_t Size) {
    // Initialize magic_t object

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of magic_open
    magic_t cookie = magic_open(MAGIC_PARAM_REGEX_MAX);
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

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function magic_load with magic_check
    magic_check(cookie, filename);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Fuzz magic_errno

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from magic_check to magic_buffer
    int ret_magic_getflags_afqwb = magic_getflags(cookie);
    if (ret_magic_getflags_afqwb < 0){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of magic_buffer
    const char* ret_magic_buffer_qfefw = magic_buffer(cookie, (const void *)Data, MAGIC_PARAM_MAGWARN_MAX);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_magic_buffer_qfefw == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int err = magic_errno(cookie);

    // Fuzz magic_version
    int version = magic_version();

    // Fuzz magic_getparam
    int param_type = (Size > 0) ? Data[0] : 0;
    size_t param_value;

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of magic_getparam
    magic_getparam(cookie, MAGIC_PARAM_NAME_MAX, &param_value);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Fuzz magic_load_buffers
    void *buffers[] = { (void *)Data };
    size_t buffer_sizes[] = { Size };

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from magic_getparam to magic_check

    int ret_magic_check_ushoi = magic_check(NULL, (const char *)&param_value);
    if (ret_magic_check_ushoi < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    magic_load_buffers(cookie, buffers, buffer_sizes, 1);

    // Fuzz magic_setparam

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from magic_load_buffers to magic_descriptor

    const char* ret_magic_descriptor_slfkm = magic_descriptor(cookie, MAGIC_PARAM_ELF_NOTES_MAX);
    if (ret_magic_descriptor_slfkm == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    magic_setparam(cookie, param_type, &param_value);

    // Cleanup
    magic_close(cookie);

    return 0;
}