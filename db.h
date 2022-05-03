#ifndef DB_H
#define DB_H

#include <QtSql/QSqlDatabase>
#include <QVector>

class Db
{
public:
    static Db& Instance();
    bool login(const QString& username,const QString& password);
    QString signUp(const QString& nom,const QString& prenom,const QString& pseudo,const QString& email, const QString& mot_de_passe);
    QString addInvitation(const QString& senderId,const QString& receiverId);
//    bool addMessage(const QString& message,const QString& senderId, const QString& receiverId);
    bool setInvitationStatus(const QString& invitationId,const QString& status);

    QVector <QVector <QString>> listInvitationEnAttente(const QString& senderId);
    QVector <QVector <QString>> amis(const QString& idEnvoyeur);
    QVector <QVector <QString>> listMessage(const QString& Id,const QString& receiverId);


    QString userId();
    QString get_pseudo();
    QString get_prenom();
    QString get_nom();
private:
    QSqlDatabase m_db;

    Db& operator= (const Db&){}
    Db (const Db&){}

    static Db m_instance;
    Db();
    ~Db();

     QString id;
     QString pseudo;
     QString prenom;
     QString nom;

};
#endif // DB_H
