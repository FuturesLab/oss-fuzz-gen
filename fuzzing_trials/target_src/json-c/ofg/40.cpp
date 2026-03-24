#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include <stddef.h>
#include <stdint.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  // Create a json_object
  struct json_object *json_obj1 = json_object_new_object();
  struct json_object *json_obj2 = json_object_new_object();

  // Consume a string for the key
  std::string key = fuzzed_data.ConsumeRandomLengthString();
  const char *key_cstr = key.c_str();

  // Consume a string for the value and convert it to a json_object
  std::string value_str = fuzzed_data.ConsumeRandomLengthString();
  struct json_object *value_obj = json_object_new_string(value_str.c_str());

  // Call the function-under-test
  json_object_object_add(json_obj1, key_cstr, value_obj);

  // Clean up
  json_object_put(json_obj1);
  json_object_put(json_obj2);

  return 0;
}