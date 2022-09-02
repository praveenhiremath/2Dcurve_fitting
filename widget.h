#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    //void Widget::setupgraph(QCustomPlot *customPlot,double X[],double Y[],double a[]);

    ~Widget();
    
private slots:
    //created slots for starting the calculation,going to the second window, to reset input values , to close the window.
    void on_START_clicked();

    void on_secwindow_clicked();

    void on_pushButton_Plot_clicked();

    void on_pushButton_RESET_clicked();



private:
    Ui::Widget *ui;
   // double X[n],Y[n],a0,a1,a2,n;


};

#endif // WIDGET_H
