#include "playingfield.h"

PlayingField::PlayingField(QWidget *parent)
{
    m_pHlayout = new QHBoxLayout(this);
    m_pVlayout1 = new QVBoxLayout();
    m_pVlayout2 = new QVBoxLayout();

    m_pInventory = new Inventory(this);
    m_pItemGenerator = new ItemGenerator(this);
    m_pButtonMainMenu = new QPushButton("Главное меню", this);

    connect(m_pButtonMainMenu, SIGNAL(clicked()),
            this, SLOT(slot_ButtonMainMenuPressed()));

    m_pVlayout1->addWidget(m_pInventory);
    m_pVlayout2->addWidget(m_pItemGenerator);
    m_pVlayout2->addWidget(m_pButtonMainMenu);

    m_pHlayout->addLayout(m_pVlayout1);
    m_pHlayout->addSpacing(100);
    m_pHlayout->addLayout(m_pVlayout2);
}

PlayingField::~PlayingField()
{

}

void PlayingField::ClearAllInventorySlots()
{
    m_pInventory->ClearAllSlots();
}

void PlayingField::slot_ButtonMainMenuPressed()
{
    emit signal_ButtonMainMenuPressed();
}
