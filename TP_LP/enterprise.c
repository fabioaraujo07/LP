/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "enterprise.h"
#include "input.h"
#include "file.h"

/**
 * @brief Imprime os dados de uma empresa.
 * @param enterprise A empresa a ser impressa.
 */

void printEnterprise(Enterprise enterprise) {
    printf("\n%-3d - %-5d - %-6s - %-6s - %-6s - %-6s - %-6s - %-2s\n", enterprise.id, enterprise.Nif, enterprise.nome,
            enterprise.branche, enterprise.category, enterprise.locality, enterprise.street,
            enterprise.isActive ? " Active" : " Inactive");
}

/**
 * @brief Verifica se uma empresa existe com base no ID.
 * @param enterprises Lista de empresas.
 * @param id ID da empresa a ser verificada.
 * @return Índice da empresa se existir, -1 caso contrário.
 */

int checkEnterprise(Enterprises enterprises, int id) {
    int i = 0;
    while (i < enterprises.contador) {
        if (enterprises.enterprises[i].id == id) {
            return i;
        }
        i++;
    }
    return -1;
}

/**
 * @brief Edita os dados de uma empresa.
 * @param enterprises Lista de empresas.
 * @param filename Nome do arquivo para salvar os dados.
 */

void editEnterprise(Enterprises *enterprises, char* filename) {
    int index = checkEnterprise(*enterprises, getInt(MIN_NUM_ENTERPRISE, MAX_NUM_ENTERPRISE, MSG_GET_ID_ENTERPRISE));

    if (index != -1) {
        readString(enterprises->enterprises[index].nome, MAX_NAME_ENTERPRISE, MSG_NAME);
        readString(enterprises->enterprises[index].category, MAX_CATEGORY_NAME, MSG_CATEGORY);
        readString(enterprises->enterprises[index].branche, MAX_BRANCHE_NAME, MSG_BRANCHE);
        readString(enterprises->enterprises[index].locality, MAX_LOCALITY_NAME, MSG_LOCALITY);
        readString(enterprises->enterprises[index].street, MAX_STREET_NAME, MSG_STREET);
        enterprises->enterprises[index].Nif = getInt(MIN_NIF_ENTERPRISE, MAX_NIF_ENTERPRISE, MSG_NIF);
        enterprises->enterprises[index].isActive = getInt(MIN_OPTION_ENT, MAX_OPTION_ENT, MSG_ENTERPRISE_OPTION);

        //Save file

        int option = getInt(1, 2, "Save in the database?\n1. Yes\n2. No\n");
        if (option == 1) {
            updateEnterprise(*enterprises, index, filename);
        }
    } else {
        puts(ERROR_ENTERPRISE_NOT_EXIST);
    }
}

/**
 * @brief Zera os valores de uma empresa.
 * @param enterprise A empresa a ser resetada.
 */

void RemoveEnterpriseData(Enterprise *enterprise) {
    enterprise->id = 0;
    enterprise->Nif = 0;
    strcpy(enterprise->nome, "");
    strcpy(enterprise->street, "");
    strcpy(enterprise->locality, "");
    enterprise->isActive = false;
    strcpy(enterprise->category, "");
}

/**
 * @brief Cria uma nova empresa.
 * @param enterprises Lista de empresas.
 * @return Índice da empresa criada ou -1 se já existir.
 */

int createEnterprise(Enterprises *enterprises) {
    int id = getInt(MIN_NUM_ENTERPRISE, MAX_NUM_ENTERPRISE, MSG_GET_ID_ENTERPRISE);

    if (checkEnterprise(*enterprises, id) == -1) {

        enterprises->enterprises[enterprises->contador].id = id;

        readString(enterprises->enterprises[enterprises->contador].nome, MAX_NAME_ENTERPRISE, MSG_NAME);
        readString(enterprises->enterprises[enterprises->contador].category, MAX_CATEGORY_NAME, MSG_CATEGORY);
        readString(enterprises->enterprises[enterprises->contador].locality, MAX_LOCALITY_NAME, MSG_LOCALITY);
        readString(enterprises->enterprises[enterprises->contador].street, MAX_STREET_NAME, MSG_STREET);
        readString(enterprises->enterprises[enterprises->contador].postCode, MAX_NUM_POSTCODE, MSG_POSTCODE);

        while (enterprises->enterprises[enterprises->contador].postCode[4] != '-' || strnlen(enterprises->enterprises[enterprises->contador].postCode + 5, (MAX_NUM_POSTCODE - 5)) != 3) {
            printf(ERROR_INVALID_POSTCODE);
            readString(enterprises->enterprises[enterprises->contador].postCode, MAX_NUM_POSTCODE, MSG_POSTCODE);
        }
        enterprises->enterprises[enterprises->contador].Nif = getInt(MIN_NIF_ENTERPRISE, MAX_NIF_ENTERPRISE, MSG_NIF);
        enterprises->enterprises[enterprises->contador].isActive = true;

        return enterprises->contador++;

    }
    return -1;
}

