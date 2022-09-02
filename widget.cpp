#include "widget.h"
#include "ui_widget.h"
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<float.h>
#include<QMessageBox>     //to use the MessageBox function.
#include"qcustomplot.h"   //For ui->customPlots
#include"dialog.h"



void normal_eqn_coefficients(double M[3][4], double *c, double *d, int n);//user defined function for coefficient matrix
void polynomial(double J[3],double D[3][4]);       //user defined matrix to find coefficients of quadratic polynomial.



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->pushButton_Close2,SIGNAL(clicked()),this,SLOT(close())); //to close 1st window

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_START_clicked()  //initialized after clicking on FIND button.
{
    int n,i; //declaring number of data points(X AND Y each)

        //scanf("%d",&n);
        n=ui->spinBox->value();     //Input for "n" value

        if(n<3)         //Condition to check possibility of regression (Curve Fitting).
        {    QMessageBox msgBox;
                     msgBox.setText("Regression is not possible.");
                     msgBox.exec();
            printf("Regression is not possible and hence the equation to the data can't be determined \n");
        }
        else
        {
        printf("Regression is possible\n");
        double X[n],Y[n],C[3][4],J[3];

        //Input of X and Y vales in the array form.

        X[0]=ui->doubleSpinBox_1->value();

        X[1]=ui->doubleSpinBox_2->value();

        X[2]=ui->doubleSpinBox_3->value();

        X[3]=ui->doubleSpinBox_4->value();

        X[4]=ui->doubleSpinBox_5->value();

        X[5]=ui->doubleSpinBox_6->value();

        Y[0]=ui->doubleSpinBox_7->value();

        Y[1]=ui->doubleSpinBox_8->value();

        Y[2]=ui->doubleSpinBox_9->value();

        Y[3]=ui->doubleSpinBox_10->value();

        Y[4]=ui->doubleSpinBox_11->value();

        Y[5]=ui->doubleSpinBox_12->value();

        //Printing input values of X and Y.

        for( i=0; i<n; i++)
        {
        printf("X[%d]=%lf\t", i, X[i]);
        printf("Y[%d]=%lf\n", i, Y[i]);
        }

        normal_eqn_coefficients(C,X,Y,n); //First user defined function calling

        polynomial(J,C);                  //Second user defined function calling

        //Printing the quadratic polynomial

        printf("the polynomial is f(x) = %lf + %lf x+ %lf x^2 \n",J[0],J[1],J[2]);


        //to print a0,a1,a2....in GUI
        ui->listWidget_1->addItem(QString::number((J[0])));
        ui->listWidget_2->addItem(QString::number((J[1])));
        ui->listWidget_3->addItem(QString::number((J[2])));

        //to print quadratic equation...in GUI
        ui->listWidget_4->addItem(QString::number((J[0])));
        ui->listWidget_5->addItem(QString::number((J[1])));
        ui->listWidget_6->addItem(QString::number((J[2])));

        //Plotting graph

        QVector<double> a(101), b(101); // initializing entries
        a[0]=ui->doubleSpinBox_1->value();

        a[1]=ui->doubleSpinBox_2->value();

        a[2]=ui->doubleSpinBox_3->value();

        a[3]=ui->doubleSpinBox_4->value();

        a[4]=ui->doubleSpinBox_5->value();

        a[5]=ui->doubleSpinBox_6->value();

        for (int i=0; i<6; ++i)
        {
            a[i] =X[i];
            b[i] =J[0]+J[1]*a[i]+J[2]* a[i]*a[i]; // let's plot a quadratic function
        }
        // creating graph and assigning data to it:
        ui->customPlot->addGraph();
        ui->customPlot->graph(0)->setData(a, b);

        ui->customPlot->xAxis->setLabel("x"); //Naming X-axis
        ui->customPlot->yAxis->setLabel("y"); //Naming Y-axis

        ui->customPlot->xAxis->setRange(-10000, 10000); //X-axis range
        ui->customPlot->yAxis->setRange(-10000, 10000);    //Y-axis range
        ui->customPlot->graph(0)->rescaleAxes();     //rescaling axes
        ui->customPlot->replot();


    }


        }







