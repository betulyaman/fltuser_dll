# fltuser_wrapper

This is a wrapper for the functions needed for communication between User and Minifilter.  

The following support routines are provided for communication initiated by a user operation:
- `long WINAPI filter_connect_communication_port(const wchar_t* port_name, PVOID context, ULONG context_size, HANDLE* port_handle)` ([FilterConnectCommunicationPort](https://learn.microsoft.com/en-us/windows/win32/api/fltuser/nf-fltuser-filterconnectcommunicationport))
- `long filter_send_message(const HANDLE port_handle, void* input_buffer, unsigned long input_buffer_size, void* output_buffer, unsigned long output_buffer_size)` ([FilterSendMessage](https://learn.microsoft.com/en-us/windows/win32/api/fltuser/nf-fltuser-filtersendmessage))
- `long filter_disconnect(HANDLE port_handle)`

The following support routines are provided for responding to communication initiated by a minifilter driver:
- `long filter_get_message(const HANDLE, const void*, unsigned long)` ([FilterGetMessage](https://learn.microsoft.com/en-us/windows/win32/api/fltuser/nf-fltuser-filtergetmessage))
- `long filter_reply_message(const HANDLE, void*, unsigned long)` ([FilterReplyMessage](https://learn.microsoft.com/en-us/windows/win32/api/fltuser/nf-fltuser-filterreplymessage))
- `long filter_get_dos_name(const wchar_t*, void*, unsigned long)` ([FilterGetDosName](https://learn.microsoft.com/en-us/windows/win32/api/fltuser/nf-fltuser-filtergetdosname))
