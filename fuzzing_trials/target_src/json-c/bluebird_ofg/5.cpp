#include "fuzzer/FuzzedDataProvider.h"
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <sys/stat.h>  // Include this header for fchmod and file permission macros
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include "/src/json-c/json_util.h"  // Include the header file instead of the source file

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_tokener_parse to json_object_set_uint64
    int32_t ret_json_object_get_int_xazjq = json_object_get_int(NULL);
    if (ret_json_object_get_int_xazjq < 0){
    	return 0;
    }

    int ret_json_object_set_uint64_aglnm = json_object_set_uint64(json_obj, (uint64_t )ret_json_object_get_int_xazjq);
    if (ret_json_object_set_uint64_aglnm < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int flags = fuzzed_data.ConsumeIntegral<int>();

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 2 of json_object_to_fd
    json_object_to_fd(fd, json_obj, size);
    // End mutation: Producer.REPLACE_ARG_MUTATOR



    // Clean up
    json_object_put(json_obj);
    close(fd);
    unlink(tmpl);

    return 0;
}