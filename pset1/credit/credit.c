#include <cs50.h>
#include <stdio.h>

void AMEX(long number); //starting nº in AMEX
void MASTERCARD(long number);   //starting nº in MASTERCARD
int doubledsum(int second_to_last);

int main(void)
{
    long card_number = get_long("Number: ");  //propmt user to input number
    int card_lenght = 0;  //card lenght
    long j = card_number;

    do  //see card lenght
    {
        j = j / 10;
        card_lenght++;
    }
    while (j > 0);

    if (card_lenght != 13 && card_lenght != 15 && card_lenght != 16)
    {
        printf("INVALID\n");
        return 0;
    }

    long x = card_number;
    int last;  //last number
    int ndouble_sum = 0; //not doubled sum
    int s_last; //second to last
    int double_sum = 0; //doubled sum
    int i = 0;

    do  //Lunh's algorithm
    {
        last = x % 10;
        x = x / 10;
        ndouble_sum += last;

        s_last = x % 10;
        x = x / 10;
        i = doubledsum(s_last);
        double_sum += i;
    }
    while (x > 0);

    int total = ndouble_sum + double_sum;

    if (total % 10 != 0)    //validity of the card
    {
        printf("INVALID\n");
        return 0;
    }
    else if (card_lenght == 13) //visa validity
    {
        printf("VISA\n");
    }
    else if (s_last == 4 && card_lenght == 16)  //visa validity
    {
        printf("VISA\n");
    }
    else if (card_lenght == 15) //amex validity
    {
        AMEX(card_number);
    }
    else if (card_lenght == 16) //mastercard validity
    {
        MASTERCARD(card_number);
    }
}

int doubledsum(int something)   //1st part of Lunh's algorithm
{
    something = something * 2;
    int k;  //last
    int l;  //nlast
    int sum;

    if (something >= 10)
    {
        k = something % 10;
        something = something / 10;

        l = something % 10;
        sum = k + l;
        return sum;
    }
    return something;
}

void AMEX(long number)
{
    do
    {
        number = number / 10;
    }
    while (number > 38);

    if (number == 34 || number == 37)
    {
        printf("AMEX\n");
        return;
    }
    else
    {
        printf("INVALID\n");
    }
}

void MASTERCARD(long number)
{
    do
    {
        number = number / 10;
    }
    while (number > 58);

    if (number == 51 || number == 52 || number == 53 || number == 54 || number == 55)
    {
        printf("MASTERCARD\n");
        return;
    }
    else
    {
        printf("INVALID\n");
    }
}