#include <fuzzer/FuzzedDataProvider.h>
#include <json-c/json_tokener.h>

extern "C" int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
  // Initialize the FuzzedDataProvider with the input data
  FuzzedDataProvider fuzzed_data(data, size);

  // Consume an integer for the json_tokener_new_ex function
  int depth = fuzzed_data.ConsumeIntegral<int>();

  // Call the function-under-test
  struct json_tokener *tokener = json_tokener_new_ex(depth);

  // Clean up
  if (tokener != nullptr) {
    json_tokener_free(tokener);
  }

  return 0;
}