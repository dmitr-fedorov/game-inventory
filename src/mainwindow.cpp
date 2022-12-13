#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pGameMenu = new GameMenu(this);
    m_pPlayingField = new PlayingField(this);

    ui->verticalLayout->addWidget(m_pGameMenu, 0, Qt::AlignTop);
    ui->verticalLayout->addWidget(m_pPlayingField, 1, Qt::AlignCenter);
    ui->verticalLayout->setAlignment(Qt::AlignCenter);

    connect(m_pGameMenu, SIGNAL(signal_buttonNewGamePressed()),
            this, SLOT(slot_StartNewGame()));

    connect(m_pGameMenu, SIGNAL(signal_buttonExitPressed()),
            this, SLOT(slot_Exit()));

    connect(m_pPlayingField, SIGNAL(signal_ButtonMainMenuPressed()),
            this, SLOT(slot_ShowMenu()));

    m_pPlayingField->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    m_pPlayingField->ClearAllInventorySlots();
}

void MainWindow::slot_StartNewGame()
{
    m_pPlayingField->ClearAllInventorySlots();
    m_pGameMenu->hide();
    m_pPlayingField->setDisabled(false);
}

void MainWindow::slot_Exit()
{
    qApp->quit();
}

void MainWindow::slot_ShowMenu()
{
    m_pPlayingField->setDisabled(true);
    m_pGameMenu->show();
}
