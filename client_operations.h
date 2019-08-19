/*********************************.FILE_HEADER.*******************************/
/** @file client_operations.h
 *  @brief Contains the header file to check the cardnumber,PIN and oerofrms 
    concatenation, parsing and file handling.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */
/***********************.INCLUDES****************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <time.h>
/**********************.IMPLICIT_DECLARATION.*********************************/
bool CheckPIN(char*);
bool CheckCardNumber(char*);
char* Concatenate(char *,char *);
bool Parsing(char [], char[], int, int);
int FileOperation(char* ,char* );
/************************************************************************/
