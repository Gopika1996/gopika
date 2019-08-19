/*********************************.FILE_HEADER.*******************************/
/** @file popup.c
 *  @brief This program contains the GUI program for the POP-UP window.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */
/***********************.INCLUDES********************************************************************************************/
#include "popup.h"
/**
*constant array declaration
*/
const char* cArray[]=   
{   "NAME",
    "BALANCE",
    "MINISTATEMENT",
    "PINCHANGE",
    "AUTHENTICATION",
    "CONNECTION_FAILED",
    "END",
    "VALID_AMOUNT",
    "VALID_PIN",
    "OPERATOR_LOGIN",
    "DISPENSE_FAILED",
    "DISPENSE_SUCCESS",
    "EXIT",
    NULL
};
/**
*constant array declaration
*/
const char* cBuf[]= 
{   "BLOCKED",
    "PIN_ERROR",
    "INVALID_CARD",
    "PROCESS",
    "WELCOME",
    "INVALID_PIN",
    "INVALID_AMOUNT",
    "INVALID_DENOMINATION",
    "PROCESS_ERROR",
    "DISPENSE_ERROR",            
    NULL
};
/** 
 * brief This is an enumeration.
 * This is to define the pop-up window.
 */
typedef enum
{
    BLOCKED,
    PIN_ERROR,
    INVALID_CARD,
    PROCESS,
    WELCOME,
    INVALID_PIN,
    INVALID_AMOUNT,
    INVALID_DENOMINATION,
    PROCESS_ERROR,
    DISPENSE_ERROR

}TyPopUp;
/** 
 * brief This is an enumeration.
 * This is to define the pop-up window.
 */
typedef enum 
{
    NAME,
    BALANCE,
    MINISTATEMENT,
    PINCHANGE,
    AUTHENTICATION,
    CONNECTION_FAILED,
    END,
    VALID_AMOUNT,
    VALID_PIN,
    OPERATOR_LOGIN,
    DISPENSE_FAILED,
    DISPENSE_SUCCESS,
    EXIT    

}TyCond;
/*! 
   \brief sets the constant integer value for strings.
   \param BUFFER_SIZE input value  
 */
#define BUFFER_SIZE 1024
/*! 
   \brief sets the constant integer value for strings.
   \param WINDOW_WIDTH input value  
 */
#define WINDOW_WIDTH 700
/*! 
   \brief sets the constant integer value for strings.
   \param WINDOW_HEIGHT input value  
 */
#define WINDOW_HEIGHT 750
/*! 
   \brief sets the constant integer value for strings.
   \param SUCCESS input value  
 */
#define SUCCESS 0

/** @brief Pop_Up_Timeout
 *  To quit from the pop-up window.
 *  @param data 
 *  @return gboolean
 */
gboolean Pop_Up_Timeout(gpointer data) {
    GtkWidget *pop_up_widget = (GtkWidget*) data;
    gtk_widget_destroy(pop_up_widget);
    gtk_main_quit();

    return FALSE;
}

/*********************************.FUNCTION_HEADER.*******************************/
/** @brief Identification
 *  This contain  the pop-up window. 
 *  @param pName is the buffer value 
 *  @param ucArg is the pop-up window option
 *  @return when this function is success it returns zero.
 */
