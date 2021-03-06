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
    GenericGene *getBestGene();

signals:

public slots:

private: GenericGeneticAlgorithm *_ga;
};

#endif // GATHREAD_H
