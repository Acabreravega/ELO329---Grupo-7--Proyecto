#ifndef RESERVA_H
#define RESERVA_H

#include <QString>
#include <QDate>

class Reserva{
public:
    // Constructor
    Reserva(const QString& nombreReservante,
            int numeroHabitacion,
            const QDate& inicio_Reserva,
            const QDate& fin_Reserva,
            bool incluye_Desayuno,
            bool incluye_Lavanderia,
            bool incluye_Extras,
            double costo_Reserva);

    // Metodos getter
    /// @brief Obtiene el nombre del reservante
    /// @return Retorna nombre reservante
    QString getNombreReservante() const;
    /// @brief Obtiene el numero de habitacion
    /// @return Numero de habitacion
    int getNumeroHabitacion() const;
    /// @brief Obtiene Inicio de reserva
    /// @return Inicio de reserva
    QDate getInicio_Reserva() const;
    /// @brief Obtiene Fin de reserva
    /// @return  Fin de reserva
    QDate getFin_Reserva() const;
    /// @brief  Retorna True o False dependiendo si el usuario incluye desayuno
    /// @return Estado de desayuno
    bool getIncluye_Desayuno() const;
    /// @brief Retorna True o False dependiendo si el usuario incluye servicio de  Lavanderia
    /// @return Estado de lavanderi
    bool getIncluye_Lavanderia() const;
    /// @brief Retorna True o False dependiendo si el usuario incluye Extras
    /// @return  estado de Extras
    bool getIncluye_Extras() const;
    /// @brief Calcula el costo final de la reserva dependiendo de las comodidades, el periodo y el tipo de habitacion
    /// @return costo reserva
    double getCosto_Reserva() const;

    // Metodos setter
    /// @brief  Fija el nombre del reservante
    /// @param nombreReservante Nombre reservante
    void setNombreReservante(QString nombreReservante);
    /// @brief Fija el numero de habitacion
    /// @param numeroHabitacion numero de habitacion
    void setNumeroHabitacion(int numeroHabitacion);
    /// @brief Fija la fecha de inicio de reserva
    /// @param inicio_Reserva Fecha de inicio de reserva
    void setInicio_Reserva(QDate inicio_Reserva);
    /// @brief Fija la fecha final de reserva
    /// @param fin_Reserva  Fecha final de reserva
    void setFin_Reserva(QDate fin_Reserva);
    /// @brief Fija si el usuario incluye servicio desayuno
    /// @param incluye_Desayuno Estado de inclusion desayuno
    void setIncluye_Desayuno(bool incluye_Desayuno);
    /// @brief Fija si el usuario incluye servicio de lavanderia
    /// @param incluye_Lavanderia  Estado de la inclusion del servicio de lavanderia
    void setIncluye_Lavanderia(bool incluye_Lavanderia);
    /// @brief  Fija si el usuario decide agregar extras
    /// @param incluye_Extras Estado de la inclusion de Extras
    void setIncluye_Extras(bool incluye_Extras);
    /// @brief Fija costo de la reserva
    /// @param costo_reserva Costo de la reserva
    void setCosto_Reserva(double costo_reserva);

    // Metodos
    /// @brief Verifica si la fecha estan super puestas
    /// @param inicio Fecha de inicio
    /// @param fin  Fecha final
    /// @return  Estado de la superposicion de las fechas
    bool fechaSuperpuesta(const QDate& inicio, const QDate& fin) const;

private:
    QString nombreReservante;
    int numeroHabitacion;
    QDate inicio_Reserva;
    QDate fin_Reserva;
    bool incluye_Desayuno;
    bool incluye_Lavanderia;
    bool incluye_Extras;
    double costo_Reserva;
};

#endif // RESERVA_H
