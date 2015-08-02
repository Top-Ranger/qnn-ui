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

#ifndef RUNPROPERTIES_H
#define RUNPROPERTIES_H

#include <QDialog>
#include <QString>

namespace Ui {
class RunProperties;
}

class RunProperties : public QDialog
{
    Q_OBJECT

public:
    explicit RunProperties(QWidget *parent = 0);
    ~RunProperties();
    QString folderPath();
    bool saveGA();
    bool saveGene();
    int runs();


private slots:
    void on_horizontalSlider_valueChanged(int value);
    void on_spinBox_valueChanged(int arg1);
    void on_toolButton_clicked();
    void on_checkBox_GA_clicked();
    void on_checkBox_gene_clicked();

private:
    void checkbox_clicked();

    Ui::RunProperties *ui;
};

#endif // RUNPROPERTIES_H
