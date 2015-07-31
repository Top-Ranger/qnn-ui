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
