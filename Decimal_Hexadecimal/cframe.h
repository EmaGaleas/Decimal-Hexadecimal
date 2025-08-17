#ifndef CFRAME_H
#define CFRAME_H

#include <QMainWindow>
#include <iostream>
#include <string>

using std::string;

QT_BEGIN_NAMESPACE
namespace Ui { class Cframe; }
QT_END_NAMESPACE

class Cframe : public QMainWindow
{
    Q_OBJECT

public:
    Cframe(QWidget *parent = nullptr);
    ~Cframe();
    //void Doc_Hex();
    void estiloInicial();
    void actualizarLabels(const QString& , const QString& );
    //int hex_dec(const QString& text);
    void Dec_Hex();
    void Hex_Dec();
    void Deci();
    bool esHexadecimalValido(const QString &texto);

    void Hex();

private slots:
    void on_Rb_dec_a_hex_clicked();
    void on_Rb_hex_a_dec_clicked();
    void on_Pb_calcular_clicked();

private:
    Ui::Cframe *ui;
    int *Dec,*Coc,*Res,*Pos, *Val;
    QString *Hexi;
    QChar *digito;
};
#endif // CFRAME_H
