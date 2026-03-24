#include "fuzzer/FuzzedDataProvider.h"
#include "/src/json-c/json_object.h"
#include <stddef.h>
#include <stdint.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
  // Create a FuzzedDataProvider to manage the fuzzing input data
  FuzzedDataProvider fuzzed_data(data, size);

  // Consume a random length string from the fuzzed data for the key
  std::string key = fuzzed_data.ConsumeRandomLengthString();

  // Create a JSON object to work with
  struct json_object *json_obj = json_object_new_object();

  // Add a key-value pair to the JSON object to ensure it is not empty
  json_object_object_add(json_obj, "example_key", json_object_new_string("example_value"));

  // Call the function-under-test with the JSON object and the key
  json_object_object_del(json_obj, key.c_str());

  // Decrement the reference count of the JSON object to free it

  // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from json_object_put to json_object_set_double
  int32_t ret_json_object_get_int_yxnhs = json_object_get_int(json_obj);
  if (ret_json_object_get_int_yxnhs < 0){
  	return 0;
  }

  int ret_json_object_set_double_mrhdm = json_object_set_double(json_obj, (double )ret_json_object_get_int_yxnhs);
  if (ret_json_object_set_double_mrhdm < 0){
  	return 0;
  }

  // End mutation: Producer.APPEND_MUTATOR

  json_object_put(json_obj);

  return 0;
}