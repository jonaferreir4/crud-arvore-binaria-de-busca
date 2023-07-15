// Sistema de cadastro de jogos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct jogo {
    int id;
    char nome[50];
    char plataforma[50];
    char desenvolvedora[50];
    char genero[50];
    int ano;

} JOGO;

typedef struct no {
    JOGO jogo;
    struct no *dir;
    struct no *esq;
    struct no *pai;
} NO;

NO *raiz = NULL;

void limpar_buffer_entrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

NO *busca_arvore(int x, NO *pt) {
    if (pt == NULL) {
        return NULL;
    } else if (x == pt->jogo.id) {
        return pt;
    } else if (x < pt->jogo.id) {
        if (pt->esq == NULL) {
            return pt;
        } else {
            return busca_arvore(x, pt->esq);
        }
    } else {
        if (pt->dir == NULL) {
            return pt;
        } else {
            return busca_arvore(x, pt->dir);
        }
    }
}


void insercao_arvore(int id, const char *nome, const char *plataforma, const char *desenvolvedora, const char * genero, int ano) {
    JOGO novoJogo;

    novoJogo.id = id;
    strncpy(novoJogo.nome, nome, sizeof(novoJogo.nome) - 1);
    strncpy(novoJogo.plataforma, plataforma, sizeof(novoJogo.plataforma) - 1);
    strncpy(novoJogo.desenvolvedora, desenvolvedora, sizeof(novoJogo.desenvolvedora) - 1);
    strncpy(novoJogo.genero, genero, sizeof(novoJogo.genero) - 1);
    novoJogo.ano = ano;

    NO *pt = busca_arvore(id, raiz);
    if (pt != NULL) {
        if (pt->jogo.id == id) {
            printf("Ja existe um jogo com esse ID!\n");
        } else {
            NO *pt1 = malloc(sizeof(NO));
            pt1->jogo = novoJogo;
            pt1->esq = NULL;
            pt1->dir = NULL;
            pt1->pai = NULL;
            if (id < pt->jogo.id) {
                pt->esq = pt1;
                printf("jogo adicionado!\n");
                pt1->pai = pt;
            } else {
                pt->dir = pt1;
                printf("jogo adicionado!\n");
                pt1->pai = pt;
            }
        }
    } else {
        NO *pt1 = malloc(sizeof(NO));
        pt1->jogo = novoJogo;
        pt1->esq = NULL;
        pt1->dir = NULL;
        pt1->pai = NULL;
        raiz = pt1;
        printf("jogo adicionado!\n");
    }
  
}

NO *achar_sucessor(NO *pt) {
    if (pt->esq == NULL) {
        return pt;
    }
    return achar_sucessor(pt->esq);
}

void atualizar_arvore(int id) {
    NO *jogoEncontrado = busca_arvore(id, raiz);
    if (jogoEncontrado->jogo.id == id) {
        int op;
        char novoNome[50];
        char novaPlataforma[50];
        char novadesenvolvedora[50];
        char novoGenero[50];
        int novoAno;

            printf("Qual informacao voce quer atualizar?\n");
            printf("1 - Nome do jogo\n");
            printf("2 - Plataforma do jogo\n");
            printf("3 - Desenvolvedora do jogo\n");
            printf("4 - Genero do jogo\n");
            printf("5 - Ano do jogo\n");
            printf("0 - cancelar atualizacao\n");
            scanf("%d", &op);

            switch(op){
                case 1:{
                    printf("Digite o nome do jogo: ");
                    limpar_buffer_entrada();
                    fgets(novoNome, sizeof(novoNome), stdin);
                    novoNome[strcspn(novoNome, "\n")] = '\0';
                    strncpy(jogoEncontrado->jogo.nome, novoNome, sizeof(jogoEncontrado->jogo.nome) - 1);
                    printf("Nome atualizado!\n");
                    break;
                }
                case 2:{
                    printf("Digite a nova plataforma do jogo: ");
                    limpar_buffer_entrada();
                    fgets(novaPlataforma, sizeof(novaPlataforma), stdin);
                    novaPlataforma[strcspn(novaPlataforma, "\n")] = '\0';
                    strncpy(jogoEncontrado->jogo.plataforma, novaPlataforma, sizeof(jogoEncontrado->jogo.plataforma) - 1);
                    printf("Plataforma atualizada!\n");
                    break;
                }
                case 3:{
                    printf("Digite a nova desenvolvedora do jogo: ");
                    limpar_buffer_entrada();
                    fgets(novadesenvolvedora, sizeof(novadesenvolvedora), stdin);
                    novadesenvolvedora[strcspn(novadesenvolvedora, "\n")] = '\0';
                    strncpy(jogoEncontrado->jogo.desenvolvedora, novadesenvolvedora, sizeof(jogoEncontrado->jogo.desenvolvedora) - 1);
                    printf("Desenvolvedora atualizada!\n");
                    break;
                }
                case 4:{
                    printf("Digite o novo genero do jogo: ");
                    limpar_buffer_entrada();
                    fgets(novoGenero, sizeof(novoGenero), stdin);
                    novoGenero[strcspn(novoGenero, "\n")] = '\0';
                    strncpy(jogoEncontrado->jogo.genero, novoGenero, sizeof(jogoEncontrado->jogo.genero) - 1);
                    printf("Genero atualizado!\n");
                    break;
                }
                case 5:{
                   while(printf("Digite o ano do jogo: ") && scanf("%d", &novoAno) != 1){
                    printf("O ano deve ser composto somente de numeros!\n");
                    limpar_buffer_entrada();
                } 
                    limpar_buffer_entrada();
                    jogoEncontrado->jogo.ano  = novoAno;
                    printf("Ano atualizado!\n");
                    break;
                }
                case 0:
                    printf("atualizacao cancelada!");
                    break;
                default:
                    printf("opcao invalida!");
                    break;
            }

            } else {
                 printf("jogo nao encontrado.\n");
    }
}



