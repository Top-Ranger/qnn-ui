#include "gaprogress.h"
#include "ui_gaprogress.h"

#include <QMessageBox>

GAProgress::GAProgress(GenericGeneticAlgorithm *ga, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GAProgress),
    _thread(NULL)
{
    ui->setupUi(this);


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
}

void GAProgress::get_ga_progress(int current, int max, double best_fitness_value, double average_fitness)
{
    ui->progressBar->setMaximum(max);
    ui->progressBar->setValue(current);
    ui->textEdit->append(QString(tr("Round %1 of %2: %3 (avg. %4)")).arg(current).arg(max).arg(best_fitness_value).arg(average_fitness));
}

void GAProgress::ga_finished(double best_fitness_value, double average_fitness, int rounds)
{
    QMessageBox::information(this,
                             tr("GA finished"),
                             QString(tr("Genetic algorithm finished with a fitness of %1 (avg. %2) after %3 rounds").arg(best_fitness_value).arg(average_fitness).arg(rounds)));
     this->close();
}
