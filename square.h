#ifndef SQUARE_H
#define SQUARE_H

#include <QAbstractTableModel>

class Square : public QAbstractTableModel
{
public:
    Square(const int size = 3);
    ~Square();
    int value(int x, int y) const;
    int size() const;
    void setValue(int x, int y, const int value);
    void resize(const int size);
    void clear();

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    int *_squareValues;
    int _size;
    void _realloc();
    int _position(int &x, int &y) const;
};

#endif // SQUARE_H
