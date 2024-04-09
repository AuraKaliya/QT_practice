#include "enginestyle.h"
EngineStyle * EngineStyle::m_instance=nullptr;


EngineStyle *EngineStyle::getInstance()
{
    if(m_instance==nullptr)
    {
        m_instance = new EngineStyle();
    }
    return m_instance;
}

QFont EngineStyle::thirdTitleFont() const
{
    return m_thirdTitleFont;
}

QFont EngineStyle::secondTitleFont() const
{
    return m_secondTitleFont;
}

QFont EngineStyle::firstTitleFont() const
{
    return m_firstTitleFont;
}

QString EngineStyle::firstComboBoxStyle() const
{
    return m_firstComboBoxStyle;
}

QString EngineStyle::editLabelStyle() const
{
    return m_editLabelStyle;
}

QString EngineStyle::firstButtonStyle() const
{
    return m_firstButtonStyle;
}

QFont EngineStyle::firstTextFont() const
{
    return m_firstTextFont;
}

EngineStyle::EngineStyle()
{
    //QFont  字体样式
    //第三标题
    m_thirdTitleFont.setFamily("宋体");
    m_thirdTitleFont.setPixelSize(15);
    m_thirdTitleFont.setBold(true);
    //m_thirdTitleFont.setLetterSpacing(QFont::PercentageSpacing,100);
    //m_thirdTitleFont.setLetterSpacing(QFont::AbsoluteSpacing,1);

    // 第一文本
    m_firstTextFont.setFamily("宋体");
    m_firstTextFont.setPixelSize(15);

    //QString 下拉框样式

    m_firstComboBoxStyle=
    "QComboBox{color:rgb(10,10,10);font-size:14px;padding:1px 15px 1px 3px;border:1px solid rgba(225,225,225,1);border-radius:5px 5px 0px 0px;}"
    "QComboBox::drop-down{subcontrol-origin: padding;subcontrol-position: top right; width: 15px; border:none;}"
    "QComboBox::down-arrow{width:15px;background:transparent;padding:0px 0px 0px 0px;image:url(:/RESOURCE/default/arrow1.png);}"
    "QComboBox::down-arrow:on{image:url(:/RESOURCE/default/arrow2.png);}"
    ;


    //QString 编辑框 label样式

    m_editLabelStyle=
    "QWidget{color: white;background-color:rgba(52,58,64,0.4);}"
    "QLineEdit{border-width:0;border-style:outset;}"
    ;


    //QString   按钮样式

    m_firstButtonStyle=
        "QPushButton:hover { border-radius:10px;color: white;background-color:rgba(52,58,64,0.2); }"
        "QPushButton:!hover { border-radius:10px;color: white;background-color:rgba(52,58,64,0.6); }"
        ;


}
