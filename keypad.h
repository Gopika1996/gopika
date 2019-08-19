/*********************************.FILE_HEADER.*******************************/
/** @file keypad.h
 *  @brief Contains the header file for keypad.c
    concatenation, parsing and file handling.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */
/***********************.INCLUDES****************************************/
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/**********************.IMPLICIT_DECLARATION.****************************/
bool DisplayKeypad(char *ucArg);
int  ReadInputBuffer(char* pQueue ,unsigned int uMaxSize);
bool TransactionOptions();
bool AmountOption() ;
char *  ReadOptionBuffer();
void InitBuffer();
char * AmountOptionBuffer();
/************************************************************************/
/*! 
   \brief sets the constant integer value for strings.
   \param BUTTON_WIDTH as 50   
*/
#define BUTTON_WIDTH    50
/*! 
   \brief sets the constant integer value for strings.
   \param BUTTON_HEIGHT as 54   
*/
#define BUTTON_HEIGHT   54
/*! 
   \brief sets the constant integer value for strings.
   \param BUTTON_GAP as 5   
*/
#define BUTTON_GAP      5
/*! 
   \brief sets the constant integer value for strings.
   \param SIZE as 512   
*/
#define SIZE      512
/** 
     * brief This is an enumeration.
     * This is to define the row position of buttons.
*/
typedef enum 
{
	ROW_0 = BUTTON_GAP, 
	ROW_1 = BUTTON_HEIGHT + BUTTON_GAP,
	ROW_2 = ROW_1+ BUTTON_HEIGHT + BUTTON_GAP,
	ROW_3 = ROW_2 + BUTTON_HEIGHT+ BUTTON_GAP,
} rowPos;
/** 
     * brief This is an enumeration.
     * This is to define the column position of buttons.
*/
typedef enum
{
	COL_0 = BUTTON_GAP, 
	COL_1 = BUTTON_WIDTH + BUTTON_GAP, 
	COL_2 = COL_1+ BUTTON_WIDTH + BUTTON_GAP,
    sCOL_3 = COL_2 + BUTTON_WIDTH+ BUTTON_GAP,
} colPos;
/************************************************************************/



