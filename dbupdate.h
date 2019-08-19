/*********************************.FILE_HEADER.*******************************/
/** @file dbupdate.h
 *  @brief Contains the header file for updating data into the database.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */
/***********************.INCLUDES****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include<time.h>
/***********************.MACROS****************************************/
/*! 
   \brief sets the constant integer value for strings.
   \param MAX_SIZE input value  
 */
#define MAX_SIZE 3
/*! 
   \brief sets the constant integer value for strings.
   \param BLOCK_SIZE input value  
 */
#define BLOCK_SIZE 1024

/**********************.IMPLICIT_DECLARATION.****************************/
int DbUpdate(char *pcCardnumber,char* pcOption,char *pcValue);
int MinistatementArray(char strBuf[]);
char* SetMiniStatement(char pcOption[]);
void PrintQueue();
void ClearQueue();
void AddStringToQueue(char* string);
int MinistatementUpdate(char *,char *);
/************************************************************************/
