#ifndef INVITATION_H
#define INVITATION_H

#include <QDialog>

namespace Ui {
class invitation;
}

class invitation : public QDialog
{
    Q_OBJECT

public:
    explicit invitation(QWidget *parent = 0);
    ~invitation();

private slots:
    void on_pushButtonEnvoyerInv_clicked();

private:
    Ui::invitation *ui;
};

#endif // INVITATION_H
