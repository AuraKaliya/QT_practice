#ifndef CARD_H
#define CARD_H
#include <QString>
#include <QVariant>

class Card
{
public:
    Card();
    static int cardIdinGlobal;
    int cardId;
    QString cardName;
    QString cardIntroduction;
};


Q_DECLARE_METATYPE(Card)

#endif // CARD_H
