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

#ifndef QNNUI_H
#define QNNUI_H

#include <QMainWindow>
#include <QString>
#include <QStringListModel>

namespace Ui {
class QNNUI;
}

class QNNUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit QNNUI(QWidget *parent = 0);
    ~QNNUI();

private slots:
    void on_pushButton_clicked();
    void on_actionAbout_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionQuit_triggered();

private:
    void showUnknownSelectionWindow(QString s);
    Ui::QNNUI *ui;

    QStringListModel *_nn_model;
    QStringListModel *_sim_model;
    QStringListModel *_ga_model;
};

#endif // QNNUI_H
