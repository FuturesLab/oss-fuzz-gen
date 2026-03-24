#include "fuzzer/FuzzedDataProvider.h"
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <stddef.h>
#include <stdint.h>

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    FuzzedDataProvider fuzzed_data(data, size);

    // Create a source json_object from the fuzzed data
    std::string json_string = fuzzed_data.ConsumeRandomLengthString(fuzzed_data.remaining_bytes());
    struct json_object *src = json_tokener_parse(json_string.c_str());

    // Prepare a destination json_object pointer
    struct json_object *dst = nullptr;

    // Define a shallow copy function pointer, set to nullptr for default behavior
    json_c_shallow_copy_fn *shallow_copy_fn = nullptr;

    // Call the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_tokener_parse to json_object_set_int64
    uint64_t ret_json_object_get_uint64_tdijy = json_object_get_uint64(src);
    if (ret_json_object_get_uint64_tdijy < 0){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_object_get_uint64 to json_object_set_string_len
    struct json_object* ret_json_object_new_uint64_nftcd = json_object_new_uint64(64);
    if (ret_json_object_new_uint64_nftcd == NULL){
    	return 0;
    }
    const char cbhpxuze[1024] = "bqrya";

    int ret_json_object_set_string_len_ppige = json_object_set_string_len(ret_json_object_new_uint64_nftcd, cbhpxuze, (int )ret_json_object_get_uint64_tdijy);
    if (ret_json_object_set_string_len_ppige < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_json_object_set_int64_uvsjp = json_object_set_int64(src, (int64_t )ret_json_object_get_uint64_tdijy);
    if (ret_json_object_set_int64_uvsjp < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    json_object_deep_copy(src, &dst, shallow_copy_fn);

    // Clean up
    if (src) {
        json_object_put(src);
    }
    if (dst) {
        json_object_put(dst);
    }

    return 0;
}