int Identification(char* pName, char *ucArg) 
{
    GtkWidget *gtkPopupWindow;
    GtkWidget *gtkLabel;
    char cBuf[BUFFER_SIZE] = { 0 };     
    int nInc=0;
    typedef struct
    {
        TyCond tycond;
    }POPUP_OPTION;
    POPUP_OPTION Popup_option;
    for (nInc=0; cArray[nInc]!=NULL; ++nInc)
    {
        if (0==strcmp(ucArg, cArray[nInc])) 
        {
            Popup_option.tycond = nInc;
        }
    }
        
    gtkPopupWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    /* --- Create a small border --- */
    gtk_container_set_border_width(GTK_CONTAINER(gtkPopupWindow), 10);
    gtk_window_set_resizable(GTK_WINDOW(gtkPopupWindow), FALSE);
    gtk_window_set_decorated(GTK_WINDOW(gtkPopupWindow), FALSE);
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(gtkPopupWindow), TRUE);
    gtk_window_set_skip_pager_hint(GTK_WINDOW(gtkPopupWindow), TRUE);
    gtk_widget_set_size_request(gtkPopupWindow, WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_position(GTK_WINDOW(gtkPopupWindow), GTK_WIN_POS_CENTER);
    
    switch(Popup_option.tycond)
    {
        case NAME:
            g_snprintf(cBuf, sizeof(cBuf), "Hai, %s", pName);
            printf("data is %s", cBuf);
            break;
        case BALANCE:
            g_snprintf(cBuf, sizeof(cBuf), "YOUR CURRENT BALANCE IS %s", pName);
            printf("data is %s", cBuf);
            break;
        case MINISTATEMENT:
            g_snprintf(cBuf, sizeof(cBuf), "YOUR MINISTATEMENT IS %s", pName);
            printf("data is %s", cBuf);
            break;
            case PINCHANGE:
            g_snprintf(cBuf, sizeof(cBuf), "PIN CHANGE %s", pName);
            printf("data is %s", cBuf);
            break;      
        case AUTHENTICATION:
            g_snprintf(cBuf, sizeof(cBuf),"PLEASE ENTER A VALID PIN ......AUTHENTICATION  %s", pName);
            printf("data is %s", cBuf);
            break;
        case CONNECTION_FAILED:
            g_snprintf(cBuf, sizeof(cBuf), "UNABLE TO PROCCESS YOUR REQUEST :(.....PLEASE VISIT NEAR BY ATM %s",pName);
            printf("data is %s", cBuf);
            break;
        case END:
            g_snprintf(cBuf, sizeof(cBuf), "THANK YOU FOR USING ATM :) %s",pName);
            printf("data is %s", cBuf); 
            break;
        case VALID_AMOUNT:
            g_snprintf(cBuf, sizeof(cBuf), "PLEASE ENTER A VALID AMOUNT %s",pName);
            printf("data is %s", cBuf);
            break;
        case VALID_PIN:
            g_snprintf(cBuf, sizeof(cBuf), "PLEASE ENTER A VALID PIN %s",pName);
            printf("data is %s", cBuf);
            break;
        case OPERATOR_LOGIN:
            g_snprintf(cBuf, sizeof(cBuf), "OPERATOR LOGIN %s",pName);
            printf("data is %s", cBuf);
            break;
        case DISPENSE_FAILED:
            g_snprintf(cBuf, sizeof(cBuf), "UNABLE TO DISPENSE AMOUNT %s",pName);
            printf("data is %s", cBuf);
            break;
        case DISPENSE_SUCCESS:
            g_snprintf(cBuf, sizeof(cBuf), "PLEASE COLLECT THE CASH %s",pName);
            printf("data is %s", cBuf);
            break;
        case EXIT:
            exit(0);
            break;
        default:
            break;
    }
    /* Create a gtkLabel and attach it to the content area of the dialog */
    gtkLabel = gtk_label_new(cBuf);
    gtk_label_set_justify(GTK_LABEL(gtkLabel), GTK_JUSTIFY_CENTER);
    gtk_container_add(GTK_CONTAINER(gtkPopupWindow), gtkLabel);

    gtk_widget_set_events(gtkPopupWindow, GDK_FOCUS_CHANGE_MASK);
    g_timeout_add(3000, Pop_Up_Timeout, gtkPopupWindow);
    
    /* Show the gtkPopupWindow  */
    gtk_widget_show_all(gtkPopupWindow);
    gtk_widget_grab_focus(gtkPopupWindow);
    gtk_main();

    return SUCCESS;
}
/********************************.FUNCTION_HEADER.*******************************/
/** @brief Show_Question
 *  This interface is used to create a pop-up window.
 *  
 *  @return Integer
 */
