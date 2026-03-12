#include <stdint.h>
#include <stdlib.h>
#include "lcms2.h"

// Include the header where cmsPluginBase is defined
#include "/src/lcms/include/lcms2_plugin.h"

int LLVMFuzzerTestOneInput_164(const uint8_t *data, size_t size) {
    cmsContext context;
    cmsPluginBase *pluginData;

    // Initialize context to non-NULL value
    context = cmsCreateContext(NULL, NULL);
    if (context == NULL) {
        return 0;
    }

    // Ensure that the size is sufficient for a cmsPluginBase structure
    if (size < sizeof(cmsPluginBase)) {
        cmsDeleteContext(context);
        return 0;
    }

    // Interpret the input data as a cmsPluginBase structure
    pluginData = (cmsPluginBase *)data;

    // Call the function-under-test
    cmsBool result = cmsPluginTHR(context, pluginData);

    // Clean up the context
    cmsDeleteContext(context);

    return 0;
}