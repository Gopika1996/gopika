/*********************************.FILE_HEADER.*******************************/
/** @file statuscheck.c
 *  @brief used to check the validity ie,expiry date,blocked or not etc..
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */
/***********************.INCLUDES****************************************/
#include "statuscheck.h"
/**********************.FUNCTION_HEADER.*********************************/
/** @brief CurrentDate
 *  This is the main function used to get the current date. 
 *  @return the character pointer.
 */
char* CurrentDate() 
{
	char* cBuff = NULL;
	cBuff = (char*) malloc(1024 * sizeof(*cBuff));
	int day, month, year;
	time_t now;
	time(&now);
	struct tm *local = localtime(&now);
	day = local->tm_mday;
	month = local->tm_mon + 1;
	year = local->tm_year + 1900;
	sprintf(cBuff, "%02d/%02d/%d\n", day, month, year);
	printf("cBuff is %s ", cBuff);
	return cBuff;

}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief StatusCheck
 *  This function is used to check the expiry date.
 *  @param blCard is used to hold the card number of the user and it is
    declared as a character pointer type.
 *  @return true if the function is successful, otherwise returns false.
 */
bool StatusCheck(char* blCard) 
{
	char* pBuff = NULL;
	pBuff = (char*) malloc(1024 * sizeof(*pBuff));
	pBuff = fetch(blCard, "EXPIRYDATE");
	char array[1024];
	strcpy(array, CurrentDate());
	if (strcmp(array, pBuff) == 0)
	{
		return false;
	} 
	else
	{
		return true;
	}
}

