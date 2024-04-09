#ifndef ENGINESTYLE_H
#define ENGINESTYLE_H
#include<QFont>
#include <QString>

class EngineStyle
{
public:
    static EngineStyle* getInstance();


    QFont thirdTitleFont() const;

    QFont secondTitleFont() const;

    QFont firstTitleFont() const;

    QString firstComboBoxStyle() const;

    QString editLabelStyle() const;

    QString firstButtonStyle() const;

    QFont firstTextFont() const;

private:

    QFont m_firstTitleFont;
    QFont m_secondTitleFont;
    QFont m_thirdTitleFont;
    QFont m_firstTextFont;

    QString m_firstComboBoxStyle;

    QString m_editLabelStyle;

    QString m_firstButtonStyle;

    static EngineStyle * m_instance;
    EngineStyle();
};

#endif // ENGINESTYLE_H
