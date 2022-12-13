#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>

class GameMenu : public QWidget
{
    Q_OBJECT
public:
    GameMenu(QWidget *parent = nullptr);
    ~GameMenu();

private:
    QHBoxLayout* m_pHlayout;
    QPushButton* m_pButtonNewGame;
    QPushButton* m_pButtonExit;

signals:
    void signal_buttonNewGamePressed();
    void signal_buttonExitPressed();

private slots:
    /*
     * Испускает сигнал о нажатии на кнопку начала новой игры.
     * Сигнал необходим для работы главного окна.
     */
    void slot_buttonNewGamePressed();
    /*
     * Испускает сигнал о нажатии на кнопку выхода из игры.
     * Сигнал необходим для работы главного окна.
     */
    void slot_buttonExitPressed();
};

#endif // GAMEMENU_H
