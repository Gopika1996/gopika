/*********************************.FILE_HEADER.*******************************/
/** @file client_main.c
 *  @brief This main function is acting as a master control unit, which controls
    all the other interfaces.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author
 */
/***********************.INCLUDES****************************************/
#include "login.h"
#include "keypad.h"
#include "client_operations.h"
#include "encoding.h"
#include "client.h"
#include "popup.h"
#include "cash_dispenser.h"
#include <pthread.h>
/***********************.MACROS****************************************/
/*! 
   \brief sets the constant integer value for strings.
   \param BUFSIZE input value  
 */
#define BUFSIZE 20
/*! 
   \brief sets the constant integer value for strings.
   \param LENGTH input value  
 */
#define LENGTH 4
/*! 
   \brief sets the constant integer value for strings.
   \param PRIORITY_HIGH input value  
 */
#define PRIORITY_HIGH 0
/*! 
   \brief sets the constant integer value for strings.
   \param PRIORITY_LOW input value  
 */
#define PRIORITY_LOW 1
/*! 
   \brief sets the constant integer value for strings.
   \param AMOUNT_BUFFER input value  
 */
#define AMOUNT_BUFFER "105"
/*! 
   \brief sets the constant integer value for strings.
   \param CURRENT_BALANCE input value  
 */
#define CURRENT_BALANCE "101"
/*! 
   \brief sets the constant integer value for strings.
   \param PIN_CHANGE input value  
 */
#define PINCHANGE "104"
/*! 
   \brief sets the constant integer value for strings.
   \param WITHDRAW_AMOUNT input value  
 */
#define WITHDRAW_AMOUNT "103"
/*! 
   \brief sets the constant integer value for strings.
   \param DATA_LOSS input value  
 */
#define DATA_LOSS "111"
/*! 
   \brief sets the constant integer value for strings.
   \param MINISTATEMENT input value  
 */
#define MINISTATEMENT "102"
/*! 
   \brief sets the constant integer value for strings.
   \param USER_BLOCKED input value  
 */
#define USER_BLOCKED "000" 
/*! 
   \brief sets the constant integer value for strings.
   \param USER_NAME input value  
 */
#define USER_NAME "001"
/*! 
   \brief sets the constant integer value for strings.
   \param AUTHENTICATION_FAILED input value  
 */
#define AUTHENTICATION_FAILED "002"
/*! 
   \brief sets the constant integer value for strings.
   \param BLOCKED input value  
 */
#define BLOCK_USER "100"
/*! 
   \brief sets the constant integer value for strings.
   \param INDEX_VALUE input value  
 */
#define INDEX_VALUE 3
/*! 
   \brief sets the constant integer value for strings.
   \param LENGTH_OF_CARD input value  
 */
#define LENGTH_OF_CARD 5

/*! 
   \brief sets the constant integer value for strings.
   \param LENGTH_OF_PIN input value  
 */
#define LENGTH_OF_PIN 4

/********************************************************************************/
/** 
 * brief This is an enumeration.
 * This is to define the status of client state machine.
 */
typedef enum 
{
	BLOCKED,
	AUTHENTICATE

}TyCondition;
/** 
 * brief This is an enumeration.
 * This is to define the status of client state machine.
 */
typedef enum {
	LOGIN,
	READ_USER_INFO,
	SEND_INFO,
	RECEIVE_INFO,
	ANALYSE,
	TRANSOPTIONS,
	READ_OPTION_BUFFER,
	BALANCE_ENQUIRY,
	MINI_STATEMENT,
	PIN_CHANGE,
	CASH_WITHDRAWAL,	
	EXIT
} TyStatus;
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief OperatorLogin
 *  This function checks whether an operator is logined or not.
 *  
 *  @return void*.
 */
void* OperatorLogin()
{
	printf("waiting for an operator to login\n");
        int *ret = malloc(sizeof(int));
	while(1)
	{
    		/* launch a command and gets its output */
    		FILE *fp = popen("mount | grep /dev/sdb1", "r");
    		if (NULL != fp)
    		{
        	/* test if something has been outputed by the command */
        		if(EOF != fgetc(fp))
        		{     			
        			puts("/dev/sdb1 is mounted");
					*ret = 1;
				break;
        		}        
        	/* close the command file */
        	pclose(fp);        
    		}
	} 
	pthread_exit(ret);
    
}	
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief main
 *  Main function control all the other functions.
 *  @param agrc is the number of command line argument.
 *  @param agrv[] array of string representing the command line arguments.
 *  @return int.
 */
