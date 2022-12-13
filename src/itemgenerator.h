#ifndef ITEMGENERATOR_H
#define ITEMGENERATOR_H

#include <QFrame>
#include <QVBoxLayout>
#include <QMouseEvent>

#include "item.h"

/*
 * Класс виджета, который генерирует предмет.
 * В данном случае он генерирует яблоко.
 * Содержит указатель на генерируемый предмет и
 * количество генерируемых предметов.
 */
class ItemGenerator : public QFrame
{
    Q_OBJECT
public:
    explicit ItemGenerator(QWidget *parent = nullptr);

    Item* m_pItem;
    int m_itemsCount;
    QVBoxLayout* m_pLyt;

    /*
     * При нажатии на левую кнопку мыши дает возможность перетаскивать предмет.
     */
    void mousePressEvent(QMouseEvent* event) override;

signals:

};

#endif // ITEMGENERATOR_H
