#include "Card/card.h"
#include <stdio.h>
#include <string.h>
EN_cardError_t getCardHolderName(ST_cardData_t*cardData){
    int size_name;
    printf("Enter your Name in valid format\n");
    gets((char*)cardData->cardHolderName);
    size_name=strlen((char*)cardData->cardHolderName);
    if(size_name>24 || size_name<20)
    {
        return WRONG_NAME;
    }
    else
    {
        return OK_CARD;
    }
}
EN_cardError_t getCardExpiryDate(ST_cardData_t*cardData)
{
    printf("Enter Date in format MM/YY\n");
    gets((char*)cardData->cardExpirationDate);
    int size_date=strlen((char*)cardData->cardExpirationDate);
    if(size_date>5 || size_date<5 || cardData->cardExpirationDate[2]!='/')
    {
        return WRONG_EXP_DATE;
    }
    else
    {
        return OK_CARD;
    }

}
EN_cardError_t getCardPAN(ST_cardData_t*cardData)
{
    printf("Enter your primary account number in valid format\n");
    gets((char*)cardData->primaryAccountNumber);
    int size_PAN= strlen((char*)cardData->primaryAccountNumber);
    if(size_PAN<16 || size_PAN>19)
    {
        return WRONG_PAN;
    }
    else
    {
        return  OK_CARD;
    }
}
