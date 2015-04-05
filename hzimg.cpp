#include <fstream>
#include <istream>
#include <QPainter>
#include <QDir>
#include "hzImg.h"

using namespace std;

hzImg::hzImg(QWidget *parent) :QWidget(parent),code(0x1FFF)
{
    setFixedSize(32,32);
}

QGridLayout* hzImg::CodeToImg(unsigned short code){
    setcode(code);
    QGridLayout* layout=new QGridLayout;
    update();
    layout->addWidget(this, 0, 0, 16, 16);
    return layout;
}

hzImg::~hzImg()
{
}

void hzImg::setcode(unsigned short code){
    this->code=code;
}

void hzImg::paintEvent(QPaintEvent *)
{
    char u[32];
    int		i, j, k=0, m;
    long	ofs;
    if (code==0x1FFF) return;
    if ((code&0xE000)==0)
        ofs=code*32;
    else
        ofs=(code-0x2000+256)*32;

    QString home_path = QDir::homePath();
    home_path = home_path.append("/Development/cpp/Chinput/mhzk16");
    fstream fbin(home_path.toUtf8().constData(), ios::binary | ios::in);
    fbin.seekp(ofs);
    fbin.read(u,32);
    fbin.close();

    QPainter painter(this);
    QPen pen;
    QPointF pointf[1000];
    pen.setColor(Qt::red);
    painter.setPen(pen);

    for(j=0; j<16; j++){
        m=0x80;
        for(i=0; i<8; i++){
            if(u[2*j]&m){
                pointf[k].setX(i*2);
                pointf[k].setY(j*2);
                k++;
                pointf[k].setX(i*2+1);
                pointf[k].setY(j*2);
                k++;
                pointf[k].setX(i*2);
                pointf[k].setY(j*2+1);
                k++;
                pointf[k].setX(i*2+1);
                pointf[k].setY(j*2+1);
                k++;
            }
            m>>=1;
        }
        m=0x80;
        for(i=8; i<16; i++){
            if(u[2*j+1]&m){
                pointf[k].setX(i*2);
                pointf[k].setY(j*2);
                k++;
                pointf[k].setX(i*2+1);
                pointf[k].setY(j*2);
                k++;
                pointf[k].setX(i*2);
                pointf[k].setY(j*2+1);
                k++;
                pointf[k].setX(i*2+1);
                pointf[k].setY(j*2+1);
                k++;
            }
            m>>=1;
        }
    }
    painter.drawPoints(pointf, k-1);

}
