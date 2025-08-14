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

int Cframe::hex_dec(const QString& text){
    int potenciaActual=1;
    int decimal = 0;

    QString hexadecimal = text.toUpper();

    for(int i = hexadecimal.length() - 1; i >= 0; i--){
        QChar c = hexadecimal.at(i);
        int digito;

        switch (c.toLatin1()) {
        case '0':  digito = 0; break;
        case '1':  digito = 1; break;
        case '2':  digito = 2; break;
        case '3':  digito = 3; break;
        case '4':  digito = 4; break;
        case '5':  digito = 5; break;
        case '6':  digito = 6; break;
        case '7':  digito = 7; break;
        case '8':  digito = 8; break;
        case '9':  digito = 9; break;
        case 'A':  digito = 10; break;
        case 'B':  digito = 11; break;
        case 'C':  digito = 12; break;
        case 'D':  digito = 13; break;
        case 'E':  digito = 14; break;
        case 'F':  digito  = 15; break;
        default:
        throw std::invalid_argument("Carácter hexadecimal no válido: " + QString(c).toStdString());
        }

    decimal += digito * potenciaActual;
    potenciaActual = potenciaActual*16;

    }
    return decimal;
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
                    QMessageBox::warning(this, "Error", "Debe ingresar un número decimal válido.");
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
