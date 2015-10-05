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

#include "gathread.h"

GAThread::GAThread(GenericGeneticAlgorithm *ga, QObject *parent) :
    QThread(parent),
    _ga(ga)
{
}

void GAThread::run()
{
    _ga->runGa();
}

GenericGene *GAThread::getBestGene()
{
    return _ga->bestGene();
}
