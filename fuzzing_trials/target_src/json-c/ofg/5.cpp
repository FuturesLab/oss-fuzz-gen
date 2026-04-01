#include <fuzzer/FuzzedDataProvider.h>
#include "/src/json-c/json_object.h"
#include "/src/json-c/json_tokener.h"
#include <stddef.h>
#include <stdint.h>
#include <string>

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
  // Initialize FuzzedDataProvider
  FuzzedDataProvider fuzzed_data(data, size);

  // Create a json_tokener object
  struct json_tokener *tok = json_tokener_new();
  if (tok == nullptr) {
    return 0; // Exit if tokener creation fails
  }

  // Consume a string from the fuzzed data
  std::string json_string = fuzzed_data.ConsumeRemainingBytesAsString();

  // Parse the JSON string
  struct json_object *parsed_obj = json_tokener_parse_ex(tok, json_string.c_str(), json_string.size());

  // Free the parsed JSON object if not null
  if (parsed_obj != nullptr) {
    json_object_put(parsed_obj);
  }

  // Free the json_tokener object
  json_tokener_free(tok);

  return 0;
}