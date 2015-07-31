#ifndef GAPROGRESS_H
#define GAPROGRESS_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
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
    void startRun();

    Ui::GAProgress *ui;
    int _run;
    int _amountRuns;
    bool _saveGA;
    bool _saveGene;
    QString _folderPath;
    QString _fileName;
    GAThread *_thread;
    QFile *_file;
    QTextStream *_stream;
    GenericGeneticAlgorithm *_ga;
};

#endif // GAPROGRESS_H
