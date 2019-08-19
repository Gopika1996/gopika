/*********************************.FILE_HEADER.*******************************/
/** @file dbupdate.c
 *	@brief This program contains function for database update.
 *	@date 2019/03/06
 *	@copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *	@author 
 */

/***********************.INCLUDES**************************************************************/
#include "dbupdate.h"
#include "fetch.h"
/*! 
   \brief sets the constant integer value for strings.
   \param SUCCESS input value  
 */
#define SUCCESS 0
/***********************.DECLARATIONS********************************************************************************************/
/** \brief define global variable*/
static int QueuePos = 0; /** \brief QueuePos is initialised as zero*/
static char* pcQueue[MAX_SIZE] = {0};/** \brief pcQueue is initialised as zero*/
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief callback
 *	This function is used in conjunction with the sqlite3_exec() function. 
 *	@param data,argc,argv,azColName.
 *	@return zero if the function is successful, otherwise return one.
 */
static int callback(void *data, int argc, char **argv, char **azColName)
{
	printf("Inside Callback Function\n");
	return SUCCESS;
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief DbUpdate
 *      Interface for database updation.
 *	@param pcCardnumber is used to hold the card number.
 *	@param pcOption specifies which field in the database need to be updated.
 *	@param pcValue is the value corresponding to the pcOption.
 *	@return zero if the function is successful, otherwise return one.
 */
int DbUpdate(char *pcCardnumber,char* pcOption,char *pcValue) 
{
    sqlite3 *sqlDb;
    char *zErrMsg = 0;
    int nDbOpen =0;
    char *pcSql = NULL;
    const char* data = "Callback function called";
    char cbuf[1024] = {0};
    /* ---This routine opens a connection to an SQLite database file and returns a database connection object to be used by other SQLite routines.---*/
    nDbOpen = sqlite3_open("test1.db", &sqlDb);
    printf("\nthe value of 	pcCardnumber:%s",pcCardnumber);
    printf("\nthe value of 	pcOption:%s",pcOption);
    printf("\nthe value of 	pcValue:%s",pcValue);
								 
    if( nDbOpen ) 
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(sqlDb));
	return(0);
    } 
    else
    {
	fprintf(stderr, "Opened database successfully\n");
    }
    if( 0 == strcmp(pcOption ,"CURRENTBALANCE"))
    {
	sprintf(cbuf, "UPDATE BANK set CURRENTBALANCE =%d  where CARDNUMBER= %s",atoi(pcValue),pcCardnumber);
    }
    else if( 0 == strcmp(pcOption ,"PIN"))
    {
	sprintf(cbuf, "UPDATE BANK set PIN =%d	where CARDNUMBER= %s",atoi(pcValue),pcCardnumber);
    }
    else if( 0 == strcmp(pcOption ,"MINISTATEMENT"))
    {
	sprintf(cbuf, "UPDATE BANK set MINISTATEMENT =%s  where CARDNUMBER= %s", pcValue, pcCardnumber);
    }
    else if( 0 == strcmp(pcOption ,"BLOCKED"))
    {
	sprintf(cbuf, "UPDATE BANK set BLOCKED =1 where CARDNUMBER= %s", pcCardnumber);
    }
    else
    {
	printf("Error occcured\n");
    }
    pcSql = cbuf;
    printf("\nthe value of 	cbuf:%s",cbuf); 
    /*----Execute SQL statement----*/
    nDbOpen = sqlite3_exec(sqlDb, pcSql, callback, (void*)data, NULL); 
    printf("\nthe value of 	nDbOpen:%d",nDbOpen);  
    if( nDbOpen != SQLITE_OK )
    {
	fprintf(stderr, "SQL error: %s\n", zErrMsg);			
    } 
    else 
    {
	fprintf(stdout, "Operation done successfully\n");
    }
    /*--This routine closes a database connection previously opened by a call to sssqlite3_open().--*/
    if (SQLITE_OK == sqlite3_close(sqlDb))
    {		
        printf("\n database closed successfully");
    }
    else
    {
	printf("\n database not closed successfully");
    }
    return SUCCESS;
	
}

/*********************************.FUNCTION_HEADER.*******************************/
/** @brief MinistatementArray
 *	Interface for ministatement.
 *	@param strBuf is used to hold the new ministatement. 
 *	@return zero if the function is successful, otherwise return one.
 */
