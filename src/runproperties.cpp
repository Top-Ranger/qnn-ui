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
    QFileDialog dialog(this, tr("Save ga run"), "", "comma-seperated values (*.csv)");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.exec();
    if(dialog.selectedFiles()[0].length() > 0)
    {
    ui->lineEdit->setText(dialog.selectedFiles()[0]);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(dialog.selectedFiles()[0] != "");
    }
    else
    {
        ui->lineEdit->setText("");
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}
