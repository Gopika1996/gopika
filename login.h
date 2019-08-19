/*********************************.FILE_HEADER.*******************************/
/** @file login.h
 *  @brief Contains the header file for Login
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */

/***********************.INCLUDES****************************************/
#include<gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
/**********************.IMPLICIT_DECLARATION.****************************/
bool Login();
void OnClosed(GtkWidget *widget);
/************************************************************************/
/**
 * A global integer value.
 * This global variable is used to initialise window.
 */
GtkWidget *gtkWindow;
/************************************************************************/
