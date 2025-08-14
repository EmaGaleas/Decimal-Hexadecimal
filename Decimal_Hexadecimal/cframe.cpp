#include "cframe.h"
#include "ui_cframe.h"
#include <QPixmap>
#include <QMessageBox>
#include <bits/stdc++.h>

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

int Cframe::hex_dec(const QString& text){
    QByteArray arr = text.toUpper().toLatin1();
    const char* p = arr.constData();
    int len = arr.size();

    const char* end = p + len - 1;
    int base = 1;      // 16^0
    int dec_val = 0;

    for (const char* ptr = end; ptr >= p; --ptr) {
        if (*ptr >= '0' && *ptr <= '9') {
            dec_val += (*ptr - '0') * base;
        }
        else if (*ptr >= 'A' && *ptr <= 'F') {
            dec_val += (*ptr - 'A' + 10) * base;
        }
        else {
            throw std::invalid_argument(
                        std::string("Carácter hexadecimal no válido: ") + *ptr
                        );
        }
        base *= 16;
    }

    return dec_val;
}



void Cframe::on_Pb_calcular_clicked()
{
    if(ui->Rb_dec_a_hex->isChecked() || ui->Rb_hex_a_dec->isChecked()){
        QString texto = ui->TXT_ingresado->text();
        if(texto.isEmpty()){
            QMessageBox::warning(this, "Revisar", "Debe ingresar un dato a convertir.");
        }else{

            if(ui->Rb_dec_a_hex->isChecked()){

                bool esNumero;
                texto.toInt(&esNumero);
                if(!esNumero) {
                    QMessageBox::warning(this, "Error", "Debe ingresar un número decimal valido.");
                    return;
                }

                int* numeroPtr = new int(ui->TXT_ingresado->text().toInt());
                QString hex = Dec_Hex(numeroPtr);
                delete numeroPtr;
                ui->Le_obtenido->setText(hex);

            }else{

                try {
                    int* decimalPtr = new int(hex_dec(texto));
                    ui->Le_obtenido->setText(QString::number(*decimalPtr));
                    delete decimalPtr;

                } catch (const std::invalid_argument& e) {
                    QMessageBox::warning(this, "Error", "Entrada hexadecimal no valida.\n Solo use digitos del 0-9 y letras entre A-F");
                }
            }
        }

    }else{
        QMessageBox::warning(this, "Aviso", "Debe seleccionar el proceso que desea realizar.");
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
