// This fuzz driver is generated for library lcms, aiming to fuzz the following functions:
// _cmsReadUInt16Number at cmsplugin.c:124:20 in lcms2_plugin.h
// _cmsReadUInt32Number at cmsplugin.c:156:20 in lcms2_plugin.h
// _cmsReadAlignment at cmsplugin.c:445:19 in lcms2_plugin.h
// _cmsWriteAlignment at cmsplugin.c:462:19 in lcms2_plugin.h
// _cmsIOPrintf at cmsplugin.c:482:19 in lcms2_plugin.h
// cmsCloseIOhandler at cmsio0.c:510:19 in lcms2.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "lcms2_plugin.h"
#include "lcms2.h"

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
    return ftell((FILE*)iohandler->stream);
}

static cmsBool DummyWrite(struct _cms_io_handler* iohandler, cmsUInt32Number size, const void* Buffer) {
    return fwrite(Buffer, size, 1, (FILE*)iohandler->stream) == 1;
}

int LLVMFuzzerTestOneInput_92(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    FILE* file = fopen("./dummy_file", "wb+");
    if (!file) return 0;
    fwrite(Data, 1, Size, file);
    rewind(file);

    cmsIOHANDLER iohandler = {
        .stream = file,
        .Read = DummyRead,
        .Seek = DummySeek,
        .Close = DummyClose,
        .Tell = DummyTell,
        .Write = DummyWrite
    };

    cmsUInt16Number uint16;
    cmsUInt32Number uint32;

    _cmsReadUInt16Number(&iohandler, &uint16);
    _cmsReadUInt32Number(&iohandler, &uint32);
    _cmsReadAlignment(&iohandler);
    _cmsWriteAlignment(&iohandler);
    _cmsIOPrintf(&iohandler, "Test, number: %u", uint32);
    cmsCloseIOhandler(&iohandler);

    // Remove the fclose(file) to avoid double-free since cmsCloseIOhandler already closes it.
    return 0;
}