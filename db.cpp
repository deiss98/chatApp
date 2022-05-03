#include "db.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QVector>
#include <QVector>
#include <qDebug>
#include <QDateTime>
#include <QMessageBox>

Db Db::m_instance=Db();

Db& Db::Instance()
{
    return m_instance;
}
Db::~Db()
{
    qDebug()<<"Destruction"<<endl;
}

Db::Db()
{
   m_db = QSqlDatabase::addDatabase("QSQLITE");
   m_db.setHostName("127.0.0.1");
   m_db.setDatabaseName("C:/Users/KONDO-TECH/Documents/chatApp/chat_app.db");

   if (!m_db.open())
   {
      qDebug() << "Error: connection with database failed";
   }
   else
   {
      qDebug() << "Database: connection ok";
   }
}
//void Db::set_userId(QString id){
//        userId=id;
//}
//void Db::set_username(QString u){
//        username=u;
//}
//void Db::set_firstname(QString f){
//        firstname=f;
//}
//void Db::set_lastname(QString l){
//        lastname=l;
//}
QString Db::userId(){
        return id;
}
QString Db::get_pseudo(){
        return pseudo;
}
QString Db::get_prenom(){
        return prenom;
}
QString Db::get_nom(){
        return nom;
}
bool Db::login(const QString& usernam,const QString& password)
{
   bool res =false;
   // you should check if args are ok first...
   QSqlQuery query;
   query.prepare("SELECT * from utilisateur WHERE pseudo=:username and password=:password");
   query.bindValue(":username", usernam);
   query.bindValue(":password", password);

   if(query.exec())
   {
       if(query.next())
       {

            qDebug() << "Data: " <<QVariant(query.value(0)).toString();
            id = QVariant(query.value(0)).toString();
            nom = QVariant(query.value(1)).toString();
            prenom = QVariant(query.value(2)).toString();
            pseudo = QVariant(query.value(3)).toString();
            res =true;
       }

   }
   else
   {
         res =false;
   }

   return res;
}
//QVector <QString> Db::getUser(const QString& id)
//{
//   QVector <QString> res;
//   QSqlQuery query;
//   query.prepare("SELECT * from users WHERE id=:id");
//   query.bindValue(":id", id);

//   if(query.exec())
//   {
//       if(query.next()){
//            res.push_back(QVariant(query.value(0)).toString());
//            res.push_back(QVariant(query.value(1)).toString());
//            res.push_back(QVariant(query.value(2)).toString());
//            res.push_back(QVariant(query.value(3)).toString());
//       }

//   }
//   return res;
//}

QString Db::signUp(const QString& name,const QString& firstname,const QString& login,const QString& mail, const QString& password)
{
   // you should check if args are ok first...
   QSqlQuery checkquery;
  checkquery.prepare("SELECT * from utilisateur WHERE pseudo=:username");
  checkquery.bindValue(":username", login);

  if(checkquery.exec()){
      if(checkquery.next()){
        return "utlisateur_existe";
      }
  }else{
      qDebug() << "Check user existe error: "<< checkquery.lastError();
  }

   QSqlQuery query;
   query.prepare("INSERT INTO utilisateur (nom, prenom, pseudo, email, password) VALUES (:nom,:prenom, :pseudo, :email, :password)");
   query.bindValue(":nom", name);
   query.bindValue(":prenom", firstname);
   query.bindValue(":pseudo", login);
   query.bindValue(":email", mail);
   query.bindValue(":password", password);
   if(query.exec())
   {
       return "success";
   }
   else
   {
       qDebug() << "Add user error: "<< checkquery.lastError();
       return "error";
   }

}

//bool Db::addMessage(const QString& message,const QString& senderId, const QString& invitationId)
//{

//   QSqlQuery query;
//   query.prepare("INSERT INTO messages (senderId, invitationId, content, created_at) VALUES (:senderId,:invitationId, :content, :created_at)");
//   query.bindValue(":senderId", senderId);
//   query.bindValue(":invitationId", invitationId);
//   query.bindValue(":content", message);
//   query.bindValue(":created_at", QDateTime::currentDateTime());

//   if(query.exec())
//   {
//       return true;
//   }
//   else
//   {
//       return false;
//   }

//}

bool Db::setInvitationStatus(const QString& invitationId,const QString& statut){
    bool res=false;
    QSqlQuery query;
    query.prepare("UPDATE invitation SET statut=:status WHERE id_invitation=:id");
    query.bindValue(":status", statut);
    query.bindValue(":id", invitationId);
    if(query.exec())
    {
        res = true;
    }
    else
    {
         qDebug() << "update inviatation error: "
                  << query.lastError();
    }

    return res;
}

