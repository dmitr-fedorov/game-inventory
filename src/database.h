#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QObject *parent = nullptr);

signals:

private:
    QSqlDatabase m_database;

private slots:
    /*
     * Меняет количество и тип предмета в ячейке с индексом slotIndex.
     */
    void slot_ItemInSlotChanged(int slotIndex, const QString& itemType, int itemsCount);
    /*
     * Удаляет из базы данных запись с информацией об ячейке с индексом slotIndex.
     */
    void slot_SlotCleared(int slotIndex);
};

#endif // DATABASE_H
