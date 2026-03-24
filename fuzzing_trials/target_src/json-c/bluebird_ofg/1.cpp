#include "fuzzer/FuzzedDataProvider.h"
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <sys/stat.h>  // Include this header for fchmod and file permission macros
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include "/src/json-c/json_util.h"  // Include the header file instead of the source file

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    // Initialize the FuzzedDataProvider
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a temporary file to get a valid file descriptor
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Ensure the file is writable
    fchmod(fd, S_IRUSR | S_IWUSR);

    // Consume data to create a json_object
    std::string json_str = fuzzed_data.ConsumeRemainingBytesAsString();
    struct json_object *json_obj = json_tokener_parse(json_str.c_str());

    // If json_obj is NULL, clean up and exit
    if (!json_obj) {
        close(fd);
        return 0;
    }

    // Consume an integer for the flags parameter

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_tokener_parse to json_object_set_userdata
    struct json_object* ret_json_object_new_int_ufqls = json_object_new_int(JSON_C_TO_STRING_PRETTY_TAB);
    if (ret_json_object_new_int_ufqls == NULL){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_object_new_int to json_object_set_serializer
    struct json_object* ret_json_object_from_file_mgsvc = json_object_from_file((const char *)"w");
    if (ret_json_object_from_file_mgsvc == NULL){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of json_object_set_serializer
    json_object_set_serializer(json_obj, NULL, (void *)ret_json_object_new_int_ufqls, NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of json_object_set_userdata
    json_object_set_userdata(ret_json_object_new_int_ufqls, (void *)"r", NULL);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // End mutation: Producer.APPEND_MUTATOR

    int flags = fuzzed_data.ConsumeIntegral<int>();

    // Call the function-under-test
    json_object_to_fd(fd, json_obj, flags);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_object_to_fd to json_object_array_insert_idx
    int64_t ret_json_object_get_int64_juoxq = json_object_get_int64(json_obj);
    if (ret_json_object_get_int64_juoxq < 0){
    	return 0;
    }
    struct json_object* ret_json_object_new_null_ezdyk = json_object_new_null();
    if (ret_json_object_new_null_ezdyk == NULL){
    	return 0;
    }

    int ret_json_object_array_insert_idx_ogivg = json_object_array_insert_idx(json_obj, (size_t )ret_json_object_get_int64_juoxq, ret_json_object_new_null_ezdyk);
    if (ret_json_object_array_insert_idx_ogivg < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    json_object_put(json_obj);
    close(fd);
    unlink(tmpl);

    return 0;
}