/**
 * @brief Cria e adiciona empresas à lista.
 * @param enterprises Lista de empresas.
 * @param filename Nome do arquivo para salvar os dados.
 */

void createEnterprises(Enterprises *enterprises, char* filename) {
    if (enterprises->contador < enterprises->nMax) {
        if (createEnterprise(enterprises) == -1) {
            puts(ERROR_ENTERPRISE_EXIST);
        }
    } else {
        reallocEnterprises(enterprises);
    }
    int option = getInt(1, 2, "Save in the database?\n1. Yes\n2. No\n");
    if (option == 1) {
        insertEnterprise(enterprises, filename);
    }
}

/**
 * @brief Procura uma empresa pelo ID.
 * @param enterprises Lista de empresas.
 */
void searchEnterprises(Enterprises enterprises) {
    int id = checkEnterprise(enterprises, getInt(MIN_NUM_ENTERPRISE, MAX_NUM_ENTERPRISE, MSG_GET_ID_ENTERPRISE));

    if (id != -1) {
        printf("\nID - NIF - Enterprise name - Category - Locality - Street - State\n");
        printEnterprise(enterprises.enterprises[id]);
        printf("\n");
    } else {
        puts(ERROR_ENTERPRISE_NOT_EXIST);
    }
}

/**
 * @brief Procura uma empresa pelo nome.
 * @param enterprises Lista de empresas.
 */

void searchEnterprisesByName(Enterprises enterprises) {
    char name[MAX_NAME_ENTERPRISE];

    // Use a função readString para obter o nome da empresa
    cleanInputBuffer();
    readString(name, MAX_NAME_ENTERPRISE, MSG_NAME);

    int index = checkEnterpriseByName(enterprises, name);

    if (index != -1) {
        printf("\nID - NIF - Enterprise name - Category - Locality - Street - State\n");
        printEnterprise(enterprises.enterprises[index]);
        printf("\n");
    } else {
        puts(ERROR_ENTERPRISE_NOT_EXIST);
    }
}

/**
 * @brief Verifica se uma empresa existe pelo nome.
 * @param enterprises Lista de empresas.
 * @param name Nome da empresa.
 * @return Índice da empresa se existir, -1 caso contrário.
 */

int checkEnterpriseByName(Enterprises enterprises, char* name) {
    int i = 0;
    while (i < enterprises.contador) {
        if (strcmp(enterprises.enterprises[i].nome, name) == 0) {
            return i;
        }
        i++;
    }
    return -1;
}

/**
 * @brief Verifica se há uma empresa na lista pertencente a uma determinada categoria.
 * @param enterprises Lista de empresas.
 * @param category Categoria a ser verificada.
 * @return Índice da empresa se encontrada, -1 caso contrário.
 */

int checkEnterpriseByCategory(Enterprises enterprises, char* category) {
    int i = 0;
    while (i < enterprises.contador) {
        if (strcmp(enterprises.enterprises[i].category, category) == 0) {
            return i;
        }
        i++;
    }
    return -1;
}

/**
 * @brief Procura e exibe empresas por categoria.
 * @param enterprises Lista de empresas.
 */
void searchEnterprisesByCategory(Enterprises enterprises) {
    char category[MAX_CATEGORY_NAME];
    cleanInputBuffer();
    readString(category, MAX_CATEGORY_NAME, "Enter the category: ");

    // Verifica se a categoria não está vazia
    if (strlen(category) == 0) {
        puts("Invalid category. Please try again.");
        return;
    }

    for (int i = 0; i < enterprises.contador; i++) {
        if (strcmp(enterprises.enterprises[i].category, category) == 0 && enterprises.enterprises[i].isActive) {
            printf("\nID - NIF - Enterprise name - Category - Locality - Street - State\n");
            printEnterprise(enterprises.enterprises[i]);
            printf("\n");
        }
    }

    puts(ERROR_ENTERPRISE_NOT_EXIST);
}

/**
 * @brief Remove uma empresa da lista, se não houver comentários associados.
 * @param enterprises Lista de empresas.
 */
void removeEnterprises(Enterprises *enterprises) {
    int i, id = checkEnterprise(*enterprises, getInt(MIN_NUM_ENTERPRISE, MAX_NUM_ENTERPRISE, MSG_GET_ID_ENTERPRISE));

    if (id != -1) {
        for (i = id; i < enterprises->contador - 1; i++) {
            enterprises->enterprises[i] = enterprises->enterprises[i + 1];
        }

        RemoveEnterpriseData(&enterprises->enterprises[i]);

        enterprises->contador--;
    } else {
        puts(ERROR_ENTERPRISE_NOT_EXIST);
    }
}

