#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pewwidget.h"
#include "timeline.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void receivedActivated(PEWWidget *wid); // Receives signal from one of the widgets

protected:
    void mousePressEvent(QMouseEvent *me);

private:
    Ui::MainWindow *ui;
    Timeline *tline;

    // Widgets settings
    // *Connections
    void setConnections();
    void connectWidgets();
    // *Validators
    void setValidators();

    // Scene stuff
    void prepareScene();

signals:
    void becameActiveSignal(PEWWidget *wid); // Sends signal to all the widgets
};

#endif // MAINWINDOW_H
