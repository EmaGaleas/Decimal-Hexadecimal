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
//Area de codigo funcional

QString Cframe::Dec_Hex(int* numeroDecimal)
{
    char hexDigitos[] = "0123456789ABCDEF";
    int valor = *numeroDecimal;

    if(valor == 0) return "0";

    char* temp = new char[20];
    char* pTemp = temp;

    while(valor > 0) {
        *pTemp = hexDigitos[valor % 16];
        valor /= 16;
        pTemp++;
    }
    *pTemp = '\0';

    QString resultado;
    char* end = pTemp - 1;
    for(char* ptr = end; ptr >= temp; ptr--) {
        resultado.append(*ptr);
    }

    delete[] temp;

    return resultado;
}



void Cframe::on_Pb_calcular_clicked()
{
    if(ui->Rb_dec_a_hex->isChecked() || ui->Rb_hex_a_dec->isChecked()){
        QString texto = ui->TXT_ingresado->text();
        if(texto.isEmpty()){
            QMessageBox::warning(this, "Revisar", "Debe ingresar un dato a convertir.");
        }else{
            //aqui llamar a funcion con resultado
            if(ui->Rb_dec_a_hex->isChecked()){
                int* numeroPtr = new int(ui->TXT_ingresado->text().toInt());
                QString hex = Dec_Hex(numeroPtr);
                delete numeroPtr;

                ui->Le_obtenido->setText(hex);
            }else{
                QMessageBox::warning(this, "Aviso", "Aun no tenemos una funcion que resuelva este caso.\nVuelve Pronto ;(");

            }
        }
    }else{
        QMessageBox::warning(this, "Aviso", "Debe seleccionar qué proceso desea realizar.");
    }
}


//codigo de estilo y logica relacionada a lo visual NO TOCAR NI HACER NADA AQUI ABAJO
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