void remover(int x) {
    NO *pt = busca_arvore(x, raiz);
    if (pt == NULL){
        printf("Nao ha jogos cadastrados!\n");
    }else {

    if (pt->jogo.id != x){
        printf("O jogo nao foi encontrado!\n");
    }else{

    if (pt->dir == NULL && pt->esq == NULL) { // folha
        if (pt->pai != NULL) {
            if (pt->jogo.id < pt->pai->jogo.id) {
                pt->pai->esq = NULL;
            } else {
                pt->pai->dir = NULL;
            }
            free(pt);
        } else {
            raiz = NULL;
            free(pt);
        }
        printf("jogo removido com sucesso\n");
    } else if ((pt->dir == NULL) || (pt->esq == NULL)) { // com um filho
                NO *filho;
                if (pt->esq != NULL) {
                    filho = pt->esq;
                } else {
                    filho = pt->dir;
                }

                if (pt->pai != NULL) {
                    if (pt->jogo.id < pt->pai->jogo.id) {
                        pt->pai->esq = filho;
                    } else {
                        pt->pai->dir = filho;
                    }
                    filho->pai = pt->pai;
                } else {
                    raiz = filho;
                    filho->pai = NULL;
                }
                free(pt);
                printf("jogo removido com sucesso\n");
    } else { // com dois filhos
        NO *sucessor = achar_sucessor(pt->dir);
        int temp = sucessor->jogo.id;
        remover(sucessor->jogo.id);
        pt->jogo.id = temp;
    }
    }
    }
}

void pre(NO *pt) {
    if(pt == NULL){
        printf("Nao ha jogos cadastrados!\n");
    }else{
    printf("ID: %d - Nome: %s - plataforma: %s - desenvolvedora: %s - genero: %s - ano: %d\n", pt->jogo.id, pt->jogo.nome, pt->jogo.plataforma, pt->jogo.desenvolvedora, pt->jogo.genero, pt->jogo.ano);
    if (pt->esq != NULL) {
        pre(pt->esq);
    }
    if (pt->dir != NULL) {
        pre(pt->dir);
    }
    }
}

int main() {
    int op;

    do {
        printf("\n_____ MENU _____\n");
        printf("1 - cadastrar jogo\n");
        printf("2 - pesquisar jogo\n");
        printf("3 - listar jogos\n");
        printf("4 - atualizar jogo\n");
        printf("5 - deletar jogo\n");
        printf("0 - sair\n");
        printf("Escolha a opcao que deseja: ");
        scanf("%d", &op);

        switch (op) {
            case 1: {
                 int id;
                char nome[50];
                char plataforma[50];
                char desenvolvedora[50];
                char genero[50];
                int ano;

               
                while ( printf("Digite o ID do jogo: ") && scanf("%d", &id) != 1) {
                    printf("O ID deve ser composto somente de numeros!\n");
                    limpar_buffer_entrada();
                }
                limpar_buffer_entrada();

                printf("Digite o nome do jogo: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Digite a plataforma do jogo: ");
                fgets(plataforma, sizeof(plataforma), stdin);
                plataforma[strcspn(plataforma, "\n")] = '\0';

                printf("Digite o desenvolvedora do jogo: ");
                fgets(desenvolvedora, sizeof(desenvolvedora), stdin);
                desenvolvedora[strcspn(desenvolvedora, "\n")] = '\0';

                printf("Digite o genero do jogo: ");
                fgets(genero, sizeof(genero), stdin);
                genero[strcspn(genero, "\n")] = '\0';

                while(printf("Digite o ano do jogo: ") && scanf("%d", &ano) != 1){
                    printf("O ano deve ser composto somente de numeros!\n");
                    limpar_buffer_entrada();

                } 
                limpar_buffer_entrada();
                
                insercao_arvore(id, nome, plataforma, desenvolvedora, genero, ano);
                break;
            }
            case 2: {
                int id;
                while ( printf("Digite o ID do jogo: ") && scanf("%d", &id) != 1) {
                    printf("O ID deve ser composto somente de numeros!\n");
                    limpar_buffer_entrada();
                }
                limpar_buffer_entrada();

                NO *jogoEncontrado = busca_arvore(id, raiz);
                if (jogoEncontrado->jogo.id == id) {
                    printf("jogo encontrado:\n");
                    printf("ID: %d - Nome: %s - plataforma: %s - desenvolvedora: %s - genero: %s - ano: %d\n", jogoEncontrado->jogo.id, jogoEncontrado->jogo.nome, jogoEncontrado->jogo.plataforma, jogoEncontrado->jogo.desenvolvedora, jogoEncontrado->jogo.genero, jogoEncontrado->jogo.ano);
                } else {
                    printf("jogo nao encontrado.\n");
                }
                break;
            }
            case 3:
                printf("Listagem de jogos:\n");
                pre(raiz);
                break;
            case 4: {
                int id;
                while ( printf("Digite o ID do jogo a ser atualizado: ") && scanf("%d", &id) != 1) {
                    printf("O ID deve ser composto somente de numeros!\n");
                    limpar_buffer_entrada();
                }
                limpar_buffer_entrada();

                atualizar_arvore(id);
                break;
            }
            case 5: {
                int id;
               while ( printf("Digite o ID para remove-lo: ") && scanf("%d", &id) != 1) {
                    printf("O ID deve ser composto somente de numeros!\n");
                    limpar_buffer_entrada();
                }
                limpar_buffer_entrada();
                remover(id);
                break;
            }
            case 0:
                printf("Sessao encerrada.\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }

    } while (op != 0);

    return 0;
}