#include <stdio.h>
#include <string.h>
#include <windows.h>
#define PERM_LER 1
#define PERM_ESCREVER 2
#define PERM_ADMIN 4

typedef struct {

    int id;
    char nome[100];
    char cpf[20];
    int dias;

}Hospede;

typedef struct {

    int numero;
    char tipo[50];
    float diaria;
    char status[20];

}Quarto;

void criarEstrutura(){

    FILE *arquivo;
    CreateDirectory("hotel", NULL);
    CreateDirectory("hotel\\hospedes", NULL);
    CreateDirectory("hotel\\quartos", NULL);
    CreateDirectory("hotel\\logs", NULL);
    CreateDirectory("hotel\\backup", NULL);
    CreateDirectory("hotel\\config", NULL);
    CreateDirectory("hotel\\temp", NULL);

    arquivo = fopen("hotel\\hospedes\\hospedes.json", "a");

    if(arquivo != NULL) {
        fclose(arquivo);
    }
    arquivo = fopen("hotel\\quartos\\quartos.json", "a");

    if(arquivo != NULL) {
        fclose(arquivo);
    }
    printf("\nEstrutura criada com sucesso!\n");
}

void registrarLog(char mensagem[]) {

    FILE *arquivo;
    arquivo = fopen("hotel\\logs\\eventos.log", "a");

    if(arquivo == NULL) {
        printf("Erro ao abrir arquivo de log.\n");
        return;
    }

    fprintf(arquivo, "LOG: %s\n", mensagem);
    fclose(arquivo);
}

void cadastrarHospede() {

    FILE *arquivo;
    Hospede h;

    printf("\n---- CADASTRO DE HOSPEDE ----\n");
    printf("ID: ");
    scanf("%d", &h.id);

    getchar();

    printf("Nome: ");
    fgets(h.nome, 100, stdin);

    h.nome[strcspn(h.nome, "\n")] = 0;

    printf("CPF: ");
    fgets(h.cpf, 20, stdin);

    h.cpf[strcspn(h.cpf, "\n")] = 0;

    printf("Dias de hospedagem: ");
    scanf("%d", &h.dias);

    arquivo = fopen("hotel\\hospedes\\hospedes.json", "a");

    if(arquivo == NULL) {

        printf("Erro ao salvar hospede.\n");
        return;
    }

    fprintf(arquivo,
    "{\n"
    "  \"id\": %d,\n"
    "  \"nome\": \"%s\",\n"
    "  \"cpf\": \"%s\",\n"
    "  \"dias\": %d\n"
    "}\n\n",
    h.id,
    h.nome,
    h.cpf,
    h.dias);

    fclose(arquivo);

    registrarLog("Hospede cadastrado");
    printf("\nHospede cadastrado com sucesso!\n");
}

void cadastrarQuarto() {

    FILE *arquivo;
    Quarto q;

    printf("\n---- CADASTRO DE QUARTO ----\n");

    printf("Numero do quarto: ");
    scanf("%d", &q.numero);

    getchar();

    printf("Tipo do quarto: ");
    fgets(q.tipo, 50, stdin);

    q.tipo[strcspn(q.tipo, "\n")] = 0;

    printf("Valor da diaria: ");
    scanf("%f", &q.diaria);

    getchar();

    printf("Status (Disponivel/Ocupado): ");
    fgets(q.status, 20, stdin);

    q.status[strcspn(q.status, "\n")] = 0;

    arquivo = fopen("hotel\\quartos\\quartos.json", "a");

    if(arquivo == NULL) {
        printf("Erro ao salvar quarto.\n");
        return;
    }

    fprintf(arquivo,
    "{\n"
    "  \"numero\": %d,\n"
    "  \"tipo\": \"%s\",\n"
    "  \"diaria\": %.2f,\n"
    "  \"status\": \"%s\"\n"
    "}\n\n",
    q.numero,
    q.tipo,
    q.diaria,
    q.status);

    fclose(arquivo);

    registrarLog("Quarto cadastrado");
    printf("\nQuarto cadastrado com sucesso!\n");
}

void mostrarInformacoes() {

    FILE *arquivo;
    char linha[200];

    printf("\n---- HOSPEDES ----\n");

    arquivo = fopen("hotel\\hospedes\\hospedes.json", "r");

    if(arquivo != NULL) {

        while(fgets(linha, 200, arquivo) != NULL) {
            printf("%s", linha);
        }
        fclose(arquivo);

    } else {
        printf("Nenhum hospede cadastrado.\n");
    }

    printf("\n---- QUARTOS ----\n");

    arquivo = fopen("hotel\\quartos\\quartos.json", "r");

    if(arquivo != NULL) {

        while(fgets(linha, 200, arquivo) != NULL) {

            printf("%s", linha);
        }
        fclose(arquivo);

    } else {
        printf("Nenhum quarto cadastrado.\n");
    }
    registrarLog("Informacoes mostradas");
}

