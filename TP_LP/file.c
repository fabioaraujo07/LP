/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.c to edit this template
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "input.h"
#include "file.h"

//---------ENTERPRISE--------

//Função para atualizar o número de clientes no ficheiro

void updateNEnterprises(int contador, char* filename) {
    FILE* fp = fopen(filename, "r+b");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&contador, sizeof (int), 1, fp);
    fclose(fp);
}

// Função para adicionar um cliente no ficheiro

void insertEnterprise(Enterprises* enterprises, char* filename) {
    //Atualizar contador
    updateNEnterprises(enterprises->contador, filename);
    FILE* fp = fopen(filename, "ab");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&enterprises->enterprises[enterprises->contador - 1], sizeof (Enterprise), 1, fp);
    fclose(fp);

}

// Função para atualiza os dados de uma empresa no ficheiro

void updateEnterprise(Enterprises enterprises, int index, char*filename) {
    FILE* fp = fopen(filename, "r+b");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fseek(fp, sizeof (int), SEEK_SET);
    fseek(fp, sizeof (Enterprise) * index, SEEK_CUR);
    fwrite(&enterprises.enterprises[index], sizeof (Enterprise), 1, fp);
    fclose(fp);
}


// Função para remover os dados de uma empresa num ficheiro

void removeEnterprise(Enterprises enterprises, char* filename) {
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&enterprises.contador, sizeof (int), 1, fp);
    fwrite(enterprises.enterprises, sizeof (Enterprise), enterprises.contador, fp);
    fclose(fp);
}

// -------------------BRANCHES-----------------------

void updateNBranches(int contador, char* filename) {
    FILE* fp = fopen(filename, "r+b");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&contador, sizeof (int), 1, fp);
    fclose(fp);
}

void insertBranche(Branches* branches, char* filename) {
    //Atualizar contador
    updateNEnterprises(branches->contador, filename);
    FILE* fp = fopen(filename, "ab");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&branches->branches[branches->contador - 1], sizeof (Branche), 1, fp);
    fclose(fp);
}

void updateBranche(Branches branches, int index, char*filename) {
    FILE* fp = fopen(filename, "r+b");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    fseek(fp, sizeof (int), SEEK_SET);
    fseek(fp, sizeof (Branche) * index, SEEK_CUR);
    fwrite(&branches.branches[index], sizeof (Branche), 1, fp);
    fclose(fp);
}

void removeBranche(Branches branches, char* filename) {
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fwrite(&branches.contador, sizeof (int), 1, fp);
    fwrite(branches.branches, sizeof (Branche), branches.contador, fp);
    fclose(fp);
}
