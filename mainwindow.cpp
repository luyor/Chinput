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
    selection_layout_ = new FlowLayout();


    main_layout_->addLayout(flow_layout_, 30);
    main_layout_->addLayout(input_layout_, 3);
    main_layout_->addLayout(selection_layout_, 3);

    setCentralWidget(new QWidget());
    centralWidget()->setLayout(main_layout_);

    input_handler_ = new InputHandler();
    selection_ = 0;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {

    }
    if (event->key() <= Qt::Key_Z && event->key() >= Qt::Key_A) {
        unsigned short int code = event->key() - Qt::Key_A + 'a';
        input_string_.append(code);
        selection_ = 0;
        input_result_ = input_handler_->get_result(input_string_.toUtf8().constData());
        RefreshInputView();
    }
    if (event->key() <= Qt::Key_9 && event->key() >= Qt::Key_0) {
        qDebug("%c", event->key() - Qt::Key_0 + '0');
        int select = event->key() - Qt::Key_0;
        if ((select > 0) && (select <= kWordsPerSelection) && (select + selection_ * kWordsPerSelection <=  input_result_.size() )) {
             hzImg *img = new hzImg;
             img->setcode(GetZBCode(input_result_[select + selection_ * kWordsPerSelection - 1]));
             flow_layout_->addWidget(img);
             qDebug("%s", input_result_[selection_ * kWordsPerSelection + select - 1].c_str());
             input_string_.clear();
             input_result_.clear();
             selection_ = 0;
             RefreshInputView();
        }
    }
    if (event->key() == Qt::Key_Space) {
        if (input_result_.size()) {
            hzImg *img = new hzImg;
            img->setcode(GetZBCode(input_result_[selection_ * kWordsPerSelection]));
            flow_layout_->addWidget(img);
            input_string_.clear();
            input_result_.clear();
            selection_ = 0;
            RefreshInputView();
        }
    }
    if (event->key() == Qt::Key_Backspace) {
        if (input_string_.size()) {
            input_string_.remove(input_string_.length() - 1, 1);
            selection_ = 0;
            input_result_ = input_handler_->get_result(input_string_.toUtf8().constData());
            RefreshInputView();
        }
        else if (flow_layout_->count()) {
            QLayoutItem *item;
            item = flow_layout_->takeAt(flow_layout_->count() - 1);
            selection_layout_->removeWidget(item->widget());
            delete item->widget();
            delete item;
        }

    }
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        qDebug("asdfasd");
        if (input_string_.size()) {
            for (int i = 0; i < input_string_.size(); i++) {
                char code = input_string_[i].unicode();
                hzImg *img = new hzImg;
                img->setcode(code);
                flow_layout_->addWidget(img);
        }
        input_string_.clear();
        input_result_.clear();
        selection_ = 0;
        RefreshInputView();
        }
    }
    if (event->key() == Qt::Key_Minus) {
        selection_ = selection_ == 0 ? selection_ : selection_ - 1;
    }

    if (event->key() == Qt::Key_Equal) {
        selection_ ++;
    }
    RefreshSelectionView();
}

void MainWindow::RefreshInputView()
{
    QLayoutItem *item;
    while ((item = input_layout_->takeAt(0)) != NULL) {
        selection_layout_->removeWidget(item->widget());
        delete item->widget();
        delete item;
    }

    for (int i = 0; i < input_string_.size(); i++) {
        char code = input_string_[i].unicode();
        hzImg *img = new hzImg;
        img->setcode(code);
        input_layout_->addWidget(img);
    }
}


void MainWindow::RefreshSelectionView()
{
    if (selection_ * kWordsPerSelection >= input_result_.size()) {
         selection_ = (input_result_.size() - 1) / kWordsPerSelection;
    }

    QLayoutItem *item;
    while((item = selection_layout_->takeAt(0)) != NULL) {
        selection_layout_->removeWidget(item->widget());
        delete item->widget();
        delete item;
    }

    for (int i = 0; i < kWordsPerSelection; i++) {
        if (selection_ * kWordsPerSelection + i >= input_result_.size()) break;
        hzImg *img = new hzImg;
        img->setcode(i + '1');
        selection_layout_->addWidget(img);
        img = new hzImg;
        img->setcode(GetZBCode(input_result_[i + selection_ * kWordsPerSelection]));
        selection_layout_->addWidget(img);
    }
}

unsigned short int MainWindow::GetZBCode(std::string str)
{
    if (str.size() != 2) return 0;
    unsigned short int a, b;
    a = str[0];
    a = (a - 0xA1) & 0xff;
    b = str[1];
    b = (b - 0xA1) & 0xff;
    return 0x2000 + a*94 + b;
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
