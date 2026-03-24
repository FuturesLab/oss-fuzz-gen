#include "fuzzer/FuzzedDataProvider.h"
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
  // Initialize FuzzedDataProvider
  FuzzedDataProvider fuzzed_data(data, size);

  // Consume two parts of the input data to create two JSON strings
  std::string json_data1 = fuzzed_data.ConsumeRandomLengthString(size / 2);
  std::string json_data2 = fuzzed_data.ConsumeRemainingBytesAsString();

  // Ensure the JSON data is null-terminated (strings in C++ are already null-terminated)
  
  // Parse the JSON strings into json_object
  json_object *json_obj1 = json_tokener_parse(json_data1.c_str());

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_tokener_parse to json_object_to_json_string


  // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function json_object_to_json_string with json_object_get_string
  const char* ret_json_object_to_json_string_lyrwu = json_object_get_string(json_obj1);
  // End mutation: Producer.REPLACE_FUNC_MUTATOR


  if (ret_json_object_to_json_string_lyrwu == NULL){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

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
  int result = json_object_equal(json_obj1, json_obj2);

  // Clean up
  json_object_put(json_obj1);
  json_object_put(json_obj2);

  return 0;
}