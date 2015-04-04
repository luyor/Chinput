#ifndef HZIMG_H
#define HZIMG_H

#include <QWidget>
#include <QLayout>
class hzImg : public QWidget{

private:
        unsigned short code;
public:
    hzImg(QWidget* parent = 0);
    ~hzImg();
    void paintEvent(QPaintEvent *);
    void setcode(unsigned short);
    QGridLayout* CodeToImg(unsigned short);
    int check(int i,int j);
};

#endif // HZIMG_H
