/*********************************.FILE_HEADER.*******************************/
/** @file cash_dispenser.c
 *  @brief This function is used to dispense currency according to the denomination option.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author
 */
/***********************.INCLUDES****************************************/
#include "cash_dispenser.h"
#include "popup.h"
/*! 
   \brief sets the constant integer value for strings.
   \param FILE_OPEN_FAILED input value  
 */
#define FILE_OPEN_FAILED -1
/*! 
   \brief sets the constant integer value for strings.
   \param FILE_OPEN_SUCCESS input value  
 */
#define FILE_OPEN_SUCCESS 0
/*! 
   \brief sets the constant integer value for strings.
   \param TWOTHOUSAND input value  
 */
#define TWOTHOUSAND 2000
/*! 
   \brief sets the constant integer value for strings.
   \param FIVEHUNDRED input value  
 */
#define FIVEHUNDRED 500
/*! 
   \brief sets the constant integer value for strings.
   \param HUNDRED input value  
 */
#define HUNDRED 100
/*! 
   \brief sets the constant integer value for strings.
   \param SUCCESS input value  
 */
#define SUCCESS 0
/*! 
   \brief sets the constant integer value for strings.
   \param FAIL input value  
 */
#define FAIL 1
/*! 
   \brief sets the constant integer value for strings.
   \param MIN_POSSIBLE_AMOUNT_WITHDRAW input value  
 */
#define MIN_POSSIBLE_AMOUNT_WITHDRAW 10000
/**
* A structure to represent 3 members
*/
struct SAtmNoteCount{
    int nTwoThousands ;/**< the count of nTwoThousands */
    int nFiveHundreds ;/**< the count of nFiveHundreds */
    int nOneHundreds ;/**< the count of nOneHundreds */
     
};
/**
* A structure to represent 3 members
*/
struct SCurrencyCounter{
    int nTwoThousandsCount ;/**< the count of nTwoThousands */
    int nFiveHundredsCount ;/**< the count of nFiveHundreds */
    int nOneHundredsCount ;/**< the count of nOneHundreds */
};
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief FileRead
 *  This function is used read the currency count.
 *  @return the structure member SNoteCount.
 */
struct SAtmNoteCount FileRead()
{  
    FILE *fptr;
    struct SAtmNoteCount SNoteCount = {0,0,0};
    fptr = fopen("ABCBANKATMDatabase.txt", "r");
    if(fptr == NULL)
    {
        PopUp("PROCESS_ERROR");
        printf("failed");
    }  

    printf("\nDetails:\n");
    fscanf(fptr, "%d %d %d", &(SNoteCount.nTwoThousands), &(SNoteCount.nFiveHundreds), &(SNoteCount.nOneHundreds)); 
    fclose(fptr);
    return SNoteCount;

}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief CountCurrency
 *  This function is used to calculate the default currency count.
 *  @param nAmount is the amount to be withdraw from the atm.
 *  @param nDenomination is the denomination option choosed by the user.
 *  @return the structure member SCurrencyCounter.
 */
