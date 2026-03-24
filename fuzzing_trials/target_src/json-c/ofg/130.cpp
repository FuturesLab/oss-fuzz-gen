#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <stddef.h>
#include <stdint.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
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
  json_object_put(json_obj);

  return 0;
}