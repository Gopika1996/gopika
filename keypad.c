/*********************************.FILE_HEADER.*******************************/
/** @file keypad.c
 *  @brief This program contains the GUI implementation for a keypad.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */
/***********************.INCLUDES********************************************************************************************/

#include "keypad.h"

/***********************.DECLARATIONS********************************************************************************************/
/** \brief define global variable*/
char sQueue[20] = { 0 }; /** \brief sQueue is initialised as NULL*/
static char* p_queue = NULL; /** \brief *p_queue is initialised as NULL*/
static char strOption[SIZE] = { 0 };/** \brief strOption is used to hold the transaction option*/
static char strAmount[SIZE] = { 0 }; /** \brief strAmount used to hold denomination option*/
GtkEntry *gtkPass = NULL; /** \brief gtkPass used to hold key value*/
GtkWidget *gtkLabelPass = NULL; /** \brief gtkLabelPass used to hold key value*/

/*! 
   \brief sets the constant integer value for strings.
   \param BUFSIZE input value  
 */
#define BUFFER_SIZE 1024
/** 
 * brief This is an enumeration.
 * This is to define the pop-up window.
 */
typedef enum
{
    CARD_NUMBER,
    PIN_NUMBER,
	AMOUNT,
    NEW_PIN,
	WITHDRAW_AMOUNT

}TyKeyPad;
/**
*constant array declaration
*/
const char* cArrays[]=
{
	"CARD_NUMBER",
	"PIN_NUMBER",
	"AMOUNT",
	"NEW_PIN",
	"WITHDRAW_AMOUNT",
	NULL
};
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief WriteInput
 *  This function is used for write the data into a queue.
 *  @param GtkWidget *widget,gpointer data .
 *  @return void static.
 */
