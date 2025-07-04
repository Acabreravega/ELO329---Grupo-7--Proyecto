#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QCloseEvent>

#include "hotel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
/// @brief Carga habitaciones desde el csv
    void cargarHabitaciones();
     /// @brief Carga Reservas desde el csv seleccionado en la interfz
    void cargarReservas();
     /// @brief Actualiza la visualizacion de las habtiaciones
    void actualizarTablaHabitaciones();
    /// @brief Actualiza la visualizacion de las habtiaciones Filtradas con parametros elegidos en la interfaz
    void actualizarTablaHabitacionesFiltradas();
    /// @brief Muestra la disponibilidad de las fechas tras senalarlas en la interfaz grafica del calendario
    void verDisponibilidadCalendario();
    /// @brief Lanza la ventana emergente para obtener datos de la reserva
    void nuevaReservaForm();

    /// @brief Se lanza al cerrado de ventano
    /// @param event  Cerrado de la ventana
    void closeEvent(QCloseEvent *event) override;

    /// @brief Se elimina una reserva del vector
    void eliminarReserva();
    /// @brief Se guarda una reserva
    void guardarReserva();


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /// @brief Actualiza la visualizacion de la tabla en la pestana de reservas
    void actualizarTablaReservas();
    /// @brief Calcula el costo de la reserva en base a la fecha y las comodidades seleccionadas
    /// @param numeroHabitacion Numero habitacion
    /// @param inicio  Fecha de inicio
    /// @param fin  Fecha de fin
    /// @param desayuno Inclusion de desayuno
    /// @param lavanderia Inclusion de lavanderia
    /// @param extras Inclusion de extras
    /// @return Costo total reserva
    double calcularCostoReserva(int numeroHabitacion, const QDate &inicio, const QDate &fin,bool desayuno, bool lavanderia, bool extras);



private:
    Ui::MainWindow *ui;
    Hotel *hotel;
    QStandardItemModel *tablaHabitaciones;
    QStandardItemModel *tablaReservas;

};
#endif // MAINWINDOW_H
