#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED
typedef unsigned char uint8_t;
typedef enum EN_cardError_t
{
  OK_CARD=1, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

typedef struct ST_cardData{
    uint8_t cardHolderName[25];
    uint8_t cardExpirationDate[6];
    uint8_t primaryAccountNumber[20];
}ST_cardData_t;
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t*cardData);
void Showdate(ST_cardData_t*c);


#endif // CARD_H_INCLUDED
