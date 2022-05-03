#ifndef CONNEXION_H
#define CONNEXION_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QMessageBox>
#include <QSqlError>

#include <QWidget>

namespace Ui {
class connexion;
}

class connexion : public QWidget
{
    Q_OBJECT

public:

    explicit connexion(QWidget *parent = nullptr);
    ~connexion();

private slots:

    void on_pushButtonConnection_clicked();

    void on_pushButtonPasCompte_clicked();

private:
    Ui::connexion *ui;
    QSqlDatabase db;
};
#endif // CONNEXION_H
