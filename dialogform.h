#ifndef DIALOGFORM_H
#define DIALOGFORM_H
#include "hotel.h"
#include <QDialog>

namespace Ui {
class DialogForm;
}

class DialogForm : public QDialog
{
    Q_OBJECT

public:
    // Constructor para nueva reserva
    DialogForm(int habitacion, QDate inicio, QDate fin, QWidget *parent = nullptr, Hotel *hotel=nullptr);


    ~DialogForm();

    // Metodos para obtener datos
    /// @brief Obtiene el nombre del reservante a traves de la cajilla en la ventana emergente
    /// @return Nombre reservante
    QString nombre() const;
    /// @brief Retorna True o False dependiendo de si la cajilla correspondiente esta marcada en la ventana emergente
    /// @return Estado de Desayuno
    bool tieneDesayuno() const;
    /// @brief Retorna True o False dependiendo de si la cajilla correspondiente esta marcada en la ventana emergente
    /// @return Estado de Lavanderia
    bool tieneLavanderia() const;
    /// @brief Retorna True o False dependiendo de si la cajilla correspondiente esta marcada en la ventana emergente
    /// @return Estado de servicios extras
    bool tieneExtras() const;
    /// @brief Retorna la fecha de inicio senalada en la ventana
    /// @return Fecha de inicio reserva
    QDate fechaInicio() const;
    /// @brief Retorna la fecha de inicio senalada en la ventana
    /// @return Fecha de fin reserva
    QDate fechaFin() const;
private slots:
    //Actualizar datos
    /// @brief Calcula el costo de la reserva en base a la fecha y las comodidades seleccionadas y lo actualiza en vivo en el formulario
    /// @param precio_base Precio por dia de la habitacion
    /// @param desayuno Precio Desayuno
    /// @param lavanderia Precio Lavanderia
    /// @param extras Precio Extras
    void updatecosts(double desayuno,double lavanderia,double extras,double precio_base);
private:
    Ui::DialogForm *ui;
};

#endif // DIALOGFORM_H
