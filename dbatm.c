/*********************************.FILE_HEADER.*******************************/
/** @file dbatm.c
 *  @brief This program contains database of the users.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */

/***********************.INCLUDES**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief callback
 *  This function is used in conjunction with the sqlite3_exec() function. 
 *  @param NotUsed,argc,argv,azColName.											
 *  @return zero if the function is successful, otherwise return one.
 */
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	unsigned int iInc = 0;
	for (iInc = 0; iInc < argc; iInc++) 
	{
		printf("%s = %s\n", azColName[iInc], argv[iInc] ? argv[iInc] : "NULL");
	}
	printf("\n");
	return 0;
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief main
 *  This function is used to create a database for the users.
 *  @param argc,argv[].
 *  @return zero if the function is successful, otherwise return one.
 */
int main(int argc, char* argv[]) 
{
	sqlite3 *db;
	char *cpErrMsg = 0;
	int nDbOpen, nDbOpen1;
	char *cpSql, *cpSql1;

	/* ---This routine opens a connection to an SQLite database file and return a database connection object to be used by other SQLite routines.---*/

	nDbOpen = sqlite3_open("test1.db", &db);								 
	if (nDbOpen) 
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		return (0);
	} 
	else
	{
		fprintf(stdout, "Opened database successfully\n");
	}
	/*----Create SQL statement----*/ 
	cpSql = "CREATE TABLE BANK("
			"CARDNUMBER INT PRIMARY KEY  NOT NULL,"
			"NAME           TEXT    NOT NULL,"
			"PIN            TEXT     NOT NULL,"
			"MINISTATEMENT        TEXT,"
			"BLOCKED		BOOL,"
			"EXPIRYDATE	TEXT,"
			"CURRENTBALANCE         UNSIGNED LONG INT );"; 								
	/*----Execute SQL statement----*/ 
	nDbOpen = sqlite3_exec(db, cpSql, callback, 0, &cpErrMsg);	
	if (nDbOpen != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", cpErrMsg);
		sqlite3_free(cpErrMsg);
	} 
	else
	{
		fprintf(stdout, "Table created successfully\n");
	}
	/*----Create SQL statement----*/
	cpSql1 =
			"INSERT INTO BANK (CARDNUMBER,NAME,PIN,MINISTATEMENT,BLOCKED,EXPIRYDATE,CURRENTBALANCE)"
			"VALUES (11111, 'Paul', 4567, '21/1/2018 CASHWITHDRAWAL \n 22/1/2018 BALANCEENQUIRY',0,'22/1/2038', 20000);"
			"INSERT INTO  BANK (CARDNUMBER,NAME,PIN,MINISTATEMENT,BLOCKED,EXPIRYDATE,CURRENTBALANCE)"
			"VALUES (21212, 'Allen', 2525, '20/1/2018 BALANCEENQUIRY \n 24/1/2018 CASHWITHDRAWAL',0,'22/1/2038',15000);"
			"INSERT INTO  BANK (CARDNUMBER,NAME,PIN,MINISTATEMENT,BLOCKED,EXPIRYDATE,CURRENTBALANCE)"
			"VALUES (31234, 'Teddy', 2323, '22/2/2018 MINISTATEMENT \n 26/1/2018 PINCHANGE',0,'22/1/2038', 20000);"
			"INSERT INTO  BANK (CARDNUMBER,NAME,PIN,MINISTATEMENT,BLOCKED,EXPIRYDATE,CURRENTBALANCE)"
			"VALUES (31313, 'Ravi', 2333, '22/2/2018 MINISTATEMENT \n 26/1/2018 PINCHANGE',0,'22/1/2038', 20000);"
			"INSERT INTO  BANK (CARDNUMBER,NAME,PIN,MINISTATEMENT,BLOCKED,EXPIRYDATE,CURRENTBALANCE)"
			"VALUES (31254, 'Sasi', 2343, '22/2/2018 MINISTATEMENT \n 26/1/2018 PINCHANGE',0,'22/1/2038', 20000);"
			"INSERT INTO  BANK (CARDNUMBER,NAME,PIN,MINISTATEMENT,BLOCKED,EXPIRYDATE,CURRENTBALANCE)"
			" VALUES (42221, 'Mark', 2525, '23/1/2018 PINCHANGE \n 25/1/2018 MINISTATEMENT',0,'22/1/2038', 65000);"; 
	/*----Execute SQL statement----*/ 
	nDbOpen1 = sqlite3_exec(db, cpSql1, callback, 0, &cpErrMsg);
	if (nDbOpen1 != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", cpErrMsg);
		sqlite3_free(cpErrMsg);
	}
	else 
	{
		fprintf(stdout, "Records created successfully\n");
	}
	/*--This routine closes a database connection previously opened by a call to sqlite3_open().--*/
	sqlite3_close(db);														 
	return 0;
}

