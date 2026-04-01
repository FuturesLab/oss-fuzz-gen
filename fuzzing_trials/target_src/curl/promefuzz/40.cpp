// This fuzz driver is generated for library curl, aiming to fuzz the following functions:
// curl_formadd at formdata.c:609:14 in curl.h
// curl_formget at formdata.c:627:5 in curl.h
// curl_formfree at formdata.c:665:6 in curl.h
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <curl/curl.h>
#include <typecheck-gcc.h>

static size_t formget_callback(void *arg, const char *buf, size_t len) {
    // Dummy callback for curl_formget
    return len;
}

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    struct curl_httppost *formpost = nullptr;
    struct curl_httppost *lastptr = nullptr;

    // Attempt to add a form part using curl_formadd
    CURLFORMcode formadd_result = curl_formadd(&formpost, &lastptr,
                                               CURLFORM_COPYNAME, "name",
                                               CURLFORM_COPYCONTENTS, "value",
                                               CURLFORM_END);

    if (formadd_result == CURL_FORMADD_OK) {
        // Use curl_formget to serialize the form
        curl_formget(formpost, nullptr, formget_callback);
    }

    // Clean up the formpost
    curl_formfree(formpost);

    return 0;
}