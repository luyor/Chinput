#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <flowlayout.h>
#include <QLabel>
#include "hzImg.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void setLayout();

private:
    Ui::MainWindow *ui;
    FlowLayout *flow_layout_;
    QVBoxLayout *main_layout_;
    FlowLayout *input_layout_;
    QVector<hzImg *> input_vector_;
};

#endif // MAINWINDOW_H
