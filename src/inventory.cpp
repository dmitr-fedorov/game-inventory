#include "inventory.h"

Inventory::Inventory(QWidget *parent)
    : QFrame{parent}
{
    m_pAppleBiteSound = new QSoundEffect(this);
    m_pAppleBiteSound->setSource(QUrl::fromLocalFile(":/sounds/sound_AppleBite.wav"));
    m_pAppleBiteSound->setLoopCount(1);
    m_pAppleBiteSound->setVolume(0.5f);

    this->setFixedSize(400, 400);

    m_pDatabase = new Database(this);

    m_gridLyt = new QGridLayout(this);

    m_gridLyt->setSpacing(0);

    /*
     * Заполнить инвентарь ячейками в количестве M_C_TOTAL_SIZE.
     * M_C_HORIZONTAL_SIZE - максимальное количество ячеек в каждой строке.
     * Когда в строке уже максимальное количество ячеек,
     * новые ячейки добавляются с новой строки.
     */
    for (int i = 0, row = 0, column = 0; i < M_C_TOTAL_SIZE; i++)
    {
        InventorySlot* newSlot = new InventorySlot(i + 1, this);

        connect(newSlot, SIGNAL(signal_ItemInSlotChanged(int, const QString&, int)),
                m_pDatabase, SLOT(slot_ItemInSlotChanged(int, const QString&, int)));

        connect(newSlot, SIGNAL(signal_SlotCleared(int)),
                m_pDatabase, SLOT(slot_SlotCleared(int)));

        connect(newSlot, SIGNAL(signal_AppleRemovedFromSlot()),
                this, SLOT(slot_AppleRemovedFromSlot()));

        m_gridLyt->addWidget(newSlot, row, column, 1, 1);

        m_slots.insert(i + 1, newSlot);

        column++;

        if((i + 1) % M_C_HORIZONTAL_SIZE == 0)
        {
            row++;
            column = 0;
        }
    }
}

void Inventory::ClearAllSlots()
{
    for (auto slot : m_slots)
    {
        slot->Clear();
    }
}

void Inventory::slot_AppleRemovedFromSlot()
{
    m_pAppleBiteSound->play();
}
