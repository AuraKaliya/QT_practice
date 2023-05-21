#include "searchblok.h"

searchblok::searchblok()
{
    QHBoxLayout *mainLayout= new QHBoxLayout(this);
    QPushButton*searchBtn= new QPushButton(this);
    searchBtn->setFixedSize(20,20);
    searchBtn->setCursor(Qt::PointingHandCursor);
    searchBtn->setToolTip("Search");
    searchBtn->setStyleSheet(
        "QPushButton{border-image:url(:/test_choiceIcon.png);"
        "background:transparent;}"
        );

    setPlaceholderText("Searching");
    mainLayout->addWidget(searchBtn);
    mainLayout->addStretch();
    mainLayout->setContentsMargins(8,0,0,0);
    setTextMargins(23,0,0,0);
    setContentsMargins(0,0,0,0);
    setLayout(mainLayout);
    setStyleSheet("border:1px solid #eaeaea;border-radius:25%");

}
