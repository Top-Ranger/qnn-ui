#ifndef GATHREAD_H
#define GATHREAD_H

#include <QThread>
#include <ga/genericgeneticalgorithm.h>

class GAThread : public QThread
{
    Q_OBJECT
public:
    explicit GAThread(GenericGeneticAlgorithm *ga, QObject *parent = 0);

    void run();

signals:

public slots:

private: GenericGeneticAlgorithm *_ga;
};

#endif // GATHREAD_H
