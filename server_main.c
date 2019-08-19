/*********************************.FILE_HEADER.*******************************/
/** @file server_main.c
 *  @brief This program contains main function.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */
/***********************.INCLUDES****************************************/
#include "serveroperations.h"
#include "fetch.h"
#include "operations.h"
#include "encoding.h"
#include "authentication.h"
#include "dbupdate.h"
#include "statuscheck.h"
/***********************.MACROS*************************************/
/*! 
   \brief sets the constant integer value for strings.
   \param BUFFER_SIZE input value  
 */
#define BUFFER_SIZE 256 
/*! 
   \brief sets the constant integer value for strings.
   \param PRIORYLOW input value  
 */
#define PRIORYLOW 0 
/*! 
   \brief sets the constant integer value for strings.
   \param PRIORYHIGH input value  
 */
#define PRIORYHIGH 1 
/*! 
   \brief sets the constant integer value for strings.
   \param USER_BLOCKED input value  
 */
#define USER_BLOCKED "1"
/*! 
   \brief sets the constant integer value for strings.
   \param CARD_INDEX input value  
 */
#define CARD_INDEX 5
/*! 
   \brief sets the constant integer value for strings.
   \param MIN_INDEX input value  
 */
#define MIN_INDEX 0
/*! 
   \brief sets the constant integer value for strings.
   \param SIZEOF_KEYVALUE input value  
 */
#define SIZEOF_KEYVALUE 3
/*! 
   \brief sets the constant integer value for strings.
   \param PIN_LENGTH input value  
 */
#define PIN_LENGTH 4
/*! 
   \brief sets the constant integer value for strings.
   \param AMOUNT_BUFFER input value  
 */
#define AMOUNT_BUFFER 8
/*! 
   \brief sets the constant integer value for strings.
   \param MAX_LENGTH input value  
 */
#define MAX_LENGTH 9
/*! 
   \brief sets the constant integer value for strings.
   \param AUTHENTICATION_FAILED input value  
 */
#define AUTHENTICATION_FAILED "002"
/*! 
   \brief sets the constant integer value for strings.
   \param USER_BLOCKED input value  
 */
#define BLOCK_USER "000" 
/*! 
   \brief sets the constant integer value for strings.
   \param USER_NAME input value  
 */
#define USER_NAME "001"
/*! 
   \brief sets the constant integer value for strings.
   \param BLOCKED input value  
 */
#define BLOCKED "100"
/*! 
   \brief sets the constant integer value for strings.
   \param AMOUNT_BUFFER input value  
 */
#define WITHDRAWAMOUNTBUFFER "105"
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
   \param DATALOSS input value  
 */
#define DATALOSS "111"

/***********************.DECLARATIONS*************************************/
/** @enum TyStatus
    *  Enumeration used to store the different states in server machine.
    *
    */
typedef enum {

    SERVER_RECEIVE = 0,
    SERVER_SEND,
    DECRYPT,
    ENCRYPT,
    PARSING,
    AUTHENTICATION,
    STATUS_CHECK,
    EXIT
} TyStatus;

/** @brief main
    *  This is the main function used to control all the other function. 
    *  @return integer
    */