int main(int agrc, char *agrv[])
{
    pthread_t pthread;
    int iInterrupt=0;
    char* cpBuffer=NULL, *cpTmp=NULL,*cpBuf=NULL,*cpDecision=NULL,*cpValue=NULL;
    static char scCardNumber[BUFSIZE]={0} ,scPIN[BUFSIZE]={0}, scSendData[BUFSIZE] = {0},scEncryptedData[BUFSIZE]={0},scDecryptedData[BUFSIZE]={0};
    char scBackup[BUFSIZE]={0},scNewPIN[BUFSIZE]={0},scBalance[BUFSIZE]={0},scMinistmnt[BUFSIZE]={0},scOption[BUFSIZE]={0};
    static char scReceiveMsg[(BUFSIZE*BUFSIZE)], scAmount[BUFSIZE];
    static bool blLogin ,blStatus = false,blTrans=false;
    unsigned char ucbuf = 0;
    cpDecision = (char*)malloc(BUFSIZE*sizeof(*cpDecision));
    cpValue = (char*)malloc(BUFSIZE*sizeof(*cpValue));

    if (cpDecision == NULL) 
    {
        printf("Memory not allocated.\n"); 
        exit(0); 
    } 
    if (cpValue == NULL)
    { 
       	printf("Memory not allocated.\n"); 
        exit(0); 
    } 
    gtk_init(&agrc, &agrv);
    TyStatus tystat = LOGIN;
    TyCondition tycond;
    iInterrupt=pthread_create(&pthread,NULL,OperatorLogin,NULL);
    while (!iInterrupt) 
    {
	switch (tystat) 
	{
	/*---- Inside user login----*/
	    case LOGIN:
	        PopUp("WELCOME");			
		blLogin = Login();
			
		if (blLogin == true)
		{
		    tystat = READ_USER_INFO;
		}
		else
		{
		     tystat = LOGIN;
		}
		break;
		/*---- Read User Information----*/
	    case READ_USER_INFO:			
		if(blStatus == false)
		{
		    scCardNumber[0]='\0';				
		    blLogin = false;           
		    blLogin = DisplayKeypad("CARD_NUMBER");
		    if (blLogin == true)
		    {
			int uReturnStatus;					
			uReturnStatus=ReadInputBuffer(scCardNumber,LENGTH_OF_CARD) ;
			printf("\n%d",uReturnStatus);
			printf("\n%s",scCardNumber);
			strcpy(scBackup,scCardNumber);
			strcpy(scBalance,scCardNumber);
			strcpy(scMinistmnt,scCardNumber);
			strcpy(scOption,scCardNumber);
			if(-1 == uReturnStatus)
			{
			    PopUp("INVALID_CARD");
			    tystat = LOGIN;						
			}
			else
			{
			    blStatus=true;
			    FileOperation("NEW LOGIN   ",scBackup);
			    tystat = READ_USER_INFO;
			}
		    }
		}
		else
		{
		    blLogin = false;
		    blLogin = DisplayKeypad("PIN_NUMBER");
		    if (blLogin == true)
		    {
			scPIN[0]='\0';
			int uReturnStatus;
			uReturnStatus=ReadInputBuffer(scPIN,LENGTH_OF_PIN) ;
			if(-1 == uReturnStatus)
			{
			    ucbuf++;
			    if (ucbuf < INDEX_VALUE)
			    {
				PopUp("PIN_ERROR");
				sleep(2);
				tystat = READ_USER_INFO;
			    }
			    else
			    {
				PopUp("INVALID_PIN");
			        tycond = BLOCKED;
				tystat = SEND_INFO;
			    }                       
			}
			else
			{
			    PopUp("PROCESS");
			    blStatus=false;
			    tycond = AUTHENTICATE;
			    tystat = SEND_INFO;
			}
		    } 
				        
		}			 
		break;
            case SEND_INFO:
		switch(tycond)
		{
		    /*---- Send the server to block the user----*/
		    case BLOCKED:
		        cpTmp = Concatenate(scCardNumber,USER_BLOCKED);				
		        strcpy(scEncryptedData,Encrypt(cpTmp,strlen(cpTmp)));				
		        ClientCommunication(scEncryptedData, scReceiveMsg,PRIORITY_HIGH);				
		        PopUp("BLOCKED");
				
		        tystat = LOGIN;
		        break;
		    /*---- Used for user authentication----*/
		    case AUTHENTICATE:				
			cpTmp = Concatenate(scCardNumber,scPIN);				
			strcpy(scEncryptedData,Encrypt(cpTmp,strlen(cpTmp)));
			cpTmp=NULL;				
			ClientCommunication(scEncryptedData, scReceiveMsg,PRIORITY_HIGH);
				
			tystat = RECEIVE_INFO;
			break;

		     default:
			break;
		}
		break;
            /*---- Used to read the receive information from the server--*/
	    case RECEIVE_INFO:				
		ClientCommunication(scSendData,scReceiveMsg,PRIORITY_LOW);				
		strcpy(scDecryptedData,Decrypt(scReceiveMsg,strlen(scReceiveMsg)));				
		tystat = ANALYSE;
		break;
	    /*---- Analyse the received information from the server----*/			
	    case ANALYSE:				
		blLogin = Parsing(scDecryptedData,cpDecision,strlen(scDecryptedData)-INDEX_VALUE,INDEX_VALUE);				
		/*---- If the user is blocked user----*/
		if(0==strcmp(cpDecision,BLOCK_USER))				
		{
		    PopUp("BLOCKED");		   
		    tystat = LOGIN;
		}
		/*----Return current balance----*/				
		if(0==strcmp(cpDecision,CURRENT_BALANCE))				
		{
		    blLogin = Parsing(scDecryptedData,cpValue,0,(strlen(scDecryptedData)-INDEX_VALUE));				
		    Identification(cpValue,"BALANCE");
		    FileOperation("AMOUNT WITHDRAWED    ",scBackup);		
		   
		    tystat = LOGIN;
		}
		/*---- If authentication is failed----*/
		else if(0==strcmp(cpDecision,AUTHENTICATION_FAILED))
		{
		    blLogin = Parsing(scDecryptedData,cpValue,0,(strlen(scDecryptedData)-INDEX_VALUE));
		    Identification(cpValue,"AUTHENTICATION");
		    scPIN[0]='\0';
		   
		    tystat = LOGIN;
		}
		/*----Return name of the user----*/
		else if(0==strcmp(cpDecision,USER_NAME))
		{
		    blLogin = Parsing(scDecryptedData,cpValue,0,strlen(scDecryptedData)-INDEX_VALUE);
		    Identification(cpValue,"NAME");
		    tystat = TRANSOPTIONS;
		}
		/*----PIN change is success----*/
		else if(0==strcmp(cpDecision,PINCHANGE))
		{
		    blLogin = Parsing(scDecryptedData,cpValue,0,(strlen(scDecryptedData)-INDEX_VALUE));
		    Identification(cpValue,"PINCHANGE");
		    
		    scCardNumber[0]='\0';
		    FileOperation("DONE PINCHANGE   ",scBackup);
		    tystat = LOGIN;
		}
		/*----Return entered amount is present in account----*/
		else if(0==strcmp(cpDecision,WITHDRAW_AMOUNT))
		{
		    blLogin = Parsing(scDecryptedData,cpValue,0,(strlen(scDecryptedData)-INDEX_VALUE));
		    if(0==strcmp(cpValue,"VALID"))
		    {
			blLogin = AmountOption();
			cpBuffer= AmountOptionBuffer();
			if(0==strcmp(cpBuffer,"QUIT"))
			{			    
			    tystat = LOGIN;
			}
			else
			{
			    if(atoi(scAmount)<atoi(cpBuffer))
			    {
				PopUp("INVALID_DENOMINATION");
			    }
			    else
			    {
				int uReturn=0;
				uReturn=Dispenser(atoi(scAmount),atoi(cpBuffer));
				if(uReturn == 1)
				{			    
				     Identification(":(","CONNECTION_FAILED");				    
				     tystat = EXIT;
				}
				else
				{
				    uReturn=Collect_Money();
				    if(0==uReturn)
				    {
		                        printf("\nThe value of uReturn%d",uReturn);
					cpBuf=cpTmp=NULL;
			                cpBuf = Concatenate(scOption,AMOUNT_BUFFER);
			                cpTmp = Concatenate(cpBuf, scAmount);
					scNewPIN[0]='\0';
					strcpy(scEncryptedData,Encrypt(cpTmp,strlen(cpTmp)));
			                cpTmp=NULL;
					ClientCommunication(scEncryptedData, scReceiveMsg,PRIORITY_HIGH);
	                            }
				}
			   }			   
			   tystat = LOGIN;
			   }
			}
		   else
		   {
			PopUp("INVALID_AMOUNT");			
			tystat = LOGIN;
		   }
		}
				/*-----If there is any dataloss----*/
		else if(0==strcmp(cpDecision,DATA_LOSS))
		{		    
		    tystat = LOGIN;
		}
		else
		{	
		    Identification(scDecryptedData,"CONNECTION_FAILED");		   
		    tystat = LOGIN;
		}
		break;
	    /*-----Shows the available transaction option----*/
            case TRANSOPTIONS:
		blTrans=TransactionOptions();
		if (blTrans == true)
		{
		    tystat = READ_OPTION_BUFFER;
		}
		else
		{
		    blTrans=TransactionOptions();
		}
		break;
            /*-----Read the transaction option----*/
            case READ_OPTION_BUFFER:
	        cpBuffer = ReadOptionBuffer();
		if(0==strcmp(cpBuffer,"BALANCEENQUIRY"))
		{
		    tystat = BALANCE_ENQUIRY;
		}
		else if(0==strcmp(cpBuffer,"MINISTATEMENT"))
		{
		    tystat = MINI_STATEMENT;
		}
		else if(0==strcmp(cpBuffer,"PINCHANGE"))
		{
		    tystat = PIN_CHANGE;
		}
		else if(0==strcmp(cpBuffer,"CASHWITHDRAWAL"))
		{
		    tystat = CASH_WITHDRAWAL;
		}
		else if(0==strcmp(cpBuffer,"QUIT"))
		{		   
		    tystat = LOGIN;
		}
		else
		{		    
		    tystat = LOGIN;
		}
		break;
            /*-----Balance Enquiry----*/
	    case BALANCE_ENQUIRY:
		cpTmp = Concatenate(scBalance, CURRENT_BALANCE);				
		strcpy(scEncryptedData,Encrypt(cpTmp,strlen(cpTmp)));
		cpTmp=NULL;				
		ClientCommunication(scEncryptedData, scReceiveMsg,PRIORITY_HIGH);
		tystat = RECEIVE_INFO;
		FileOperation("PERFRORMED BALANCE ENQUIRY   ",scBalance);
		break;
	   /*-----Mini statement----*/
	   case MINI_STATEMENT:				
		cpTmp = Concatenate(scMinistmnt,MINISTATEMENT);				
		strcpy(scEncryptedData,Encrypt(cpTmp,strlen(cpTmp)));				
		ClientCommunication(scEncryptedData, scReceiveMsg,PRIORITY_HIGH);

		ClientCommunication(scSendData,scReceiveMsg,PRIORITY_LOW);
		Identification(scReceiveMsg,"MINISTATEMENT");
		FileOperation("PERFORMED MINISTATEMENT CHECK	",scBackup);				
		tystat = TRANSOPTIONS;				
		break;
	   /*-----PIN Change----*/
	   case PIN_CHANGE:
		blLogin = false;
		blLogin = DisplayKeypad("NEW_PIN");
		if (blLogin == true)
		{   
		    int uReturnStatus;
		    uReturnStatus=ReadInputBuffer(scNewPIN,4) ;
		    if(0 == uReturnStatus)
		    {
		        cpBuf = Concatenate(scBackup,PINCHANGE);						
		        cpTmp = Concatenate(cpBuf, scNewPIN);						
		        strcpy(scEncryptedData,Encrypt(cpTmp,strlen(cpTmp)));
		        cpTmp=NULL;
		        scBackup[0]='\0';						
		        ClientCommunication(scEncryptedData, scReceiveMsg,PRIORITY_HIGH);

			tystat = RECEIVE_INFO;
		    }
		    else
		    {
			blStatus=false;
			tystat = LOGIN;
		    }
		}
		break;
	    /*-----Cash Withdrawal----*/
	    case CASH_WITHDRAWAL:				
		blLogin = false;
		blLogin = DisplayKeypad("WITHDRAW_AMOUNT");
		if (blLogin == true)
		{ 
		    int uReturnStatus;
		    uReturnStatus=ReadInputBuffer(scAmount,4) ;                                        
		    if(100>atoi(scAmount)||10000<atoi(scAmount)||0!=((atoi(scAmount)%10)))
		    { 
			PopUp("INVALID_AMOUNT");
			blStatus=false;
			tystat = LOGIN;
		    }
		    else
		    {
		        if(0 == uReturnStatus)
		        {					
			    cpBuf = Concatenate(scBackup,WITHDRAW_AMOUNT);							
			    cpTmp = Concatenate(cpBuf, scAmount);
			    scNewPIN[0]='\0';							
			    strcpy(scEncryptedData,Encrypt(cpTmp,strlen(cpTmp)));
			    cpTmp=NULL;							
			    ClientCommunication(scEncryptedData, scReceiveMsg,PRIORITY_HIGH);

			    tystat = RECEIVE_INFO;
		        }
		        else
		        {
			    blStatus=false;
			    tystat = LOGIN;
		         }
	            }
	        }
		break;
            /*-----Exit----*/
	    case EXIT:
	        exit(0);
		break;
	    default:
		break;
	}
    }	
	free(cpValue);
	free(cpDecision);
	pthread_join(pthread,NULL);
	return 0 ;
}
