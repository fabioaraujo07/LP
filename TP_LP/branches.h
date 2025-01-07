/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   branches.h
 * Author: fabio
 *
 * Created on 1 de dezembro de 2023, 19:47
 */

#include "enterprise.h"


#ifndef BRANCHES_H
#define BRANCHES_H

#include <stdbool.h>

#define INITIAL_BRANCHES 10
#define BRANCHE_EXPANSION 10
#define FILE_BRANCHES "branches.bin"

//STRINGS
#define ERROR_BRANCHE_NOT_EXISTS "The branche does not exist on the list"
#define ERROR_EMPTY_LIST "The branches list is empty"
#define ERROR_FULL_LIST "The branches list is full"
#define ERROR_BRANCHE_EXISTS "The branche already exists"

#define MAX_OPTION                 1   
#define MIN_OPTION                 0
#define MSG_BRANCHE_OPTION "Branche state:\n1 - Active 0 - Inactive\n "

#define MAX_BRANCHE_NAME 30
#define MSG_BRANCHE "Insert the branche name: "

#define MIN_NUM_BRANCHE           1
#define MAX_NUM_BRANCHE           1000
#define MSG_GET_ID_BRANCHE       "Insert the branche number [0-1000]: "

typedef struct{
    int id;
    char name[MAX_BRANCHE_NAME];
    bool isActive;
}Branche;

typedef struct{
    int contador, nMax;
    Branche *branches;
}Branches;

int checkBranche(Branches branches, int id);
void createBranches(Branches *branches, char* filename);
void editBranche(Branches *branches, char* filename);
void removeBranches(Branches *branches, Enterprises *enterprises, char* filename);
void listBranches(Branches branches);
void searchBranches(Branches branches);
void changeBrancheStatus(Branche *branche, int newStatus);


//Ficheiros e Memória dinamica

void freeBranches(Branches *branches);
int intialiseBranches(Branches *branches, char* filename);
void reallocBranches(Branches *branches);

#endif /* BRANCHES_H */

