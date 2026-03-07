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

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    // Initialize magic_t object
    magic_t cookie = magic_open(MAGIC_NONE);
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
    const char* ret_magic_error_ftvpu = magic_error(cookie);
    if (ret_magic_error_ftvpu == NULL){
    	return 0;
    }

    const char* ret_magic_buffer_arvro = magic_buffer(cookie, (const void *)cookie, MAGIC_PARAM_MAGWARN_MAX);
    if (ret_magic_buffer_arvro == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int err = magic_errno(cookie);

    // Fuzz magic_version

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from magic_errno to magic_buffer
    char ceovvhwj[1024] = "tndiv";


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of magic_buffer
    char wdbwizgw[1024] = "foisg";
    const char* ret_magic_buffer_toodm = magic_buffer(cookie, wdbwizgw, MAGIC_VERSION);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_magic_buffer_toodm == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int version = magic_version();

    // Fuzz magic_getparam
    int param_type = (Size > 0) ? Data[0] : 0;
    size_t param_value;
    magic_getparam(cookie, param_type, &param_value);

    // Fuzz magic_load_buffers
    void *buffers[] = { (void *)Data };
    size_t buffer_sizes[] = { Size };
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