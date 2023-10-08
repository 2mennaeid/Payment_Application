#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Terminal/terminal.h"
#include "Card/card.h"
#include "Server/server.h"
void appStart()
{
    ST_cardData_t card;
    ST_terminalData_t terminal;
    ST_transaction trans;
    int _check=0;
    EN_terminalError_t term;
    // take card data
    while(_check!=1)
    {
        _check=getCardHolderName(&card);
    }
    printf("--------------------------\n");
    _check=0;
    while(_check!=1)
    {
        _check=getCardExpiryDate(&card);
    }
    _check=0;
    while(_check!=1)
    {
        _check=getCardPAN(&card);
    }
    _check=0;
    printf("--------------------------\n");
    // take terminal data
    setMaxamunt(&terminal);
    while(_check!=1)
    {
        _check=getTransactionDate(&terminal);
    }
    _check=1;
     printf("--------------------------\n");
    if(isCardExpired(&card,&terminal)==_check)
    {
       term= getTransactionAmount(&terminal);
       if(term==OK_terminal)
       {
           term= isBelowMaxAmount(&terminal);
           if(term==OK_terminal)
           {
               trans.cardHolderData=card;
               trans.terminalData= terminal;
               printf("--------------------------\n");
               recieveTransactionData(&trans);
               printf("--------------------------\n");
               saveTransaction(&trans);
           }
           else
           {
               printf("Declined Amount Exceeding\n");
               return 0;
           }
       }
       else
       {
           printf("INVALId AMOUNT");
           return 0;
       }
    }
    else if(isCardExpired(&card,&terminal)!=_check)
    {
        printf("Declined Expired card");
        return 0;
    }

}
