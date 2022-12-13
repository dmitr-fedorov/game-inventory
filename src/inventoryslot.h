#ifndef INVENTORYSLOT_H
#define INVENTORYSLOT_H

#include <QFrame>
#include <QBoxLayout>
#include <QMouseEvent>

#include "item.h"

/*
 * Класс виджета ячейки инвентаря. Содержит указатель на предмет, который содержит ячейка
 * и информацию о том, сколько предметов этого типа находится в этой ячейке.
 * Принимает объекты QDrag, представляющие собой предмет.
 */
class InventorySlot : public QFrame
{
    Q_OBJECT
public:
    explicit InventorySlot(int slotIndex, QWidget *parent = nullptr);

    /*
     * Удаляет предмет, находящийся в этой ячейке.
     */
    void Clear();

protected:
    QHBoxLayout* m_pHlayout;
    QVBoxLayout* m_pVlayout;
    QSpacerItem* m_pSpacer;

    Item* m_pItem;
    QLabel* m_pItemsCounter;

    int m_itemsCount;
    int m_slotIndex;

    void dragEnterEvent(QDragEnterEvent* event) override;
    void dragMoveEvent(QDragMoveEvent* event) override;
    /*
     * Принимает объекты, которые пользователь перетаскивает в эту ячейку.
     * Если объект представляет собой предмет инвентаря, то он записывается в эту ячейку.
     */
    void dropEvent(QDropEvent* event) override;

    /*
     * При нажатии на левую кнопку мыши активирует возможность перетаскивания предмета
     * в другую ячейку инвентаря.
     * При нажатии на правую кнопку мыши убавляет количество предметов в ячейке на 1.
     * Если количество предметов в ячейке достигло 0, то воспроизводит звук откусывания яблока.
     */
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void signal_ItemInSlotChanged(int slotIndex, const QString& itemType, int itemsCount);
    void signal_SlotCleared(int slotIndex);
    void signal_AppleRemovedFromSlot();
};

#endif // INVENTORYSLOT_H
