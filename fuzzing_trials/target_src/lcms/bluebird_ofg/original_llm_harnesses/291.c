#include <stdint.h>
#include <stddef.h>
#include <lcms2.h>

int LLVMFuzzerTestOneInput_291(const uint8_t *data, size_t size) {
    // Initialize cmsContext
    cmsContext context = cmsCreateContext(NULL, NULL);

    // Ensure size is sufficient for at least one cmsUInt16Number
    if (size < sizeof(cmsUInt16Number)) {
        cmsDeleteContext(context);
        return 0;
    }

    // Cast data to cmsUInt16Number pointer
    const cmsUInt16Number *alarmCodes = (const cmsUInt16Number *)data;

    // Call the function-under-test
    cmsSetAlarmCodesTHR(context, alarmCodes);

    // Clean up
    cmsDeleteContext(context);

    return 0;
}