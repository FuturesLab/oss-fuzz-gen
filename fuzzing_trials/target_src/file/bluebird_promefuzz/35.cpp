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

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from magic_check to magic_buffer

    const char* ret_magic_buffer_uyifb = magic_buffer(cookie, (const void *)cookie, MAGIC_PARAM_ELF_SHNUM_MAX);
    if (ret_magic_buffer_uyifb == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    const char* ret_magic_error_ftvpu = magic_error(cookie);
    if (ret_magic_error_ftvpu == NULL){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from magic_error to magic_load_buffers
    int ret_magic_getflags_hlhtd = magic_getflags(cookie);
    if (ret_magic_getflags_hlhtd < 0){
    	return 0;
    }
    size_t lzjwjvhl = 64;

    int ret_magic_load_buffers_vuaty = magic_load_buffers(cookie, (void **)&cookie, &lzjwjvhl, MAGIC_PARAM_ELF_NOTES_MAX);
    if (ret_magic_load_buffers_vuaty < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of magic_buffer
    const char* ret_magic_buffer_arvro = magic_buffer(cookie, (const void *)Data, MAGIC_PARAM_MAGWARN_MAX);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from magic_close to magic_load_buffers
    int ret_magic_errno_demnv = magic_errno(cookie);
    if (ret_magic_errno_demnv < 0){
    	return 0;
    }
    int ret_magic_errno_kaflu = magic_errno(cookie);
    if (ret_magic_errno_kaflu < 0){
    	return 0;
    }

    int ret_magic_load_buffers_qkaqg = magic_load_buffers(cookie, (void **)&cookie, (size_t *)&ret_magic_errno_kaflu, MAGIC_PARAM_NAME_MAX);
    if (ret_magic_load_buffers_qkaqg < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    magic_close(cookie);

    return 0;
}