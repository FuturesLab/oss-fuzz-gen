// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// _cmsWrite15Fixed16Number at cmsplugin.c:337:20 in lcms2_plugin.h
// _cmsWriteUInt64Number at cmsplugin.c:324:20 in lcms2_plugin.h
// _cmsWriteXYZNumber at cmsplugin.c:350:20 in lcms2_plugin.h
// _cmsReadXYZNumber at cmsplugin.c:241:20 in lcms2_plugin.h
// _cmsReadUInt64Number at cmsplugin.c:206:21 in lcms2_plugin.h
// cmsCloseIOhandler at cmsio0.c:510:19 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "lcms2.h"
#include "lcms2_plugin.h"

static cmsUInt32Number DummyRead(struct _cms_io_handler* iohandler, void *Buffer, cmsUInt32Number size, cmsUInt32Number count) {
    return fread(Buffer, size, count, (FILE*)iohandler->stream);
}

static cmsBool DummySeek(struct _cms_io_handler* iohandler, cmsUInt32Number offset) {
    return fseek((FILE*)iohandler->stream, offset, SEEK_SET) == 0;
}

static cmsBool DummyClose(struct _cms_io_handler* iohandler) {
    return fclose((FILE*)iohandler->stream) == 0;
}

static cmsUInt32Number DummyTell(struct _cms_io_handler* iohandler) {
    return (cmsUInt32Number)ftell((FILE*)iohandler->stream);
}

static cmsBool DummyWrite(struct _cms_io_handler* iohandler, cmsUInt32Number size, const void* Buffer) {
    return fwrite(Buffer, size, 1, (FILE*)iohandler->stream) == 1;
}

static cmsIOHANDLER* CreateDummyIOHandler(const char* filePath, const char* mode) {
    cmsIOHANDLER* iohandler = (cmsIOHANDLER*)malloc(sizeof(cmsIOHANDLER));
    if (!iohandler) return NULL;

    FILE* file = fopen(filePath, mode);
    if (!file) {
        free(iohandler);
        return NULL;
    }

    iohandler->stream = file;
    iohandler->Read = DummyRead;
    iohandler->Seek = DummySeek;
    iohandler->Close = DummyClose;
    iohandler->Tell = DummyTell;
    iohandler->Write = DummyWrite;

    return iohandler;
}

int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cmsFloat64Number) + sizeof(cmsUInt64Number) + sizeof(cmsCIEXYZ)) {
        return 0;
    }

    cmsIOHANDLER* iohandler = CreateDummyIOHandler("./dummy_file", "wb+");
    if (!iohandler) {
        return 0;
    }

    cmsFloat64Number floatNumber;
    memcpy(&floatNumber, Data, sizeof(cmsFloat64Number));
    Data += sizeof(cmsFloat64Number);
    Size -= sizeof(cmsFloat64Number);

    cmsUInt64Number uint64Number;
    memcpy(&uint64Number, Data, sizeof(cmsUInt64Number));
    Data += sizeof(cmsUInt64Number);
    Size -= sizeof(cmsUInt64Number);

    cmsCIEXYZ xyzNumber;
    memcpy(&xyzNumber, Data, sizeof(cmsCIEXYZ));

    _cmsWrite15Fixed16Number(iohandler, floatNumber);
    _cmsWriteUInt64Number(iohandler, &uint64Number);
    _cmsWriteXYZNumber(iohandler, &xyzNumber);

    cmsCIEXYZ readXYZNumber;
    _cmsReadXYZNumber(iohandler, &readXYZNumber);

    cmsUInt64Number readUInt64Number;
    _cmsReadUInt64Number(iohandler, &readUInt64Number);

    cmsCloseIOhandler(iohandler);
    free(iohandler);

    return 0;
}