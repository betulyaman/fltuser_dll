#include "fltuser_wrapper.h"

#include <fltUser.h>
#include <stdio.h>

long filter_connect_communication_port(HANDLE* port_handle, const wchar_t* port_name) {
    if (port_handle == NULL || *port_handle == NULL || port_name == NULL) {
        return ERROR_INVALID_PARAMETER;
    }
    long hresult = FilterConnectCommunicationPort(
        port_name,
        0,
        NULL,
        0,
        NULL,
        port_handle
    );
    return hresult;
}

long filter_send_message(const HANDLE port_handle, void* input_buffer, unsigned long input_buffer_size) {
    if (port_handle == NULL || input_buffer == NULL || input_buffer_size == 0) {
        return ERROR_INVALID_PARAMETER;
    }

    DWORD bytes_returned = 0;
    long hresult = FilterSendMessage(
        port_handle,
        input_buffer,
        input_buffer_size,
        NULL,
        0,
        &bytes_returned
    );

    return hresult;
}

long filter_get_message(const HANDLE port_handle, const void* message_buffer, unsigned long message_buffer_size) {
    if (port_handle == NULL || message_buffer == NULL || message_buffer_size == 0) {
        return ERROR_INVALID_PARAMETER;
    }

    return FilterGetMessage(port_handle, (PFILTER_MESSAGE_HEADER) message_buffer, message_buffer_size, NULL);
    
}

long filter_reply_message(const HANDLE port_handle, void* reply_buffer, unsigned long reply_buffer_size) {
    if (port_handle == NULL || reply_buffer == NULL || reply_buffer_size == 0) {
        return ERROR_INVALID_PARAMETER;
    }

    return FilterReplyMessage(port_handle, (PFILTER_REPLY_HEADER)reply_buffer, reply_buffer_size);
}

long filter_disconnect(HANDLE port_handle) {
    if (port_handle) {
        CloseHandle(port_handle);
        port_handle = INVALID_HANDLE_VALUE;
    }
}