void static WriteInput(GtkWidget *widget, gpointer data) 
{     
    *p_queue = *(char*)((gchar*)data);     
    p_queue++;
    gtk_entry_grab_focus_without_selecting(gtkPass);
    gtk_entry_set_text(gtkPass, sQueue);
    gtk_editable_set_position((GtkEditable*)gtkPass, strlen(sQueue));
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @fn DeleteInput 
 *  This function is used for delete the data inputed into a queue.
 *  @param widget hold gtkwidget.
 *  @param data hold data.
 *  @return void static.
 */
void static DeleteInput(GtkWidget *widget, gpointer data) 
{	
    if (p_queue != sQueue)
    {
        p_queue--;
        *p_queue = '\0';
    }
    gtk_entry_set_text(gtkPass, sQueue);
    gtk_entry_grab_focus_without_selecting(gtkPass);
    gtk_editable_set_position((GtkEditable*)gtkPass, strlen(sQueue));
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief AddButton  
 *  This function is used for AddButton to GUI. 
 *  @param vgrid hold gtkwidget.
 *  @param name hold button name.
 *  @param handler is the function handler.
 *  @param param is the parameter.
 *  @param row is the rows.
 *  @param col is the columns.
 *  @param width is the button width.
 *  @param height is the button height.
 *  @return void.
 */
void AddButton(GtkGrid *vgrid, gchar* name, GCallback handler, gpointer param,
		gint row, gint col, gint width, gint height) 
{
	GtkWidget *button;
	button = gtk_button_new_with_label(name);
	g_signal_connect(button, "clicked", G_CALLBACK(handler), param);
	gtk_grid_attach(vgrid, button, col, row, width, height);
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief CashWithdrawal  
 *  This function is used for CashWithdrawal. 
 *  @param widget hold gtkwidget.
 *  @param data hold data.
 *  @return void.
 */
void CashWithdrawal(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
	strcpy(strOption, "CASHWITHDRAWAL");
	strcpy(strAmount, "100");
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief BalanceEnquiry  
 *  This function is used for BalanceEnquiry. 
 *  @param widget hold gtkwidget.
 *  @param data hold data.
 *  @return void.
 */
void BalanceEnquiry(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
	strcpy(strOption, "BALANCEENQUIRY");
	strcpy(strAmount, "500");
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief PinChange  
 *  This function is used for PinChange. 
 *  @param widget hold gtkwidget.
 *  @param data hold data.
 *  @return void.
 */
void PinChange(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
	strcpy(strOption, "PINCHANGE");
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief MiniStatement  
 *  This function is used for MiniStatement. 
 *  @param widget hold gtkwidget.
 *  @param data hold data.
 *  @return void.
 */
void MiniStatement(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
	strcpy(strOption, "MINISTATEMENT");
	strcpy(strAmount, "2000");
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief Quit  
 *  This function is used to quit from gtk main. 
 *  @param widget hold gtkwidget.
 *  @param data hold data.
 *  @return void.
 */
void Quit(GtkWidget *widget, gpointer data) 
{
	gtk_main_quit();
	strcpy(strOption, "QUIT");
	strcpy(strAmount, "QUIT");
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief QuitMain   
 *  @param widget hold gtkwidget.
 *  @param data hold data.
 *  @return void
 */
void static QuitMain(GtkWidget *widget, gpointer data)
{
	GtkWidget* window = (GtkWidget*)data;
	gtk_widget_hide(window);
	gtk_widget_destroy(window);
	gtk_main_quit();
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief InitBuffer 
 *  @return void
 */
void InitBuffer() 
{
	int i;
	for (i = 0; i < sizeof(sQueue); i++)
	{
		sQueue[i] = '\0';
	}
	p_queue = sQueue;
}

/*********************************.FUNCTION_HEADER.*******************************/
/** @brief ReadInputBuffer   
 *  @param pQueue,uMaxSize
 *  @return zero if the function is successful, otherwise return one.
 */
int ReadInputBuffer(char* pQueue ,unsigned int uMaxSize) 
{	
	if(uMaxSize == strlen(sQueue))
	{
		strcpy(pQueue,sQueue);		
		return 0;
	}
	else
	{
		return -1;
	}
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief ReadOptionBuffer 
 *  @return character pointer
 */
char * ReadOptionBuffer()
{
	return strOption;
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief ReadOptionBuffer
 *  @return character pointer
 */
char * AmountOptionBuffer()
{
	return strAmount;
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief DisplayKeypad   
 *  This function is the GUI for keypad.
 *  @param ucArg is to take the decision.
 *  @return true if the function is successful, otherwise returns false.
 */
bool DisplayKeypad(char *ucArg) 
{
	GtkWidget *gtkWindow;
	GtkGrid *gtkVgrid0;	
    gtkLabelPass = gtk_label_new("ABCBank ");
	InitBuffer();

	gtkWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(gtkWindow, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_position(GTK_WINDOW(gtkWindow), GTK_WIN_POS_CENTER);	  
	int nInc=0;
	typedef struct
	{
    	TyKeyPad tyKey_Pad;
	}Key_Pad;
	Key_Pad KeyPad_option;
    for (nInc=0; cArrays[nInc]!=NULL; ++nInc)
	{
        if (0==strcmp(ucArg,cArrays[nInc])) 
		{
			KeyPad_option.tyKey_Pad = nInc;
		}
	}
	switch (KeyPad_option.tyKey_Pad) 
	{
		case CARD_NUMBER:
			gtk_window_set_title(GTK_WINDOW(gtkWindow), "ENTER THE CARDNUMBER");
			break;
		case PIN_NUMBER:
			gtk_window_set_title(GTK_WINDOW(gtkWindow), "ENTER THE PINNUMBER");
			break;
		case AMOUNT:
			gtk_window_set_title(GTK_WINDOW(gtkWindow), "ENTER THE AMOUNT");
			break;
		case NEW_PIN:
			gtk_window_set_title(GTK_WINDOW(gtkWindow), "ENTER THE NEW PIN");
			break;
		case WITHDRAW_AMOUNT:
			gtk_window_set_title(GTK_WINDOW(gtkWindow), "ENTER THE AMOUNT TO WITHDRAW");
			break;
        	default:	
			printf("\n failed number");
			break;
	}
	gtkVgrid0 = (GtkGrid *)gtk_grid_new();
	gtk_grid_set_column_spacing(gtkVgrid0, 3);

	AddButton(gtkVgrid0, "1", G_CALLBACK(WriteInput), (gpointer) "1", ROW_0, COL_0,
	BUTTON_WIDTH, BUTTON_HEIGHT);
	AddButton(gtkVgrid0, "2", G_CALLBACK(WriteInput), (gpointer) "2", ROW_0, COL_1,
	BUTTON_WIDTH, BUTTON_HEIGHT);
	AddButton(gtkVgrid0, "3", G_CALLBACK(WriteInput), (gpointer) "3", ROW_0, COL_2,
	BUTTON_WIDTH, BUTTON_HEIGHT);
	AddButton(gtkVgrid0, "4", G_CALLBACK(WriteInput), (gpointer) "4", ROW_1, COL_0,
	BUTTON_WIDTH, BUTTON_HEIGHT);
	AddButton(gtkVgrid0, "5", G_CALLBACK(WriteInput), (gpointer) "5", ROW_1, COL_1,
	BUTTON_WIDTH, BUTTON_HEIGHT);
	AddButton(gtkVgrid0, "6", G_CALLBACK(WriteInput), (gpointer) "6", ROW_1, COL_2,
	BUTTON_WIDTH, BUTTON_HEIGHT);
	AddButton(gtkVgrid0, "7", G_CALLBACK(WriteInput), (gpointer) "7", ROW_2, COL_0,
	BUTTON_WIDTH, BUTTON_HEIGHT);
	AddButton(gtkVgrid0, "8", G_CALLBACK(WriteInput), (gpointer) "8", ROW_2, COL_1,
	BUTTON_WIDTH, BUTTON_HEIGHT);
	AddButton(gtkVgrid0, "9", G_CALLBACK(WriteInput), (gpointer) "9", ROW_2, COL_2,
	BUTTON_WIDTH, BUTTON_HEIGHT);
	AddButton(gtkVgrid0, "Enter", G_CALLBACK(QuitMain), gtkWindow, ROW_3, COL_0,
	BUTTON_WIDTH, BUTTON_HEIGHT);
	AddButton(gtkVgrid0, "0", G_CALLBACK(WriteInput), (gpointer) "0", ROW_3, COL_1,
	BUTTON_WIDTH, BUTTON_HEIGHT);
	AddButton(gtkVgrid0, "Clear", G_CALLBACK(DeleteInput), gtkWindow, ROW_3, COL_2,
	BUTTON_WIDTH, BUTTON_HEIGHT);

	gtkPass = (GtkEntry *)gtk_entry_new();    	
   	gtk_entry_set_placeholder_text(GTK_ENTRY(gtkPass),"CardNumber");  	
    gtk_grid_attach(GTK_GRID(gtkVgrid0), gtkLabelPass, 0, 1, 1, 1);
    gtk_entry_set_visibility(GTK_ENTRY(gtkPass), 0);
    gtk_grid_attach(GTK_GRID(gtkVgrid0),(GtkWidget*) gtkPass, 1, 1, 1, 1);
	gtk_container_set_border_width(GTK_CONTAINER(gtkWindow), 50);
    gtk_container_add(GTK_CONTAINER(gtkWindow),(GtkWidget*)gtkVgrid0); 

    gtk_widget_show_all(gtkWindow);
    gtk_main();
    gtk_widget_hide(gtkWindow);
	return true;
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief TransactionOptions   
 *  This function is used displaying the transaction option GUI.
 *  @return true if the function is successful, otherwise returns false.
 */
bool TransactionOptions() 
{
	GtkWidget *gtkWindow;
    GtkWidget *gtkButton;    
	GtkGrid *gtkVgrid0;
	
	gtkWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(gtkWindow, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_position(GTK_WINDOW(gtkWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(gtkWindow), "CHOOSE YOUR REQUIRED TRANSACTION OPTION");
	gtk_window_set_position (GTK_WINDOW (gtkWindow), GTK_WIN_POS_CENTER);

	gtkVgrid0 = (GtkGrid *)gtk_grid_new();
	gtk_grid_set_column_spacing(gtkVgrid0, 3);

	gtkButton = gtk_button_new_with_label("CASH WITHDRAWAL");
	g_signal_connect(gtkButton, "clicked", G_CALLBACK(CashWithdrawal), gtkWindow);
	gtk_grid_attach(gtkVgrid0, gtkButton, ROW_0, COL_0, BUTTON_WIDTH, BUTTON_HEIGHT);	

	gtkButton = gtk_button_new_with_label("BALANCE ENQUIRY");
	g_signal_connect(gtkButton, "clicked", G_CALLBACK(BalanceEnquiry), gtkWindow);
	gtk_grid_attach(gtkVgrid0, gtkButton, COL_0, ROW_1, BUTTON_WIDTH, BUTTON_HEIGHT);
	
	gtkButton = gtk_button_new_with_label("PIN CHANGE");
	g_signal_connect(gtkButton, "clicked", G_CALLBACK(PinChange), gtkWindow);
	gtk_grid_attach(gtkVgrid0, gtkButton, COL_2, ROW_0, BUTTON_WIDTH, BUTTON_HEIGHT);
	
	gtkButton = gtk_button_new_with_label("MINISTATEMENT");
	g_signal_connect(gtkButton, "clicked", G_CALLBACK(MiniStatement), gtkWindow);
	gtk_grid_attach(gtkVgrid0, gtkButton, COL_2, ROW_1, BUTTON_WIDTH, BUTTON_HEIGHT);	

	gtkButton = gtk_button_new_with_label("LOGOUT");
	g_signal_connect(gtkButton, "clicked", G_CALLBACK(Quit), gtkWindow);
	gtk_grid_attach(gtkVgrid0, gtkButton, COL_1, ROW_3, BUTTON_WIDTH, BUTTON_HEIGHT);	

	gtk_container_set_border_width(GTK_CONTAINER(gtkWindow), 300);
	gtk_container_add(GTK_CONTAINER(gtkWindow), (GtkWidget*)gtkVgrid0);
	gtk_widget_show_all(gtkWindow);
	gtk_main();	
	gtk_widget_hide(gtkWindow);
	gtk_widget_destroy(gtkWindow);
	
	return true;
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief AmountOption   
 *  This function is used displaying the Denomination option GUI.
 *  @return true if the function is successful, otherwise returns false.
 */
bool AmountOption() 
{
	GtkWidget *gtkWindow;
    GtkWidget *gtkButton;    	
	GtkGrid *gtkVgrid0;
	
	gtkWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(gtkWindow, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_position(GTK_WINDOW(gtkWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(gtkWindow), "CHOOSE YOUR REQUIRED DENOMINATION OPTION");

	gtkVgrid0 = (GtkGrid *)gtk_grid_new();
	gtk_grid_set_column_spacing(gtkVgrid0, 3);

	gtkButton = gtk_button_new_with_label("100");
	g_signal_connect(gtkButton, "clicked", G_CALLBACK(CashWithdrawal), gtkWindow);
	gtk_grid_attach(gtkVgrid0, gtkButton, ROW_0, COL_0, BUTTON_WIDTH, BUTTON_HEIGHT);	

	gtkButton = gtk_button_new_with_label("500");
	g_signal_connect(gtkButton, "clicked", G_CALLBACK(BalanceEnquiry), gtkWindow);
	gtk_grid_attach(gtkVgrid0, gtkButton, COL_1, ROW_0, BUTTON_WIDTH, BUTTON_HEIGHT);
	
	gtkButton = gtk_button_new_with_label("2000");
	g_signal_connect(gtkButton, "clicked", G_CALLBACK(MiniStatement), gtkWindow);
	gtk_grid_attach(gtkVgrid0, gtkButton, COL_2, ROW_0, BUTTON_WIDTH, BUTTON_HEIGHT);
	
	gtkButton = gtk_button_new_with_label("QUIT");
	g_signal_connect(gtkButton, "clicked", G_CALLBACK(Quit), gtkWindow);
	gtk_grid_attach(gtkVgrid0, gtkButton, COL_1, ROW_3, BUTTON_WIDTH, BUTTON_HEIGHT);	

	gtk_container_set_border_width(GTK_CONTAINER(gtkWindow), 300);
	gtk_container_add(GTK_CONTAINER(gtkWindow), (GtkWidget*)gtkVgrid0);
	gtk_widget_show_all(gtkWindow);
	gtk_main();	
	gtk_widget_hide(gtkWindow);
	gtk_widget_destroy(gtkWindow);

	return true;
}

