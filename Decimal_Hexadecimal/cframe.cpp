#include "cframe.h"
#include "ui_cframe.h"
#include <QPixmap>

Cframe::Cframe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Cframe)
{
    ui->setupUi(this);
    setFixedSize(size());
    estiloInicial();

}

Cframe::~Cframe()
{
    delete ui;
}

void Cframe::Doc_Hex()
{

}

void Cframe::estiloInicial()
{
    ui->f_inicial->setStyleSheet("QFrame { background-color: black; }");

    ui->L_ingresedato->setStyleSheet("color: white;");
    ui->L_valorobtenido->setStyleSheet("color: white;");
    ui->Rb_dec_a_hex->setStyleSheet("color: white;");
    ui->Rb_hex_a_dec->setStyleSheet("color: white;");
    ui->TXT_ingresado->setStyleSheet("color: blue;");
    ui->Le_obtenido->setStyleSheet("color: white;");

    QPixmap pixmap(":/new/P1/portada.png");
    ui->L_titulo->setPixmap(pixmap);
    ui->L_titulo->setScaledContents(true);
}