bool Show_Question() {

    GtkWidget *gtkWindow;
    GtkWidget *gtkDialog;
    gint response_id;
    char cBuff[BUFFER_SIZE];
    
    /*Create a gtkWindow with a title and a default size*/
    gtkWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(gtkWindow), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(gtkWindow), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_title(GTK_WINDOW(gtkWindow), "ABCBANKATM");

    gtkDialog = gtk_message_dialog_new(GTK_WINDOW(gtkWindow),
    GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_QUESTION,
    GTK_BUTTONS_YES_NO, "Do you want to perform another transaction?");
    gtk_window_set_title(GTK_WINDOW(gtkDialog), "");
    
    /*Connecting the clicked signal to the callback*/
    g_signal_connect(G_OBJECT(gtkWindow), "destroy", G_CALLBACK(gtk_main_quit),
    G_OBJECT(gtkWindow));

    response_id = gtk_dialog_run(GTK_DIALOG(gtkDialog));
    sprintf(cBuff, "%s\n", (response_id == GTK_RESPONSE_YES) ? "YES" : "NO");
    if (strcmp(cBuff, "YES") == 0)
    {
        return true;
    } 
    else    
    {
        return false;
    }
    /*This will cause the gtkDialog to be destroyed*/
    gtk_widget_destroy(gtkDialog);
    gtk_widget_hide(gtkWindow);
    gtk_widget_destroy(gtkWindow);
}
/********************************.FUNCTION_HEADER.*******************************/
/** @brief PopUp
 *  This interface is used to create a pop-up gtkWindow.
 *  @param  ucArg will determine which pop-up to be appeared while calling.
 *  @return Integer
 */
int PopUp(char *ucArg) 
{
    GtkWidget *gtkPopupWindow;
    GtkWidget *gtkLabel;
    gtkPopupWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(gtkPopupWindow), 10);
    gtk_window_set_resizable(GTK_WINDOW(gtkPopupWindow), FALSE);
    gtk_window_set_decorated(GTK_WINDOW(gtkPopupWindow), FALSE);
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(gtkPopupWindow), TRUE);
    gtk_window_set_skip_pager_hint(GTK_WINDOW(gtkPopupWindow), TRUE);
    gtk_widget_set_size_request(gtkPopupWindow, WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_position(GTK_WINDOW(gtkPopupWindow), GTK_WIN_POS_CENTER);

    int nInc=0;
    typedef struct
    {
        TyPopUp tyPop_Up;
    }Pop_Up;
    Pop_Up PopUp_option;
    for (nInc=0; cBuf[nInc]!=NULL; ++nInc)
    {
        if (0==strcmp(ucArg, cBuf[nInc])) 
        {
             PopUp_option.tyPop_Up = nInc;
        }
    }

    switch (PopUp_option.tyPop_Up) 
    {
    case BLOCKED:
        gtkLabel = gtk_label_new("Sorry you are made three attempts ...You are BLOCKED :(");
        break;
    case PIN_ERROR:
        gtkLabel = gtk_label_new("Please enter 4-Digit valid PIN Number");
        break;
    case INVALID_CARD:
        gtkLabel = gtk_label_new("Unable to Read.Please insert Card Again...........");
        break;
    case PROCESS:
        gtkLabel = gtk_label_new("Processing...............");
        break;
    case WELCOME:
        gtkLabel =gtk_label_new("Welcome to ATM.......................\n Please wait...............");
        break;
    case INVALID_PIN:
        gtkLabel = gtk_label_new("Sorry.Pin is Inavlid..Please try again after 24 Hours");
        break;
    case INVALID_AMOUNT:
        gtkLabel = gtk_label_new("Please enter valid amount......");
        break;
    case INVALID_DENOMINATION:
        gtkLabel = gtk_label_new("Please Choose a valid denomination......");
        break;
    case PROCESS_ERROR:
        gtkLabel = gtk_label_new("Unale to process your request......Please visit near by ATM :(");
        break;
    case DISPENSE_ERROR:
        gtkLabel = gtk_label_new("Unale to Dispense amount in terms of 100(");
        break;
    default:

        break;

    }
    gtk_label_set_justify(GTK_LABEL(gtkLabel), GTK_JUSTIFY_CENTER);
    gtk_container_add(GTK_CONTAINER(gtkPopupWindow), gtkLabel);
    gtk_widget_set_events(gtkPopupWindow, GDK_FOCUS_CHANGE_MASK);
    g_timeout_add(3000, Pop_Up_Timeout, gtkPopupWindow);
    gtk_widget_show_all(gtkPopupWindow);
    gtk_widget_grab_focus(gtkPopupWindow);
    gtk_main();

    return SUCCESS;

}
/********************************.FUNCTION_HEADER.*******************************/
/** @brief Collect_money
 *  This interface is used to create a pop-up gtkWindow.
 *   
 *  @return Integer.
 */
