#include "hotel.h"

Hotel::Hotel(QObject *parent) : QObject(parent) {}

// Metodos de gestion de habitaciones

// Agregar habitaciones a la lista omitiendo repetidos
bool Hotel::agregarHabitacion(const Habitacion& habitacion){

    // Verificar existencia previa de esa habitacion
    for (auto& h : habitaciones){
        if(h.getNumero() == habitacion.getNumero()){
            return false;
        }
    }
    // Agregar habitacion
    habitaciones.append(habitacion);
    return true;
}

Habitacion* Hotel::buscarHabitacion(int numero){
    for (auto& h : habitaciones){
        if (h.getNumero() == numero){
            return &h;
        }
    }
    return nullptr;
}

QList<Habitacion> Hotel::getHabitaciones() const{
    return habitaciones;
}

QList<Habitacion> Hotel::getHabitacionesDisponibles(const QDate& inicio, const QDate& fin) const{
    QList<Habitacion> disponibles;
    for(auto& h : habitaciones){

        bool disponible = true;
        for(auto& r : reservas)         // Revisa si la habitacion esta reservada en las fechas
            if ( r.getNumeroHabitacion() == h.getNumero() && r.fechaSuperpuesta(inicio, fin)){
                disponible = false;     // Habitacion no disponible en esas fechas
                break;
            }
        if (disponible){
            disponibles.append(h);      // Agrega habitacion como disponible
        }
    }
    return disponibles;                 // Lista de habitaciones disponibles
}


// Metodos gestion de reservas

// Agregar una reserva
bool Hotel::agregarReserva(const Reserva& reserva){

    // Verificar que no exista reserva en esas fechas
    for (auto& r : reservas){
        if( r.getNumeroHabitacion() == reserva.getNumeroHabitacion() &&
            r.fechaSuperpuesta( reserva.getInicio_Reserva(), reserva.getFin_Reserva() )){
            return false;       // No se efectua la reserva
        }
    }
    // Se efectua la reserva
    reservas.append(reserva);
    return true;
}

// Eliminar reserva especifica
bool Hotel::eliminarReserva(Reserva& reserva){
    for (int i = 0 ; i<reservas.size(); i++){

        // Encontrar reserva a eliminar
        if (reservas[i].getNumeroHabitacion() == reserva.getNumeroHabitacion() &&
            reservas[i].getInicio_Reserva() == reserva.getInicio_Reserva() &&
            reservas[i].getFin_Reserva() == reserva.getFin_Reserva())
        {
            reservas.removeAt(i);       // Eliminar reserva
            return true;
        }
    }
    return false;                       // Reserva no encontrada
}

// getter de lista de reservas
QList<Reserva> Hotel::getReservas() const{
    return reservas;
}

// getter de lista de reservas de una habitacion especifica
QList<Reserva> Hotel::getReservasPorHabitacion(int numero) const{
    QList<Reserva> reservas_habitacion;
    for(auto & r : reservas){
        if(r.getNumeroHabitacion() == numero){
            reservas_habitacion.append((r));
        }
    }
    return reservas_habitacion;
}


// Metodos de gestion de origen de datos

// Guardar en lista de habitaciones los datos desde archivo csv
bool Hotel::cargarHabitacionesCSV(const QString& archivoHabitaciones){
    habitaciones.clear();

    // Archivo de habitaciones
    std::ifstream archivo_hab(archivoHabitaciones.toStdString());
    if(!archivo_hab.is_open()){
        std::cerr<< " Error al abrir el archivo de habitaciones"<< archivoHabitaciones.toStdString() << std::endl;
        return false;
    }

    std::string linea;
    char delimitador = ';';
    int exito = 0;
    std::getline(archivo_hab,linea);

    // Extraer cada linea del CSV
    while (std::getline(archivo_hab,linea)){

        // Extraer de la linea los datos separados por ';'
        std::stringstream stream(linea);
        std::string num, tipo, precioH, precioL, precioD, precioE;
        getline(stream, num, delimitador);
        getline(stream, tipo, delimitador);
        getline(stream, precioH, delimitador);
        getline(stream, precioL, delimitador);
        getline(stream, precioD, delimitador);
        getline(stream, precioE, delimitador);

        // Agregar habitacion de la linea extraida
        Habitacion nueva(std::stoi(num),
                        QString::fromStdString(tipo),
                        std::stod(precioH),
                        std::stod(precioL),
                        std::stod(precioD),
                        std::stod(precioE));
        if (agregarHabitacion(nueva)){
            exito ++;
        }
    }
    archivo_hab.close();
    return exito > 0;
}

