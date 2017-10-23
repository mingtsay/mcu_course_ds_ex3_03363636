#ifndef SQUARE_H
#define SQUARE_H

#include <QAbstractTableModel>

class Square : public QAbstractTableModel
{
public:
    enum Direction
    {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight,
        Default = TopLeft
    };
    Q_ENUM(Direction)

    Square(const int size = 3, const Direction direction = Direction::Default);
    ~Square();
    int size() const;
    void resize(const int size, const Direction direction);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    int *_squareValues;
    int _size;
    void _realloc();
    void _execute(const Direction direction);
    int _positionConst(const int x, const int y) const;
    int _position(int &x, int &y) const;
};

#endif // SQUARE_H
