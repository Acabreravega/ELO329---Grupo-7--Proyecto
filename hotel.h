#ifndef HOTEL_H
#define HOTEL_H

#include "habitacion.h"
#include "reserva.h"
#include <QObject>
#include <QList>
#include <QFile>

#include <fstream>
#include <iostream>

class Hotel : public QObject{
    Q_OBJECT

public:

    explicit Hotel(QObject *parent = nullptr);

    // Metodos de gestion de habitaciones

    /// @brief Agrega habitacion al vector de habitaciones
    /// @param habitacion  Habitacion
    /// @return Estado del agregado
    bool agregarHabitacion(const Habitacion& habitacion);

    /// @brief Busca habitacion en el vector de habitaciones
    /// @param numero numero de habitacion
    /// @return puntero a la habitacion encontrada
    Habitacion* buscarHabitacion(int numero);

    /// @brief Entrega todas las habitaciones
    /// @return Lista de habitaciones
    QList<Habitacion> getHabitaciones() const;

    /// @brief Entrega las habitaciones que no tienen una reserva asociada en un periodo de tiempo
    /// @param inicio Fecha de incio 
    /// @param fin Fecha de finalizacion
    /// @return  Lista de habitaciones disponibles
    QList<Habitacion> getHabitacionesDisponibles(const QDate& inicio, const QDate& fin) const;

    // Metodos de gestion de reservas

    /// @brief Agrega reserva al vector de reservas
    /// @param reserva reserva
    /// @return Estado del agregado
    bool agregarReserva(const Reserva& reserva);

    /// @brief Elimina Reserva del vector de reservas
    /// @param reserva reserva
    /// @return Estado de la eliminiacion
    bool eliminarReserva(Reserva& reserva);
    /// @brief Retorna lista de todas las reservas
    /// @return Lista de reservas
    QList<Reserva> getReservas() const;
    /// @brief  Retorna todas las reservas asociadas a una habitacion en especifico
    /// @param numero Numero de habitacion
    /// @return Lista de reservas asociadas a la habitacion
    QList<Reserva> getReservasPorHabitacion(int numero) const;

    // Metodos gestion de origen de datos
    /// @brief Carga la base de datos de habitaciones al sistema
    /// @param archivoHabitaciones Archivo csv de habitaciones
    /// @return Estado de la carga
    bool cargarHabitacionesCSV(const QString& archivoHabitaciones);
    /// @brief Carga la base de datos de reservas al sistema
    /// @param archivoReservas Archivo csv de reservas
    /// @return Estado de la carga
    bool cargarReservasCSV(const QString& archivoReservas);
    /// @brief Guarda las modificaciones realizadas durante el uso del sistema en la base de datos de habitaciones
    /// @param archivoHabitaciones Archivo de habitaciones
    /// @return Estado del guardado
    bool guardarHabitacionesCSV(const QString& archivoHabitaciones) const;
    /// @brief Guarda las modificaciones realizadas durante el uso del sistema en la base de datos de reserva
    /// @param archivoReservas Archivo de reservas
    /// @return Estado del guardado
    bool guardarReservasCSV(const QString& archivoReservas) const;

    // Metodo para limpiar

    /// @brief Libera datos de Habitacion
    void limpiarHabitaciones();
    /// @brief Libera datos de Reserva
    void limpiarReservas();

private:
    QList<Habitacion> habitaciones;
    QList<Reserva> reservas;
};

#endif // HOTEL_H
