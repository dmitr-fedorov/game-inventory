#include "database.h"

#include <QSqlQuery>
#include <QSqlResult>

Database::Database(QObject *parent)
    : QObject{parent}
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("inventoryDB");
    m_database.open();

    QSqlQuery query(m_database);

    query.exec("PRAGMA foreign_keys = ON;");
    query.exec("PRAGMA journal_mode = WAL;");
    query.exec("PRAGMA synchronous = NORMAL");

    query.exec("CREATE TABLE Item(id INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT, "
               "name TEXT UNIQUE);");

    query.exec("CREATE TABLE Inventory(slot_index INTEGER UNIQUE NOT NULL, "
               "item_id INTEGER, "
               "items_count INTEGER, "
               "FOREIGN KEY(item_id) REFERENCES Item(id) ON DELETE CASCADE ON UPDATE CASCADE);");
}

void Database::slot_ItemInSlotChanged(int slotIndex, const QString& itemType, int itemsCount)
{
    QSqlQuery query(m_database);

    query.exec("INSERT INTO Item(name) VALUES('" + itemType + "');");

    query.exec("SELECT id FROM Item WHERE name='" + itemType + "';");
    query.next();
    int itemId = query.value(0).toInt();

    query.exec("INSERT OR REPLACE INTO Inventory(slot_index, item_id, items_count) "
               "VALUES("
               + QString::number(slotIndex) + ", "
               + QString::number(itemId)    + ", "
               + QString::number(itemsCount)
               + ");");
}

void Database::slot_SlotCleared(int slotIndex)
{
    QSqlQuery query(m_database);

    query.exec("DELETE FROM Inventory WHERE slot_index=" + QString::number(slotIndex) + ";");
}
