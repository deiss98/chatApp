#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include <QDialog>

namespace Ui {
class inscription;
}

class inscription : public QDialog
{
    Q_OBJECT

public:
    explicit inscription(QWidget *parent = 0);
    ~inscription();

private slots:
    void on_pushButtonInscription_clicked();
    void on_pushButtonInscriptionConnexion_clicked();

private:
    Ui::inscription *ui;
};

#endif // INSCRIPTION_H