int MinistatementArray(char strBuf[])
{
    printf("\ninside MinistatementArray :%s\n", strBuf);
    unsigned int iInc = 0;
    char *pcBuf = strtok (strBuf, "\n");
    char *tmpBuf = NULL;
    
    while ((pcBuf != NULL) && (iInc < MAX_SIZE))
    {        
        tmpBuf = (char*)malloc(strlen(pcBuf)+1);
        strcpy(tmpBuf, pcBuf);
        pcQueue[iInc++] = tmpBuf;
        pcBuf = strtok (NULL, "\n");
    }
    QueuePos = iInc;

    for (iInc = 0; iInc < MAX_SIZE; ++iInc) 
    {
        if (pcQueue[iInc] != NULL)
            printf("%s\n", pcQueue[iInc]);
    }

    return SUCCESS;  
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief SetMiniStatement
 *	Interface for setting the ministatement.
 *	@param pcOption is used to hold the new ministatement. 
 *	@return current time.
 */
char* SetMiniStatement(char pcOption[])
{
    printf("\ninside SetMiniStatement\n");
    time_t t;
    time(&t);    
    char* pcCurrentTime = NULL;
    pcCurrentTime = (char*)malloc(1024*sizeof(*pcCurrentTime));
    pcCurrentTime = ctime(&t);
    printf("\nSTRING IS %s",pcCurrentTime);
    strtok(pcCurrentTime, "\n");
    strcat(pcCurrentTime,pcOption);
    printf("\nSTRING %s",pcCurrentTime);
    return pcCurrentTime;

}

/*********************************.FUNCTION_HEADER.*******************************/
/** @brief AddStringToQueue
 *	Interface for adding new ministatement to the queue.
 *	@param string is used to hold the new ministatement. 
 *	@return void.
 */
void AddStringToQueue(char* string)
{
   unsigned int uInc;
   printf("\nInside AddStringToQueue");
   char* ptr = (char*)malloc(strlen(string)+1);
   if (QueuePos == MAX_SIZE) 
   {
        free(pcQueue[0]);
        for(uInc=0 ;(uInc<(MAX_SIZE-1));uInc++)
	{
		pcQueue[uInc] = pcQueue[uInc+1];
	}
        memcpy(ptr, string, strlen(string));
        ptr[strlen(string)] = '\0';
	pcQueue[uInc] = ptr; 
   }
   else
   {
	strcpy(ptr, string);
        pcQueue[QueuePos++] = ptr;
    }
   printf("\nEND OF AddStringToQueue");
}


/*********************************.FUNCTION_HEADER.*******************************/
/** @brief PrintQueue
 *	Interface for print the queue,which contain the ministatement. 
 *	@return void.
 */
void PrintQueue()
{
   unsigned int uInc;
   printf("\n#####Current Queue\n");
   for(uInc=0 ; (uInc < MAX_SIZE);uInc++) 
   {
	printf("\n[%p]", pcQueue[uInc]);
	if (pcQueue[uInc] != NULL)
        {
            printf("\nqueue[%d]:%s", uInc, pcQueue[uInc]);
        }
   }
   printf("\n");
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief ClearQueue
 *	Interface for clear the queue,which contain the ministatement. 
 *	@return void.
 */
void ClearQueue()
{
   unsigned int uInc;
   for(uInc=0 ; (uInc < MAX_SIZE);uInc++) 
   {
	if (pcQueue[uInc] != NULL)
        {
            free(pcQueue[uInc]);
            pcQueue[uInc] = NULL;
        }
   }
   QueuePos = 0;
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief StringConcatenate
 *	Interface for concatenating the queue. 
 *	@return void.
 */
char* StringConcatenate()
{
    printf("\nInside StringConcatenate");
    char* pcValue=NULL;
    pcValue=(char*)malloc(1024*sizeof(*pcValue));
    if (pcValue != NULL)
    {
        pcValue[0] = '\0';
	if (pcQueue[0] != NULL) strcat(pcValue,pcQueue[0]);
	if (pcQueue[1] != NULL) strcat(pcValue,pcQueue[1]);
	if (pcQueue[2] != NULL) strcat(pcValue,pcQueue[2]);
	printf("\nTHE VALUE OF pcValue%s",pcValue);
    }
    return pcValue;
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief MinistatementUpdate
 *	Interface for update the ministatement.
 *	@param pcCardnumber is used to hold the cardnumber. 
 *	@param pcOption is used to hold the which field in the database to be update.
 *	@return zero if the function is successful, otherwise return one.
 */
int MinistatementUpdate(char *pcCardnumber,char *pcOption)
{
    char *pcNewStatement = NULL,*pcValue = NULL;
    char pcOldStatement[BLOCK_SIZE] = {0};
	
    pcValue = (char*)malloc(BLOCK_SIZE*sizeof(*pcValue));
    pcNewStatement=(char*)malloc(BLOCK_SIZE*sizeof(*pcNewStatement));

    strcpy(pcOldStatement,fetch(pcCardnumber,"MINISTATEMENT"));
    printf("\nold mini statement:%s",pcOldStatement);
    strcpy(pcNewStatement,SetMiniStatement(pcOption));
    MinistatementArray(pcOldStatement);
    AddStringToQueue(pcNewStatement);
    printf("\nBefore copying");
	
    sprintf(pcValue,"\"%s\"",StringConcatenate());
    printf("\nconcatenated mini statement:%s",pcValue);

    DbUpdate(pcCardnumber,"MINISTATEMENT",pcValue);

    PrintQueue();
    ClearQueue();
    free(pcValue);
    free(pcNewStatement);
    return SUCCESS;

}


