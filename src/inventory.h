#ifndef INVENTORY_H
#define INVENTORY_H

#include <QWidget>
#include <QFrame>
#include <QGridLayout>
#include <QMap>
#include <QSoundEffect>

#include "database.h"
#include "inventoryslot.h"

/*
 * Класс виджета инвентаря.
 * Содержит классы ячеек инвентаря и отображает их в виде сетки.
 * Также содержит базу данных, которая описывает, какой предмет находится в каждой
 * ячейке инвентаря и сколько в ячейке этих предметов.
 * Соединяет сигналы об изменении типа и количества предметов к слотам базы данных,
 * которые корректируют базу на основе новой информации.
 */
class Inventory : public QFrame
{
    Q_OBJECT
public:
    explicit Inventory(QWidget *parent = nullptr);

    /*
     * Очищает все непустые ячейки инвентаря.
     */
    void ClearAllSlots();

signals:

private:
    const int M_C_TOTAL_SIZE = 9;  // Сколько ячеек содержит инвентарь
    const int M_C_HORIZONTAL_SIZE = 3;  // Максимум ячеек в одной строке инвентаря

    QGridLayout* m_gridLyt;
    QSoundEffect* m_pAppleBiteSound;
    Database* m_pDatabase;

    /*
     * Контейнер, в котором ключ - индекс ячейки инвентаря (начиная с 0),
     * а значение - это указатель на объект ячейки.
     */
    QMap<int, InventorySlot*> m_slots;

private slots:
    /*
     * Проигрывает звук откусывания яблока.
     */
    void slot_AppleRemovedFromSlot();
};

#endif // INVENTORY_H
