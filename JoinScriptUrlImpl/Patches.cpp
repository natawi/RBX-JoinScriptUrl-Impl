#include "pch.h"
#include "Patches.h"

#include <detours.h>

#ifdef _DEBUG
static std::runtime_error patchError(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    int size = vsnprintf(nullptr, 0, format, args) + 1;

    std::string buffer;
    buffer.resize(size);

    vsnprintf(&buffer[0], size, format, args);

    va_end(args);

    return std::runtime_error(buffer);
}
#else
#define patchError(x, ...) std::runtime_error("")
#endif

void Patches::Apply()
{
    LONG error = DetourTransactionBegin();
    if (error != NO_ERROR)
        throw patchError("DetourTransactionBegin returned %d", error);

    for (Patch patch : patchList)
    {
        error = DetourAttach(patch.toHookPointer, patch.hookFunction);
        if (error != NO_ERROR)
            throw patchError("Couldn't patch function at 0x%p! DetourAttach returned %d", *patch.toHookPointer, error);
    }

    error = DetourTransactionCommit();
    if (error != NO_ERROR)
        throw patchError("DetourTransactionCommit returned %d", error);
}