/**
 * @brief Lista as empresas.
 * @param enterprises Lista de empresas.
 */

void listEnterprises(Enterprises enterprises) {
    if (enterprises.contador > 0) {
        int i;
        for (i = 0; i < enterprises.contador; i++) {
            printf("\nID - NIF - Enterprise name - Branche - Category - Locality - Street - State\n");
            printEnterprise(enterprises.enterprises[i]);
            printf("\n");
        }
    } else {
        puts(ERROR_EMPTY_LIST_ENT);
    }
}

/**
 * @brief Ativa uma empresa na lista com base no ID.
 * @param enterprises Lista de empresas.
 * @param id ID da empresa a ser ativada.
 */

void activateEnterprise(Enterprises *enterprises, int id) {
    int index = checkEnterprise(*enterprises, id);

    if (index != -1) {
        changeEnterpriseStatus(&enterprises->enterprises[index], 1); // 1 para ativar
    } else {
        puts(ERROR_ENTERPRISE_NOT_EXIST);
    }
}

/**
 * @brief Altera o estado de uma empresa (ativa/inativa).
 * @param enterprise Empresa a ser modificada.
 * @param newStatus Novo estado (1 para ativar, 0 para desativar).
 */

void changeEnterpriseStatus(Enterprise *enterprise, int newStatus) {
    enterprise->isActive = newStatus;
}

/**
 * @brief Adiciona um ramo de atividade a uma empresa.
 * @param enterprises Lista de empresas.
 * @param branches Lista de ramos de atividade.
 */

void addBrancheToEnterprise(Enterprises *enterprises, Branches *branches) {
    int enterpriseId = getInt(MIN_NUM_ENTERPRISE, MAX_NUM_ENTERPRISE, MSG_GET_ID_ENTERPRISE);
    int brancheId = getInt(MIN_NUM_BRANCHE, MAX_NUM_BRANCHE, MSG_GET_ID_BRANCHE);

    int enterpriseIndex = checkEnterprise(*enterprises, enterpriseId);
    int brancheIndex = checkBranche(*branches, brancheId);

    if (enterpriseIndex != -1 && brancheIndex != -1) {
        // Verifica se o branche já foi adicionado à empresa
        if (strcmp(branches->branches[brancheIndex].name, enterprises->enterprises[enterpriseIndex].branche) == 0) {
            puts("Branche already added to this enterprise.");
        } else {
            strcpy(enterprises->enterprises[enterpriseIndex].branche, branches->branches[brancheIndex].name);
            printf("Branche '%s' added to Enterprise '%s'\n",
                    branches->branches[brancheIndex].name, enterprises->enterprises[enterpriseIndex].nome);
        }
    } else {
        puts("Invalid enterprise or branche ID");
    }
}

/**
 * @brief Verifica se já existe um rating com o mesmo email.
 * @param enterprise Empresa na qual verificar o email.
 * @param email Email a ser verificado.
 * @return Índice do rating se encontrado, -1 caso contrário.
 */

int checkRatingEmail(Enterprise enterprise, char email[]) {
    for (int i = 0; i < enterprise.contadorClassificacoes; i++) {
        if (strcmp(enterprise.classificacoes[i].email, email) == 0) {
            // Já existe um rating com esse email
            return i;
        }
    }
    return -1;
}

/**
 * @brief Verifica se já existe um comentário com o mesmo email.
 * @param enterprise Empresa na qual verificar o email.
 * @param userEmail Email a ser verificado.
 * @return Índice do comentário se encontrado, -1 caso contrário.
 */

int checkCommentEmail(Enterprise enterprise, char userEmail[]) {
    for (int i = 0; i < enterprise.contadorComentarios; i++) {
        if (strcmp(enterprise.comentarios[i].userEmail, userEmail) == 0) {
            //Já existe um comentário com esse email
            return i;
        }
    }
    return -1;
}

/**
 * @brief Cria ou edita um rating para uma empresa.
 * @param enterprise Empresa na qual adicionar ou editar o rating.
 */

