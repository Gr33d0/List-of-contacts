#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include "lib.h"



int main()
{

    Contato agenda[MAX_CONTATOS];
    int numContatos = contador(3);
    int opcao;
    int id = 1; // ID inicial

    setlocale(LC_ALL, "Portuguese");

    do
    {
        printf("============== MENU =============\n");
        printf("1. Criar registro\n");
        printf("2. Consulta sequencial\n");
        printf("3. Listar registros\n");
        printf("4. Buscar contato\n");
        printf("5. Modificar contato\n");
        printf("6. Remover contato\n");
        printf("7. Apagar arquivo de contatos\n");
        printf("8. About\n");
        printf("0. Sair\n");
        printf("=================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado
        switch (opcao)
        {
        case 1:
            limpa();
            criarContato(&numContatos);
            break;
        case 2:
            // passa com enter
            limpa();
            consultaSequencial(&numContatos);
            break;
        case 3:
            // Mostra todos os registos
            limpa();
            listarContatos(&numContatos);
            break;
        case 4:
            limpa();
            buscarContato(&numContatos);
            break;
        case 5:
            limpa();
            modificarContato(&numContatos);
            break;
        case 6:
            limpa();
            removerContato(&numContatos);
            break;
        case 7:
            limpa();
            apagarArquivoContatos("arquivo.txt");
            break;
        case 8:
            limpa();
            about();
            break;
        case 0:
            limpa();
            printf("Saindo...\n");
            break;
        default:
            limpa();
            printf("Opcao invalida! Tente novamente.\n");
            break;
        }
        
    } while (opcao != 0);
    return 0;
}
