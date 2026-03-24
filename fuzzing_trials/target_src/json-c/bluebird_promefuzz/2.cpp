#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "/src/json-c/json_util.h"
#include "/src/json-c/json_object.h"
#include <fcntl.h>
#include <unistd.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>

static void write_to_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    // Step 1: Write data to a dummy file
    write_to_dummy_file(Data, Size);

    // Step 2: Test json_object_from_file
    struct json_object *obj = json_object_from_file("./dummy_file");
    if (obj) {
        // Step 3: Test json_object_to_json_string_length
        size_t length;
        const char *json_str = json_object_to_json_string_length(obj, JSON_C_TO_STRING_PLAIN, &length);

        // Step 4: Test json_object_to_json_string_ext
        const char *json_str_ext = json_object_to_json_string_ext(obj, JSON_C_TO_STRING_PRETTY);

        // Step 5: Test json_object_to_file

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_object_to_json_string_ext to json_object_set_uint64

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of json_object_get_uint64
        uint64_t ret_json_object_get_uint64_dxvbj = json_object_get_uint64(obj);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        if (ret_json_object_get_uint64_dxvbj < 0){
        	return 0;
        }

        int ret_json_object_set_uint64_nzxvi = json_object_set_uint64(obj, ret_json_object_get_uint64_dxvbj);
        if (ret_json_object_set_uint64_nzxvi < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_object_set_uint64 to json_object_get_string_len

        int ret_json_object_get_string_len_wxlwa = json_object_get_string_len(obj);
        if (ret_json_object_get_string_len_wxlwa < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        int result = json_object_to_file("./dummy_file", obj);

        // Step 6: Test json_object_to_fd
        int fd = open("./dummy_file", O_WRONLY | O_CREAT, 0644);
        if (fd != -1) {

            // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of json_object_to_fd
            result = json_object_to_fd(fd, obj, 64);
            // End mutation: Producer.REPLACE_ARG_MUTATOR


            close(fd);
        }

        // Step 7: Test json_object_to_file_ext
        result = json_object_to_file_ext("./dummy_file", obj, JSON_C_TO_STRING_PRETTY);

        // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_object_from_file to json_object_set_userdata
    struct json_object* ret_json_object_new_boolean_yzuro = json_object_new_boolean(0);
    if (ret_json_object_new_boolean_yzuro == NULL){
    	return 0;
    }

    json_object_set_userdata(obj, (void *)ret_json_object_new_boolean_yzuro, NULL);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_object_set_userdata to json_object_object_get_ex
    void* ret_json_object_get_userdata_zytxf = json_object_get_userdata(obj);
    if (ret_json_object_get_userdata_zytxf == NULL){
    	return 0;
    }
    struct json_object* ret_json_object_new_int64_cziuo = json_object_new_int64(Size);
    if (ret_json_object_new_int64_cziuo == NULL){
    	return 0;
    }

    int ret_json_object_object_get_ex_bxmxs = json_object_object_get_ex(obj, (const char *)ret_json_object_get_userdata_zytxf, &ret_json_object_new_int64_cziuo);
    if (ret_json_object_object_get_ex_bxmxs < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

        json_object_put(obj);
    }

    return 0;
}