void gerarJSON() {

    FILE *arquivo;

    arquivo = fopen("hotel\\config\\config.json", "w");

    if(arquivo == NULL) {

        printf("Erro ao criar JSON.\n");
        return;
    }

    fprintf(arquivo, "{\n");
    fprintf(arquivo, "\"sistema\": \"Hotel administrativo\",\n");
    fprintf(arquivo, "\"versao\": 1,\n");
    fprintf(arquivo, "\"admin\": \"recepcao\",\n");
    fprintf(arquivo, "\"backupAtivo\": 1,\n");
    fprintf(arquivo, "\"logAtivo\": 1\n");
    fprintf(arquivo, "}\n");

    fclose(arquivo);

    registrarLog("Arquivo JSON criado");
    printf("\nconfig.json criado com sucesso!\n");
}

void criarBackup() {

     int resultadoHospedes;
     int resultadoQuartos;

    resultadoHospedes = CopyFile(
        "hotel\\hospedes\\hospedes.json",
        "hotel\\backup\\hospedes_backup.json",
        FALSE
    );

    resultadoQuartos = CopyFile(
        "hotel\\quartos\\quartos.json",
        "hotel\\backup\\quartos_backup.json",
        FALSE
    );

    if(resultadoHospedes != 0 && resultadoQuartos != 0) {

        printf("\nBackup criado com sucesso!\n");
        registrarLog("Backup de hospedes e quartos criado");

    } else {
        printf("\nErro ao criar backup.\n");
        registrarLog("Erro ao criar backup");
    }
} 

void criarTemporario() {

    FILE *arquivo;

    arquivo = fopen("hotel\\temp\\relatorio.tmp", "w");

    if(arquivo == NULL) {

        printf("Erro ao criar arquivo temporario.\n");
        return;
    }

    fprintf(arquivo, "Arquivo temporario do sistema.\n");
    fclose(arquivo);
    printf("\nArquivo temporario criado!\n");
    registrarLog("Temporario criado");
}

void removerTemporario() {

    int resultado;

    resultado = DeleteFile("hotel\\temp\\relatorio.tmp");

    if(resultado != 0) {

        printf("\nArquivo temporario removido!\n");
        registrarLog("Temporario removido");

    } else {

        printf("\nErro ao remover temporario.\n");
        registrarLog("Erro ao remover temporario");
    }
}

void verificarPermissoes() {

    unsigned int permissoes = 0;

    permissoes = permissoes | PERM_LER;
    permissoes = permissoes | PERM_ESCREVER;
    permissoes = permissoes | PERM_ADMIN;

    printf("\n---- PERMISSOES ----\n");

    if(permissoes & PERM_LER) {
        printf("Leitura ativa.\n");
    }

    if(permissoes & PERM_ESCREVER) {
        printf("Escrita ativa.\n");
    }

    if(permissoes & PERM_ADMIN) {
        printf("Administrador ativo.\n");
    } else {
        printf("Administrador inativo.\n");
    }

    registrarLog("Permissoes verificadas");
}

int main() {

    int opcao;

    do {
        printf("\n---- HOTEL ADMINISTRATIVO ----\n");
        printf("1 - Criar estrutura do hotel\n");
        printf("2 - Cadastrar hospede\n");
        printf("3 - Cadastrar quarto\n");
        printf("4 - Mostrar informacoes\n");
        printf("5 - Gerar config.json\n");
        printf("6 - Criar backup\n");
        printf("7 - Criar arquivo temporario\n");
        printf("8 - Remover temporario\n");
        printf("9 - Verificar permissoes\n");
        printf("0 - Sair do sistema\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:
                criarEstrutura();
                registrarLog("Estrutura criada");
                break;
            case 2:
                cadastrarHospede();
                break;
            case 3:
                cadastrarQuarto();
                break;
            case 4:
                mostrarInformacoes();
                break;
            case 5:
                gerarJSON();
                break;
            case 6:
                criarBackup();
                break;
            case 7:
                criarTemporario();
                break;
            case 8:
                removerTemporario();
                break;
            case 9:
                verificarPermissoes();
                break;
            case 0:
                registrarLog("Sistema encerrado");
                printf("\nEncerrando sistema...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                registrarLog("Opcao invalida");
        }
    } while(opcao != 0);
    return 0;
}
