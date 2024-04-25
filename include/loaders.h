#ifndef LOAD_Y
#define LOAD_Y


void *GetDllAddress(unsigned long DllHash);
void *GetFuncPtr(void *DllAddress, unsigned long Func);


#endif