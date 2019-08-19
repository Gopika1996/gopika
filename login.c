/*********************************.FILE_HEADER.*******************************/
/** @file login.c
 *  @brief Designing a login GUI.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */

/***********************.MACROS****************************************/
#include "login.h"
/*! 
   \brief sets the constant integer value for strings.
   \param BORDER_WIDTH input value  
 */
#define BORDER_WIDTH 300 
/*! s
   \brief sets the constant integer value for strings.
   \param BUTTON_SIZE input value  
 */
#define BUTTON_SIZE 100 

/*********************************.FUNCTION_HEADER.*******************************/
/** @brief OnClosed
 *  This function is used for hide gtkWindow and call login function on delete-event.
 *  @param widget
 *  @return void.
 */
void OnClosed(GtkWidget *widget)
{
	gtk_widget_hide(gtkWindow);
	Login();
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief Login
 *  This function is used for login GUI.
 *  @return bool.
 */
bool Login()
{	
	GtkWidget *gtkButton, *gtkVbox;	
	gtkWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);	 
  	g_signal_connect(gtkWindow, "delete-event", G_CALLBACK(OnClosed),gtkWindow);
	gtk_window_set_position(GTK_WINDOW(gtkWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(gtkWindow), "ABC Bank welcomes you");
       
	gtkVbox = gtk_box_new(0, 0);
	gtkButton = gtk_button_new_with_label("Please Insert the ATM card");
	g_signal_connect(gtkButton, "clicked", G_CALLBACK(gtk_main_quit), gtkWindow);
	gtk_box_pack_start(GTK_BOX(gtkVbox), gtkButton, FALSE, TRUE, BUTTON_SIZE);

	gtk_container_set_border_width(GTK_CONTAINER(gtkWindow), BORDER_WIDTH);
	gtk_container_add(GTK_CONTAINER(gtkWindow), gtkVbox);
	
	gtk_widget_show_all(gtkWindow);
	gtk_main();
	gtk_widget_hide(gtkWindow);	
	return true;	
}

