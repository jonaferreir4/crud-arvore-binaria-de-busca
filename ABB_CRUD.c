#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno {
    int id;
    char nome[50];
    char curso[50];
} Aluno;

typedef struct no {
    Aluno aluno;
    struct no *dir;
    struct no *esq;
    struct no *pai;
} NO;

NO *raiz = NULL;

NO *busca_arvore(int x, NO *pt) {
    if (pt == NULL) {
        return NULL;
    } else if (x == pt->aluno.id) {
        return pt;
    } else if (x < pt->aluno.id) {
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


void insercao_arvore(int id, const char *nome, const char *curso) {
    Aluno aluno;
    aluno.id = id;
    strncpy(aluno.nome, nome, sizeof(aluno.nome) - 1);
    strncpy(aluno.curso, curso, sizeof(aluno.curso) - 1);

    NO *pt = busca_arvore(id, raiz);
    if (pt != NULL) {
        if (pt->aluno.id == id) {
            printf("Chave duplicada!\n");
        } else {
            NO *pt1 = malloc(sizeof(NO));
            pt1->aluno = aluno;
            pt1->esq = NULL;
            pt1->dir = NULL;
            if (id < pt->aluno.id) {
                pt->esq = pt1;
            } else {
                pt->dir = pt1;
            }
            pt1->pai = pt;
        }
    } else {
        NO *pt1 = malloc(sizeof(NO));
        pt1->aluno = aluno;
        pt1->esq = NULL;
        pt1->dir = NULL;
        pt1->pai = pt;
        raiz = pt1;
    }
}

NO *achar_sucessor(NO *pt) {
    if (pt->esq == NULL) {
        return pt;
    }
    return achar_sucessor(pt->esq);
}

void atualizar_arvore(int id) {
    NO *alunoEncontrado = busca_arvore(id, raiz);
    if (alunoEncontrado != NULL) {
        char novoNome[50];
        char novoCurso[50];
        
        printf("Digite o novo nome do aluno: ");
        scanf("%s", novoNome);
        printf("Digite o novo curso do aluno: ");
        scanf("%s", novoCurso);

        strncpy(alunoEncontrado->aluno.nome, novoNome, sizeof(alunoEncontrado->aluno.nome) - 1);
        strncpy(alunoEncontrado->aluno.curso, novoCurso, sizeof(alunoEncontrado->aluno.curso) - 1);

        printf("Aluno atualizado com sucesso.\n");
    } else {
        printf("Aluno nao encontrado.\n");
    }
}



void remover(int x) {
    NO *pt = busca_arvore(x, raiz);

    if (pt->dir == NULL && pt->esq == NULL) { // folha
        if (pt->pai != NULL) {
            if (pt->aluno.id < pt->pai->aluno.id) {
                pt->pai->esq = NULL;
            } else {
                pt->pai->dir = NULL;
            }
        } else {
            raiz = NULL;
        }
        free(pt);
    } else if ((pt->dir == NULL) ^ (pt->esq == NULL)) { // com um filho
        if (pt->dir == NULL) {
            pt->pai->dir = pt->esq;
        } else if (pt->esq == NULL) {
            pt->pai->esq = pt->dir;
        }
        free(pt);
    } else {
        NO *sucessor = achar_sucessor(pt->dir);
        int temp = sucessor->aluno.id;
        remover(sucessor->aluno.id);
        pt->aluno.id = temp;
    }
}

void pre(NO *pt) {
    printf("ID: %d | Nome: %s | Curso: %s\n", pt->aluno.id, pt->aluno.nome, pt->aluno.curso);
    if (pt->esq != NULL) {
        pre(pt->esq);
    }
    if (pt->dir != NULL) {
        pre(pt->dir);
    }
}

int main() {
    int op;

    do {
        printf("_____ MENU _____\n");
        printf("1 - cadastrar aluno\n");
        printf("2 - pesquisar aluno\n");
        printf("3 - listar alunos\n");
        printf("4 - atualizar aluno\n");
        printf("5 - deletar aluno\n");
        printf("0 - sair\n");
        printf("Escolha a opcao que deseja: ");
        scanf("%d", &op);

        switch (op) {
            case 1: {
                int id;
                char nome[50];
                char curso[50];
                printf("Digite o ID do aluno: ");
                scanf("%d", &id);
                printf("Digite o nome do aluno: ");
                scanf("%s", nome);
                printf("Digite o curso do aluno: ");
                scanf("%s", curso);
                insercao_arvore(id, nome, curso);
                break;
            }
            case 2: {
                int id;
                printf("Digite o ID do aluno a ser pesquisado: ");
                scanf("%d", &id);

                NO *alunoEncontrado = busca_arvore(id, raiz);
                if (alunoEncontrado != NULL) {
                    printf("Aluno encontrado:\n");
                    printf("ID: %d - Nome: %s - Curso: %s\n", alunoEncontrado->aluno.id, alunoEncontrado->aluno.nome, alunoEncontrado->aluno.curso);
                } else {
                    printf("Aluno nao encontrado.\n");
                }
                break;
            }
            case 3:
                printf("Listagem de alunos:\n");
                pre(raiz);
                break;
            case 4: {
                int id;
                printf("Digite o ID do aluno para atualiza-lo: ");
                scanf("%d", &id);
                atualizar_arvore(id);
                break;
            }
            case 5: {
                int id;
                printf("Digite o ID do aluno para remove-lo: ");
                scanf("%d", &id);
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
