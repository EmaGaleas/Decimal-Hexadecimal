#include "cframe.h"
#include "ui_cframe.h"
#include <QPixmap>
#include <QMessageBox>

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


void Cframe::on_Pb_calcular_clicked()
{
    if(ui->Rb_dec_a_hex->isChecked() || ui->Rb_hex_a_dec->isChecked()){
        QString texto = ui->TXT_ingresado->text();
        if(texto.isEmpty()){
            QMessageBox::warning(this, "Revisar", "Debe ingresar un dato a convertir.");
        }else{
            //aqui llamar a funcion con resultado
            ui->Le_obtenido->setText(texto);
        }
    }else{
        QMessageBox::warning(this, "Aviso", "Debe seleccionar qué proceso desea realizar.");
    }
}


//codigo de estilo y logica relacionada a lo visual
void Cframe::estiloInicial()
{
    ui->f_inicial->setStyleSheet("QFrame { background-color: black; }");

    ui->L_ingresedato->setStyleSheet("color: white;");
    ui->L_valorobtenido->setStyleSheet("color: white;");
    ui->TXT_ingresado->setStyleSheet("background-color: black; color: #5ce1e6;");

    ui->Rb_dec_a_hex->setStyleSheet("color: white;");
    ui->Rb_hex_a_dec->setStyleSheet("color: white;");
    ui->TXT_ingresado->setStyleSheet("color: #5ce1e6;");
    ui->Le_obtenido->setStyleSheet("color: white;");

    QPixmap pixmap(":/new/P1/portada.png");
    ui->L_titulo->setPixmap(pixmap);
    ui->L_titulo->setScaledContents(true);
}

void Cframe::actualizarLabels(const QString& textoIngreso, const QString& textoSalida) {
    ui->L_ingresedato->setText(textoIngreso);
    ui->L_valorobtenido->setText(textoSalida);
    ui->TXT_ingresado->clear();
    ui->Le_obtenido->clear();
}

void Cframe::on_Rb_dec_a_hex_clicked() {
    actualizarLabels("Ingrese dato en Decimal: ", "Valor obtenido en Hexadecimal: ");
}

void Cframe::on_Rb_hex_a_dec_clicked() {
    actualizarLabels("Ingrese dato en Hexadecimal: ", "Valor obtenido en Decimal: ");
}
