#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>



typedef struct artista Artista;
struct artista{
    char nome[100];
    char genero[100];
    char naturalidade[100];
    char album1[100];
    char album2[100];
};
void editar();
void excluir();
void buscarAlbum();
void listar();
void inserir();
void cabecalho();
void buscarArtistaEspecifico();
int main(){


    int opcao;
    do{
        cabecalho();
        printf("1 - Inserir\n");
        printf("2 - Remover\n");
        printf("3 - Editar\n");
        printf("4 - Listar artistas\n");
        printf("5 - Buscar album\n");
        printf("6 - Buscar artista especifico\n");
        printf("7 - Sair\n\n");

        printf("Digite uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){

            case 1:

                inserir();
            break;

            case 2:

                excluir();
            break;

            case 3:

                editar();
            break;

            case 4:

                listar();
            break;

            case 5:
                buscarAlbum();
            break;

              case 6:
   
    fflush(stdin);
    printf("Digite o nome do artista a ser buscado: ");
    char nomeArtistaBuscado[100];
    gets(nomeArtistaBuscado);
    buscarArtistaEspecifico(nomeArtistaBuscado);
    break;

            case 7:
                //SAIR
                printf("Obrigado pela visita!\n");
                getch();
            break;

            default:
                printf("Opcao invalida\n");
                getch();
            break;

        };

    } while(opcao != 7);



    return 0;
}

void cabecalho(){
    system("cls");
    printf("--------------------------------------\n");
    printf("                 MENU\n");
    printf("--------------------------------------\n");
}

void inserir(){
    FILE *arquivo;
    FILE *arquivo2;
    Artista att, attLeitura;
    arquivo = fopen("artistas.txt","ab");
    if(arquivo == NULL){
        printf("Problemas na abertura do arquivo!\n");
    } else{
        do{
            cabecalho();
            fflush(stdin);
            printf("Digite o nome: ");
            gets(&att.nome);


             arquivo2 = fopen("artistas.txt","rb");
             if(arquivo2 == NULL){
                printf("Erro ao abrir o arquivo!\n");
             }else{
                while(fread(&attLeitura, sizeof(Artista),1,arquivo2) == 1){
                    if(strcmp(att.nome, attLeitura.nome) == 0){
                        printf(" O artista ja esta cadastrado no sistema!");
                        getch();
                        return;
                    }
                }
             }
            fclose(arquivo2);

             printf("Digite o genero: ");
            gets(&att.genero);

             printf("Digite a naturalidade: ");
            gets(&att.naturalidade);

            printf("Digite o primeiro album: ");
            gets(&att.album1);

            printf("Digite o segundo album: ");
            gets(&att.album2);

            fwrite(&att, sizeof(Artista), 1, arquivo);

            printf("Deseja continuar? (s/n)");
        }while(getche() == 's');
    }
    fclose(arquivo);
}

void listar(){
    FILE *arquivo;
    Artista att;

    arquivo = fopen("artistas.txt","rb");
    cabecalho();
    if(arquivo == NULL){
        printf("Problemas na abertura do arquivo!\n");
    }else{
        while(fread(&att, sizeof(Artista), 1, arquivo) == 1){
            printf("\nNome: %s", att.nome);
            printf("\nGenero: %s", att.genero);
            printf("\nNaturalidade: %s", att.naturalidade);
            printf("\nAlbum 1: %s", att.album1);
            printf("\nAlbum 2: %s", att.album2);
            printf("\n\n-----------------------------------------");
        }
    }
    fclose(arquivo);
    getch();
}

void buscarAlbum(){
    FILE *arquivo;
    Artista att;
    char album[100];

    arquivo = fopen("artistas.txt","rb");
    cabecalho();
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo!\n");
    } else {
        fflush(stdin);
        printf("Digite o nome do album: ");
        gets(album);
        int encontrados = 0;
        while (fread(&att,sizeof(Artista),1,arquivo) == 1) {
            if (strcmp(album, att.album1) == 0 || strcmp(album, att.album2) == 0) {
                encontrados++;
                printf("\nNome: %s", att.nome);
                printf("\nGenero: %s", att.genero);
                printf("\nNaturalidade: %s", att.naturalidade);
                printf("\nAlbum 1: %s", att.album1);
                printf("\nAlbum 2: %s", att.album2);
                printf("\n\n-----------------------------------------");
            }
        }
        if (encontrados == 0) {
            printf("Nenhum artista encontrado com esse album.\n");
        }
    }
    fclose(arquivo);
    getch();

}





