#include "minifilter_communication_lib.h"

#include <fltUser.h>
#include <stdio.h>

#ifdef _DEBUG
#include <strsafe.h>
#define DEBUG_PRINT(fmt, ...) do { \
    wchar_t dbg_msg[512]; \
    StringCchPrintfW(dbg_msg, 512, L"[fltuser_wrapper] " fmt L"\n", __VA_ARGS__); \
    OutputDebugStringW(dbg_msg); \
} while(0)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

long WINAPI filter_connect_communication_port(const wchar_t* port_name, PVOID context, ULONG context_size, HANDLE* port_handle) {
    if (port_name == NULL || port_handle == NULL) {
        DEBUG_PRINT(L"filter_connect_communication_port: Invalid parameter");
        return ERROR_INVALID_PARAMETER;
    }

    long result = FilterConnectCommunicationPort(
        port_name,
        0,
        context,
        context_size,
        NULL,
        port_handle
    );

    DEBUG_PRINT(L"filter_connect_communication_port: port_name=%s, result=0x%08lx", port_name, result);
    return result;
}

long WINAPI filter_send_message(const HANDLE port_handle, void* input_buffer, unsigned long input_buffer_size, void* output_buffer, unsigned long output_buffer_size) {
    if (port_handle == NULL) {
        DEBUG_PRINT(L"filter_send_message: Invalid parameter");
        return ERROR_INVALID_PARAMETER;
    }

    // Handle NULL + 0 input buffer safely
    BYTE dummy_input = 0;
    if (input_buffer == NULL || input_buffer_size == 0) {
        input_buffer = &dummy_input;
        input_buffer_size = 1;
    }

    DWORD bytes_returned = 0;
    long result = FilterSendMessage(
        port_handle,
        input_buffer,
        input_buffer_size,
        output_buffer,
        output_buffer_size,
        &bytes_returned
    );

    DEBUG_PRINT(L"filter_send_message: result=0x%08lx", result);
    return result;
}

long WINAPI filter_get_message(const HANDLE port_handle, void* message_buffer, unsigned long message_buffer_size) {
    if (port_handle == NULL || message_buffer == NULL || message_buffer_size == 0) {
        DEBUG_PRINT(L"filter_get_message: Invalid parameter");
        return ERROR_INVALID_PARAMETER;
    }

    long result = FilterGetMessage(
        port_handle,
        (PFILTER_MESSAGE_HEADER)message_buffer,
        message_buffer_size,
        NULL
    );

    DEBUG_PRINT(L"filter_get_message: result=0x%08lx", result);
    return result;
}

long WINAPI filter_reply_message(const HANDLE port_handle, void* reply_buffer, unsigned long reply_buffer_size) {
    if (port_handle == NULL || reply_buffer == NULL || reply_buffer_size == 0) {
        DEBUG_PRINT(L"filter_reply_message: Invalid parameter");
        return ERROR_INVALID_PARAMETER;
    }

    long result = FilterReplyMessage(
        port_handle,
        (PFILTER_REPLY_HEADER)reply_buffer,
        reply_buffer_size
    );

    DEBUG_PRINT(L"filter_reply_message: result=0x%08lx", result);
    return result;
}

long WINAPI filter_disconnect(HANDLE port_handle) {
    if (port_handle == NULL) {
        DEBUG_PRINT(L"filter_disconnect: Invalid parameter");
        return ERROR_INVALID_PARAMETER;
    }

    BOOL success = CloseHandle(port_handle);
    DWORD lastError = success ? ERROR_SUCCESS : GetLastError();

    DEBUG_PRINT(L"filter_disconnect: success=%d, lastError=0x%08lx", success, lastError);
    return lastError;
}

long WINAPI filter_get_dos_name(const wchar_t* volume_name, void* dos_name, unsigned long dos_name_size) {
    if (volume_name == NULL || dos_name == NULL || dos_name_size == 0) {
        DEBUG_PRINT(L"filter_get_dos_name: Invalid parameter");
        return ERROR_INVALID_PARAMETER;
    }

    long result = FilterGetDosName(
        volume_name,
        dos_name,
        dos_name_size
    );

    DEBUG_PRINT(L"filter_get_dos_name: volume_name=%s, result=0x%08lx", volume_name, result);
    return result;
}