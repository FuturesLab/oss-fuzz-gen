#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcms2.h"

static void FuzzCmsFreeNamedColorList(cmsNAMEDCOLORLIST* list) {
    cmsFreeNamedColorList(list);
}

static cmsNAMEDCOLORLIST* FuzzCmsAllocNamedColorList(cmsContext ContextID, cmsUInt32Number n, cmsUInt32Number ColorantCount, const char* Prefix, const char* Suffix) {
    return cmsAllocNamedColorList(ContextID, n, ColorantCount, Prefix, Suffix);
}

static cmsBool FuzzCmsNamedColorInfo(const cmsNAMEDCOLORLIST* NamedColorList, cmsUInt32Number nColor, char* Name, char* Prefix, char* Suffix, cmsUInt16Number* PCS, cmsUInt16Number* Colorant) {
    return cmsNamedColorInfo(NamedColorList, nColor, Name, Prefix, Suffix, PCS, Colorant);
}

static cmsNAMEDCOLORLIST* FuzzCmsDupNamedColorList(const cmsNAMEDCOLORLIST* list) {
    return cmsDupNamedColorList(list);
}

static cmsUInt32Number FuzzCmsNamedColorCount(const cmsNAMEDCOLORLIST* list) {
    return cmsNamedColorCount(list);
}

int LLVMFuzzerTestOneInput_146(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize context and named color list
    cmsContext context = NULL;  // Simplified, normally would be a valid context
    cmsNAMEDCOLORLIST* list = FuzzCmsAllocNamedColorList(context, Size % 256, Size % 10, "Prefix", "Suffix");
    
    if (list != NULL) {
        // Use cmsNamedColorCount
        FuzzCmsNamedColorCount(list);

        // Use cmsNamedColorInfo
        char Name[100], Prefix[33], Suffix[33];
        cmsUInt16Number PCS[3], Colorant[10];
        FuzzCmsNamedColorInfo(list, 0, Name, Prefix, Suffix, PCS, Colorant);

        // Duplicate the list
        cmsNAMEDCOLORLIST* dupList = FuzzCmsDupNamedColorList(list);
        FuzzCmsFreeNamedColorList(dupList); // Free duplicated list
    }

    // Free the original list
    FuzzCmsFreeNamedColorList(list);

    return 0;
}