#include "mainwindow.h"
#include "dialogform.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);

    // Iniciar con fecha actual para busqueda de disponibilidad
    ui->dateInicioBusqueda->setDate(QDate::currentDate());
    ui->dateFinBusqueda->setDate(QDate::currentDate());

    // Instancia de hotel
    hotel = new Hotel(this);

    // Inicializacion de tablas
    tablaHabitaciones = new QStandardItemModel(this);
    if (ui->tblHabitaciones) {
        ui->tblHabitaciones->setModel(tablaHabitaciones);
    }
    tablaReservas = new QStandardItemModel(this);
    if (ui->tblReservaciones) {
        ui->tblReservaciones->setModel(tablaReservas);
    }

    // Connects
    connect(ui->actionCargar_Habitaciones, &QAction::triggered, this, &MainWindow::cargarHabitaciones);
    connect(ui->actionCargar_Reservas, &QAction::triggered, this, &MainWindow::cargarReservas);
    connect(ui->btnMostrarTodas, &QPushButton::clicked, this, &MainWindow::actualizarTablaHabitaciones);
    connect(ui->btnBuscarDisponibilidad, &QPushButton::clicked, this, &MainWindow::actualizarTablaHabitacionesFiltradas);
    connect(ui->btnVerDisponibilidad, &QPushButton::clicked, this, &MainWindow::verDisponibilidadCalendario);
    connect(ui->btnReservarHabitacion, &QPushButton::clicked, this, &MainWindow::nuevaReservaForm);
    connect(ui->btnEliminarReserva, &QPushButton::clicked, this, &MainWindow::eliminarReserva);
    connect(ui->actionGuardad_Reservas, &QAction::triggered, this, &MainWindow::guardarReserva);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete hotel;
}

// Carga habitaciones desde CSV
void MainWindow::cargarHabitaciones() {
    hotel->limpiarHabitaciones();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Cargar Habitaciones"), "", tr("Todos los Archivos ()"));
    if (!fileName.isEmpty()) {
        try {
            bool success = hotel->cargarHabitacionesCSV(fileName);
            if (success) {
                actualizarTablaHabitaciones();
            } else {
                QMessageBox::warning(
                    this,
                    tr("Error"),
                    tr("No se pudieron cargar las habitaciones del archivo.")
                    );
            }
        } catch (const std::exception& e) {
            QMessageBox::critical(
                this,
                tr("Error"),
                tr("Ocurrió un error al cargar el archivo de habitaciones ")
                );
        }
    }
}

// Carga reservas desde CSV
void MainWindow::cargarReservas() {
    //hotel->limpiarReservas();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Cargar Reservas"), "", tr("Todos los Archivos ()"));
    if (!fileName.isEmpty()) {
        try {
            bool success = hotel->cargarReservasCSV(fileName);
            if (success) {
                actualizarTablaReservas();
            } else {
                QMessageBox::warning(
                    this,
                    tr("Error"),
                    tr("No se pudieron cargar las reservas del archivo.")
                    );
            }
        } catch (const std::exception& e) {
            QMessageBox::critical(
                this,
                tr("Error"),
                tr("Ocurrió un error al cargar el archivo de reservas ")
                );}
    }
}
void MainWindow::guardarReserva()  {
    QString reservasFile = QFileDialog::getSaveFileName(this,
                                                        "Guardar reservas",
                                                        "",
                                                        "Archivos CSV (*.csv)");
    if (!reservasFile.isEmpty()) {
        if (hotel->guardarReservasCSV(reservasFile)) {
            QMessageBox::information(this, "Éxito", "Reservas guardadas correctamente");
        } else {
            QMessageBox::warning(this, "Error", "No se pudieron guardar las reservas");
        }
    }
}



    void MainWindow::eliminarReserva(){
    auto selected = ui->tblReservaciones->selectionModel()->selectedRows();
    if(selected.isEmpty()) {
        QMessageBox::warning(this, "Error", "Seleccione una reserva");
        return;
    }

    if(QMessageBox::question(this, "Confirmar", "¿Eliminar esta reserva?") == QMessageBox::Yes) {
        int index = selected.first().row();
        Reserva resActual = hotel->getReservas()[index];
        hotel->eliminarReserva(resActual);
        actualizarTablaReservas();
    }
}


    // Actualiza la tabla de habitaciones, mostrando todas las habitaciones y el estado de cada una
