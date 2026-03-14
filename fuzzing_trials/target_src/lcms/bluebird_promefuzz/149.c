#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "lcms2.h"

static cmsCIExyY GenerateRandomCIExyY(const uint8_t *Data, size_t Size) {
    cmsCIExyY whitePoint;
    if (Size >= sizeof(cmsCIExyY)) {
        memcpy(&whitePoint, Data, sizeof(cmsCIExyY));
    } else {
        whitePoint.x = 0.3127; // Default D65 white point
        whitePoint.y = 0.3290;
        whitePoint.Y = 1.0;
    }
    return whitePoint;
}

static cmsFloat64Number GenerateRandomTemperature(const uint8_t *Data, size_t Size) {
    if (Size >= sizeof(cmsFloat64Number)) {
        cmsFloat64Number temp;
        memcpy(&temp, Data, sizeof(cmsFloat64Number));
        // Ensure temperature is within the valid range
        if (temp < 4000.0) temp = 4000.0;
        if (temp > 25000.0) temp = 25000.0;
        return temp;
    }
    return 6500.0; // Default to D65
}

int LLVMFuzzerTestOneInput_149(const uint8_t *Data, size_t Size) {
    cmsContext context = NULL;
    cmsCIExyY whitePoint = GenerateRandomCIExyY(Data, Size);
    cmsFloat64Number tempK = GenerateRandomTemperature(Data, Size);
    cmsFloat64Number calculatedTempK;
    cmsHPROFILE profile;

    // Test cmsCreateLab4ProfileTHR
    profile = cmsCreateLab4ProfileTHR(context, &whitePoint);
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    // Test cmsCreateLab4Profile
    profile = cmsCreateLab4Profile(&whitePoint);
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    // Test cmsCreateLab2Profile
    profile = cmsCreateLab2Profile(&whitePoint);
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    // Test cmsWhitePointFromTemp
    cmsWhitePointFromTemp(&whitePoint, tempK);

    // Test cmsTempFromWhitePoint
    cmsTempFromWhitePoint(&calculatedTempK, &whitePoint);

    // Test cmsCreateLab2ProfileTHR
    profile = cmsCreateLab2ProfileTHR(context, &whitePoint);
    if (profile != NULL) {
        cmsCloseProfile(profile);
    }

    return 0;
}