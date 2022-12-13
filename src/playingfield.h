#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include <QBoxLayout>
#include <QPushButton>

#include "inventory.h"
#include "itemgenerator.h"

/*
 * Класс игрового поля. Содержит инвентарь, виджет для генерации предмета
 * и кнопку доступа к главному меню игры.
 */
class PlayingField : public QWidget
{
    Q_OBJECT
public:
    PlayingField(QWidget *parent = nullptr);
    ~PlayingField();

    /*
     * Очищает все непустые ячейки инвентаря.
     */
    void ClearAllInventorySlots();

private:
    QHBoxLayout* m_pHlayout;
    QVBoxLayout* m_pVlayout1;
    QVBoxLayout* m_pVlayout2;
    QPushButton* m_pButtonMainMenu;

    Inventory* m_pInventory;
    ItemGenerator* m_pItemGenerator;

signals:
    void signal_ButtonMainMenuPressed();

private slots:
    /*
     * Испускает сигнал о нажатии на кнопку отображения главного меню.
     * Сигнал необходим для работы главного окна.
     */
    void slot_ButtonMainMenuPressed();
};

#endif // PLAYINGFIELD_H
