#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    
private slots:
    void on_Read_clicked();

    void on_pushButton_close_clicked();

private:
    Ui::Dialog *ui;
    void getTextFile();
};

#endif // DIALOG_H
