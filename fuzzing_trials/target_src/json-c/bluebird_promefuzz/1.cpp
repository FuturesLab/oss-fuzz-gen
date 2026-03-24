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

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    // Step 1: Write data to a dummy file
    write_to_dummy_file(Data, Size);

    // Step 2: Test json_object_from_file
    struct json_object *obj = json_object_from_file("./dummy_file");
    if (obj) {
        // Step 3: Test json_object_to_json_string_length
        size_t length;
        const char *json_str = json_object_to_json_string_length(obj, JSON_C_TO_STRING_PLAIN, &length);

        // Step 4: Test json_object_to_json_string_ext

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_object_to_json_string_length to json_object_double_to_json_string
        struct printbuf qrivridm;
        memset(&qrivridm, 0, sizeof(qrivridm));

        int ret_json_object_double_to_json_string_rxxjk = json_object_double_to_json_string(obj, &qrivridm, JSON_OBJECT_DEF_HASH_ENTRIES, 1);
        if (ret_json_object_double_to_json_string_rxxjk < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        const char *json_str_ext = json_object_to_json_string_ext(obj, JSON_C_TO_STRING_PRETTY);

        // Step 5: Test json_object_to_file
        int result = json_object_to_file("./dummy_file", obj);

        // Step 6: Test json_object_to_fd

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_object_to_file to json_object_array_insert_idx
        struct json_object* ret_json_object_new_array_ext_mnihs = json_object_new_array_ext(JSON_C_OPTION_THREAD);
        if (ret_json_object_new_array_ext_mnihs == NULL){
        	return 0;
        }
        struct json_object* ret_json_object_get_amobz = json_object_get(obj);
        if (ret_json_object_get_amobz == NULL){
        	return 0;
        }


        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_object_get to json_object_set_boolean
        json_bool ret_json_object_get_boolean_hmcei = json_object_get_boolean(NULL);

        int ret_json_object_set_boolean_ezzkl = json_object_set_boolean(obj, ret_json_object_get_boolean_hmcei);
        if (ret_json_object_set_boolean_ezzkl < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        int ret_json_object_array_insert_idx_aydwt = json_object_array_insert_idx(ret_json_object_new_array_ext_mnihs, (size_t )result, ret_json_object_get_amobz);
        if (ret_json_object_array_insert_idx_aydwt < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        int fd = open("./dummy_file", O_WRONLY | O_CREAT, 0644);
        if (fd != -1) {
            result = json_object_to_fd(fd, obj, JSON_C_TO_STRING_PLAIN);
            close(fd);
        }

        // Step 7: Test json_object_to_file_ext
        result = json_object_to_file_ext("./dummy_file", obj, JSON_C_TO_STRING_PRETTY);

        // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_object_from_file to json_object_set_int
    int64_t ret_json_object_get_int64_nekgb = json_object_get_int64(obj);
    if (ret_json_object_get_int64_nekgb < 0){
    	return 0;
    }

    int ret_json_object_set_int_pquiw = json_object_set_int(obj, (int )ret_json_object_get_int64_nekgb);
    if (ret_json_object_set_int_pquiw < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

        json_object_put(obj);
    }

    return 0;
}