//This function makes of the data points stored in X[i],Y[i] and produces the matrix form for the system of normal equations,the solution of which yields us the
//coefficients a0,a1,a2 of the quadratic polynomial a0 + a1*X+ a2*X^2.


    void normal_eqn_coefficients(double M[3][4], double *c, double *d, int n)
    {
    int i,j;

    double X1=0.0, X2=0.0, X3=0.0, X4=0.0, Y1=0.0, X1Y1=0.0,X2Y1=0.0; //Variable initialization and declaration.


    for(i=0;i<=n-1;i++)
    {

    X1=X1+*(c+i);                      //Calculation of Summation of X[n]
    X2=X2+pow(*(c+i),2);               //Calculation of Summation of X[n]^2
    X3=X3+pow(*(c+i),3);               //Calculation of Summation of X[n]^3
    X4=X4+pow(*(c+i),4);               //Calculation of Summation of X[n]^4
    Y1=Y1+*(d+i);                      //Calculation of Summation of Y[n]
    X1Y1=X1Y1+(*(c+i))*(*(d+i));       //Calculation of Summation of X[n]*Y[n]
    X2Y1=X2Y1+ pow(*(c+i),2)*(*(d+i)); //Calculation of Summation of X[n]^2*Y[n]
    }

    //The coefficient matrix

    M[0][0]=n;
    M[0][1]=X1;
    M[0][2]=X2;
    M[0][3]=Y1;
    M[1][0]=X1;
    M[1][1]=X2;
    M[1][2]=X3;
    M[1][3]=X1Y1;
    M[2][0]=X2 ;
    M[2][1]=X3;
    M[2][2]=X4;
    M[2][3]=X2Y1;

    //Printing the coefficient matrix

    printf("The coefficient matrix is\n");

    for(i=0;i<=2;i++)
    {
    for(j=0;j<=3;j++)
    {
    printf("%lf\t", M[i][j]);
    }
    printf("\n");
    }

    }

    //This function receives the matrix obtained from the previous function as one of its arguments and reduces it to Row Echelon form Matrix.
    //After the reducing to Row Echelon form by performing series of row operations,the system is solved for a0,a1,a2.

    void polynomial(double A[3],double D[3][4])
    {

    int i,j;
    double N[3][4], a0,a1,a2,c2;  //Declaration of coefficients of x for the found Quadratic Polynomial.

    for(i=0;i<=2;i++)
    {
    for(j=0;j<=3;j++)
    {
    N[i][j]=D[i][j];   //Copying the matrix
    }
    }
    //Row operations start.
    for(j=0;j<=3;j++)
    {
    N[0][j]=D[0][j];
    }

    if(D[1][0] != 0)   //Checking whether the 1st element of the 2nd row is "0" or not
    {
    for(j=0; j<=3; j++)
    {
    N[1][j]=(D[1][j]*(D[0][0]/D[1][0]))-D[0][j];  //Calculation to find the 2nd row.
    }
    }

    printf("The row reduced matrix after 2nd row reduction\n");
    for(i=0;i<=2;i++)
    {
    for(j=0;j<=3;j++)
    {
    printf("%lf\t",N[i][j]);
    }
    printf("\n");
    }

    if(D[2][0] != 0)  //Checking whether the 1st element of the 3rd row is "0" or not
    {
    for(j=0; j<=3; j++)
    {
    N[2][j]=(D[2][j]*(D[0][0]/D[2][0]))-D[0][j];  //Calculating 3rd row.
    }
    }

    printf("The row reduced matrix after 3rd row reduction\n");
    for(i=0;i<=2;i++)
    {
    for(j=0;j<=3;j++)
    {
    printf("%lf\t",N[i][j]);
    }
    printf("\n");
    }


    //matrix copying after 2nd & 3rd row 1st element reduction to 0
    for(i=0;i<=2;i++)
    {
    for(j=0;j<=3;j++)
    {
    D[i][j]=N[i][j];
    }
    }

    //Reducing 3rd row 2nd element to 0
    if(N[2][1] != 0) //Checking whether the 2nd element of the 3rd row is "0" or not
    {
    for(j=0;j<=3;j++)
    {
    N[2][j]=(D[2][j]*(D[1][1]/D[2][1]))-D[1][j];  //Calculating 3rd row.
    }
    }

    //Checking for the conditions where a number of elements of the matrix can have value '0' and result in different kinds of solutions.

    //evaluating for a0,a1,a2.

    if(N[2][2]==0 && N[2][3]!=0)  //and operator to check the consistancy of the system.
    {

        QMessageBox msgBox;
                 msgBox.setText("Given system is inconsistent.");
                 msgBox.exec();
                 printf("Given system is inconsistent");
    }
    else if(N[2][2]==0 && N[2][3]==0)
    {
    a2=1;         //a2 value calculation based on the above condition.
    }
    else
    {
    a2=N[2][3]/N[2][2];  //a2 value calculation based on the above condition.
    }




    if((N[1][1]==0 && N[1][2]==0) && N[1][3]!=0)  //condition to check consistancy of system.
    {

        QMessageBox msgBox;
                 msgBox.setText("Given system is inconsistent.");
                 msgBox.exec();
                 printf("Given system is inconsistent");
    }
    else if((N[1][1]==0 && N[1][2]!=0) && N[1][3]!=0)
    {
    c2=N[1][3]/N[1][2];
    if(c2==a2)
    {
    a1=1;
    a0=(N[0][3]-(N[0][2]*a2)-(N[0][1]*a1))/N[0][0];
    A[0]=a0;    //assigning the a0 value to the array
    A[1]=a1;    //assigning the a1 value to the array
    A[2]=a2;    //assigning the a2 value to the array
    }
    }
    else if((N[1][1]==0 && N[1][2]==0) && N[1][3]==0)
    {
    a1=1;
    a0=(N[0][3])/N[0][0]-(N[0][2]*a2)/N[0][0]-(N[0][1]*a1)/N[0][0];
    A[0]=a0;
    A[1]=a1;
    A[2]=a2;
    }
    else
    {
    a1=(N[1][3]-(N[1][2]*a2))/N[1][1];
    a0=(N[0][3]-(N[0][2]*a2)-(N[0][1]*a1))/N[0][0];
    }

    A[0]=a0;
    A[1]=a1;
    A[2]=a2;

    printf("the coefficients are %lf %lf %lf \n",a0,a1,a2); //Final values of the coefficients of the Quadratic equation.

    }



void Widget::on_secwindow_clicked()
{
    Dialog dialog;
    dialog.setModal(true);
    dialog.exec();
}


//Reset input values to default.

void Widget::on_pushButton_RESET_clicked()
{
   ui->doubleSpinBox_1->setValue(0);
   ui->doubleSpinBox_2->setValue(0);
   ui->doubleSpinBox_3->setValue(0);
   ui->doubleSpinBox_4->setValue(0);
   ui->doubleSpinBox_5->setValue(0);
   ui->doubleSpinBox_6->setValue(0);
   ui->doubleSpinBox_7->setValue(0);
   ui->doubleSpinBox_8->setValue(0);
   ui->doubleSpinBox_9->setValue(0);
   ui->doubleSpinBox_10->setValue(0);
   ui->doubleSpinBox_11->setValue(0);
   ui->doubleSpinBox_12->setValue(0);

   ui->listWidget_1->clear();
   ui->listWidget_2->clear();
   ui->listWidget_3->clear();
   ui->listWidget_4->clear();
   ui->listWidget_5->clear();
   ui->listWidget_6->clear();
}
