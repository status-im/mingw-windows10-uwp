#include "pureDLL.h"

void forceLinkingByMethodReferencing() { GetConstantInt32FromDLL(); }

int main() {}

// Workaround to redefine functions forbidden on UWP platform
#define _WIN32_WINNT 0x501 /* Redefined functions are available from Windows XP+ */

#define RtlAddFunctionTable __RtlAddFunctionTable
#define RtlCaptureContext __RtlCaptureContext
#define RtlVirtualUnwind __RtlVirtualUnwind

#include <windef.h>
#include <winbase.h>

#undef RtlAddFunctionTable
#undef RtlCaptureContext
#undef RtlVirtualUnwind

BOOLEAN WINAPI RtlAddFunctionTable(PRUNTIME_FUNCTION FunctionTable,
                                   DWORD EntryCount, DWORD64 BaseAddress,
                                   ULONGLONG TargetGp) {
  return 1;
}

VOID WINAPI RtlCaptureContext(PCONTEXT ContextRecord) {}

PEXCEPTION_ROUTINE WINAPI RtlVirtualUnwind(HandlerType, ImageBase, ControlPC,
                                           FunctionEntry, ContextRecord,
                                           InFunction, EstablisherFrame,
                                           ContextPointers) {}

#ifdef _X86_
LPTOP_LEVEL_EXCEPTION_FILTER(WINAPI *__MINGW_IMP_SYMBOL(RtlAddFunctionTable))
(PRUNTIME_FUNCTION, DWORD, DWORD64,
 ULONGLONG) asm("__imp__RtlAddFunctionTable@4") = RtlAddFunctionTable;
#else
LPTOP_LEVEL_EXCEPTION_FILTER(WINAPI *__MINGW_IMP_SYMBOL(RtlAddFunctionTable))
(PRUNTIME_FUNCTION, DWORD, DWORD64,
 ULONGLONG) asm("__imp_RtlAddFunctionTable") = RtlAddFunctionTable;
#endif

#ifdef _X86_
LPTOP_LEVEL_EXCEPTION_FILTER(WINAPI *__MINGW_IMP_SYMBOL(RtlCaptureContext))
(PCONTEXT) asm("__imp__RtlCaptureContext@4") = RtlCaptureContext;
#else
LPTOP_LEVEL_EXCEPTION_FILTER(WINAPI *__MINGW_IMP_SYMBOL(RtlCaptureContext))
(PCONTEXT) asm("__imp_RtlCaptureContext") = RtlCaptureContext;
#endif

#ifdef _X86_
LPTOP_LEVEL_EXCEPTION_FILTER(WINAPI *__MINGW_IMP_SYMBOL(RtlVirtualUnwind))
(HandlerType, ImageBase, ControlPC, FunctionEntry, ContextRecord, InFunction,
 EstablisherFrame,
 ContextPointers) asm("__imp__RtlVirtualUnwind@4") = RtlVirtualUnwind;
#else
LPTOP_LEVEL_EXCEPTION_FILTER(WINAPI *__MINGW_IMP_SYMBOL(RtlVirtualUnwind))
(HandlerType, ImageBase, ControlPC, FunctionEntry, ContextRecord, InFunction,
 EstablisherFrame,
 ContextPointers) asm("__imp_RtlVirtualUnwind") = RtlVirtualUnwind;
#endif