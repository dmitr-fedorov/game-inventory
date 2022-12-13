#include "inventoryslot.h"

#include <QDragEnterEvent>
#include <QMimeData>
#include <QDrag>
#include <QPainter>

InventorySlot::InventorySlot(int slotIndex, QWidget *parent)
    : QFrame(parent), m_slotIndex(slotIndex)
{
    m_pHlayout = new QHBoxLayout(this);
    m_pVlayout = new QVBoxLayout();

    m_pHlayout->setContentsMargins(0, 0, 0, 0);

    m_pSpacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_pVlayout->addItem(m_pSpacer);

    m_pItemsCounter = new QLabel(this);
    m_pItemsCounter->setText("0");
    m_pItemsCounter->setAttribute(Qt::WA_TranslucentBackground);
    m_pVlayout->addWidget(m_pItemsCounter, 0, Qt::AlignRight);
    m_pItemsCounter->hide();

    m_pHlayout->addLayout(m_pVlayout);

    m_pItem = nullptr;
    m_itemsCount = 0;

    setStyleSheet("border: 1px solid black");

    setAcceptDrops(true);
}

void InventorySlot::Clear()
{
    if (m_pItem)
    {
        delete m_pItem;
        m_pItem = nullptr;

        m_itemsCount = 0;
        m_pItemsCounter->setText(QString::number(m_itemsCount));
        m_pItemsCounter->hide();

        emit signal_SlotCleared(m_slotIndex);
    }
}

void InventorySlot::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void InventorySlot::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void InventorySlot::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        if(event->source() == this)
        {
            event->setDropAction(Qt::IgnoreAction);
            event->accept();
            return;
        }

        QByteArray droppedItemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&droppedItemData, QIODevice::ReadOnly);

        QPixmap droppedItemPixmap;
        int droppedItemsCount;
        QString droppedItemType;
        dataStream >> droppedItemType >> droppedItemsCount >> droppedItemPixmap;

        if (m_pItem)
        {
            delete m_pItem;
            m_pItem = nullptr;
        }
        m_pItem = new Item(this);
        m_pItem->SetType(droppedItemType);
        m_pItem->setPixmap(droppedItemPixmap);
        m_pItem->setAlignment(Qt::AlignCenter);

        m_itemsCount += droppedItemsCount;
        m_pItemsCounter->setText(QString::number(m_itemsCount));
        m_pItemsCounter->show();
        m_pHlayout->insertWidget(0, m_pItem);

        emit signal_ItemInSlotChanged(m_slotIndex, m_pItem->GetType(), m_itemsCount);

        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void InventorySlot::mousePressEvent(QMouseEvent *event)
{
    if (!m_pItem)
        return;
    if (!m_pItem->geometry().contains(event->pos()))
        return;

    if (event->button() == Qt::LeftButton)
    {
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

        if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
        {
            this->Clear();
        }
        else
        {
            m_pItem->setPixmap(itemPixmap);
        }
    }
    else if (event->button() == Qt::RightButton && m_itemsCount > 0)
    {
        m_itemsCount--;
        m_pItemsCounter->setText(QString::number(m_itemsCount));

        if (m_itemsCount == 0)
        {
            this->Clear();
            emit signal_AppleRemovedFromSlot();
        }
        else
        {
            emit signal_ItemInSlotChanged(m_slotIndex, m_pItem->GetType(), m_itemsCount);
        }
    }
    else
        return;
}
