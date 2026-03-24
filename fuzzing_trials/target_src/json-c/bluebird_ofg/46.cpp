#include "fuzzer/FuzzedDataProvider.h"
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
  // Initialize FuzzedDataProvider
  FuzzedDataProvider fuzzed_data(data, size);

  // Consume two parts of the input data to create two JSON strings
  std::string json_data1 = fuzzed_data.ConsumeRandomLengthString(size / 2);
  std::string json_data2 = fuzzed_data.ConsumeRemainingBytesAsString();

  // Ensure the JSON data is null-terminated (strings in C++ are already null-terminated)
  
  // Parse the JSON strings into json_object
  json_object *json_obj1 = json_tokener_parse(json_data1.c_str());
  json_object *json_obj2 = json_tokener_parse(json_data2.c_str());

  // If parsing failed, return early
  if (!json_obj1 || !json_obj2) {
    if (json_obj1) {
        json_object_put(json_obj1);
    }
    if (json_obj2) {
        json_object_put(json_obj2);
    }
    return 0;
  }

  // Call the function-under-test

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_tokener_parse to json_object_get_object

  struct lh_table* ret_json_object_get_object_pubnw = json_object_get_object(json_obj2);
  if (ret_json_object_get_object_pubnw == NULL){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  int result = json_object_equal(json_obj1, json_obj2);

  // Clean up

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_object_equal to json_object_new_string_len

  struct json_object* ret_json_object_new_string_len_gnemh = json_object_new_string_len((const char *)"r", result);
  if (ret_json_object_new_string_len_gnemh == NULL){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  json_object_put(json_obj1);
  json_object_put(json_obj2);

  return 0;
}