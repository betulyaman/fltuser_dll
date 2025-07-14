#ifndef MINIFILTER_COMMUNICATION_LIB_H
#define MINIFILTER_COMMUNICATION_LIB_H

#include <Windows.h>

#ifdef __cplusplus
extern "C" {
#endif

    __declspec(dllexport) 
        long WINAPI filter_connect_communication_port(
            const wchar_t* port_name,
            PVOID context,
            ULONG context_size,
            HANDLE* port_handle
        );

    __declspec(dllexport)
        long WINAPI filter_send_message(
            HANDLE port_handle,
            void* input_buffer,
            unsigned long input_buffer_size,
            void* output_buffer,
            unsigned long output_buffer_size
        );

    __declspec(dllexport)
        long WINAPI filter_get_message(
            HANDLE port_handle,
            void* message_buffer,
            unsigned long message_buffer_size
        );

    __declspec(dllexport) 
        long WINAPI filter_reply_message(
            HANDLE port_handle, 
            void* reply_buffer, 
            unsigned long reply_buffer_size
        );

    __declspec(dllexport)
        long WINAPI filter_get_dos_name(
            const wchar_t* volume_name,
            wchar_t* dos_name,
            unsigned long dos_name_size
        );

#ifdef __cplusplus
}
#endif

#endif // MINIFILTER_COMMUNICATION_LIB_H
