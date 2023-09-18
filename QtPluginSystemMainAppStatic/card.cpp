#include "card.h"

int Card::cardIdinGlobal=0;
Card::Card()
{
    cardId=cardIdinGlobal;
    ++cardIdinGlobal;
    cardIntroduction="";
};
