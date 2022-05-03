
#include "connexion.h"
#include "ui_connexion.h"
#include "inscription.h"
#include "db.h"
#include "chat.h"

Db& dbm =  Db::Instance();

connexion::connexion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::connexion)
{
    ui->setupUi(this);
}

connexion::~connexion()
{
    delete ui;
}


void connexion::on_pushButtonConnection_clicked()
{
    QString identifiant,motDePasse;
    identifiant = ui->lineEditPseudo->text();
    motDePasse = ui->lineEditMotDePasse->text();

    if(dbm.login(identifiant,motDePasse)){
        QMessageBox::information(this,"Connexion","Réussi");
        chat ch;
        ch.exec();
      }else{
        QMessageBox::critical(this,"Connexion","Connexion échouée, veuillez reprendre.");
    }

}

//void fermerConnexion(){

//}
void connexion::on_pushButtonPasCompte_clicked()
{
    inscription i;
    i.exec();
}
