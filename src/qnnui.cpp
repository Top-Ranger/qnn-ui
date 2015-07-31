#include "qnnui.h"
#include "ui_qnnui.h"

#include <math.h>
#include <QStringList>
#include <QMessageBox>
#include "gaprogress.h"
#include "gathread.h"

// NN
#include <network/abstractneuralnetwork.h>
#include <network/feedforwardnetwork.h>
#include <network/continuoustimerecurrenneuralnetwork.h>
#include <network/gasnet.h>
#include <network/modulatedspikingneuronsnetwork.h>

// SIM
#include <simulation/genericsimulation.h>
#include <simulation/tmazesimulation.h>

// GA
#include <ga/genericgeneticalgorithm.h>
#include <ga/nonparallelgenericgeneticalgorithm.h>


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
    nn << "FeedForwardNeuralNetwork (tanh)";
    nn << "ContinuousTimeRecurrenNeuralNetwork";
    nn << "ContinuousTimeRecurrenNeuralNetwork (tanh)";
    nn << "ContinuousTimeRecurrenNeuralNetwork (size changing)";
    nn << "ContinuousTimeRecurrenNeuralNetwork (size changing, tanh)";
    nn << "GasNet";
    nn << "ModulatedSpikingNeuronsNetwork (a)";
    nn << "ModulatedSpikingNeuronsNetwork (b)";
    nn << "ModulatedSpikingNeuronsNetwork (c)";
    nn << "ModulatedSpikingNeuronsNetwork (d)";
    nn << "ModulatedSpikingNeuronsNetwork (full)";
    nn << "ModulatedSpikingNeuronsNetwork (none)";

    _nn_model->setStringList(nn);

    QStringList sim;
    sim << "GenericSimulation";
    sim << "TMazeSimulation";

    _sim_model->setStringList(sim);

    QStringList ga;
    ga << "GenericGeneticAlgorithm";
    ga << "NonParallelGenericGeneticAlgorithm";

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
    else if(selection == "TMazeSimulation")
    {
        simulation = new TMazeSimulation();
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
    else if(selection == "FeedForwardNeuralNetwork (tanh)")
    {
        FeedForwardNetwork::config config;
        config.activision_function = &tanh;
        network = new FeedForwardNetwork(simulation->needInputLength(), simulation->needOutputLength(), config);
    }
    else if(selection == "ContinuousTimeRecurrenNeuralNetwork")
    {
        network = new ContinuousTimeRecurrenNeuralNetwork(simulation->needInputLength(), simulation->needOutputLength());
    }
    else if(selection == "ContinuousTimeRecurrenNeuralNetwork (tanh)")
    {
        ContinuousTimeRecurrenNeuralNetwork::config config;
        config.activision_function = &tanh;
        network = new ContinuousTimeRecurrenNeuralNetwork(simulation->needInputLength(), simulation->needOutputLength(), config);
    }
    else if(selection == "ContinuousTimeRecurrenNeuralNetwork (size changing)")
    {
         ContinuousTimeRecurrenNeuralNetwork::config config;
         config.size_changing = true;
         config.network_default_size_grow = 1;
         network = new ContinuousTimeRecurrenNeuralNetwork(simulation->needInputLength(), simulation->needOutputLength(), config);
    }
    else if(selection == "ContinuousTimeRecurrenNeuralNetwork (size changing, tanh)")
    {
         ContinuousTimeRecurrenNeuralNetwork::config config;
         config.size_changing = true;
         config.network_default_size_grow = 1;
         config.activision_function = &tanh;
         network = new ContinuousTimeRecurrenNeuralNetwork(simulation->needInputLength(), simulation->needOutputLength(), config);
    }
    else if(selection == "GasNet")
    {
        network = new GasNet(simulation->needInputLength(), 4*simulation->needOutputLength());
    }
    else if(selection == "ModulatedSpikingNeuronsNetwork (a)")
    {
        ModulatedSpikingNeuronsNetwork::config config;
        config.a_modulated = true;
        config.b_modulated = false;
        config.c_modulated = false;
        config.d_modulated = false;
        network = new ModulatedSpikingNeuronsNetwork(simulation->needInputLength(), 4*simulation->needOutputLength(), config);
    }
    else if(selection == "ModulatedSpikingNeuronsNetwork (b)")
    {
        ModulatedSpikingNeuronsNetwork::config config;
        config.a_modulated = false;
        config.b_modulated = true;
        config.c_modulated = false;
        config.d_modulated = false;
        network = new ModulatedSpikingNeuronsNetwork(simulation->needInputLength(), 4*simulation->needOutputLength(), config);
    }
    else if(selection == "ModulatedSpikingNeuronsNetwork (c)")
    {
        ModulatedSpikingNeuronsNetwork::config config;
        config.a_modulated = false;
        config.b_modulated = false;
        config.c_modulated = true;
        config.d_modulated = false;
        network = new ModulatedSpikingNeuronsNetwork(simulation->needInputLength(), 4*simulation->needOutputLength(), config);
    }
    else if(selection == "ModulatedSpikingNeuronsNetwork (d)")
    {
        ModulatedSpikingNeuronsNetwork::config config;
        config.a_modulated = false;
        config.b_modulated = false;
        config.c_modulated = false;
        config.d_modulated = true;
        network = new ModulatedSpikingNeuronsNetwork(simulation->needInputLength(), 4*simulation->needOutputLength(), config);
    }
    else if(selection == "ModulatedSpikingNeuronsNetwork (full)")
    {
        ModulatedSpikingNeuronsNetwork::config config;
        config.a_modulated = true;
        config.b_modulated = true;
        config.c_modulated = true;
        config.d_modulated = true;
        network = new ModulatedSpikingNeuronsNetwork(simulation->needInputLength(), 4*simulation->needOutputLength(), config);
    }
    else if(selection == "ModulatedSpikingNeuronsNetwork (none)")
    {
        ModulatedSpikingNeuronsNetwork::config config;
        config.a_modulated = false;
        config.b_modulated = false;
        config.c_modulated = false;
        config.d_modulated = false;
        network = new ModulatedSpikingNeuronsNetwork(simulation->needInputLength(), 4*simulation->needOutputLength(), config);
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
    else if(selection == "NonParallelGenericGeneticAlgorithm")
    {
        ga = new NonParallelGenericGeneticAlgorithm(network, simulation);
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
