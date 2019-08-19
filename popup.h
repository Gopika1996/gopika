/*********************************.FILE_HEADER.*******************************/
/** @file popup.h
 *  @brief Contains the header file for GUI pop-up window.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */
/***********************.INCLUDES****************************************/
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
/**********************.IMPLICIT_DECLARATION.*********************************/
gboolean Pop_Up_Timeout(gpointer data);
int Identification(char* , char *) ;
bool Show_Question();
int PopUp(char *);  
unsigned int  Collect_Money();                                       
int TotalAmount(int ,int ,int );
/*****************************************************************************/


