#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QBoxLayout>

#include "gamemenu.h"
#include "playingfield.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*
 * Класс главного окна приложения.
 * Содержит меню и игровое поле.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QHBoxLayout* m_pHlayout;

    GameMenu* m_pGameMenu;
    PlayingField* m_pPlayingField;

    /*
     * Очищает все непустые ячейки инвентаря при выходе из приложения.
     */
    void closeEvent(QCloseEvent *event);

private slots:
    /*
     * Начинает новую игру, очищает все непустые ячейки инвентаря,
     * открывает доступ к игровому полю.
     */
    void slot_StartNewGame();
    /*
     * Очищает все непустые ячейки инвентаря, закрывает приложение.
     */
    void slot_Exit();
    /*
     * Закрывает доступ к игровому полю, открывает доступ к меню игры.
     */
    void slot_ShowMenu();
};

#endif // MAINWINDOW_H
