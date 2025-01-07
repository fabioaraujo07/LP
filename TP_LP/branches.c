/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "branches.h"
#include "input.h"
#include "enterprise.h"

//função para imprimir os dados dos branches

void printBranches(Branche branche) {
    printf("\n%-3d - %-6s - %-2s\n", branche.id, branche.name, branche.isActive ? " Active" : " Inactive");
};

int checkBranche(Branches branches, int id) {
    int i = 0;
    while (i < branches.contador) {
        if (branches.branches[i].id == id) {
            return i;
        }
        i++;
    }
    return -1;
};

// Função para editar os ramos de atividade

void editBranche(Branches *branches, char* filename) {
    int index = checkBranche(*branches, getInt(MIN_NUM_BRANCHE, MAX_NUM_BRANCHE, MSG_GET_ID_BRANCHE));

    if (index != -1) {
        readString(branches->branches[index].name, MAX_BRANCHE_NAME, MSG_BRANCHE);
        branches->branches[index].isActive = getInt(MIN_OPTION, MAX_OPTION, MSG_BRANCHE_OPTION);

        //Save file
        int option = getInt(1, 2, "Save in the database?\n1. Yes\n2. No\n");
        if (option == 1) {
            updateBranche(*branches, index, filename);
        }

    } else {
        puts(ERROR_BRANCHE_NOT_EXISTS);
    }
}

int createBranche(Branches *branches) {
    int id = getInt(MIN_NUM_BRANCHE, MAX_NUM_BRANCHE, MSG_GET_ID_BRANCHE);

    if (checkBranche(*branches, id) == -1) {
        branches->branches[branches->contador].id = id;

        readString(branches->branches[branches->contador].name, MAX_BRANCHE_NAME, MSG_BRANCHE);
        branches->branches[branches->contador].isActive = true;

        return branches->contador++;
    }
    return -1;

};

void createBranches(Branches *branches, char* filename) {
    if (branches->contador < branches->nMax) {
        if (createBranche(branches) == -1) {
            puts(ERROR_BRANCHE_EXISTS);
        }
    } else {
        reallocBranches(branches);
    }
    int option = getInt(1, 2, "Save in the database?\n1. Yes\n2. No\n");
    if (option == 1) {
        insertBranche(branches, filename);
    }
}

//Função utilizada para zerar os campos dos ramos de atividade

void removeBrancheData(Branche *branche) {
    branche->id = 0;
    strcpy(branche->name, "");
    branche->isActive = false;
};

//Esta função faz o realloc da estrutura de branches após eliminar um branche
void reallocBranchesAfterDelete(Branches* branches){
    Branche* tempPtr = (Branche*)realloc(branches->branches, sizeof(Branche) * (branches->nMax - 1));
    if (tempPtr != NULL) {
        branches->nMax -=1;
        branches->branches = tempPtr;
    }
}

//Função para remover os ramos de atividade

void removeBranches(Branches *branches, Enterprises *enterprises, char* filename) {
    int i, id = getInt(MIN_NUM_BRANCHE, MAX_NUM_BRANCHE, MSG_GET_ID_BRANCHE);

    int index = checkBranche(*branches, id);

    if (index != -1) {
        // Verifica se o branch está designado a alguma empresa
        int enterpriseIndex = -1;
        for (i = 0; i < enterprises->contador; i++) {
            if (strcmp(branches->branches[index].name, enterprises->enterprises[i].branche) == 0) {
                enterpriseIndex = i;
                break;
            }
        }

        if (enterpriseIndex != -1) {
            // Branch está designado a uma empresa, então muda o estado para inativo
            changeBrancheStatus(&branches->branches[index], 0);
            printf("Branche '%s' set to inactive\n", branches->branches[index].name);

            updateBranche(*branches, index, filename);

        } else {
            int userConfirmInput = getInt(1, 2, "Delete the branche?\n1. Yes\n2. No\n");
            if (userConfirmInput == 1) {
                // Branch não está designado a uma empresa, então pode ser removido
                for (i = index; i < branches->contador - 1; i++) {
                    branches->branches[i] = branches->branches[i + 1];
                }
                // Limpa os dados do branch removido
                removeBrancheData(&branches->branches[i]);
                branches->contador--;
                // Remover no ficheiro
                removeBranche(*branches, FILE_BRANCHES);
                reallocBranchesAfterDelete(branches);
                return userConfirmInput;
                printf("Branche '%s' removed\n", branches->branches[i].name);
            }
        }
    } else {
        puts(ERROR_BRANCHE_NOT_EXISTS);
    }
}

void listBranches(Branches branches) {
    if (branches.contador > 0) {
        int i;
        for (i = 0; i < branches.contador; i++) {
            printf("\nID - Enterprise name - State\n");
            printBranches(branches.branches[i]);
            printf("\n");
        }
    } else {
        puts(ERROR_EMPTY_LIST);
    }
}

void activateBranche(Branches *branches, int id) {
    int index = checkBranche(*branches, id);

    if (index != 1) {
        changeBrancheStatus(&branches->branches[index], 1);
    } else {
        puts(ERROR_BRANCHE_NOT_EXISTS);
    }
}

// Função para alterar o estado de uma empresa de ativo para inativo

void changeBrancheStatus(Branche *branche, int newStatus) {
    branche->isActive = newStatus;
}


// Função para libertar a memória alocada para os branches

void freeBranches(Branches* branches) {
    free(branches->branches);
}


//Esta função realoca a memória alocada para as branches para que seja possivel adicionar mais branche

void reallocBranches(Branches* branches) {
    Branche* tempPtr = (Branche*) realloc(branches->branches, sizeof (Branche) * (branches->nMax + BRANCHE_EXPANSION));
    if (tempPtr != NULL) {
        branches->nMax += BRANCHE_EXPANSION;
        branches->branches = tempPtr;
    }
}

int initialiseBranches(Branches* branches, char* filename) {
    int confirm = 0;

    FILE* fp = fopen(filename, "rb");
    if (fp != NULL) {
        fread(&branches->contador, sizeof (int), 1, fp);
        if (branches->contador > 0) {
            branches->branches = (Branche*) malloc(branches->contador * sizeof (Branche));
            fread(branches->branches, sizeof (Branche), branches->contador, fp);
            branches->nMax = branches->contador;
            confirm = 1;

        }
        fclose(fp);
    }
    if (!confirm) {
        fp = fopen(filename, "wb");
        if (fp != NULL) {
            branches->branches = (Branche*) malloc(INITIAL_BRANCHES * sizeof (Branche));
            branches->contador = 0;
            branches->nMax = INITIAL_BRANCHES;

            confirm = 1;
        }
    }
    return confirm;
}