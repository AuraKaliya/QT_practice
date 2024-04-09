#include "modelbag.h"

ModelBag::ModelBag(QObject *parent)
    : ComponentObject{parent}
{

}

void ModelBag::tick()
{




}

int ModelBag::bagSize() const
{
    return m_bagSize;
}

void ModelBag::setBagSize(int newBagSize)
{
    if (m_bagSize == newBagSize)
        return;
    m_bagSize = newBagSize;
    emit bagSizeChanged();
}
