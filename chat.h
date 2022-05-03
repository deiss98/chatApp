#ifndef CHAT_H
#define CHAT_H

#include <QDialog>

namespace Ui {
class chat;
}

class chat : public QDialog
{
    Q_OBJECT

public:
    explicit chat(QWidget *parent = 0);
    ~chat();

private slots:
    void on_pushButtonEnvoyerInv_clicked();

    void on_pushButtonAccepter_clicked();

    void on_pushButtonRefuserInvitation_clicked();

    void on_comboBoxCorrespondantAmis_currentIndexChanged(const QString &arg1);

    void on_pushButtonEnvoyerMessage_clicked();

private:
    Ui::chat *ui;
};

#endif // CHAT_H