void createEditRating(Enterprise* enterprise) {
    char email[MAX_EMAIL_SIZE];
    cleanInputBuffer();
    readString(email, MAX_EMAIL_SIZE, EMAIL_MSG);
    int index = checkRatingEmail(*enterprise, email);

    if (index != -1) {
        enterprise->classificacoes[index].valor = getInt(RATE_MIN, RATE_MAX, "Insert Rating [0-5]: ");
        printf("Rating updated successfully!\n");

    } else {
        // Aloca espaço para mais uma classificação
        enterprise->classificacoes = realloc(enterprise->classificacoes, (enterprise->contadorClassificacoes + 1) * sizeof (Rating));

        // Verifica se a alocação foi bem-sucedida antes de continuar
        if (enterprise->classificacoes == NULL) {
            fprintf(stderr, "Error allocating memory for ratings\n");
            exit(EXIT_FAILURE);
        }


        // Preenche os dados da nova classificação
        readString(enterprise->classificacoes[enterprise->contadorClassificacoes].nome, USER_NAME_MAX, NAME_MSG);
        strcpy(enterprise->classificacoes[enterprise->contadorClassificacoes].email, email);
        enterprise->classificacoes[enterprise->contadorClassificacoes].valor = getInt(RATE_MIN, RATE_MAX, "Insert Rating [0-5]: ");

        enterprise->contadorClassificacoes++;

        printf("Rating added with success!\n");
    }
}

/**
 * @brief Cria ou edita um comentário para uma empresa.
 * @param enterprise Empresa na qual adicionar ou editar o comentário.
 */
void createEditComment(Enterprise* enterprise) {
    char userEmail[MAX_EMAIL_SIZE];
    cleanInputBuffer();
    readString(userEmail, MAX_EMAIL_SIZE, EMAIL_MSG);
    int index = checkCommentEmail(*enterprise, userEmail);

    if (index != -1) {
        readString(enterprise->comentarios[index].comment, COMMENT_MAX, COMMENT_MSG);
        printf("Comment updated successfully!\n");
    } else {
        // Aloca espaço para mais um comentário
        enterprise->comentarios = realloc(enterprise->comentarios, (enterprise->contadorComentarios + 1) * sizeof (Comment));

        // Verifica se a alocação foi bem-sucedida antes de continuar
        if (enterprise->comentarios == NULL) {
            fprintf(stderr, "Error allocating memory for comments\n");
            exit(EXIT_FAILURE);
        }

        printf("\n");

        // Preenche os dados do novo comentário
        readString(enterprise->comentarios[enterprise->contadorComentarios].userName, USER_NAME_MAX, NAME_MSG);
        readString(enterprise->comentarios[enterprise->contadorComentarios].title, MAX_TITLE_SIZE, "Insert the title: ");
        strcpy(enterprise->comentarios[enterprise->contadorComentarios].userEmail, userEmail);
        readString(enterprise->comentarios[enterprise->contadorComentarios].comment, COMMENT_MAX, COMMENT_MSG);

        enterprise->contadorComentarios++;

        printf("Comment added with success!\n");
    }
}

/**
 * @brief Libera a memória alocada para a lista de empresas.
 * @param enterprises Lista de empresas.
 */

void freeEnterprises(Enterprises* enterprises) {
    for (int i = 0; i < enterprises->contador; i++) {
        free(enterprises->enterprises[i].classificacoes);
        free(enterprises->enterprises[i].comentarios);
    }
    free(enterprises->enterprises);
    
}

/**
 * @brief Realoca a memória alocada para empresas.
 * @param enterprises Lista de empresas.
 */

void reallocEnterprises(Enterprises* enterprises) {
    Enterprise* tempPtr = (Enterprise*) realloc(enterprises->enterprises, sizeof (Enterprise) * (enterprises->nMax + ENTERPRISE_EXPANSION));
    if (tempPtr != NULL) {
        enterprises->nMax += ENTERPRISE_EXPANSION;
        enterprises->enterprises = tempPtr;
    }
}

/**
 * @brief Inicializa a lista de empresas a partir de um arquivo.
 * @param enterprises Lista de empresas.
 * @param filename Nome do arquivo de dados.
 * @return 1 se a inicialização foi bem-sucedida, 0 caso contrário.
 */

int initialiseEnterprises(Enterprises* enterprises, char* filename) {
    int confirm = 0;

    FILE* fp = fopen(filename, "rb");
    if (fp != NULL) {
        fread(&enterprises->contador, sizeof (int), 1, fp);
        if (enterprises->contador > 0) {
            enterprises->enterprises = (Enterprise*) malloc(enterprises->contador * sizeof (Enterprise));
            fread(enterprises->enterprises, sizeof (Enterprise), enterprises->contador, fp);
            enterprises->nMax = enterprises->contador;
            confirm = 1;

        }
        fclose(fp);
    }
    if (!confirm) {
        fp = fopen(filename, "wb");
        if (fp != NULL) {
            enterprises->enterprises = (Enterprise*) malloc(INITIAL_ENTERPRISES * sizeof (Enterprise));
            enterprises->contador = 0;
            enterprises->nMax = INITIAL_ENTERPRISES;

            confirm = 1;
        }
    }
    return confirm;
}




