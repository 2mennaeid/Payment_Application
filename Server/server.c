#include "Server/server.h"
#include "Card/card.h"
#include "Terminal/terminal.h"
#include <stdio.h>
#include <string.h>
ST_accountsDB_t data_atm[255]= {{6000,RUNNING,"12345678901234567"},{7000,RUNNING,"12345678901234510"},{8000,RUNNING,"12345678901234512"},
 {5000,RUNNING,"12345678901234523"},{3000,RUNNING,"12345678901234524"},{4000,BLOCKED,"12345678901234525"},{2000,RUNNING,"12345678901234526"},
 {1000,RUNNING,"12345678901234537"},{20,BLOCKED,"12345678901234538"},
};
ST_transaction trans_data_base[255] = {0};
int seqance_number=3000;
int index=0;
int ref_of_db=0;
ST_accountsDB_t b;
EN_serverError_t isValidAccount(ST_cardData_t*cardData,ST_accountsDB_t *accountRefrence)
{
    for(int i=0;i<9;i++)
    {
        if(strcmp((char*)cardData->primaryAccountNumber,(char*)data_atm[i].primaryAccountNumber)==0)
        {
            ref_of_db=i;
            return OK_Server;
        }
    }
    return ACCOUNT_NOT_FOUND;

}
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
    if(accountRefrence->state==RUNNING)
    {
        return OK_Server;
    }
    else
    {
        return BLOCKED_ACCOUNT;
    }
}
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{
    if(termData->transAmount > accountRefrence->balance)
    {
        return LOW_BALANCE;
    }
    else
    {
        accountRefrence->balance= accountRefrence->balance - termData->transAmount;
        return OK_Server;
    }
}
void listSavedTransactions(ST_transaction*transData)
{
    printf("Cardholder Name: %s\n",transData->cardHolderData.cardHolderName);
    printf("Transaction Sequence Number: %d\n",transData->transactionSequenceNumber);
    printf("Transaction Date: %s\n",transData->terminalData.transactionDate);
    printf("Transaction Amount: %f \n",transData->terminalData.transAmount);
    printf("Terminal Max Amount: %f\n",transData->terminalData.maxTransAmount);
    printf("PAN: %s\n",transData->cardHolderData.primaryAccountNumber);
    printf("Card Expiration Date: %s\n",transData->cardHolderData.cardExpirationDate);
    if(transData->transState==APPROVED)
    {
       printf("Transaction State: APPROVED");
    }
   else if(transData->transState==DECLINED_INSUFFECIENT_FUND)
    {
        printf("Transaction State: DECLINED_INSUFFECIENT_FUND");
    }
    else if(transData->transState==DECLINED_STOLEN_CARD)
    {
        printf("Transaction State: DECLINED_STOLEN_CARD");
    }
   else if(transData->transState==INTERNAL_SERVER_ERROR)
    {
        printf("Transaction State: INTERNAL_SERVER_ERROR");
    }
    else if(transData->transState==FRAUD_CARD)
    {
        printf("Transaction State:FRAUD_CARD");
    }

}
EN_serverError_t saveTransaction(ST_transaction *transData)
{
    seqance_number = 2000;
    if(transData->transState==APPROVED && index!=255)
    {
        transData->transactionSequenceNumber= seqance_number+1;
        trans_data_base[index].cardHolderData=transData->cardHolderData;
        trans_data_base[index].terminalData=transData->terminalData;
        trans_data_base[index].transactionSequenceNumber= transData->transactionSequenceNumber;
        trans_data_base[index].transState=transData->transState;
        index++;
        listSavedTransactions(transData);
    }
  listSavedTransactions(transData);
    return OK_Server;

}
EN_transStat_t recieveTransactionData(ST_transaction *transData)
{
    if(isValidAccount(&transData->cardHolderData,&b)==ACCOUNT_NOT_FOUND)
    {
        transData->transState=FRAUD_CARD;
        return FRAUD_CARD;
    }
    if(isBlockedAccount(&data_atm[ref_of_db])==BLOCKED_ACCOUNT)
    {
        transData->transState=DECLINED_STOLEN_CARD;
        return DECLINED_STOLEN_CARD;
    }
    if(isAmountAvailable(&transData->terminalData,&data_atm[ref_of_db])==LOW_BALANCE)
    {
        transData->transState=DECLINED_INSUFFECIENT_FUND;
        return DECLINED_INSUFFECIENT_FUND;
    }
    if(saveTransaction(transData)!=OK_Server)
    {
        transData->transState=INTERNAL_SERVER_ERROR;
        return INTERNAL_SERVER_ERROR;
    }

    transData->transState=APPROVED;
    printf("APPROVED");
    return APPROVED;

}



