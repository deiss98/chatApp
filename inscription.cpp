#include "inscription.h"
#include "ui_inscription.h"
#include "connexion.h"
#include "db.h"


Db& dbi =  Db::Instance();

inscription::inscription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inscription)
{
    ui->setupUi(this);
}

inscription::~inscription()
{
    delete ui;
}

void inscription::on_pushButtonInscription_clicked()
{
    QString nom(ui->lineEditNom->text()), prenom(ui->lineEditPrenom->text()), pseudo(ui->lineEditPseudo->text()),email(ui->lineEditEmail->text()), password(ui->lineEditMotDePasse->text()), repeterPassword(ui->lineEditRMotDePasse->text()) ;
    if(!nom.isEmpty() && !prenom.isEmpty() && !pseudo.isEmpty() && !pseudo.isEmpty() && !email.isEmpty() && !password.isEmpty())
    {
        if(password != repeterPassword){
             QMessageBox::warning(this, "Erreur", "Les mots de passe ne sont pas identiques !");
             //Arreter la fonction ici aussi
             return;

        }

       QString response = dbi.signUp(nom, prenom, pseudo, email, password);
        if(response == "utlisateur_existe"){

            // Vérification de l'unicité du pseudo
            QMessageBox::warning(this, "Erreur", "Ce utilisateur existe déjà !");
            //Arreter la fonction ici
            return;
        }else if(response == "success"){

            QMessageBox::information(this, "Ajouter user", "Utilisateur inscrit avec succès !");
        }else{
         QMessageBox::warning(this, "Erreur", "Impossible de vous ajouter veuillez reprendre");
    }
    }else{
        QMessageBox::warning(this, "Champ vide", "Veuillez renseigner tous les champs vide");
    }
}



void inscription::on_pushButtonInscriptionConnexion_clicked()
{
    connexion c;
    c.show();
}
