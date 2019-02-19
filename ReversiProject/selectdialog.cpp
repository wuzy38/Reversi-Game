#include "selectdialog.h"
#include "ui_selectdialog.h"
#include <QMessageBox>

SelectDialog::SelectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Reversi");
}

SelectDialog::~SelectDialog()
{
    delete ui;
}

void SelectDialog::on_ackButton_clicked()
{
    if (!ui->firstHandButton->isChecked() && !ui->secondHandButton->isChecked())
    {
        QMessageBox::warning(this, "Warning!", "请选择先后手");
    }
    else if(!ui->easyButton->isChecked() && !ui->middleButton->isChecked() && !ui->hardButton->isChecked())
    {
        QMessageBox::warning(this, "Warning!", "请选择难度");
    }
    else
    {
        if (ui->firstHandButton->isChecked())
            humanplayer = -1;
        else
            humanplayer = 1;
        if (ui->easyButton->isChecked())
            search_depth = 6;
        else if (ui->middleButton->isChecked())
            search_depth = 7;
        else
            search_depth = 8;
        accept();
    }
}
