#include "item.h"

Item::Item(QWidget* parent) : QLabel(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
}

const QString& Item::GetType()
{
    return m_type;
}

void Item::SetType(const QString& type)
{
    m_type = type;
}
