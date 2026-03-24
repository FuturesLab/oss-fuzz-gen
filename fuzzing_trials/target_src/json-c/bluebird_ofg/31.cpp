#include "fuzzer/FuzzedDataProvider.h"
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <cstddef>
#include <cstdint>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_31(const uint8_t *data, size_t size) {
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
  int result = json_object_equal(json_obj1, json_obj2);

  // Clean up

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_object_equal to json_object_new_string_len
  void* ret_json_object_get_userdata_aqbja = json_object_get_userdata(json_obj2);
  if (ret_json_object_get_userdata_aqbja == NULL){
  	return 0;
  }

  struct json_object* ret_json_object_new_string_len_kchcj = json_object_new_string_len((const char *)ret_json_object_get_userdata_aqbja, result);
  if (ret_json_object_new_string_len_kchcj == NULL){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  json_object_put(json_obj1);

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_object_put to json_object_array_add
  struct json_object* ret_json_tokener_parse_gpbum = json_tokener_parse((const char *)"w");
  if (ret_json_tokener_parse_gpbum == NULL){
  	return 0;
  }

  int ret_json_object_array_add_wrnbt = json_object_array_add(ret_json_tokener_parse_gpbum, json_obj2);
  if (ret_json_object_array_add_wrnbt < 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  json_object_put(json_obj2);

  return 0;
}