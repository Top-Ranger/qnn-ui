#include "gathread.h"

GAThread::GAThread(GenericGeneticAlgorithm *ga, QObject *parent) :
    QThread(parent),
    _ga(ga)
{
}

void GAThread::run()
{
    _ga->run_ga();
}