// Guardar en lista de reservas los datos desde archivo csv
bool Hotel::cargarReservasCSV(const QString& archivoReservas){
    reservas.clear();

    // Archivo de reservas
    std::ifstream archivo_res(archivoReservas.toStdString());
    if(!archivo_res.is_open()){
        std::cerr<< " Error al abrir el archivo de reservas"<< archivoReservas.toStdString() << std::endl;
        return false;
    }

    std::string linea;
    char delimitador = ';';
    std::getline(archivo_res,linea);

    // Extraer cada linea del CSV
    while (std::getline(archivo_res,linea)){

        // Extraer de la linea los datos separados por ';'
        std::stringstream stream(linea);
        std::string name, num, f_in, f_fin, des, lav, extr, cost;
        getline(stream, name, delimitador);
        getline(stream, num, delimitador);
        getline(stream, f_in, delimitador);
        getline(stream, f_fin, delimitador);
        getline(stream, des, delimitador);
        getline(stream, lav, delimitador);
        getline(stream, extr, delimitador);
        getline(stream, cost, delimitador);

        // Agregar reserva de la linea extraida
        reservas.append( Reserva(QString::fromStdString(name),
                                std::stoi(num),
                                QDate::fromString(QString::fromStdString(f_in), "dd/MM/yyyy"),
                                QDate::fromString(QString::fromStdString(f_fin), "dd/MM/yyyy"),
                                des == "si",
                                lav == "si",
                                extr == "si",
                                std::stod(cost)));
    }
    archivo_res.close();
    return true;
}



bool Hotel::guardarHabitacionesCSV(const QString& archivoHabitaciones) const{
    std::ofstream archivo(archivoHabitaciones.toStdString());
    if(!archivo.is_open()){
        std::cerr << "Error al abrir el archivo para guardar habitaciones: "<< archivoHabitaciones.toStdString() << std::endl;
        return false;
    }
    for (auto& h : habitaciones){
        archivo << h.getNumero()<<";"
                << h.getTipoHabitacion().toStdString()<<";"
                << h.getPrecioHabitacion() << ";"
                << h.getPrecioLavanderia() << ";"
                << h.getPrecioDesayuno() << ";"
                << h.getPrecioExtras() << "\n";
    }
    archivo.close();
    return true;
}

bool Hotel::guardarReservasCSV(const QString& archivoReservas) const{
    std::ofstream archivo(archivoReservas.toStdString());

    if(!archivo.is_open()){
        std::cerr << "Error al abrir el archivo para guardar reservas: "<< archivoReservas.toStdString() << std::endl;
        return false;
    }
    archivo << "Nombre_Reservante;Numero_Habitacion;Inicio_Reserva;Fin_Reserva;Desayunos;Lavanderia;Extras;Costo_Total\n";
    for (auto& r : reservas){
        archivo << r.getNombreReservante().toStdString()<<";"
                << r.getNumeroHabitacion()<<";"
                << r.getInicio_Reserva().toString("dd/MM/yyyy").toStdString() << ";"
                << r.getFin_Reserva().toString("dd/MM/yyyy").toStdString() << ";"
                << (r.getIncluye_Desayuno() ? "si" : "no" )<< ";"
                << (r.getIncluye_Lavanderia() ? "si" : "no")<< ";"
                << (r.getIncluye_Extras() ? "si" : "no")<< ";"
                << r.getCosto_Reserva() << "\n";
    }
    archivo.close();
    return true;
}


void Hotel::limpiarHabitaciones(){
    habitaciones.clear();
}

void Hotel::limpiarReservas(){
    reservas.clear();
}