void MainWindow::actualizarTablaHabitaciones(){
    tablaHabitaciones->clear();
    tablaHabitaciones->setHorizontalHeaderLabels({ "Numero", "Tipo", "Piso", "Estado"});

    QDate inicioBusqueda = ui->dateInicioBusqueda->date();
    QDate finBusqueda = ui->dateFinBusqueda->date();

    if (finBusqueda < inicioBusqueda){
        QMessageBox::warning(this, "Error", "Rango de fecha incorrecto.");
        return;
    }
    // Lista de habitaciones completa
    QList<Habitacion> listaHabitaciones = hotel->getHabitaciones();
    // Lista de habitaciones disponibles en la fecha indicada
    QList<Habitacion> listaHabitacionesDispo = hotel->getHabitacionesDisponibles(inicioBusqueda,finBusqueda );

    QString dispo = "Disponible";
    QString ocupado = "Ocupada";

    // Recorrer todas las habitaciones y mostrar sus parametros en la tabla
    for (const Habitacion& h : listaHabitaciones) {
        QList<QStandardItem*> filas;
        filas.append(new QStandardItem(QString::number(h.getNumero())));
        filas.append(new QStandardItem(h.getTipoHabitacion()));
        filas.append(new QStandardItem(QString::number(h.getPiso())));

        // Verificar si la habitacion esta disponible para actualizar estado a Disponible
        bool encontrada = false;
        for( const Habitacion& d : listaHabitacionesDispo){
            if (h.getNumero() == d.getNumero()){
                filas.append(new QStandardItem(dispo));
                filas.last()->setForeground(Qt::darkGreen);
                encontrada = true;
                break;
            }
        }
        // Si no esta disponible muestra estado Ocupada
        if (!encontrada) {
            filas.append(new QStandardItem(ocupado));
            filas.last()->setForeground(Qt::red);
        }
        tablaHabitaciones->appendRow(filas);
    }
    if (ui->tblHabitaciones) {
        ui->tblHabitaciones->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
}

// Actualiza la tabla de reservas, mostrando las caracteristicas de cada reserva
void MainWindow::actualizarTablaReservas(){
    tablaReservas->clear();
    tablaReservas->setHorizontalHeaderLabels({ "Reservante", "Habitación", "Inicio", "Fin", "Desayuno", "Lavandería", "Extras", "Costo"});

    QList<Reserva> listaReservas = hotel->getReservas();

    // Recorre lista de reservas e incluye cada parametro en la tabla
    for (const Reserva& r : listaReservas) {
        QList<QStandardItem*> filas;
        filas.append(new QStandardItem(r.getNombreReservante()));
        filas.append(new QStandardItem(QString::number(r.getNumeroHabitacion())));
        filas.append(new QStandardItem(r.getInicio_Reserva().toString("dd/MM/yyyy")));
        filas.append(new QStandardItem(r.getFin_Reserva().toString("dd/MM/yyyy")));
        filas.append(new QStandardItem(r.getIncluye_Desayuno() ? "Si" : "No"));
        filas.append(new QStandardItem(r.getIncluye_Lavanderia() ? "Si" : "No"));
        filas.append(new QStandardItem(r.getIncluye_Extras() ? "Si" : "No"));

        filas.append(new QStandardItem(QString::number(r.getCosto_Reserva(), 'f', 2)));
        tablaReservas->appendRow(filas);
    }

    if (ui->tblReservaciones) {
        ui->tblReservaciones->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
    actualizarTablaHabitaciones();
}

// Actualiza la tabla filtrada para mostrar solo habitaciones disponibles
void MainWindow::actualizarTablaHabitacionesFiltradas(){

    QDate inicioBusqueda = ui->dateInicioBusqueda->date();
    QDate finBusqueda = ui->dateFinBusqueda->date();

    if (finBusqueda < inicioBusqueda){
        QMessageBox::warning(this, "Error", "Rango de fecha incorrecto.");
        return;
    }

    QList<Habitacion> habitacionesDisponibles = hotel->getHabitacionesDisponibles(inicioBusqueda, finBusqueda);
    tablaHabitaciones->clear();
    tablaHabitaciones->setHorizontalHeaderLabels({ "Numero", "Tipo", "Piso", "Estado"});

    for (const Habitacion& h : habitacionesDisponibles) {
        QList<QStandardItem*> filas;
        filas.append(new QStandardItem(QString::number(h.getNumero())));
        filas.append(new QStandardItem(h.getTipoHabitacion()));
        filas.append(new QStandardItem(QString::number(h.getPiso())));
        filas.append(new QStandardItem("Disponible"));
        filas.last()->setForeground(Qt::darkGreen);
        tablaHabitaciones->appendRow(filas);
    }

    if (ui->tblHabitaciones) {
        ui->tblHabitaciones->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
}


void MainWindow::verDisponibilidadCalendario()
{
    QDate inicio = ui->calendarInicio->selectedDate();
    QDate fin = ui->calendarFin->selectedDate();

    if (fin<inicio){
        QMessageBox::warning(this, "Error", "Rango de fecha incorrecto.");
        return;
    }

    // Actualizar fechas en la pestaña de búsqueda
    ui->dateInicioBusqueda->setDate(inicio);
    ui->dateFinBusqueda->setDate(fin);

    // Cambiar a pestaña de habitaciones
    ui->tabWidget->setCurrentIndex(0);

    // Ejecutar búsqueda automaticamente
    actualizarTablaHabitacionesFiltradas(); // Llamar a la funcion que actualiza la tabla de habitaciones
}


void MainWindow::nuevaReservaForm(){
    QModelIndexList selected = ui->tblHabitaciones->selectionModel()->selectedRows();


    // Verificar que hay una fila seleccionada y no esta ocupada la habitacion
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Error",
                             "No se ha selecciona una habitación.");
        return;
    }

    // Obtener datos de la fila seleccionada
    int row = selected.first().row();
    int numeroHabitacion = tablaHabitaciones->item(row, 0)->text().toInt();
    std::string estado = tablaHabitaciones->item(row, 3)->text().toStdString();

    // Verificar que hay una fila seleccionada y no esta ocupada la habitacion
    if (estado == "Ocupada") {
        QMessageBox::warning(this, "Error",
                             "Habitación ocupada.");
        return;
    }

    // Obtencion de fechas
    QDate inicio = ui->dateInicioBusqueda->date();
    QDate fin = ui->dateFinBusqueda->date();

    // Crear ventana nueva
    DialogForm dialog(numeroHabitacion, inicio, fin, this, hotel);
    if (dialog.exec() == QDialog::Accepted){

        // datos del formulario
        QString nombre = dialog.nombre();
        bool desayuno = dialog.tieneDesayuno();
        bool lavanderia = dialog.tieneLavanderia();
        bool extras = dialog.tieneExtras();

        double costo = calcularCostoReserva(numeroHabitacion,inicio, fin, desayuno, lavanderia, extras);
        Reserva nuevaReserva(nombre, numeroHabitacion, inicio, fin, desayuno, lavanderia, extras, costo);
        if (hotel->agregarReserva(nuevaReserva)){
            actualizarTablaReservas();
            actualizarTablaHabitaciones();
        } else{
            QMessageBox::warning(this, "Error", "Error, no se ha creado la reserva.");
        }

    }
}

double MainWindow::calcularCostoReserva(int numeroHabitacion, const QDate &inicio, const QDate &fin,bool desayuno,bool lavanderia, bool extras){
    int dias = inicio.daysTo(fin);
    if (dias <= 0) dias = 1;

    Habitacion h = *hotel->buscarHabitacion(numeroHabitacion);
    double precio_base = h.getPrecioHabitacion();
    double costoTotal = precio_base * dias;

    // Agregar servicios adicionales
    if (desayuno) {
        costoTotal += h.getPrecioDesayuno() * dias;
    }
    if (lavanderia) {
        costoTotal += h.getPrecioLavanderia();
    }
    if (extras) {
        costoTotal += h.getPrecioExtras() * dias;
    }

    return costoTotal;
}

// Cierre de programa exige guardado de archivos de reservas
void MainWindow::closeEvent(QCloseEvent *event){
    // Preguntar al usuario si desea guardar los datos
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Guardar datos",
                                  "¿Desea guardar los datos antes de salir?",
                                  QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

    if (reply == QMessageBox::Yes) {
        // Guardar reservas
        QString reservasFile = QFileDialog::getSaveFileName(this,
                                                            "Guardar reservas",
                                                            "",
                                                            "Archivos CSV (*.csv)");

        if ( !reservasFile.isEmpty()) {
            bool reservasOk = hotel->guardarReservasCSV(reservasFile);

            if (!reservasOk) {
                QMessageBox::warning(this, "Error",
                                     "Ocurrio un error al guardar algunos archivos.");
            }
        }
        event->accept();
    }
    else if (reply == QMessageBox::No) {
        event->accept();
    } else if (reply == QMessageBox::Cancel){
        event->ignore();
    }
}
