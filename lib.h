#define MAX_CONTATOS 100

#define BACKSPACE 8
#define ENTER 13
#define SPACE 32

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define Contato404 printf(ANSI_COLOR_RED "Contato não encontrado.\n" ANSI_COLOR_RESET);
#define ErroArquivo printf(ANSI_COLOR_RED "Erro ao abrir o arquivo.\n" ANSI_COLOR_RESET);

typedef struct
{
    char nome[21];
    char telefone[11];
    char morada[31];
    char codigo_postal[11];
    char cidade[21];
    char pais[21];
} Contato;

void limpa()
{
    system("cls");
}
// conta o numero de contatos
int contador(int booleano)
{
    int contador = 0;

    // Abrir o arquivo para leitura e escrita
    FILE *arquivo = fopen("contador.txt", "r+");

    // Verificar se o arquivo foi aberto corretamente
    if (arquivo == NULL)
    {
        ErroArquivo;
        return 1;
    }

    // Ler o valor atual do contador a partir do arquivo
    fscanf(arquivo, "%d", &contador);

    if (booleano == 0)
    {
        // Incrementar o contador
        contador++;
    }
    else if (booleano == 1)
    {
        contador--;
    }

    // Posicionar o cursor de arquivo no início
    fseek(arquivo, 0, SEEK_SET);

    // Escrever o novo valor do contador no arquivo
    fprintf(arquivo, "%d", contador);

    // Fechar o arquivo
    fclose(arquivo);

    // Exibir o valor atual do contador
    // printf("Valor atual do contador: %d\n", contador);
    return contador;
}
// Falta retornar o texto ver chat gpt com a correcao
void verifica_tipo(int tipo, int posicao, char texto[], int npc)
{
    char vazio = '\0';
    int letra;

    switch (tipo)
    {
    case 1:
        // Nome e cidade e pais
        while (letra != ENTER) // enter
        {
            letra = getche();
            limpa();

            // verifica_tipo(1,input) //Nome
            if (letra >= 65 && letra <= 90 && posicao < 21 || letra >= 97 && letra <= 122 && posicao < 21 || letra == SPACE)
            {
                if (posicao == 0 && letra >= 65 && letra <= 90)
                {
                    // adicionar ao array
                    texto[posicao] = letra;
                    posicao += 1;
                }
                else if (posicao > 0 && letra >= 97 && letra <= 122 || posicao > 0 && letra == SPACE)
                {
                    texto[posicao] = letra;
                    posicao += 1;
                }
                else
                {
                    texto[posicao] = vazio;
                }
            }
            // backspace
            else if (letra == BACKSPACE)
            {
                if (posicao == 0)
                {
                    texto[posicao] = vazio;
                }
                else
                {
                    posicao -= 1;
                    texto[posicao] = vazio;
                }
            }
            // Nao é uma letra maiuscula
            else
            {
                texto[posicao] = vazio;
            }

            switch (npc)
            {
            case 1:
                printf("\nNome: %s", texto);
                break;
            case 2:
                printf("\nCidade: %s", texto);
                break;
            case 3:
                printf("\nPais: %s", texto);
                break;

            default:
                break;
            }
        }

        break;
    case 2:
        // telefone
        while (letra != ENTER) // enter
        {
            letra = getche();
            limpa();
            // Verifica se é um numero inteiro
            if (letra >= 48 && letra <= 57 && posicao < 9)
            {
                // adicionar ao array
                texto[posicao] = letra;
                posicao += 1;
            }
            // backspace
            else if (letra == BACKSPACE)
            {
                if (posicao == 0)
                {
                    texto[posicao] = vazio;
                }
                else
                {
                    posicao -= 1;
                    texto[posicao] = vazio;
                }
            }

            // Nao é um numero inteiro
            else
            {
                texto[posicao] = vazio;
            }

            printf("\nTelefone: %s", texto);
        }
        break;
    case 3:
        // morada
        while (letra != ENTER) // enter
        {
            letra = getche();
            // printf("pos = %d",posicao);
            limpa();
            // backspace
            if (letra == BACKSPACE)
            {
                if (posicao == 0)
                {
                    texto[posicao] = vazio;
                }
                else
                {
                    posicao -= 1;
                    texto[posicao] = vazio;
                }
            }
            else if (posicao < 31)
            {
                // adicionar ao array
                texto[posicao] = letra;
                posicao += 1;
            }

            // Nao é um numero inteiro
            else
            {
                texto[posicao] = vazio;
            }

            printf("\nMorada: %s", texto);
        }

        break;
    case 4:
        // codigo_postal
        while (letra != ENTER) // enter
        {
            letra = getche();
            limpa();
            // verifica_tipo(5,input) //Verifica se é um numero inteiro
            if (letra >= 48 && letra <= 57 && posicao < 8)
            {
                if (posicao == 4)
                {
                    // adicionar ao array
                    texto[posicao] = '-';
                    posicao += 1;
                }
                else
                {
                    // adicionar ao array
                    texto[posicao] = letra;
                    posicao += 1;
                }
            }
            // backspace
            else if (letra == BACKSPACE)
            {
                if (posicao == 0)
                {
                    texto[posicao] = vazio;
                }
                else
                {
                    posicao -= 1;
                    texto[posicao] = vazio;
                }
            }

            // Nao é um numero inteiro
            else
            {
                texto[posicao] = vazio;
            }
            limpa();
            printf("\nCodigo Postal: %s", texto);
        }
        break;
    default:
        printf(ANSI_COLOR_RED "\nERRO! FUNCAO MAL DEFINIDA" ANSI_COLOR_RESET);
        break;
    }
    printf("\n");
}

