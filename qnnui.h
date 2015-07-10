#ifndef QNNUI_H
#define QNNUI_H

#include <QMainWindow>
#include <QString>
#include <QStringListModel>

namespace Ui {
class QNNUI;
}

class QNNUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit QNNUI(QWidget *parent = 0);
    ~QNNUI();

private slots:
    void on_pushButton_clicked();
    void on_actionAbout_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionQuit_triggered();

private:
    void showUnknownSelectionWindow(QString s);
    Ui::QNNUI *ui;

    QStringListModel *_nn_model;
    QStringListModel *_sim_model;
    QStringListModel *_ga_model;
};

#endif // QNNUI_H
