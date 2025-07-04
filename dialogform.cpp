#include "dialogform.h"
#include "habitacion.h"
#include "qaction.h"
#include "ui_dialogform.h"
#include <iostream>

DialogForm::DialogForm(int habitacion, QDate inicio, QDate fin, QWidget *parent, Hotel *hotel) :
    QDialog(parent),
    ui(new Ui::DialogForm)
{
    ui->setupUi(this);
    Habitacion h = *hotel->buscarHabitacion(habitacion);
    float desayuno=h.getPrecioDesayuno();
    float lavanderia = h.getPrecioLavanderia();
    float extras = h.getPrecioExtras();
    double precio_base = h.getPrecioHabitacion();
    int dias = inicio.daysTo(fin);
    ui->lblPrecioTotalValor->setText(QString::number(precio_base*dias, 'f', 2));
    ui->lblPrecioBaseValor->setText(QString::number(precio_base, 'f', 2));
    // datos fijos obtenidos desde ventana anterior
    ui->txtHabitacion->setText(QString::number(habitacion));
    ui->dateInicio->setDate(inicio);
    ui->dateFin->setDate(fin);


    connect(ui->checkDesayuno, &QCheckBox::stateChanged, this, [this, desayuno,lavanderia,extras,precio_base]() { updatecosts(desayuno,lavanderia,extras,precio_base); });
    connect(ui->checkLavanderia, &QCheckBox::stateChanged, this, [this, desayuno,lavanderia,extras,precio_base]() { updatecosts(desayuno,lavanderia,extras,precio_base); });
    connect(ui->checkParking, &QCheckBox::stateChanged, this, [this, desayuno,lavanderia,extras,precio_base]() { updatecosts(desayuno,lavanderia,extras,precio_base); });
    connect(ui->dateInicio, &QDateEdit::dateChanged,this, [this, desayuno,lavanderia,extras,precio_base]() { updatecosts(desayuno,lavanderia,extras,precio_base); });
    connect(ui->dateFin, &QDateEdit::dateChanged,this, [this, desayuno,lavanderia,extras,precio_base]() { updatecosts(desayuno,lavanderia,extras,precio_base); });



    // Deshabilitar edición de campos fijos
    ui->txtHabitacion->setEnabled(false);
    ui->dateInicio->setEnabled(false);
    ui->dateFin->setEnabled(false);
    updatecosts(desayuno,lavanderia,extras,precio_base);
}


DialogForm::~DialogForm()
{
    delete ui;
}

QString DialogForm::nombre() const {
    return ui->txtNombre->text();
}

bool DialogForm::tieneDesayuno() const {
    return ui->checkDesayuno->isChecked();
}

bool DialogForm::tieneLavanderia() const {
    return ui->checkLavanderia->isChecked();
}

bool DialogForm::tieneExtras() const {
    return ui->checkParking->isChecked();
}

QDate DialogForm::fechaInicio() const {
    return ui->dateInicio->date();
}

QDate DialogForm::fechaFin() const {
    return ui->dateFin->date();
}

void DialogForm::updatecosts(double desayuno,double lavanderia,double extras,double precio_base){
    QDate inicio = ui->dateInicio->date();
    QDate fin = ui->dateFin->date();
    int dias = inicio.daysTo(fin);
    if (dias < 1) dias = 1; // Ensure at least 1 day

    std::cout << "Días calculados: " << dias << std::endl;

    // Base cost (always applied)
    double costoDias = precio_base * dias;
    double costoServicios = 0.0;

    // Apply breakfast cost only if checked (per day)
    if (ui->checkDesayuno->isChecked()) {
        costoServicios += desayuno * dias;
    }

    // Apply laundry cost only if checked (assuming one-time fee)
    if (ui->checkLavanderia->isChecked()) {
        costoServicios += lavanderia; // Not multiplied by days
    }

    // Apply extras cost only if checked (per day or one-time? Adjust as needed)
    if (ui->checkParking->isChecked()) {
        costoServicios += extras * dias; // Assuming per-day
    }

    // Total cost = base + services
    double costoTotal = costoDias + costoServicios;

    // Update UI
    ui->lblPrecioDiasValor->setText(QString::number(costoDias, 'f', 2));
    ui->lblPrecioTotalValor->setText(QString::number(costoTotal, 'f', 2));
    ui->lblPrecioServiciosValor->setText(QString::number(costoServicios, 'f', 2));
    ui->lblPrecioBaseValor->setText(QString::number(precio_base, 'f', 2));
}
