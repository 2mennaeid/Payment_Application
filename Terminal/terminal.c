#include "terminal.h"
#include <stdio.h>
#include <string.h>
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData){
    int size_dt;
    printf("Enter Current Date in format DD/MM/YYYY\n");
    gets((char*)termData->transactionDate);
    size_dt=strlen((char*)termData->transactionDate);
    if(size_dt>10 || size_dt<10 || termData->transactionDate[2]!='/' || termData->transactionDate[5]!='/')
    {
        return WRONG_DATE;
    }
    else
    {
         return OK_terminal;
    }
}
EN_terminalError_t isCardExpired(ST_cardData_t*cardData, ST_terminalData_t *termData)
{
    int pos1=3;
    int pos2 = 8;
    char ts1[3];
    char ts2[3];
     char mon1[3];
     char mon2[3];
    int num1,num2,num3,num4;
    for(int i=0;i<=2;i++)
    {
        if(i==2)
        {
            ts1[i]='\0';
            ts2[i]='\0';
            mon1[i]='\0';
            mon2[i]='\0';
        }
        else
        {
          mon1[i]=cardData->cardExpirationDate[i];
          mon2[i]= termData->transactionDate[pos1];
          ts1[i]=cardData->cardExpirationDate[pos1];
          ts2[i]=termData->transactionDate[pos2];
        }
        pos1++;
        pos2++;
    }
    num1=atoi(ts1);
    num2=atoi(ts2);
    num3= atoi(mon1);
    num4= atoi(mon2);
    if(num1>num2)
    {
      return OK_terminal;
    }
    else if(num1==num2)
    {
        if(num3<=num4)
        {
            return WRONG_EXP_DATE;
        }
        else
        {
            return OK_terminal;
        }
    }
    else
    {
      return WRONG_EXP_DATE;
    }
}
EN_terminalError_t setMaxamunt(ST_terminalData_t*term)
{
    term->maxTransAmount=5000;
    return OK_terminal;
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    printf("Enter the amount of money you need\n");
    scanf("%f",&termData->transAmount);
    if(termData->transAmount<=0)
    {
        return INVALID_AMOUNT;
    }
    else
    {
        return OK_terminal;
    }
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if(termData->transAmount>termData->maxTransAmount || termData->transAmount<=0)
    {
       return EXCEED_MAX_AMOUNT;
    }
    else
    {
        return OK_terminal;
    }

}

