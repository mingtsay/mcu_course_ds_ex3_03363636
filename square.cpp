#include "square.h"

Square::Square(const int size, const Square::Direction direction)
{
    resize(size, direction);
}

Square::~Square()
{
    delete _squareValues;
}

int Square::size() const
{
    return _size;
}

void Square::resize(const int size, const Square::Direction direction)
{
    _size = size;
    QModelIndex top = index(0, 0);
    QModelIndex bottom = index(_size, _size);

    emit layoutAboutToBeChanged();

    _realloc();
    _execute(direction);

    emit dataChanged(top, bottom);
    emit layoutChanged();
}

int Square::rowCount(const QModelIndex & /* unused */) const
{
    return _size + 1;
}

int Square::columnCount(const QModelIndex & /* unused */) const
{
    return _size + 1;
}

QVariant Square::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        if (index.column() == _size && index.row() == _size)
        {
            int sum = 0, sum2 = 0;
            for (int i = 0; i < _size; ++i)
            {
                sum += _squareValues[_positionConst(i, i)];
                sum2 += _squareValues[_positionConst(_size - i - 1, i)];
            }
            return QStringLiteral("↖︎%1\n↗︎%2").arg(sum).arg(sum2);
        }
        if (index.column() == _size)
        {
            int sum = 0;
            for (int i = 0; i < _size; ++i)
                sum += _squareValues[_positionConst(i, index.row())];
            return QStringLiteral("←%1").arg(sum);
        }
        if (index.row() == _size)
        {
            int sum = 0;
            for (int i = 0; i < _size; ++i)
                sum += _squareValues[_positionConst(index.column(), i)];
            return QStringLiteral("↑%1").arg(sum);
        }
        return _squareValues[_positionConst(index.column(), index.row())];
    }
    return QVariant();
}

void Square::_realloc()
{
    delete[] _squareValues;
    _squareValues = new int[_size * _size]{};
}

void Square::_execute(const Direction direction)
{
    int x = _size / 2, y = 0, value = 1;

    _squareValues[_positionConst(x, y)] = value;

    while (value++ < _size * _size)
    {
        int nextX = x, nextY = y;
        switch (direction)
        {
        case Direction::TopLeft:     --nextX; --nextY; break;
        case Direction::TopRight:    ++nextX; --nextY; break;
        case Direction::BottomLeft:  --nextX; ++nextY; break;
        case Direction::BottomRight: ++nextX; ++nextY; break;
        }
        if (_squareValues[_position(nextX, nextY)])
        {
            if (direction == Direction::TopLeft || direction == Direction::TopRight)
            {
                ++y;
            }
            else
            {
                --y;
            }
        }
        else
        {
            x = nextX;
            y = nextY;
        }
        _squareValues[_position(x, y)] = value;
    }
}

int Square::_positionConst(const int x, const int y) const
{
    int _x = x, _y = y;
    return _position(_x, _y);
}

int Square::_position(int &x, int &y) const
{
    x = (x + _size) % _size;
    y = (y + _size) % _size;
    return x + y * _size;
}