unsigned int  Collect_Money() 
{
    GtkWidget *gtkWindow;   
    int response_id;

    gtkWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(gtkWindow), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(gtkWindow), WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_title(GTK_WINDOW(gtkWindow), "Message dialogs");
      
    gtk_container_set_border_width(GTK_CONTAINER(gtkWindow), 15);
    GtkWidget *gtkDialog;
    gtkDialog = gtk_message_dialog_new(GTK_WINDOW(gtkWindow),
                                      GTK_DIALOG_DESTROY_WITH_PARENT,
                                      GTK_MESSAGE_INFO,
                                      GTK_BUTTONS_OK,
                                      "Please collect the money and press OK");
    response_id = gtk_dialog_run(GTK_DIALOG(gtkDialog));    
    switch (response_id)
    {
        case GTK_RESPONSE_OK:
            break;
        default:                 
            printf("\nthe value of OK button:%d",response_id);
            gtk_widget_hide(gtkWindow);
            gtk_widget_destroy(gtkWindow);
            return 1;
    }
    if (response_id == GTK_RESPONSE_OK)
    {
        printf("\nGot OK");
    }   
    gtk_widget_hide(gtkWindow);
    gtk_widget_destroy(gtkWindow);  

    return SUCCESS;
}
/********************************.FUNCTION_HEADER.*******************************/
/** @brief TotalAmount
 *  This interface is used to create a pop-up gtkWindow.
 *  @param  nThousand is the amount of Thousand currencies.
 *  @param  nFiveHundred is the amount of FiveHundred currencies.
 *  @param  nHundred is the amount of Hundred currencies.
 *  @return Integer
 */
int TotalAmount(int nThousand,int nFiveHundred,int nHundred)
{
    GtkWidget *gtkPopupWindow;
    GtkWidget *gtkLabel;
    char cBuf[BUFFER_SIZE] = { 0 }; 
    gtkPopupWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);   
    /* --- Create a small border --- */
    gtk_container_set_border_width(GTK_CONTAINER(gtkPopupWindow), 10);
    gtk_window_set_resizable(GTK_WINDOW(gtkPopupWindow), FALSE);
    gtk_window_set_decorated(GTK_WINDOW(gtkPopupWindow), FALSE);
    gtk_window_set_skip_taskbar_hint(GTK_WINDOW(gtkPopupWindow), TRUE);
    gtk_window_set_skip_pager_hint(GTK_WINDOW(gtkPopupWindow), TRUE);
    gtk_widget_set_size_request(gtkPopupWindow, WINDOW_WIDTH, WINDOW_HEIGHT);
    gtk_window_set_position(GTK_WINDOW(gtkPopupWindow), GTK_WIN_POS_CENTER);
    g_snprintf(cBuf, sizeof(cBuf), "TWOTHOUSAND = %d\n\nFIVEHUNDRED=%d\n\nHUNDRED=%d",nThousand,nFiveHundred,nHundred);
    printf("%s", cBuf);
    /* Create a gtkLabel and attach it to the content area of the dialog */
    gtkLabel = gtk_label_new(cBuf);
    gtk_label_set_justify(GTK_LABEL(gtkLabel), GTK_JUSTIFY_CENTER);
    gtk_container_add(GTK_CONTAINER(gtkPopupWindow), gtkLabel);

    gtk_widget_set_events(gtkPopupWindow, GDK_FOCUS_CHANGE_MASK);
    g_timeout_add(3000, Pop_Up_Timeout, gtkPopupWindow);
    
    /* Show the gtkPopupWindow  */
    gtk_widget_show_all(gtkPopupWindow);
    gtk_widget_grab_focus(gtkPopupWindow);
    gtk_main();

    return SUCCESS;
 
}

