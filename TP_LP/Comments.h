/*
 
Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
*/

/* 
 
File:   Comments.h
Author: fabio
*
Created on 9 de janeiro de 2024, 01:51
*/

#include "enterprise.h"

#ifndef COMMENTS_H
#define COMMENTS_H

#define MAX_LENGTH_COMMENTS 100
#define MSG_COMMENTS "Insert Comment"

#define MAX_LENGTH_NAME 40
#define MSG_NAME_C "Insert your name"

#define MAX_LENGTH_EMAIL 30
#define MSG_EMAIL "Insert Email"

typedef struct{
    char comments[MAX_LENGTH_COMMENTS];
    char nome[MAX_LENGTH_NAME];
    char email[MAX_LENGTH_EMAIL];
}Comment;

typedef struct{
    int contador, nMaxComments;
    Comment* comments;
}Comments;

typedef struct{
    
};

void addCommentsEnterprises(Enterprises enterprises, Comments comments);
void addRanksEnterprises(Enterprises enterprises, )



#endif /* COMMENTS_H */
