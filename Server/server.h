#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED
#include "Card/card.h"
#include "Terminal/terminal.h"
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef enum EN_transState_t
{
APPROVED=1, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, INTERNAL_SERVER_ERROR,FRAUD_CARD
}EN_transStat_t;
typedef struct ST_transaction_t
{
 ST_cardData_t cardHolderData;
ST_terminalData_t terminalData;
EN_transStat_t transState;
uint32_t transactionSequenceNumber;
}ST_transaction;
typedef enum EN_serverError_t
{
OK_Server=1, SAVING_FAILE, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE,BLOCKED_ACCOUNT
}EN_serverError_t;
typedef enum EN_accountState_t
{
     RUNNING=1,
     BLOCKED=0
}EN_accountState_t;
typedef struct ST_accountsDB_t
{
float balance;
EN_accountState_t state;
uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;
EN_transStat_t recieveTransactionData(ST_transaction *transData);
EN_serverError_t isValidAccount(ST_cardData_t*cardData,ST_accountsDB_t *accountRefrence);
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence);
EN_serverError_t saveTransaction(ST_transaction *transData);
void listSavedTransactions(ST_transaction*transData);
ST_accountsDB_t data_atm[255];
#endif // SERVER_H_INCLUDED
