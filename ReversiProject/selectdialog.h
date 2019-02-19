#ifndef SELECTDIALOG_H
#define SELECTDIALOG_H

#include <QDialog>

namespace Ui {
class SelectDialog;
}

class SelectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectDialog(QWidget *parent = 0);
    ~SelectDialog();
    int get_search_depth() { return search_depth; }
    int get_humanplayer() { return humanplayer; }

private slots:
    void on_ackButton_clicked();

private:
    Ui::SelectDialog *ui;
    int search_depth;
    int humanplayer;
};

#endif // SELECTDIALOG_H