int main() 
{
    static char scReceiveMsg[BUFFER_SIZE]={0};
    char psendMessage[BUFFER_SIZE] = {0};
    char cWorkBuffer[BUFFER_SIZE]={0};
    char* cpOption=NULL,*cpCard=NULL,*cpPin=NULL,*cpAmount=NULL,*cpNewPin=NULL,*cpDecision=NULL,*cpTmp=NULL;
    bool blLogin, blStatus = false;
    TyStatus tystat = SERVER_RECEIVE;
    cpCard = (char*)malloc(BUFFER_SIZE*sizeof(*cpCard));    
    cpPin = (char*)malloc(BUFFER_SIZE*sizeof(*cpPin));
    cpOption = (char*)malloc(BUFFER_SIZE*sizeof(*cpOption));    
    cpAmount = (char*)malloc(BUFFER_SIZE*sizeof(*cpAmount));    
    cpNewPin = (char*)malloc(BUFFER_SIZE*sizeof(*cpNewPin));
    cpDecision = (char*)malloc(BUFFER_SIZE*sizeof(*cpDecision));
    cpTmp = (char*)malloc(BUFFER_SIZE*sizeof(*cpTmp));
    if (cpCard == NULL) 
    { 
        printf("Memory not allocated.\n"); 
        exit(0); 
    } 
    if (cpPin == NULL) 
    { 
        printf("Memory not allocated.\n"); 
        exit(0); 
    }
    if (cpOption == NULL) 
    { 
        printf("Memory not allocated.\n"); 
        exit(0); 
    } 
    if (cpAmount == NULL) 
    { 
        printf("Memory not allocated.\n"); 
        exit(0); 
    }
    if (cpNewPin == NULL) 
    { 
        printf("Memory not allocated.\n"); 
        exit(0); 
    }
    if (cpDecision == NULL) 
    { 
        printf("Memory not allocated.\n"); 
        exit(0); 
    }
    if (cpTmp == NULL) 
    { 
        printf("Memory not allocated.\n"); 
        exit(0); 
    }

    while (1) 
    {
        switch (tystat)
        {

	    case SERVER_RECEIVE:            
	        ServerCommunicate(psendMessage, scReceiveMsg,PRIORYLOW);
			tystat = DECRYPT;
			break;
	    case SERVER_SEND:          
			strcpy(psendMessage,cpOption);
			ServerCommunicate(psendMessage, scReceiveMsg,PRIORYHIGH);
			tystat = SERVER_RECEIVE;
			break;
	    case DECRYPT:
			printf("\nInside DECRYPT");
			(void)Decrypt(scReceiveMsg, sizeof(scReceiveMsg));
			printf("\n Received messsage in main :%s", scReceiveMsg);           
			tystat = PARSING;
			break;
	    case ENCRYPT:
			printf("\nInside ENCRYPT");
			(void)Encrypt(cpOption, strlen(cpOption));
			printf("\n AFTER ENCRYPTION messsage in main :%s", cpOption);           
			tystat = SERVER_SEND;
			break;
	    case PARSING:        
			printf("\nInside PARSING");
			blLogin = Parsing(scReceiveMsg,cpCard,MIN_INDEX,CARD_INDEX);
			if(MAX_LENGTH==strlen(scReceiveMsg))
			{
			    blLogin = Parsing(scReceiveMsg,cpPin,CARD_INDEX,PIN_LENGTH);
			    cpOption=fetch(cpCard,"PIN");
			    tystat = AUTHENTICATION;
			}
			else 
			{
			    blLogin = Parsing(scReceiveMsg,cpDecision,CARD_INDEX,SIZEOF_KEYVALUE);
			    if(0==strcmp(CURRENT_BALANCE,cpDecision))
			    {
			        MinistatementUpdate(cpCard,"BALANCECHECKED");
					cpOption=fetch(cpCard,"CURRENTBALANCE");		
					cpTmp=Concatenate(cpOption,CURRENT_BALANCE);
					tystat = ENCRYPT;
		    	}
		    	else if(0==strcmp(cpDecision,MINISTATEMENT))
		    	{
					MinistatementUpdate(cpCard,"TAKENMINISTATEMENT");
					cpOption=fetch(cpCard,"MINISTATEMENT");
					strcpy(psendMessage,cpOption);			
					/*update ministatement*/	
					ServerCommunicate(psendMessage, scReceiveMsg,PRIORYHIGH);
					tystat = SERVER_RECEIVE;
			    }
			    else if(0==strcmp(cpDecision,WITHDRAW_AMOUNT))
			    {
					strcpy(cpAmount, &scReceiveMsg[AMOUNT_BUFFER]);						                
					cpOption=fetch(cpCard,"CURRENTBALANCE");
					if(atof(cpAmount)<=atof(cpOption))
					{
					    strcpy(cpOption,"VALID");			    
					    cpTmp=Concatenate(cpOption,WITHDRAW_AMOUNT);
					    tystat = ENCRYPT;
					}
					else
					{
						strcpy(cpOption,"INVALID");
						cpTmp=Concatenate(cpOption,WITHDRAW_AMOUNT);
						tystat = ENCRYPT;
					}
				}
		    	else if(0==strcmp(cpDecision,WITHDRAWAMOUNTBUFFER))
		    	{
					MinistatementUpdate(cpCard,"CASHWITHDRAWN");
					strcpy(cpAmount, &scReceiveMsg[AMOUNT_BUFFER]);						
					cpOption=fetch(cpCard,"CURRENTBALANCE");
					unsigned int uTotalAmount= atoi(cpOption)-atoi(cpAmount); 
					sprintf(cWorkBuffer,"%u",uTotalAmount);
					DbUpdate(cpCard,"CURRENTBALANCE",cWorkBuffer);
					tystat = SERVER_RECEIVE;
		    	}
			    else if(0==strcmp(cpDecision,PINCHANGE))
			    {
					MinistatementUpdate(cpCard,"PINCHANGED");
					strcpy(cpNewPin, &scReceiveMsg[AMOUNT_BUFFER]);
					DbUpdate(cpCard,"PIN",cpNewPin);
					strcpy(cpOption,"DONE");
					cpTmp=Concatenate(cpOption,PINCHANGE);
					tystat = ENCRYPT;
			    }
			    else if(strcmp(cpDecision,BLOCKED)==0)
			    {
					strcpy(cpAmount, &scReceiveMsg[CARD_INDEX]);						                    
					DbUpdate(cpCard,"BLOCKED",USER_BLOCKED);
					tystat = EXIT;
			    }
			    else
			    {	
					strcpy(cpOption,"DATALOSS");
					cpTmp=Concatenate(cpOption,DATALOSS);
					tystat = ENCRYPT;						
			    }

			}           
        	break;            
        case AUTHENTICATION:				
			blLogin=Authenticate(cpOption,cpPin);
			if(blLogin==true)
			{
			    tystat = STATUS_CHECK;
			}
			else
			{
			    strcpy(cpOption,"FAILED");
			    cpTmp=Concatenate(cpOption,AUTHENTICATION_FAILED);
			    tystat = ENCRYPT;
			}
            break;
	    case STATUS_CHECK:
			blStatus = StatusCheck(cpCard);
			cpOption=fetch(cpCard,"BLOCKED");				
			if(strcmp(cpOption,USER_BLOCKED)==0)
			{
			    strcpy(cpOption,"BLOCKED");
			    cpTmp=Concatenate(cpOption,BLOCK_USER);
			    tystat = ENCRYPT;
			}
			else
			{           
			    if (blStatus == true)
			    {               
				cpOption=fetch(cpCard,"NAME");			
			        Concatenate(cpOption,USER_NAME);
			        tystat = ENCRYPT;               
			    }
			    else
			    {
			        tystat = EXIT;
			    }
			}
            break;
        case EXIT:
            exit(0);
            break;
            
        default:        
            break;

        }

    }
    /* Free the allocated buffers. */
    free(cpCard);
    free(cpPin);
    free(cpNewPin);
    free(cpOption);
    free(cpAmount);
    free(cpDecision);
    free(cpTmp);
    return 0;
}