void buscarArtistaEspecifico(const char *nomeBuscado) {
    FILE *arquivo;
    Artista att;
    int encontrou = 0;
    int inicio, meio, fim;

    arquivo = fopen("artistas.txt","rb");
    cabecalho();
    if (arquivo == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }

    fseek(arquivo, 0, SEEK_END);
    int totalRegistros = ftell(arquivo) / sizeof(Artista);

    inicio = 0;
    fim = totalRegistros - 1;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        fseek(arquivo, meio * sizeof(Artista), SEEK_SET);
        fread(&att, sizeof(Artista), 1, arquivo);

        if (strcmp(nomeBuscado, att.nome) == 0) {
            encontrou = 1;
            break;
        } else if (strcmp(nomeBuscado, att.nome) < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    if (encontrou) {
        printf("Artista encontrado:\n");
        printf("\nNome: %s", att.nome);
        printf("\nGenero: %s", att.genero);
        printf("\nNaturalidade: %s", att.naturalidade);
        printf("\nAlbum 1: %s", att.album1);
        printf("\nAlbum 2: %s", att.album2);
    } else {
        printf("Artista nao encontrado!\n");
    }

    fclose(arquivo);
    getch();
}






void excluir(){
    FILE* arquivoOriginal;
    FILE* arquivoModificado;
    Artista att;

    char nome[100];

    cabecalho();
    arquivoOriginal= fopen("artistas.txt","rb");
    arquivoModificado = fopen("artistaTemporario.txt","ab");


    if(arquivoOriginal == NULL || arquivoModificado == NULL){
        printf("Erro na abertura do arquivo!");
    }else{
        fflush(stdin);
        printf("Digite o artista a ser excluido:");
        gets(nome);

        while(fread(&att,sizeof(Artista),1,arquivoOriginal) == 1){
            if(strcmp(nome,att.nome)!= 0){
                fwrite(&att,sizeof(Artista),1,arquivoModificado);
            }
        }

    }
    fclose(arquivoOriginal);
    fclose(arquivoModificado);
    remove("artistas.txt");
    rename("artistaTemporario.txt","artistas.txt");
    printf("Artista excluido!\n");
    getch();
}

void editar() {
    FILE *arquivoOriginal;
    FILE *arquivoModificado;
    Artista att;

    char nome[100];
    char novoNome[100];
    char novoGenero[100];
    char novaNaturalidade[100];
    char novoAlbum1[100];
    char novoAlbum2[100];
    int encontrado = 0;

    cabecalho();
    arquivoOriginal = fopen("artistas.txt", "rb");
    arquivoModificado = fopen("artistaTemporario.txt", "ab");

    if (arquivoOriginal == NULL || arquivoModificado == NULL) {
        printf("Erro na abertura do arquivo!");
        return;
    }

    fflush(stdin);
    printf("Digite o nome do artista a ser editado: ");
    gets(nome);

    while (fread(&att, sizeof(Artista), 1, arquivoOriginal) == 1) {
        if (strcmp(nome, att.nome) == 0) {
            encontrado = 1;

            printf("Digite o novo nome: ");
            gets(novoNome);
            strcpy(att.nome, novoNome);

            printf("Digite o novo genero: ");
            gets(novoGenero);
            strcpy(att.genero, novoGenero);

            printf("Digite a nova naturalidade: ");
            gets(novaNaturalidade);
            strcpy(att.naturalidade, novaNaturalidade);

            printf("Digite o novo album 1: ");
            gets(novoAlbum1);
            strcpy(att.album1, novoAlbum1);

            printf("Digite o novo album 2: ");
            gets(novoAlbum2);
            strcpy(att.album2, novoAlbum2);
        }
        fwrite(&att, sizeof(Artista), 1, arquivoModificado);
    }

    fclose(arquivoOriginal);
    fclose(arquivoModificado);

    if (!encontrado) {
        printf("Artista nao encontrado!\n");
        remove("artistaTemporario.txt");
    } else {
        remove("artistas.txt");
        rename("artistaTemporario.txt", "artistas.txt");
        printf("Artista editado com sucesso!\n");
    }

    getch();
}