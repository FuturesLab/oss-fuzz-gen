#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Dummy comparison function for json_object_array_bsearch
int dummy_compare(const void *a, const void *b) {
  return 0; // Always returns 0 for simplicity
}

extern "C" int LLVMFuzzerTestOneInput_38(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  // Create JSON objects from fuzzed data
  std::string json_str1 = fuzzed_data.ConsumeRandomLengthString();
  std::string json_str2 = fuzzed_data.ConsumeRandomLengthString();

  struct json_object *json_obj1 = json_tokener_parse(json_str1.c_str());
  struct json_object *json_obj2 = json_tokener_parse(json_str2.c_str());

  if (json_obj1 == nullptr || json_obj2 == nullptr) {
    // Clean up and exit if JSON parsing failed
    if (json_obj1) json_object_put(json_obj1);
    if (json_obj2) json_object_put(json_obj2);
    return 0;
  }

  // Call the function-under-test
  struct json_object *result = json_object_array_bsearch(json_obj1, json_obj2, dummy_compare);

  // Clean up
  json_object_put(json_obj1);
  json_object_put(json_obj2);
  if (result) json_object_put(result);

  return 0;
}