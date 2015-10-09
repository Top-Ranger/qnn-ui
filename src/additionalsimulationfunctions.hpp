#ifndef ADDITIONALSIMULATIONFUNCTIONS_HPP
#define ADDITIONALSIMULATIONFUNCTIONS_HPP

#include <QVector>

namespace AdditionalSimulationFunctions {
QVector<qint32> generateHugeMaze()
{
    QVector<qint32> list;
    int number = (qrand()%5)+1;
    list << number;
    for(int i = 0; i < 150; ++i)
    {
        list << 0;
    }
    if(qrand()%2)
    {
        list << number;
    }
    else
    {
        list << (qrand()%5)+1;
    }
    return list;
}
}

#endif // ADDITIONALSIMULATIONFUNCTIONS_HPP
