#ifndef FUNCS_Y
#define FUNCS_Y

#define STDCALL __stdcall
#include <winsock2.h>


NTSTATUS            (STDCALL    *LoadDllFunc)       (PWSTR, PULONG, PUNICODE_STRING, PVOID);
int                 (STDCALL    *WSAStartupFunc)    (WORD, LPWSADATA);
unsigned long long  (STDCALL    *WSASocketFunc)     (int, int, int, LPWSAPROTOCOL_INFOW, GROUP, DWORD);
int                 (STDCALL    *WSAConnectFunc)    (SOCKET,const struct sockaddr*,int,LPWSABUF,LPWSABUF,LPQOS,LPQOS);
int                 (STDCALL    *CreateProcFunc)    (LPCWSTR, LPWSTR, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES, BOOL, DWORD, LPVOID, LPCWSTR, LPSTARTUPINFOW, LPPROCESS_INFORMATION);

#endif