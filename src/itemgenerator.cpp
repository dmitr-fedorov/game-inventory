#include "itemgenerator.h"

#include <QPixmap>
#include <QMimeData>
#include <QPainter>
#include <QDrag>

ItemGenerator::ItemGenerator(QWidget *parent)
    : QFrame{ parent }
{
    setFixedSize(100, 100);
    setStyleSheet("border: 1px solid black");

    m_pLyt = new QVBoxLayout(this);
    m_pLyt->setContentsMargins(0, 0, 0, 0);

    m_itemsCount = 1;

    m_pItem = new Item(this);
    m_pItem->SetType("Apple");
    QPixmap pixmap(":/icons/icon_Apple.jpg");
    m_pItem->setPixmap(pixmap);
    m_pItem->setScaledContents(true);
    m_pLyt->addWidget(m_pItem);
}

void ItemGenerator::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton || !m_pItem->geometry().contains(event->pos()))
        return;

    QPixmap itemPixmap = m_pItem->pixmap(Qt::ReturnByValue);

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << m_pItem->GetType() << m_itemsCount << itemPixmap;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(itemPixmap);
    drag->setHotSpot(event->position().toPoint() - m_pItem->pos());

    QPixmap darkenedPixmap = itemPixmap;
    QPainter painter;
    painter.begin(&darkenedPixmap);
    painter.fillRect(itemPixmap.rect(), QColor(160, 160, 160, 127));
    painter.end();

    m_pItem->setPixmap(darkenedPixmap);

    drag->exec(Qt::MoveAction);

    m_pItem->setPixmap(itemPixmap);
}
