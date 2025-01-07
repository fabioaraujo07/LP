/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   input.h
 * Author: fabio
 *
 * Created on 29 de dezembro de 2023, 20:15
 */

#ifndef INPUT_H
#define INPUT_H


void cleanInputBuffer();
int getInt(int minValue, int maxValue, char *msg);
float getFloat(float minValor, float maxValor, char *msg);
double getDouble(double minValor, double maxValor, char *msg);
char getChar(char *msg);
void readString(char *string, unsigned int tamanho, const char *msg);

#endif /* INPUT_H */

