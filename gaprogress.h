#ifndef GAPROGRESS_H
#define GAPROGRESS_H

#include <QDialog>
#include <ga/genericgeneticalgorithm.h>
#include "gathread.h"

namespace Ui {
class GAProgress;
}

class GAProgress : public QDialog
{
    Q_OBJECT

public:
    explicit GAProgress(GenericGeneticAlgorithm *ga, QWidget *parent = 0);
    ~GAProgress();

public slots:
    void get_ga_progress(int current, int max, double best_fitness_value, double average_fitness);
    void ga_finished(double best_fitness_value, double average_fitness, int rounds);

private:
    Ui::GAProgress *ui;
    GAThread *_thread;
};

#endif // GAPROGRESS_H
