#include "gaprogress.h"
#include "ui_gaprogress.h"
#include "runproperties.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QTime>
#include <QDate>
#include <network/genericgene.h>

GAProgress::GAProgress(GenericGeneticAlgorithm *ga, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GAProgress),
    _run(0),
    _amountRuns(1),
    _saveGA(false),
    _saveGene(false),
    _folderPath(""),
    _fileName(""),
    _thread(NULL),
    _file(NULL),
    _stream(NULL),
    _ga(ga)
{
    ui->setupUi(this);

    RunProperties window;
    if(window.exec() == window.Accepted && window.folderPath() != "")
    {
        _amountRuns = window.runs();
        _saveGA = window.saveGA();
        _saveGene = window.saveGene();
        _folderPath = window.folderPath();
        _fileName = QString("%1T%2").arg(QDate::currentDate().toString("yyyy-mm-dd")).arg(QTime::currentTime().toString("HH:mm:ss.zzz"));
    }

    this->setWindowFlags(((windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowCloseButtonHint));
    ui->progressBar_2->setMaximum(_amountRuns);

    QObject::connect(_ga,SIGNAL(ga_current_round(int,int,double, double)),this,SLOT(get_ga_progress(int,int,double, double)));
    QObject::connect(_ga,SIGNAL(ga_finished(double, double, int)),this,SLOT(ga_finished(double, double, int)));

    startRun();
}

GAProgress::~GAProgress()
{
    delete ui;

    if(_thread != NULL)
    {
        delete _thread;
    }
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

void GAProgress::startRun()
{
    if(_file != NULL)
    {
        _file->close();
        delete _file;
    }

    if(_stream != NULL)
    {
        delete _stream;
    }

    if(_saveGA && _folderPath != "")
    {
        QString path(_folderPath);
        path = path.append("/%1-%2.csv").arg(_fileName).arg(_run+1);

        _file = new QFile(path);
        if(_file->open(QIODevice::WriteOnly))
        {
            _stream = new QTextStream(_file);
            *_stream << "round;best_fitness;average_fitness\n";
        }
    }

    if(_run != 0)
    {
        ui->textEdit->append(QString(tr("\n")).arg(_run+1));
    }

    ui->textEdit->append(QString(tr("+++ Starting run %1 +++")).arg(_run+1));

            if(_thread != NULL)
    {
        delete _thread;
    }

    _thread = new GAThread(_ga);
    _thread->start();
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
    if(_saveGene)
    {
        QString path(_folderPath);
        path = path.append("/%1-%2.gene").arg(_fileName).arg(_run+1);
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
    if(++_run < _amountRuns)
    {
        startRun();
    }
    else
    {
        QMessageBox::information(this,
                                 tr("Finished"),
                                 tr("All runs finished"),
                                 QMessageBox::Ok);
        this->close();
    }
}
