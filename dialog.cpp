#include "dialog.h"
#include "ui_dialog.h"
#include"widget.h"
#include"ui_widget.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_close,SIGNAL(clicked()),this,SLOT(close())); //to close second window

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_Read_clicked()
{
 getTextFile();   //calling function to import file
}

//getting input textfile.

void Dialog::getTextFile()
{
    QFile myFile(":/to_user.txt");
    myFile.open(QIODevice::ReadOnly);    //Textfile opening and reading.

    QTextStream textStream(&myFile);

    QString line=textStream.readAll();   //Storing textfile in line variable.
    myFile.close();
    ui->textEdit->setPlainText(line);    //Getting the content of the text file in the textedit area of the window.


}

