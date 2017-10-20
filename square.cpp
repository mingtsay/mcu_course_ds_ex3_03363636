#include "square.h"
#include <cstring>

Square::Square(const int size)
{
    resize(size);
}

Square::~Square()
{
    delete _squareValues;
}

int Square::value(int x, int y) const
{
    return _squareValues[_position(x, y)];
}

int Square::size() const
{
    return _size;
}

void Square::setValue(int x, int y, const int value)
{
    _squareValues[_position(x, y)] = value;
    QModelIndex top = index(y, x);
    QModelIndex bottom = index(y, x);
    emit dataChanged(top, bottom);
}

void Square::resize(const int size)
{
    _size = size;
    _realloc();
}

void Square::clear()
{
    QModelIndex top = index(0, 0);
    QModelIndex bottom = index(_size - 1, _size - 1);

    memset(_squareValues, 0, sizeof(int) * _size * _size);
    emit dataChanged(top, bottom);
}

int Square::rowCount(const QModelIndex &parent) const
{
    return _size;
}

int Square::columnCount(const QModelIndex &parent) const
{
    return _size;
}

QVariant Square::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        return value(index.column(), index.row());
    }
    return QVariant();
}

void Square::_realloc()
{
    emit layoutAboutToBeChanged();
    delete _squareValues;
    _squareValues = new int[_size * _size];
    clear();
    emit layoutChanged();
}

int Square::_position(int &x, int &y) const
{
    while (x < 0) x += _size;
    while (y < 0) y += _size;
    x %= _size;
    y %= _size;
    return x + y * _size;
}
