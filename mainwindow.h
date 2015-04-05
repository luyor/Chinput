#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <flowlayout.h>
#include <QLabel>
#include "hzImg.h"
#include "InputHandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    const int kWordsPerSelection = 5;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void RefreshSelectionView();
    void RefreshInputView();
    void setLayout();

    unsigned short int GetZBCode(std::string);

private:
    Ui::MainWindow *ui;
    QVBoxLayout *main_layout_;
    FlowLayout *flow_layout_;
    FlowLayout *input_layout_;
    FlowLayout *selection_layout_;
    QVector<hzImg *> input_vector_;
    QString input_string_;
    InputHandler *input_handler_;
    InputHandler::ResultVector input_result_;
    std::size_t selection_;
};

#endif // MAINWINDOW_H
