/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   enterprise.h
 * Author: fabio
 *
 * Created on 1 de dezembro de 2023, 19:44
 */

#include <stdbool.h>

#ifndef ENTERPRISE_H
#define ENTERPRISE_H

#define INITIAL_ENTERPRISES 10
#define ENTERPRISE_EXPANSION 10
#define FILE_ENTERPRISES "enterprises.bin"

//STRINGS
#define ERROR "ERROOOOR"
#define ERROR_ENTERPRISE_NOT_EXIST "The enterprise does not exist on the list"
#define ERROR_EMPTY_LIST_ENT "The enterprises list is empty"
#define ERROR_FULL_LIST_ENT "The enterprises list is full"
#define ERROR_ENTERPRISE_EXIST "The enterprise already exists"
#define ERROR_INVALID_OPTION_ENT "Invalid Option"
#define ERROR_INVALID_POSTCODE "Post Code invalide"

//CONSTANTS

#define MAX_OPTION_ENT                 1   
#define MIN_OPTION_ENT                 0
#define MSG_ENTERPRISE_OPTION "Enterprise state:\n1 - Active \n0 - Inactive\n "


#define MIN_NIF_ENTERPRISE 100000000
#define MAX_NIF_ENTERPRISE 999999999
#define MSG_NIF "Insert NIF: "

#define MAX_NAME 40
#define MAX_EMAIL_SIZE 40
#define MAX_TITLE_SIZE 40
#define MAX_TEXT_SIZE 40

#define MAX_NAME_ENTERPRISE 40
#define MSG_NAME "Insert name of the enterprise: "

#define MAX_CATEGORY_NAME 40
#define MSG_CATEGORY "Insert the category name: "

#define MAX_BRANCHE_NAME 30
#define MSG_BRANCHE "Insert the branche name: "

#define MAX_STREET_NAME 40
#define MSG_STREET "Insert the street name: "

#define MAX_LOCALITY_NAME 30
#define MSG_LOCALITY "Insert the locality name: "

#define MIN_NUM_ENTERPRISE           1
#define MAX_NUM_ENTERPRISE           1000
#define MSG_GET_ID_ENTERPRISE       "Insert the enterprise number [0-1000]: "

#define MAX_NUM_POSTCODE 9
#define MSG_POSTCODE "Insert the Post Code: "

#define NAME_MSG "Enter your name: "
#define EMAIL_MSG "Enter your email: "
#define COMMENT_MSG "Comment: "
#define USER_NAME_MAX  20
#define EMAIL_MAX  30
#define COMMENT_MAX  100

#define MAX_NUM_CLASSIFICATIONS 10
#define MAX_NUM_COMENTARIOS 10

#define RATE_MSG "Insert Rating [0-5]: "
#define RATE_MAX 5
#define RATE_MIN 0
//Structs

typedef struct{
    char nome[USER_NAME_MAX];
    char email[EMAIL_MAX];
    int valor;
}Rating;

typedef struct {
    char userName[USER_NAME_MAX];
    char userEmail[EMAIL_MAX];
    char title[MAX_TITLE_SIZE];
    char comment[COMMENT_MAX];
}Comment;


typedef struct {
    int id;
    int Nif;
    char nome[MAX_NAME_ENTERPRISE];
    char category[MAX_CATEGORY_NAME];
    char branche[MAX_BRANCHE_NAME];
    char locality[MAX_LOCALITY_NAME];
    char street[MAX_STREET_NAME];
    char postCode[MAX_NUM_POSTCODE];
//    Rating classificacoes[MAX_NUM_CLASSIFICATIONS];
//    Comment comentarios[MAX_NUM_COMENTARIOS];
    Rating* classificacoes;
    Comment* comentarios;
    bool isActive;
    int contadorClassificacoes;
    int contadorComentarios;
} Enterprise;

typedef struct {
    int contador, nMax;
    Enterprise *enterprises;
}Enterprises;





#include "branches.h"


int checkEnterprise(Enterprises enterprises, int id);
void changeEnterpriseStatus(Enterprise *enterprise, int newStatus);
void createEnterprises(Enterprises *enterprises, char* filename);
void editEnterprise(Enterprises *enterprises, char* filename);
void removeEnterprises(Enterprises *enterprises);
void listEnterprises(Enterprises enterprises);
void searchEnterprises(Enterprises enterprises);
void addBrancheToEnterprise(Enterprises *enterprises, Branches *branches);
void searchEnterprisesByName(Enterprises enterprises);
void searchEnterprisesByCategory(Enterprises enterprises);
int checkEnterpriseByName(Enterprises enterprises, char* name);
int checkEnterpriseByCategory(Enterprises enterprises, char* category);
int checkRatingEmail(Enterprise enterprise, char email[]);
void createEditRating(Enterprise* enterprise);
void createEditComment(Enterprise* enterprise);


// Ficheiros e Memória dinamica
void freeEnterprises(Enterprises* enterprises);
void reallocEnterprises(Enterprises* enterprises);
int initializeEnterprise(Enterprises* enterprises, char* filename);

#endif /* ENTERPRISE_H */

