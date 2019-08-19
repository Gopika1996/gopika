/*********************************.FILE_HEADER.*******************************/
/** @file client_operations.c
 *  @brief Check the cardnumber,PIN and performs concatenation, parsing and file handling.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */
/***********************.INCLUDES****************************************/
#include "client_operations.h"
/*! 
   \brief sets the constant integer value for strings.
   \param MIN_LENGTH input value  
 */
#define MIN_LENGTH 4
/*! 
   \brief sets the constant integer value for strings.
   \param MAX_LENGTH input value  
 */
#define MAX_LENGTH 6
/*! 
   \brief sets the constant integer value for strings.
   \param CARD_LENGTH input value  
 */
#define CARD_LENGTH 5

/** @brief CheckCardNumber
 *  Check the CardNumber before sending to the server for validation.
 *  @param pcPinNumber 
 *  @return bool
 */
bool CheckCardNumber(char* pcPinNumber)
{
    unsigned int uLength=0;
	printf("\nvalue of cPASS %s",pcPinNumber);
	while(*pcPinNumber != '\0')
	{
		pcPinNumber++;
		uLength++;
	}
	printf("\nlength of cPASS %d",uLength);
	if( CARD_LENGTH == uLength)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief CheckPIN
 *  Check the PIN before sending to the server for validation.
 *  @param pcPIN 
 *  @return bool
 */
bool CheckPIN(char* pcPIN)
{
	unsigned int uLength=0;
	while(*pcPIN != '\0')
	{
		pcPIN++;
		uLength++;
	}
	printf("\nlength of cPIN %d",uLength);
	if( MIN_LENGTH == uLength||MAX_LENGTH == uLength)
	{		
		return true;
	}
	else
    {		
		return false;
	}
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief Concatenate
 *  Concatinating the user credentials and a string which notify the operation to be performed at server side.
 *  @param ucStr1, ucStr2
 *  @return Concatenated string
 */
char* Concatenate(char* ucStr1,char* ucStr2) 
{
	strcat(ucStr1,ucStr2);
	return ucStr1;
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief Parsing
 *  This function is used for parsing.
 *  @param cstr1,cstr2,nIndex,nLength
 *  @return bool
 */
bool Parsing(char cstr1[], char cstr2[], int nIndex, int nLength) 
{
	int nInc = 0;
	if ( 0 <= nIndex) 
	{
		while (nInc < nLength) 
		{
			cstr2[nInc] = cstr1[(nIndex + nInc)];
			nInc++;
		}
		cstr2[nInc] = '\0';
		return true;
	}
	else 
	{
		printf("Error condition occured");
		return false;
	}
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief fileoperation
 *  This function is used for storing the activity log to a file.
 *  @param pcName,pcCardNumber
 *  @return int
 */
int FileOperation(char* pcName,char* pcCardNumber)
{
	FILE *fileAddress;
	fileAddress = fopen("file.txt", "a");
	int iVal;
	int nLength = strlen(pcName);

	if ( NULL != fileAddress) 
	{
		for (iVal = 0; iVal < nLength; iVal++) 
		{
			fputc (pcName[iVal], fileAddress);
		}
		time_t mytime;
		mytime = time(NULL);
		fprintf(fileAddress,"%s",pcCardNumber);
		fprintf(fileAddress,"%s",ctime(&mytime));
		printf("\n We have written the Name successfully");
		fclose(fileAddress);		
	}
	else
	{
		printf("\n Unable to Create or Open the Sample.txt File");
	}
	return 0;
}
