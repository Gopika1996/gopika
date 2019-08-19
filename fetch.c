/*********************************.FILE_HEADER.*******************************/
/** @file fetch.c
 *  @brief used to fetch data from the database.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */

/***********************.INCLUDES**************************************************************/

#include "fetch.h"
/*! 
   \brief sets the constant integer value for strings.
   \param BUFFER_SIZE input value  
 */
#define BUFFER_SIZE 1024 
static char cbuff[BUFFER_SIZE]={0}; /*!< Define cbuff to store data from database*/

/*********************************.FUNCTION_HEADER.*******************************/
/** @brief callback
 *  This function is used in conjunction with the sqlite3_exec() function.   
 *  @param data, argc,argv,azColName.
 *  @return character pointer.
 */
static int callback(void *data, int argc, char **argv, char **azColName)
{
	unsigned int PIN = 0;
	fprintf(stderr, "%s: ", (const char*) data);
	strcpy(cbuff,argv[PIN]);
	printf("the fetched data is %s",cbuff);
	printf("\n");
	return SUCCESS;
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief fetch
 *  This function is used to fetch data from the database.
 *  @param pcCardnumber is used to store the card number of the user.
 *  @param pcOption decides which data to fetch from the database.
 *  @return character pointer.
 */
char * fetch(char *pcCardnumber,char* pcOption) 
{
	sqlite3 *sqlDb;
	char *pcErrMsg = NULL;
	int nDbOpen = 0;
	char *pcSql = NULL;
	char *pcbuf = NULL;
	const char* ccData = "Callback function called";
	char cbuf[BUFFER_SIZE]= {0};
	/*----Open database----*/
	nDbOpen = sqlite3_open("test1.db", &sqlDb);
	if (nDbOpen) 
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(sqlDb));
		return NULL;
	} 
	else
	{
		fprintf(stderr, "Opened database successfully\n");
	}
	if( 0 == strcmp(pcOption ,"NAME"))
	{

		sprintf(cbuf, "SELECT NAME from BANK where CARDNUMBER = %s", pcCardnumber);

	}
	else if( 0 == strcmp(pcOption ,"PIN"))
	{

		sprintf(cbuf, "SELECT PIN from BANK where CARDNUMBER = %s", pcCardnumber);
	}
	else if( 0 == strcmp(pcOption ,"CURRENTBALANCE"))
	{
		sprintf(cbuf, "SELECT CURRENTBALANCE from BANK where CARDNUMBER = %s", pcCardnumber);
	}
	else if ( 0 == strcmp(pcOption ,"MINISTATEMENT"))
	{
		sprintf(cbuf, "SELECT MINISTATEMENT from BANK where CARDNUMBER = %s", pcCardnumber);
	}
	else if ( 0 == strcmp(pcOption ,"EXPIRYDATE"))
	{
		sprintf(cbuf, "SELECT EXPIRYDATE from BANK where CARDNUMBER = %s", pcCardnumber);
	}
	else if ( 0 == strcmp(pcOption ,"BLOCKED"))
	{
		sprintf(cbuf, "SELECT BLOCKED from BANK where CARDNUMBER = %s", pcCardnumber);
	}
	else
	{
		printf("Error occcured\n");
	}
	printf("\n%s\n", cbuf);
	pcSql = cbuf;
	/*----Execute function----*/
	nDbOpen = sqlite3_exec(sqlDb, pcSql, callback, (void*)ccData, &pcErrMsg);
	if (nDbOpen != SQLITE_OK)
	{
		fprintf(stderr, "pcSql error: %s\n", pcErrMsg);
		sqlite3_free(pcErrMsg);
	} 
	else 
	{
		fprintf(stdout, "Operation done successfully\n");
	}
	pcbuf=cbuff;
	/*----Close database----*/        
	sqlite3_close(sqlDb);																			
	return pcbuf;
}



