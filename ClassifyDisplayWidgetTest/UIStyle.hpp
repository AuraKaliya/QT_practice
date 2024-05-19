#ifndef UISTYLE_HPP
#define UISTYLE_HPP

#include <QJsonObject>

#include <QColor>
#include <QString>
#include <QMap>

class UIStyle
{
public:
    static QColor getStateColor(QString stateName){

        if(!m_stateColorDictionary.contains(stateName))
        {
            stateName="Default";
        }

        return m_stateColorDictionary[stateName];
    };

    static void loadJson(const QJsonObject & obj){
        // 读取配置 style  -color等
    }


public:
    UIStyle()=default;
private:
    static QMap<QString ,QColor > m_stateColorDictionary;
};




#endif // UISTYLE_HPP
