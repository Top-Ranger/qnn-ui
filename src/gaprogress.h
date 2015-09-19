/*
 * Copyright (C) 2015 Marcus Soll
 * This file is part of qnn-ui.
 *
 * qnn-ui is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * qnn-ui is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with qnn-ui. If not, see <http://www.gnu.org/licenses/>.
 */

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
    void get_ga_progress(qint32 current, qint32 max, double best_fitness_value, double average_fitness);
    void ga_finished(double best_fitness_value, double average_fitness, qint32 rounds);

private:
    void startRun();

    Ui::GAProgress *ui;
    qint32 _run;
    qint32 _amountRuns;
    bool _saveGA;
    bool _saveGene;
    bool _saveXML;
    QString _folderPath;
    QString _fileName;
    GAThread *_thread;
    QFile *_file;
    QTextStream *_stream;
    GenericGeneticAlgorithm *_ga;
};

#endif // GAPROGRESS_H
