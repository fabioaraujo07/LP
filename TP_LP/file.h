/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   file.h
 * Author: fabio
 *
 * Created on 12 de janeiro de 2024, 01:49
 */

#ifndef FILE_H
#define FILE_H

#include "branches.h"
#include "enterprise.h"


void updateNEnterprises(int contador, char* filename);
void insertEnterprise(Enterprises* enterprises, char* filename);
void updateEnterprise(Enterprises enterprises, int index, char*filename);
void removeEnterprise(Enterprises enterprises, char* filename);
void updateNBranches(int contador, char* filename);
void insertBranche(Branches* branches, char* filename);
void updateBranche(Branches branches, int index, char*filename);
void removeBranche(Branches branches, char* filename);

#endif /* FILE_H */