struct SCurrencyCounter CountCurrency(int nAmount,unsigned int nDenomination) 
{ 
    struct SCurrencyCounter SCurrencyCounter={0,0,0};
    int nNotes[3] = { TWOTHOUSAND, FIVEHUNDRED, HUNDRED }; 
    static int snNoteCounter[3] = {0};
    if (nDenomination == TWOTHOUSAND)
    {
        for (int iInc = 0; iInc < 3; iInc++) 
        { 
            if (nAmount >= nNotes[iInc] && nNotes[iInc] != 0) 
            { 
                snNoteCounter[iInc] = nAmount/nNotes[iInc]; 
                nAmount = nAmount - snNoteCounter[iInc] * nNotes[iInc]; 
            } 
        }
        SCurrencyCounter.nTwoThousandsCount = SCurrencyCounter.nTwoThousandsCount+snNoteCounter[0];
        SCurrencyCounter.nFiveHundredsCount = SCurrencyCounter.nFiveHundredsCount+snNoteCounter[1];
        SCurrencyCounter.nOneHundredsCount = SCurrencyCounter.nOneHundredsCount+snNoteCounter[2];
        }
        else if (nDenomination == FIVEHUNDRED)
        {
        for (int iInc = 1; iInc < 3; iInc++) 
        { 
            if (nAmount >= nNotes[iInc]) 
            { 
                snNoteCounter[iInc] = nAmount/nNotes[iInc]; 
                nAmount = nAmount - snNoteCounter[iInc] * nNotes[iInc]; 
            } 
        }
        SCurrencyCounter.nTwoThousandsCount = SCurrencyCounter.nTwoThousandsCount;
        SCurrencyCounter.nFiveHundredsCount = SCurrencyCounter.nFiveHundredsCount+snNoteCounter[1];
        SCurrencyCounter.nOneHundredsCount = SCurrencyCounter.nOneHundredsCount+snNoteCounter[2];
        }
        else
        {
        snNoteCounter[2] = nAmount/ nNotes[2];
        SCurrencyCounter.nTwoThousandsCount = SCurrencyCounter.nTwoThousandsCount;
        SCurrencyCounter.nFiveHundredsCount = SCurrencyCounter.nFiveHundredsCount;
        SCurrencyCounter.nOneHundredsCount = SCurrencyCounter.nOneHundredsCount+snNoteCounter[2];    
        }
        printf("\nCurrency Count ->") ; 
        for (int iInc= 0; iInc <3; iInc++) 
        {         
            printf( " \n%d: %d\n", nNotes[iInc] ,snNoteCounter[iInc]); 
        }   
    return SCurrencyCounter;
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief DispensorTwoThousand
 *  Function used to dispense two thousand.
 *  @param SNoteCount is the available notecount in the database of cash.
 *  @param SCurrencyCounter is the calculated currency count for choosen amount.
 *  @return zero when the function is success otherwise return one.
 */
int DispensorTwoThousand(struct SAtmNoteCount *SNoteCount,struct  SCurrencyCounter *SCurrencyCounter)
{
    int uAmount =0,uBal =0,uRemainder =0;

    if (SNoteCount->nTwoThousands< SCurrencyCounter->nTwoThousandsCount)
    {       
        uAmount =uAmount +( (SCurrencyCounter->nTwoThousandsCount)-(SNoteCount->nTwoThousands)) *TWOTHOUSAND;
        (SCurrencyCounter->nTwoThousandsCount) = (SNoteCount->nTwoThousands);
        printf("uAmount:%d",uAmount);
        uBal = (uAmount/FIVEHUNDRED);
        uRemainder=(uAmount/FIVEHUNDRED);
        SCurrencyCounter->nFiveHundredsCount = (SCurrencyCounter->nFiveHundredsCount)+uBal;
        uAmount =uAmount - (uBal*FIVEHUNDRED);
        printf("new uAmount:%d",uAmount);
        if (uRemainder > 0)
        {
            uBal = (uAmount/HUNDRED);
            SCurrencyCounter->nOneHundredsCount=(SCurrencyCounter->nOneHundredsCount)+uBal; 
        }       
    }
    return uAmount;

}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief DispensorFiveHundred
 *  Function used to dispense amount of five hundred.
 *  @param SNoteCount is the available notecount in the database of cash.
 *  @param SCurrencyCounter is the calculated currency count for choosen amount.
 *  @return zero when the function is success otherwise return one.
 */
int DispensorFiveHundred(struct SAtmNoteCount *SNoteCount,struct  SCurrencyCounter *SCurrencyCounter)
{   
    unsigned int uAmount =0,uBal=0;
    if (SNoteCount->nFiveHundreds < SCurrencyCounter->nFiveHundredsCount)
    {       
        uAmount =uAmount +((SCurrencyCounter->nFiveHundredsCount) - (SNoteCount->nFiveHundreds))*FIVEHUNDRED;
        SCurrencyCounter->nFiveHundredsCount = SNoteCount->nFiveHundreds;
        printf("uAmount:%d",uAmount);
        uBal = (uAmount/HUNDRED);
        SCurrencyCounter->nOneHundredsCount=(SCurrencyCounter->nOneHundredsCount)+uBal;
        printf("500 count:%d",SCurrencyCounter->nFiveHundredsCount);    
        printf("100 count:%d",SCurrencyCounter->nOneHundredsCount);       
        printf("new uAmount:%d",uAmount);
    }
    return uAmount;
}

/*********************************.FUNCTION_HEADER.*******************************/
/** @brief DispensorOneHundred
 *  Function used to dispense an amount of hundred.
 *  @param SNoteCount is the available notecount in the database of cash.
 *  @param SCurrencyCounter is the calculated currency count for choosen amount.
 *  @return zero when the function is success otherwise return one.
 */
int DispensorOneHundred(struct SAtmNoteCount *SNoteCount,struct  SCurrencyCounter *SCurrencyCounter)
{   
    int uAmount =0;
    if (SNoteCount->nOneHundreds < SCurrencyCounter->nOneHundredsCount)
    {
        PopUp("DISPENSE_ERROR");
    }
    return uAmount;
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief DataBaseUpdation
 *  This function is used to update the database of cash.
 *  @param SNoteCount is the available notecount in the database of cash.
 *  @param SCurrencyCounter is the calculated currency count for choosen amount.
 *  @return zero when the function is success otherwise return one.
 */
int DataBaseUpdation(struct SAtmNoteCount *SNoteCount,struct  SCurrencyCounter *SCurrencyCounter)
{
    FILE *fptr;  
    fptr = fopen("ABCBANKATMDatabase.txt", "w+");   
    if (fptr != NULL) 
    {
        printf("File created successfully!\n");
    }
    else 
    {
        printf("Failed to create the file.\n");
        return FILE_OPEN_FAILED;
    }        
    SNoteCount->nTwoThousands = SNoteCount->nTwoThousands - SCurrencyCounter->nTwoThousandsCount;
    SNoteCount->nFiveHundreds = SNoteCount->nFiveHundreds - SCurrencyCounter->nFiveHundredsCount;  
    SNoteCount->nOneHundreds = SNoteCount->nOneHundreds - SCurrencyCounter->nOneHundredsCount;
        
    fprintf(fptr, "%d %d %d",SNoteCount->nTwoThousands,SNoteCount->nFiveHundreds,SNoteCount->nOneHundreds);
    fclose(fptr);
    return SUCCESS;
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief Dispenser
 *  This function used to process the denomination option.
 *  @param uAmount is the total amount to withdraw.
 *  @param uDenomination is the denomination choosed by the user.
 *  @return zero when the function is success otherwise return one.
 */
int Dispenser(int uAmount,int uDenomination )
{
    struct SAtmNoteCount SNoteCount = {0,0,0};
    struct SCurrencyCounter SCurrencyCounter = {0,0,0};
    unsigned int uSum=0;
    SNoteCount = FileRead();    
    uSum =(SNoteCount.nTwoThousands * TWOTHOUSAND)+(SNoteCount.nFiveHundreds * FIVEHUNDRED)+(SNoteCount.nOneHundreds * HUNDRED);
    if((uSum < uAmount) || (uSum < MIN_POSSIBLE_AMOUNT_WITHDRAW))
    {   
        Identification(":)","DISPENSE_FAILED");
        printf("\n Unable to Dispense Amount. ");
        return FAIL;
    }
    else
    {
        SCurrencyCounter = CountCurrency(uAmount ,uDenomination);
    }
    if(uDenomination == TWOTHOUSAND)
    {
        DispensorTwoThousand(&SNoteCount,&SCurrencyCounter);        
    }
    else if (uDenomination == FIVEHUNDRED)
    {       
        DispensorFiveHundred(&SNoteCount,&SCurrencyCounter);        
    }
    else
    {       
        DispensorOneHundred(&SNoteCount,&SCurrencyCounter);     
    }   
    DataBaseUpdation(&SNoteCount,&SCurrencyCounter);
    TotalAmount(SCurrencyCounter.nTwoThousandsCount,SCurrencyCounter.nFiveHundredsCount,SCurrencyCounter.nOneHundredsCount);
    Identification(":)","DISPENSE_SUCCESS");
    
    return SUCCESS;
}








