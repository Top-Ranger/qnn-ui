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

    QObject::connect(ga,SIGNAL(ga_current_round(int,int,double)),this,SLOT(get_ga_progress(int,int,double)));
    QObject::connect(ga,SIGNAL(ga_finished(double)),this,SLOT(ga_finished(double)));

    _thread = new GAThread(ga);
    _thread->start();
}

GAProgress::~GAProgress()
{
    delete ui;
    delete _thread;
}

void GAProgress::get_ga_progress(int current, int max, double best_fitness_value)
{
    ui->progressBar->setMaximum(max);
    ui->progressBar->setValue(current);
    ui->textEdit->append(QString(tr("Round %1 of %2: %3")).arg(current).arg(max).arg(best_fitness_value));
}

void GAProgress::ga_finished(double best_fitness_value)
{
    QMessageBox::information(this,
                             tr("GA finished"),
                             QString(tr("Genetic algorithm finished with a fitness of %1").arg(best_fitness_value)));
     this->close();
}
