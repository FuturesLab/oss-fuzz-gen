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

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
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
    int version = magic_version();

    // Fuzz magic_getparam
    int param_type = (Size > 0) ? Data[0] : 0;
    size_t param_value;
    magic_getparam(cookie, param_type, &param_value);

    // Fuzz magic_load_buffers
    void *buffers[] = { (void *)Data };
    size_t buffer_sizes[] = { Size };

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 3 of magic_load_buffers

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from magic_getparam to magic_load
    int ret_magic_getflags_siacc = magic_getflags(cookie);
    if (ret_magic_getflags_siacc < 0){
    	return 0;
    }

    int ret_magic_load_kbriu = magic_load(cookie, (const char *)&param_value);
    if (ret_magic_load_kbriu < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from magic_load to magic_getparam
    magic_close(cookie);
    magic_close(cookie);

    int ret_magic_getparam_cevnk = magic_getparam(cookie, ret_magic_load_kbriu, (void *)cookie);
    if (ret_magic_getparam_cevnk < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    magic_load_buffers(cookie, buffers, buffer_sizes, 1);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



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