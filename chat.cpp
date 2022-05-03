#include "chat.h"
#include "ui_chat.h"
#include "db.h"
#include <QMessageBox>
#include <QVector>
#include <QtSql>
#include <QDateTime>
Db& dbc =  Db::Instance();
QString currentReceiverId;

chat::chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chat)
{
    ui->setupUi(this);
    ui->labelIdUtilisateur->setText(dbc.userId());
    // Invitation list
    QVector <QVector <QString>> listInvitationAttente(dbc.listInvitationEnAttente(dbc.userId()));
    for(size_t i(0); i < listInvitationAttente.size(); i++){
        ui->comboBoxListeInvitation->addItem(listInvitationAttente.at(i).at(4),QVariant(listInvitationAttente.at(i).at(0)));
    }

//    // Friend list
    QVector <QVector <QString>> listDesAmis(dbc.amis(dbc.userId()));
    for(size_t j(0); j < listDesAmis.size(); j++){
        if(dbc.userId() == QVariant(listDesAmis.at(j).at(2)).toString()){
            ui->comboBoxCorrespondantAmis->addItem(listDesAmis.at(j).at(4), QVariant(listDesAmis.at(j).at(1)));
        }else{
            ui->comboBoxCorrespondantAmis->addItem(listDesAmis.at(j).at(4), QVariant(listDesAmis.at(j).at(2)));
        }
    }



 }

chat::~chat()
{
    delete ui;
}

void chat::on_pushButtonEnvoyerInv_clicked()
{
   QString idSaisie(ui->lineEditEnvoyerInvitation->text());

   if(idSaisie == dbc.userId()){
       QMessageBox::critical(this, "Invitation", "Envoie impossible à votre identifiant");
   }else{
       QString invitation = dbc.addInvitation(dbc.userId(), idSaisie);
       if(invitation == "En_attente"){
           QMessageBox::critical(this, "Invitation", "Vous avez déjà cette invitation en attente");
       }else if(invitation == "Accepter"){
           QMessageBox::critical(this, "Invitation", "Vous ête déjà amis");
        }else if(invitation == "Rejeter"){
           QMessageBox::critical(this, "Invitation", "Vous avez refuser cette invitation, veuillez l'accepter !");
       }else if(invitation =="success"){
            QMessageBox::information(this, "Invitation", "Invitation envoyé avec succès");
            ui->lineEditEnvoyerInvitation->clear();
       }else if(invitation=="id_error"){
           QMessageBox::critical(this, "Invitation", "Vous ne pouvez pas envoyé d'invitation à cet utilisateur");
            ui->lineEditEnvoyerInvitation->clear();
       }else{
           QMessageBox::information(this, "Invitation", "Impossible d'envoyer l'invitation veuillez vous reconnecter !");
       }
   }
}

void chat::on_pushButtonAccepter_clicked()
{
    if(dbc.setInvitationStatus(ui->comboBoxListeInvitation->currentData().toString(),"Accepter")){
        QMessageBox::information(this, "Invitation", "Vous avez accepter l'invitation");
    }else{
        QMessageBox::critical(this, "Invitation", "Erreur lors de l'acceptation veuillez vous déconnecter !");
    }

}

void chat::on_pushButtonRefuserInvitation_clicked()
{
    if(dbc.setInvitationStatus(ui->comboBoxListeInvitation->currentData().toString(),"Refuser")){
        QMessageBox::information(this, "Invitation", "Vous avez refuser l'invitation de "+ui->comboBoxListeInvitation->currentText());
    }else{
        QMessageBox::critical(this, "Invitation", "Erreur lors de l'acceptation veuillez vous déconnecter !");
    }
}

void chat::on_comboBoxCorrespondantAmis_currentIndexChanged(const QString &arg1)
{

    ui->listWidgetChat->clear();
    QVector <QVector <QString>> listMessage = dbc.listMessage(dbc.userId(), QVariant(ui->comboBoxCorrespondantAmis->currentData()).toString());
    for(size_t t(0); t < listMessage.size(); t++){
        new QListWidgetItem(listMessage.at(t).at(2)+" : "+listMessage.at(t).at(0)+" : "+listMessage.at(t).at(1),ui->listWidgetChat);
    }
}

void chat::on_pushButtonEnvoyerMessage_clicked()
{
    QMessageBox::information(this, "Identifant ", QVariant(ui->comboBoxCorrespondantAmis->currentData()).toString());
    QString message = ui->lineEditSendMessage->text();
    QSqlQuery envoyerMessage;
    envoyerMessage.prepare("INSERT INTO message (id_utilisateur1, id_utilisateur2, message_texte, date_envoie) VALUES (:envoyeur,:receveur, :message, :date)");
    envoyerMessage.bindValue(":envoyeur", dbc.userId());

    envoyerMessage.bindValue(":receveur", QVariant(ui->comboBoxCorrespondantAmis->currentData()).toString());
    envoyerMessage.bindValue(":message", message);
    QString dateEnvoie = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    envoyerMessage.bindValue(":date",dateEnvoie);
    if(envoyerMessage.exec()){
        QMessageBox::information(this, "Message", "Message envoyé avec succès !");
    }else{
        QMessageBox::critical(this, "Message", "Impossible d'envoyer ce message' !");
    }
}