// Criar os registos
void criarContato(int *numContatos)
{
    FILE *arquivo;
    Contato contato;

    // Abrir o arquivo para escrita no modo "append" (acrescentar ao final)
    arquivo = fopen("contacts.dat", "ab");
    // Verifica se ainda á espaço para novos contatos
    if (*numContatos == MAX_CONTATOS)
    {
        printf(ANSI_COLOR_RED "A agenda está cheia. Impossível adicionar mais contatos.\n" ANSI_COLOR_RESET);
        return;
    }
    // Verifica se o ficheiro existe
    if (arquivo == NULL)
    {
        arquivo = fopen("contacts.dat", "w");
        return;
    }

    // Pedir ao utilizador os dados
    printf("=======================\n");
    printf("Criando novo registro: \n");

    // Ler os dados do contato
    printf("Nome: ");
    verifica_tipo(1, 0, contato.nome, 1);
    printf("\n");
    // scanf("%s", contato.nome);
    printf("Telefone: ");
    verifica_tipo(2, 0, contato.telefone, 0);
    printf("\n");
    // scanf("%s", contato.telefone);
    printf("Morada: ");
    verifica_tipo(3, 0, contato.morada, 0);
    printf("\n");
    // scanf("%s", contato.morada);
    printf("Código Postal: ");
    verifica_tipo(4, 0, contato.codigo_postal, 0);
    printf("\n");
    // scanf("%s", contato.codigo_postal);
    printf("Cidade: ");
    verifica_tipo(1, 0, contato.cidade, 2);
    printf("\n");
    // scanf("%s", contato.cidade);
    printf("País: ");
    verifica_tipo(1, 0, contato.pais, 3);
    if (strlen(contato.pais) == 0)
    {

        strcpy(contato.pais, "Portugal");
    }
    printf("\n");
    // scanf("%s", contato.pais);

    // Escrever a frase no arquivo
    fwrite(&contato, sizeof(Contato), 1, arquivo);
    contador(0);
    fclose(arquivo);
}
// Mostra Todos os contatos de maneira sequencial
void consultaSequencial(int *numContatos)
{
    FILE *arquivo;
    Contato contato;

    // Abrir o arquivo para leitura
    arquivo = fopen("contacts.dat", "r");

    // Verificar se o arquivo foi aberto corretamente
    if (arquivo == NULL)
    {
        ErroArquivo;
        return;
    }

    // Ler e mostrar cada registro do arquivo
    while (fread(&contato, sizeof(Contato), 1, arquivo) == 1)
    {
        printf("=======================\n");
        printf("Nome: %s\n", contato.nome);
        printf("Telefone: %s\n", contato.telefone);
        printf("Morada: %s\n", contato.morada);
        printf("Código Postal: %s\n", contato.codigo_postal);
        printf("Cidade: %s\n", contato.cidade);
        printf("País: %s\n", contato.pais);
        printf("=======================\n");
        printf("Pressione ENTER para continuar...");
        getchar();
        limpa();
    }

    // Fechar o arquivo
    fclose(arquivo);
}
// Mostra todos os contatos
void listarContatos(int *numContatos)
{
    FILE *arquivo;
    Contato contato;

    // Abrir o arquivo para leitura
    arquivo = fopen("contacts.dat", "r");

    // Verificar se o arquivo foi aberto corretamente
    if (arquivo == NULL)
    {
        ErroArquivo;
        return;
    }

    // Ler e mostrar cada registro do arquivo
    while (fread(&contato, sizeof(Contato), 1, arquivo) == 1)
    {
        printf("=======================\n");
        printf("Nome: %s\n", contato.nome);
        printf("Telefone: %s\n", contato.telefone);
        printf("Morada: %s\n", contato.morada);
        printf("Código Postal: %s\n", contato.codigo_postal);
        printf("Cidade: %s\n", contato.cidade);
        printf("País: %s\n", contato.pais);
        printf("=======================\n");
    }

    // Fechar o arquivo
    fclose(arquivo);
}
// Pesquisa de contato
void buscarContato(int *numContatos)
{
    FILE *arquivo;
    Contato contato;
    char nomeBusca[21];
    int nome_contato, telefone_contato, morada_contato, codpostal_contato, cidade_contato, pais_contato;

    // Abrir o arquivo para leitura
    arquivo = fopen("contacts.dat", "r");

    // Verificar se o arquivo foi aberto corretamente
    if (arquivo == NULL)
    {
        ErroArquivo;
        return;
    }

    // Solicitar o nome do contato a ser buscado
    printf("Digite o nome do contato a ser buscado: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; // Remover o caractere de nova linha

    // Ler e buscar cada registro do arquivo
    while (fread(&contato, sizeof(Contato), 1, arquivo) == 1)
    {
        // Comparar o nome do contato com o nome buscado
        if (strcmp(contato.nome, nomeBusca) == 0)
        {
            printf("=======================\n");
            printf("Contato encontrado:\n");
            printf("Nome: %s\n", contato.nome);
            printf("Telefone: %s\n", contato.telefone);
            printf("Morada: %s\n", contato.morada);
            printf("Código Postal: %s\n", contato.codigo_postal);
            printf("Cidade: %s\n", contato.cidade);
            printf("País: %s\n", contato.pais);
            printf("=======================\n");

            // Encerrar o loop após encontrar o contato
            break;
        }
    }

    // Verificar se o contato não foi encontrado
    nome_contato = strcmp(contato.nome, nomeBusca);
    telefone_contato = strcmp(contato.telefone, nomeBusca);
    morada_contato = strcmp(contato.morada, nomeBusca);
    codpostal_contato = strcmp(contato.codigo_postal, nomeBusca);
    cidade_contato = strcmp(contato.cidade, nomeBusca);
    pais_contato = strcmp(contato.pais, nomeBusca);

    if (feof(arquivo) && nome_contato != 0 || feof(arquivo) && telefone_contato != 0 || feof(arquivo) && morada_contato != 0 || feof(arquivo) && codpostal_contato != 0 || feof(arquivo) && cidade_contato != 0 || feof(arquivo) && pais_contato != 0)
    {
        Contato404;
    }

    // Fechar o arquivo
    fclose(arquivo);
}
// Remover um contato
void removerContato(int *numContatos)
{
    FILE *arquivo;
    FILE *arquivoTemp;
    Contato contato;
    char nomeBusca[21];
    int encontrado = 0;

    // Abrir o arquivo para leitura e escrita
    arquivo = fopen("contacts.dat", "r+");
    arquivoTemp = fopen("temp.txt", "w");

    // Verificar se os arquivos foram abertos corretamente
    if (arquivo == NULL || arquivoTemp == NULL)
    {
        ErroArquivo;
        return;
    }

    // Solicitar o nome do contato a ser buscado e apagado
    printf("Digite o nome do contato a ser apagado: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; // Remover o caractere de nova linha

    // Ler e copiar cada registro do arquivo para o arquivo temporário, exceto o registro a ser apagado
    while (fread(&contato, sizeof(Contato), 1, arquivo) == 1)
    {
        if (strcmp(contato.nome, nomeBusca) != 0)
        {
            fwrite(&contato, sizeof(Contato), 1, arquivoTemp);
            contador(1);
        }
        else
        {
            encontrado = 1;
        }
    }

    // Verificar se o contato não foi encontrado
    if (!encontrado)
    {
        Contato404;
    }
    else
    {
        printf("Contato apagado com sucesso.\n");

        // Fechar os arquivos
        fclose(arquivo);
        fclose(arquivoTemp);

        // Remover o arquivo original
        remove("contacts.dat");

        // Renomear o arquivo temporário para substituir o arquivo original
        rename("temp.txt", "contacts.dat");
    }
}
// Edita um contato
void modificarContato(int *numContatos)
{
    FILE *arquivo;
    Contato contato;
    char nomeBusca[21], nome_verificado[200], telefone_verificado[200], codigo_verificado[200], cidade_verificado[200], pais_verificado[200], morada_verificado[200];
    int encontrado = 0;

    // Abrir o arquivo para leitura e escrita
    arquivo = fopen("contacts.dat", "r+");

    // Verificar se o arquivo foi aberto corretamente
    if (arquivo == NULL)
    {
        ErroArquivo;
        return;
    }

    // Solicitar o nome do contato a ser buscado
    printf("Digite o nome do contato a ser editado: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; // Remover o caractere de nova linha

    // Ler e editar cada registro do arquivo
    while (fread(&contato, sizeof(Contato), 1, arquivo) == 1)
    {
        // Comparar o nome do contato com o nome buscado
        if (strcmp(contato.nome, nomeBusca) == 0)
        {
            printf("Contato encontrado. Digite os novos dados:\n");
            printf("Nome(%s):", contato.nome);
            verifica_tipo(1, 0, nome_verificado, 1);
            if (strlen(nome_verificado) != 0)
            {
                strcpy(contato.nome, nome_verificado);
            }
            printf("Telefone(%s):", contato.telefone);
            verifica_tipo(2, 0, contato.telefone, 0);
            if (strlen(telefone_verificado) != 0)
            {
                strcpy(contato.telefone, telefone_verificado);
            }
            printf("Morada(%s):", contato.morada);
            verifica_tipo(3, 0, contato.morada, 0);
            if (strlen(morada_verificado) != 0)
            {
                strcpy(contato.morada, morada_verificado);
            }
            printf("Código Postal(%s):", contato.codigo_postal);
            verifica_tipo(4, 0, contato.codigo_postal, 0);
            if (strlen(codigo_verificado) != 0)
            {
                strcpy(contato.codigo_postal, codigo_verificado);
            }
            printf("Cidade(%s):", contato.cidade);
            verifica_tipo(1, 0, contato.cidade, 2);
            if (strlen(cidade_verificado) != 0)
            {
                strcpy(contato.cidade, cidade_verificado);
            }
            printf("País(%s):", contato.pais);
            verifica_tipo(1, 0, contato.pais, 3);
            if (strlen(pais_verificado) != 0)
            {
                strcpy(contato.pais, pais_verificado);
            }
            // Posicionar o cursor de arquivo para a posição correta
            fseek(arquivo, -sizeof(Contato), SEEK_CUR);

            // Escrever o registro atualizado no arquivo
            fwrite(&contato, sizeof(Contato), 1, arquivo);

            encontrado = 1;
            break;
        }
    }

    // Verificar se o contato não foi encontrado
    if (!encontrado)
    {
        Contato404;
    }
    else
    {
        printf("Contato editado com sucesso.\n");
    }

    // Fechar o arquivo
    fclose(arquivo);
}

// Apaga o arquivo
void apagarArquivoContatos(char nome_arquivo[])
{
    FILE *arquivo;
    Contato contato;

    char confirmacao;

    // Abrir o arquivo para escrita no modo "append" (acrescentar ao final)
    arquivo = fopen(nome_arquivo, "r");

    // Verifica se o ficheiro existe
    if (arquivo == NULL)
    {
        ErroArquivo;
        return;
    }

    // Verificar se o arquivo existe antes de apagá-lo
    printf("Tem a certeza que deseja apagar o ficheiro (s/n): ");
    scanf("%c", &confirmacao);
    if (confirmacao == 's')
    {
        remove(nome_arquivo);
        printf("Arquivo apagado com sucesso.\n");
    }
    else
    {
        printf(ANSI_COLOR_RED "Erro ao apagar o arquivo.\n" ANSI_COLOR_RESET);
    }
}
// Descricao do programa
void about()
{
    limpa();
    printf("=====================================\n");
    printf("          SOBRE O PROGRAMA\n");
    printf("=====================================\n");
    printf("Nome do Programa: Agenda\n");
    printf("Versao: 1.0.0\n");
    printf("Descricao: Angenda de contatos\n");
    printf("Autor: contacts Gomes\n");
    printf("=====================================\n");
}
