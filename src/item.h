#ifndef ITEM_H
#define ITEM_H

#include <QLabel>
#include <QPixmap>

/*
 * Класс, представляющий собой виджет предмета.
 * В данном случае это яблоко.
 * Содержит тип предмета в виде строки.
 * Часть QLabel этого класса содержит изображение предмета в виде QPixmap.
 */
class Item : public QLabel
{
    Q_OBJECT
public:
    explicit Item(QWidget* parent = nullptr);

    /*
     * Возвращает типа предмета в виде строки.
     */
    const QString& GetType();
    /*
     * Устанавливает тип предмета в предмет type.
     */
    void SetType (const QString& type);

protected:
    QString m_type; // Тип предмета
};

#endif // ITEM_H
