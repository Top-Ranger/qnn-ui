#include "gaprogress.h"
#include "ui_gaprogress.h"

#include <QMessageBox>
#include <QFileDialog>
#include <network/genericgene.h>

GAProgress::GAProgress(GenericGeneticAlgorithm *ga, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GAProgress),
    _thread(NULL),
    _file(NULL),
    _stream(NULL)
{
    ui->setupUi(this);

    if(QMessageBox::information(this, tr("Save Details"), tr("Do you want to save the details of this run as comma-seperated values?"), QMessageBox::Yes|QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
    {
        QFileDialog dialog(this, tr("Save ga run"), "", "comma-seperated values (*.csv)");
        dialog.setAcceptMode(QFileDialog::AcceptSave);
        dialog.setDefaultSuffix("csv");
        dialog.exec();
        QString path = dialog.selectedFiles()[0];
        if(path != "")
        {
            _file = new QFile(path);
            if(_file->open(QIODevice::WriteOnly))
            {
                _stream = new QTextStream(_file);
                *_stream << "round;best_fitness;average_fitness\n";
            }
        }
    }

    this->setWindowFlags(((windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowCloseButtonHint));

    QObject::connect(ga,SIGNAL(ga_current_round(int,int,double, double)),this,SLOT(get_ga_progress(int,int,double, double)));
    QObject::connect(ga,SIGNAL(ga_finished(double, double, int)),this,SLOT(ga_finished(double, double, int)));

    _thread = new GAThread(ga);
    _thread->start();
}

GAProgress::~GAProgress()
{
    delete ui;
    delete _thread;
    if(_stream != NULL)
    {
        delete _stream;
    }
    if(_file != NULL)
    {
        _file->close();
        delete _file;
    }
}

void GAProgress::get_ga_progress(int current, int max, double best_fitness_value, double average_fitness)
{
    ui->progressBar->setMaximum(max);
    ui->progressBar->setValue(current);
    ui->textEdit->append(QString(tr("Round %1 of %2: %3 (avg. %4)")).arg(current).arg(max).arg(best_fitness_value).arg(average_fitness));
    if(_stream != NULL)
    {
        *_stream << current << ";" << best_fitness_value << ";" << average_fitness << "\n";
    }
}

void GAProgress::ga_finished(double best_fitness_value, double average_fitness, int rounds)
{
    QMessageBox::information(this,
                             tr("GA finished"),
                             QString(tr("Genetic algorithm finished with a fitness of %1 (avg. %2) after %3 rounds").arg(best_fitness_value).arg(average_fitness).arg(rounds)));
    if(QMessageBox::information(this, tr("Save Gene"), tr("Do you want to save the best gene?"), QMessageBox::Yes|QMessageBox::No, QMessageBox::No) == QMessageBox::Yes)
    {
        QFileDialog dialog(this, tr("Save gene"), "", "Gene (*.gene)");
        dialog.setAcceptMode(QFileDialog::AcceptSave);
        dialog.setDefaultSuffix("gene");
        dialog.exec();
        QString path = dialog.selectedFiles()[0];
        if(path != "")
        {
            QFile file(path);
            GenericGene *gene = _thread->getBestGene();
            if(!gene->saveGene(&file))
            {
                QMessageBox::warning(this,
                                     tr("Can not save"),
                                     tr("Can not save gene"));
            }
            delete gene;
        }
    }
    this->close();
}
