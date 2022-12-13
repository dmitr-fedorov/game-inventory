#include "gamemenu.h"

GameMenu::GameMenu(QWidget *parent)
{
    m_pHlayout = new QHBoxLayout(this);

    m_pButtonNewGame = new QPushButton("Новая игра", this);
    m_pButtonExit = new QPushButton("Выход", this);

    m_pHlayout->addWidget(m_pButtonNewGame);
    m_pHlayout->addSpacing(50);
    m_pHlayout->addWidget(m_pButtonExit);

    connect(m_pButtonNewGame, SIGNAL(clicked()),
            this, SLOT(slot_buttonNewGamePressed()));

    connect(m_pButtonExit, SIGNAL(clicked()),
            this, SLOT(slot_buttonExitPressed()));
}

GameMenu::~GameMenu()
{

}

void GameMenu::slot_buttonNewGamePressed()
{
    emit signal_buttonNewGamePressed();

}

void GameMenu::slot_buttonExitPressed()
{
    emit signal_buttonExitPressed();
}
