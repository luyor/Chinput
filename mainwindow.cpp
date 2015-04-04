#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QHBoxLayout>
#include "hzImg.h"
#include <flowlayout.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    flow_layout_ = new FlowLayout();
    main_layout_ = new QVBoxLayout();
    input_layout_ = new FlowLayout();

    main_layout_->addLayout(flow_layout_, 30);
    main_layout_->addLayout(input_layout_, 3);

    setCentralWidget(new QWidget());
    centralWidget()->setLayout(main_layout_);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {

    }
    if (event->key() <= Qt::Key_Z && event->key() >= Qt::Key_A) {
        qDebug("%c", event->key() - Qt::Key_A + 'a');
        unsigned short int code = event->key() - Qt::Key_A + 'a';
        hzImg *img = new hzImg;
        img->setcode(code);
        input_layout_->addWidget(img);
        input_vector_.push_back(img);
    }
    if (event->key() <= Qt::Key_9 && event->key() >= Qt::Key_0) {
        qDebug("%c", event->key() - Qt::Key_0 + '0');
    }
    if (event->key() == Qt::Key_Backspace) {
        if (! input_vector_.empty()) {

            auto img = input_vector_.back();
            img->hide();
            input_layout_->removeWidget(img);
            input_vector_.pop_back();
            delete img;
        }

    }
}

void MainWindow::setLayout()
{

}

void MainWindow::keyReleaseEvent(QKeyEvent *)
{

}

MainWindow::~MainWindow()
{
    delete ui;
}
