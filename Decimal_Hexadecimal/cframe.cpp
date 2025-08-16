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
    Res= new int();
    Coc= new int();
    Dec= new int();
    Hexi = new QString();
    Pos = new int();
    Val = new int();
    digito = new QChar();
}

Cframe::~Cframe()
{
    Coc=NULL;
    delete Coc;
    Res=NULL;
    delete Res;
    Dec=NULL;
    delete Dec;
    Hexi=NULL;
    delete Hexi;
    delete ui;
    Pos=NULL;
    delete Pos;
    Val = NULL;
    delete Val;
    digito = NULL;
    delete digito;

}
//Area de codigo funcional

void Cframe::Dec_Hex()
{
    Dec=Coc;
    for (;*Dec>=16 ; ) {
        *Res=*Dec%16;
        *Coc=*Dec/16;
      //  *Dec=*Dec/16;
        Hex();
    }
    *Res=*Dec;
    Hex();
}

void Cframe::Hex_Dec()
{
    *Dec = 0;
    *Pos = Hexi->length() - 1;

    for (;*Pos >= 0;) {
        *digito = Hexi->at(*Pos);
        Deci();
        *Dec += *Val * pow(16, (Hexi->length() - 1 - *Pos));
        (*Pos)--;
    }
}

void Cframe::Deci()
{
    (*digito=='F')? *Val = 15 : (*digito=='E')? *Val =14 : (*digito=='D')? *Val =13 : (*digito=='C')? *Val =12 : (*digito=='B')? *Val =11: (*digito=='A')? *Val = 10: *Val = digito->digitValue();

}
void Cframe::Hex()
{
    switch(*Res){
    case 15:
        *Hexi= *Hexi + "F";
        break;
    case 14:
        *Hexi= *Hexi + "E";
        break;
    case 13:
        *Hexi= *Hexi + "D";
        break;
    case 12:
        *Hexi= *Hexi + "C";
        break;
    case 11:
        *Hexi= *Hexi + "B";
        break;
    case 10:
        *Hexi= *Hexi + "A";
        break;
    default:
        *Hexi= *Hexi + QString::number(*Res);

    }

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
                Hexi= new QString("");
                bool esNumero;
                int numero = texto.toInt(&esNumero);
                if(!esNumero) {
                    QMessageBox::warning(this, "Error", "Debe ingresar un número decimal valido.");
                    return;
                }
                *Dec=numero;
                *Coc=numero;
                Dec_Hex();
                ui->Le_obtenido->setText(*Hexi);

            }else{

                try {
                    if (!esHexadecimalValido(texto)) {
                        QMessageBox::warning(this, "Error", "Entrada hexadecimal no válida.\nSolo use dígitos (0-9) o letras (A-F).");
                        return;
                    }
                    Hexi = new QString(texto.toUpper());
                    Hex_Dec();
                    ui->Le_obtenido->setText(QString::number(*Dec));
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

bool Cframe::esHexadecimalValido(const QString &texto) {
    for (int i = 0; i < texto.length(); ++i) {
        QChar c = texto.at(i).toUpper(); // Convertir a mayúscula para simplificar
        bool esDigito = (c >= '0' && c <= '9');
        bool esLetraValida = (c >= 'A' && c <= 'F');

        if (!esDigito && !esLetraValida) {
            return false; // Carácter no válido
        }
    }
    return true; // Todos los caracteres son válidos
}

void Cframe::on_Rb_dec_a_hex_clicked() {
    actualizarLabels("Ingrese dato en Decimal: ", "Valor obtenido en Hexadecimal: ");
}

void Cframe::on_Rb_hex_a_dec_clicked() {
    actualizarLabels("Ingrese dato en Hexadecimal: ", "Valor obtenido en Decimal: ");
}