QString Db::addInvitation(const QString& id_envoyeur,const QString& id_receveur)
{
   QString res = "error";
   // you should check if args are ok first...
   QSqlQuery checkquery, checkId;
   checkId.prepare("SELECT * FROM utilisateur WHERE id_utilisateur=:idReceveur");
   checkId.bindValue(":idReceveur", id_receveur);
   if(checkId.exec()){
       if(checkId.next()){
           checkquery.prepare("SELECT * from invitation WHERE (id_utilisateur2=:id_r and id_utilisateur1=:id_s) or (id_utilisateur2=:id_s and id_utilisateur1=:id_r)");
           checkquery.bindValue(":id_r", id_receveur);
           checkquery.bindValue(":id_s", id_envoyeur);

          if(checkquery.exec()){
              if(checkquery.next()){
                  if(QVariant(checkquery.value(3)).toString()=="En_attente"){
                       return "invitation_exist_in_pending";
                  }else if(QVariant(checkquery.value(3)).toString()=="Accepter"){
                      return "invitation_exist_in_success";
                 }else if(QVariant(checkquery.value(3)).toString()=="Rejeter"){
                      return "invitation_exist_in_reject";
                 }
              }
          }
           QSqlQuery query;
           query.prepare("INSERT INTO invitation (id_utilisateur1, id_utilisateur2, statut) VALUES (:sender, :receiver, :status)");
           query.bindValue(":sender", id_envoyeur);
           query.bindValue(":receiver", id_receveur);
           query.bindValue(":status", "En_attente");
           if(query.exec()){
               res = "success";
           }
           else{
                qDebug() << "addInviation error: "
                         << query.lastError();
           }
           return res;
       }else{
           return "id_error";
       }
   }
}

//QVector <QVector <QString>> Db::listUser()
//{
//   QVector <QVector <QString>> list;
//   // you should check if args are ok first...
//   QSqlQuery query;


//   if(query.exec("SELECT * from users"))
//   {
//       while(query.next()){
//            QVector <QString> current;
//            current.push_back(QVariant(query.value(0)).toString());
//            current.push_back(QVariant(query.value(1)).toString());
//            list.push_back(current);
//       }
//   }

//   return list;
//}

QVector <QVector <QString>> Db::listInvitationEnAttente(const QString& senderId)
{
   QVector <QVector <QString>> list;
   // you should check if args are ok first...
   QSqlQuery query;

   if(query.exec("SELECT invitation.id_invitation, invitation.id_utilisateur1, invitation.id_utilisateur2, invitation.statut, utilisateur.pseudo from invitation, utilisateur where invitation.id_utilisateur2="+QVariant(senderId).toString()+" and invitation.id_utilisateur1=utilisateur.id_utilisateur and statut='En_attente'"))
   {
       while(query.next()){
            QVector <QString> current;
            current.push_back(QVariant(query.value(0)).toString());
            current.push_back(QVariant(query.value(1)).toString());
            current.push_back(QVariant(query.value(2)).toString());
            current.push_back(QVariant(query.value(3)).toString());
            current.push_back(QVariant(query.value(4)).toString());
            list.push_back(current);
       }
   }

   return list;
}


//QVector <QString> Db::getInvitation(const QString& invitationId)
//{
//    QVector <QString> current;
//   // you should check if args are ok first...
//   QSqlQuery query;

//   if(query.exec("SELECT invitations.id,users.username,invitations.senderId, invitations.receiverId,invitations.status from invitations,users where invitations.id="+QVariant(invitationId).toString()+" and invitations.senderId=users.id"))
//   {
//       if(query.next()){

//            current.push_back(QVariant(query.value(0)).toString());
//            current.push_back(QVariant(query.value(1)).toString());
//            current.push_back(QVariant(query.value(2)).toString());
//            current.push_back(QVariant(query.value(3)).toString());
//            current.push_back(QVariant(query.value(4)).toString());

//       }
//   }

//   return current;
//}

QVector <QVector <QString>> Db::amis(const QString& idEnvoyeur)
{
   QVector <QVector <QString>> listAmis;

   QSqlQuery query;

   if(query.exec("SELECT invitation.id_invitation, invitation.id_utilisateur1, invitation.id_utilisateur2, invitation.statut, utilisateur.pseudo FROM invitation,utilisateur WHERE (invitation.id_utilisateur1="+QVariant(idEnvoyeur).toString()+" or invitation.id_utilisateur2="+QVariant(idEnvoyeur).toString()+") and invitation.id_utilisateur2=utilisateur.id_utilisateur and statut='Accepter'"))
   {
       while(query.next()){
            QVector <QString> current;
            current.push_back(QVariant(query.value(0)).toString());
            current.push_back(QVariant(query.value(1)).toString());
            current.push_back(QVariant(query.value(2)).toString());
            current.push_back(QVariant(query.value(3)).toString());
            current.push_back(QVariant(query.value(4)).toString());
            listAmis.push_back(current);
       }
   }

   return listAmis;
}


QVector <QVector <QString>> Db::listMessage(const QString& Id,const QString& receiverId)
{
   QVector <QVector <QString>> list;
   // you should check if args are ok first...
   QSqlQuery query;
   qDebug()<<"SELECT date_envoie, message_texte, utilisateur.pseudo from message, utilisateur where (id_utilisateur1="+Id+" and id_utilisateur2="+receiverId+" and utilisateur.id_utilisateur=id_utilisateur1) or (id_utilisateur2="+receiverId+" and id_utilisateur1="+Id+" and utilisateur.id_utilisateur=id_utilisateur2)";
   if(query.exec("SELECT date_envoie, message_texte, utilisateur.pseudo from message, utilisateur where (id_utilisateur1="+Id+" and id_utilisateur2="+receiverId+" and utilisateur.id_utilisateur=id_utilisateur1) or (id_utilisateur2="+receiverId+" and id_utilisateur1="+Id+" and utilisateur.id_utilisateur=id_utilisateur2)"))
   {
       while(query.next()){
            QVector <QString> current;
            current.push_back(QVariant(query.value(0)).toString());
            current.push_back(QVariant(query.value(1)).toString());
            current.push_back(QVariant(query.value(2)).toString());
            list.push_back(current);
       }
   }

   return list;
}
