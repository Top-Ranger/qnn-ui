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

#include "runproperties.h"
#include "ui_runproperties.h"

#include <QFileDialog>
#include <QPushButton>

RunProperties::RunProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RunProperties)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

RunProperties::~RunProperties()
{
    delete ui;
}

QString RunProperties::folderPath()
{
    return ui->lineEdit->text();
}

bool RunProperties::saveGA()
{
    return ui->checkBox_GA->isChecked();
}

bool RunProperties::saveGene()
{
    return ui->checkBox_gene->isChecked();
}

int RunProperties::runs()
{
    return ui->spinBox->value();
}

void RunProperties::on_horizontalSlider_valueChanged(int value)
{
    ui->spinBox->setValue(value);
}

void RunProperties::on_spinBox_valueChanged(int arg1)
{
    ui->horizontalSlider->setValue(arg1);
}

void RunProperties::on_toolButton_clicked()
{
    ui->lineEdit->setText(QFileDialog::getExistingDirectory(this, "Select output folder", ""));
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(ui->lineEdit->text() != "");
}

void RunProperties::on_checkBox_GA_clicked()
{
    checkbox_clicked();
}

void RunProperties::on_checkBox_gene_clicked()
{
    checkbox_clicked();
}

void RunProperties::checkbox_clicked()
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!(ui->checkBox_GA->isChecked() || ui->checkBox_gene->isChecked()));
}
