#include "reserva.h"

Reserva::Reserva(
                const QString& nombreReservante,
                int numeroHabitacion,
                const QDate& inicio_Reserva,
                const QDate& fin_Reserva,
                bool incluye_Desayuno,
                bool incluye_Lavanderia,
                bool incluye_Extras,
                double costo_Reserva):
    nombreReservante(nombreReservante),
    numeroHabitacion(numeroHabitacion),
    inicio_Reserva(inicio_Reserva),
    fin_Reserva(fin_Reserva),
    incluye_Desayuno(incluye_Desayuno),
    incluye_Lavanderia(incluye_Lavanderia),
    incluye_Extras(incluye_Extras),
    costo_Reserva(costo_Reserva)
{
    if (inicio_Reserva > fin_Reserva) {
        this->fin_Reserva=inicio_Reserva;
    }
}

// Metodos getter
QString Reserva::getNombreReservante() const {return nombreReservante;}
int Reserva::getNumeroHabitacion() const {return numeroHabitacion;}
QDate Reserva::getInicio_Reserva() const {return inicio_Reserva;}
QDate Reserva::getFin_Reserva() const {return fin_Reserva;}
bool Reserva::getIncluye_Desayuno() const {return incluye_Desayuno;}
bool Reserva::getIncluye_Lavanderia() const {return incluye_Lavanderia;}
bool Reserva::getIncluye_Extras() const {return incluye_Extras;}
double Reserva::getCosto_Reserva() const {return costo_Reserva;}

// Metodos setter
void Reserva::setNombreReservante(QString nombreReservante){
    this->nombreReservante = nombreReservante;
}
void Reserva::setNumeroHabitacion(int numeroHabitacion){
    this->numeroHabitacion = numeroHabitacion;
}
void Reserva::setInicio_Reserva(QDate inicio_Reserva){
    this->inicio_Reserva = inicio_Reserva;
}
void Reserva::setFin_Reserva(QDate fin_Reserva){
    this->fin_Reserva = fin_Reserva;
}
void Reserva::setIncluye_Desayuno(bool incluye_Desayuno){
    this->incluye_Desayuno = incluye_Desayuno;
}
void Reserva::setIncluye_Lavanderia(bool incluye_Lavanderia){
    this->incluye_Lavanderia = incluye_Lavanderia;
}
void Reserva::setIncluye_Extras(bool incluye_Extras){
    this->incluye_Extras = incluye_Extras;
}
void Reserva::setCosto_Reserva(double costo_Reserva){
    this->costo_Reserva = costo_Reserva;
}

// Metodos
bool Reserva::fechaSuperpuesta(const QDate& inicio, const QDate& fin) const {
    return (inicio_Reserva <= fin) && (fin_Reserva >= inicio);
}

