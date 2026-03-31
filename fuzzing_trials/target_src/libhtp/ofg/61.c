#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/libhtp/htp/htp.h"  // Correct path for the htp.h header
#include "/src/libhtp/htp/bstr.h" // Correct path for the bstr.h header

int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Allocate memory for htp_uri_t structure
    htp_uri_t *uri = (htp_uri_t *)malloc(sizeof(htp_uri_t));
    if (uri == NULL) {
        return 0;
    }

    // Initialize the htp_uri_t structure with bstr values
    uri->scheme = bstr_dup_mem((const char *)data, size);
    uri->username = bstr_dup_mem((const char *)data, size);
    uri->password = bstr_dup_mem((const char *)data, size);
    uri->hostname = bstr_dup_mem((const char *)data, size);
    uri->port = bstr_dup_mem((const char *)data, size);
    uri->path = bstr_dup_mem((const char *)data, size);
    uri->query = bstr_dup_mem((const char *)data, size);
    uri->fragment = bstr_dup_mem((const char *)data, size);

    if (uri->scheme == NULL || uri->username == NULL || uri->password == NULL || 
        uri->hostname == NULL || uri->port == NULL || uri->path == NULL || 
        uri->query == NULL || uri->fragment == NULL) {
        bstr_free(uri->scheme);
        bstr_free(uri->username);
        bstr_free(uri->password);
        bstr_free(uri->hostname);
        bstr_free(uri->port);
        bstr_free(uri->path);
        bstr_free(uri->query);
        bstr_free(uri->fragment);
        free(uri);
        return 0;
    }

    // Call the function-under-test
    htp_uri_free(uri);

    // Free the memory allocated for the uri structure
    bstr_free(uri->scheme);
    bstr_free(uri->username);
    bstr_free(uri->password);
    bstr_free(uri->hostname);
    bstr_free(uri->port);
    bstr_free(uri->path);
    bstr_free(uri->query);
    bstr_free(uri->fragment);
    free(uri);

    return 0;
}