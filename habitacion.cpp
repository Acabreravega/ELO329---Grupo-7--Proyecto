#include "habitacion.h"

Habitacion::Habitacion(
                    int numero,
                    const QString& tipoHabitacion,
                    double precioHabitacion,
                    double precioDesayuno,
                    double precioLavanderia,
                    double precioExtras):
    numero(numero),
    tipoHabitacion(tipoHabitacion),
    precioHabitacion(precioHabitacion),
    precioLavanderia(precioLavanderia),
    precioDesayuno(precioDesayuno),
    precioExtras(precioExtras){
}


int Habitacion::getNumero() const {return numero;}

int Habitacion::getPiso() const {return numero/100;}

QString Habitacion::getTipoHabitacion() const {return tipoHabitacion;}

double Habitacion::getPrecioHabitacion() const {return precioHabitacion;}

double Habitacion::getPrecioDesayuno() const {return precioDesayuno;}

double Habitacion::getPrecioLavanderia() const {return precioLavanderia;}

double Habitacion::getPrecioExtras() const {return precioExtras;}
