#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_330(const uint8_t *data, size_t size) {
    // Initialize variables
    cmsMLU *mlu = cmsMLUalloc(NULL, 1);
    const char *languageCode = "en";
    const char *countryCode = "US";

    // Ensure size is sufficient for at least one wide character
    if (size < sizeof(wchar_t)) {
        cmsMLUfree(mlu);
        return 0;
    }

    // Convert input data to a wide character string
    size_t wcharCount = size / sizeof(wchar_t);
    wchar_t *wideString = (wchar_t *)malloc((wcharCount + 1) * sizeof(wchar_t));

    if (wideString == NULL) {
        cmsMLUfree(mlu);
        return 0;
    }

    for (size_t i = 0; i < wcharCount; i++) {
        wideString[i] = ((wchar_t *)data)[i];
    }
    wideString[wcharCount] = L'\0'; // Null-terminate the wide string

    // Call the function-under-test
    cmsBool result = cmsMLUsetWide(mlu, languageCode, countryCode, wideString);

    // Clean up
    free(wideString);
    cmsMLUfree(mlu);

    return 0;
}