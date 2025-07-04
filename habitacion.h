#ifndef HABITACION_H
#define HABITACION_H


#include <QString>

class Habitacion{
public:

    // Constructos
    Habitacion(int numero,
               const QString& tipo,
               double precioBase,
               double precioDesayuno,
               double precioLavanderia,
               double precioExtras);

    // Metodos getter
     /// @brief Retorna numero de habitacion
    /// @return Numero de habitacion
    int getNumero() const;
    /// @brief Retorna piso de la habitacion
    /// @return Numero de piso
    int getPiso() const;
    /// @brief Retorna precio de la habitacion por dia
    /// @return precio base de la habitacion por dia
    double getPrecioHabitacion() const;
     /// @brief Retorna precio del servicio de lavanderia de la habitacion por dia
    /// @return precio del servicio de lavanderia habitacion por dia
    double getPrecioLavanderia() const;
    /// @brief Retorna precio del servicio de lavanderia de la habitacion por dia
    /// @return precio del servicio de lavanderia habitacion por dia
    double getPrecioDesayuno() const;
    /// @brief Retorna precio del servicios extras de la habitacion por dia
    /// @return precio del servicio extras habitacion por dia
    double getPrecioExtras() const;
    /// @brief Retorna categoria de habitacion senalada en el csv
    /// @return Retorna tipo de habitacion
    QString getTipoHabitacion() const;

private:
    int numero;
    QString tipoHabitacion;
    double precioHabitacion;
    double precioLavanderia;
    double precioDesayuno;
    double precioExtras;
};

#endif // HABITACION_H
