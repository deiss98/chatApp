#include "invitation.h"
#include "ui_invitation.h"

invitation::invitation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::invitation)
{
    ui->setupUi(this);
}

invitation::~invitation()
{
    delete ui;
}

void invitation::on_pushButtonEnvoyerInv_clicked()
{

}
