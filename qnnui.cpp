#include "qnnui.h"
#include "ui_qnnui.h"

#include <QStringList>
#include <QMessageBox>
#include "gaprogress.h"
#include "gathread.h"

// NN
#include <network/abstractneuralnetwork.h>
#include <network/feedforwardnetwork.h>
#include <network/continuoustimerecurrenneuralnetwork.h>

// SIM
#include <simulation/genericsimulation.h>

// GA
#include <ga/genericgeneticalgorithm.h>


QNNUI::QNNUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QNNUI),
    _nn_model(NULL),
    _sim_model(NULL),
    _ga_model(NULL)
{
    ui->setupUi(this);

    _nn_model = new QStringListModel(this);
    ui->nnView->setModel(_nn_model);
    _sim_model = new QStringListModel(this);
    ui->simView->setModel(_sim_model);
    _ga_model = new QStringListModel(this);
    ui->gaView->setModel(_ga_model);

    QStringList nn;
    nn << "FeedForwardNeuralNetwork";
    nn << "ContinuousTimeRecurrenNeuralNetwork";

    _nn_model->setStringList(nn);

    QStringList sim;
    sim << "GenericSimulation";

    _sim_model->setStringList(sim);

    QStringList ga;
    ga << "GenericGeneticAlgorithm";

    _ga_model->setStringList(ga);
}

QNNUI::~QNNUI()
{
    delete ui;
}

void QNNUI::on_pushButton_clicked()
{
    AbstractNeuralNetwork *network = NULL;
    GenericSimulation *simulation = NULL;
    GenericGeneticAlgorithm *ga = NULL;

    QString selection;

    if(ui->simView->currentIndex().data().toString() == ""
            || ui->nnView->currentIndex().data().toString() == ""
            || ui->gaView->currentIndex().data().toString() == "")
    {
        QMessageBox::information(this,
                                 tr("Invalid selection"),
                                 tr("Please select an item from every category"));
        return;
    }

    // parse SIM
    selection = ui->simView->currentIndex().data().toString();
    if(selection == "GenericSimulation")
    {
        simulation = new GenericSimulation();
    }

    else
    {
        showUnknownSelectionWindow(selection);
        goto on_pushButton_clicked_cleanup;
    }

    // parse NN
    selection = ui->nnView->currentIndex().data().toString();
    if(selection == "FeedForwardNeuralNetwork")
    {
        network = new FeedForwardNetwork(simulation->needInputLength(), simulation->needOutputLength());
    }
    else if(selection == "ContinuousTimeRecurrenNeuralNetwork")
    {
        network = new ContinuousTimeRecurrenNeuralNetwork(simulation->needInputLength(), simulation->needOutputLength(), 2*simulation->needInputLength()*simulation->needOutputLength());
    }
    else
    {
        showUnknownSelectionWindow(selection);
        goto on_pushButton_clicked_cleanup;
    }

    // parse GA
    selection = ui->gaView->currentIndex().data().toString();
    if(selection == "GenericGeneticAlgorithm")
    {
        ga = new GenericGeneticAlgorithm(network, simulation);
    }
    else
    {
        showUnknownSelectionWindow(selection);
        goto on_pushButton_clicked_cleanup;
    }

    // show window
    GAProgress *window;
    window = new GAProgress(ga, this);

    window->exec();
    delete window;

    // cleanup
on_pushButton_clicked_cleanup:

    delete ga;
    delete simulation;
    delete network;
}

void QNNUI::on_actionAbout_triggered()
{
    QMessageBox::information(this,
                             tr("About QNNUI"),
                             tr("QNNUI is a simple graphical interface to the qnn library\nAuthor: Marcus Soll"));
}

void QNNUI::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}

void QNNUI::on_actionQuit_triggered()
{
    QApplication::quit();
}

void QNNUI::showUnknownSelectionWindow(QString s)
{
    QMessageBox::warning(this,
                         tr("Unknown selection"),
                         QString(tr("Unknown selection: &1")).arg(s));
}
