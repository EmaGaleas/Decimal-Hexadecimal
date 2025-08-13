#ifndef CFRAME_H
#define CFRAME_H

#include <QMainWindow>
#include <iostream>

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

    QString Dec_Hex(int* );

private slots:
    void on_Rb_dec_a_hex_clicked();
    void on_Rb_hex_a_dec_clicked();
    void on_Pb_calcular_clicked();

private:
    Ui::Cframe *ui;
};
#endif // CFRAME_H
