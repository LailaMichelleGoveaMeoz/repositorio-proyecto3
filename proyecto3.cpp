#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <locale.h>// configurar acentos

using namespace std;

#ifndef CONSTANTES_HPP
#define CONSTANTES_HPP

namespace Rutas {
    static const char* HOSPITAL     = "hospital.bin";
    static const char* PACIENTES    = "pacientes.bin";
    static const char* DOCTORES     = "doctores.bin";
    static const char* CITAS        = "citas.bin";
    static const char* HISTORIALES  = "historiales.bin";
}

struct ArchivoHeader {
    int cantidadRegistros;
    int proximoID;
    int registrosActivos;
    int version;
    int ultimoId; // si lo necesitas (en citas lo usaste)
};

#endif

#ifndef PACIENTE_HPP
#define PACIENTE_HPP

//CLASE PACIENTE
class Paciente {
private:
    int id;
    char nombre[50];
    char apellido[50];
    char cedula[20];
    int edad;
    char sexo;
    char tipoSangre[5];
    char telefono[15];
    char direccion[100];
    char email[50];
    char alergias[500];
    char observaciones[500];
    bool activo;
    int cantidadConsultas;
    int primerConsultaID;
    int cantidadCitas;
    int citasIDs[20];
    bool eliminado;
    time_t fechaCreacion;
    time_t fechaModificacion;

public:
    // Constructores y destructor
    Paciente();
    Paciente(int idInicial, const char* nom, const char* ape, const char* ced);
    Paciente(const Paciente& otro);
    ~Paciente();

    // Getters (const)
    int getId() const;
    const char* getNombre() const;
    const char* getApellido() const;
    const char* getCedula() const;
    int getEdad() const;
    char getSexo() const;
    const char* getTipoSangre() const;
    const char* getTelefono() const;
    const char* getDireccion() const;
    const char* getEmail() const;
    const char* getAlergias() const;
    const char* getObservaciones() const;
    bool getActivo() const;
    bool getEliminado() const;
    int getCantidadConsultas() const;
    int getPrimerConsultaID() const;
    int getCantidadCitas() const;
    const int* getCitasIDs() const;
    time_t getFechaCreacion() const;
    time_t getFechaModificacion() const;

    // Setters (con validación y actualización de fechaModificacion)
    void setId(int nuevoId);
    void setNombre(const char* nom);
    void setApellido(const char* ape);
    void setCedula(const char* ced);
    void setEdad(int nuevaEdad);
    void setSexo(char s);
    void setTipoSangre(const char* ts);
    void setTelefono(const char* tel);
    void setDireccion(const char* dir);
    void setEmail(const char* mail);
    void setAlergias(const char* a);
    void setObservaciones(const char* o);
    void setActivo(bool a);
    void setEliminado(bool e);

    // Gestión de relaciones
    bool agregarCitaID(int citaID);
    bool eliminarCitaID(int citaID);
    bool tieneCitas() const;

    // Validaciones específicas
    bool validarDatos() const;      // nombre, apellido, cedula, edad en rango, etc.
    bool esMayorDeEdad() const;
    bool cedulaEsValida() const;    // puede delegar en Validaciones

    // Presentación
    void mostrarInformacionBasica() const;
    void mostrarInformacionCompleta() const;

    // Tamaño estático (para persistencia)
    static size_t obtenerTamano();
};

#include "pacientes/Paciente.hpp"


Paciente::Paciente() : id(0), edad(0), sexo('M'), activo(false), cantidadConsultas(0),
    primerConsultaID(-1), cantidadCitas(0), eliminado(false),
    fechaCreacion(0), fechaModificacion(0) {
    nombre[0] = apellido[0] = cedula[0] = tipoSangre[0] = telefono[0] = direccion[0] = email[0] = '\0';
    alergias[0] = observaciones[0] = '\0';
    for (int i = 0; i < 20; ++i) citasIDs[i] = 0;
}

Paciente::Paciente(int idInicial, const char* nom, const char* ape, const char* ced) : Paciente() {
    id = idInicial;
    setNombre(nom);
    setApellido(ape);
    setCedula(ced);
    fechaCreacion = time(nullptr);
    fechaModificacion = fechaCreacion;
}

Paciente::Paciente(const Paciente& o) { std::memcpy(this, &o, sizeof(Paciente)); }
Paciente::~Paciente() {}

int Paciente::getId() const { return id; }
const char* Paciente::getNombre() const { return nombre; }
const char* Paciente::getApellido() const { return apellido; }
const char* Paciente::getCedula() const { return cedula; }
int Paciente::getEdad() const { return edad; }
char Paciente::getSexo() const { return sexo; }
const char* Paciente::getTipoSangre() const { return tipoSangre; }
const char* Paciente::getTelefono() const { return telefono; }
const char* Paciente::getDireccion() const { return direccion; }
const char* Paciente::getEmail() const { return email; }
const char* Paciente::getAlergias() const { return alergias; }
const char* Paciente::getObservaciones() const { return observaciones; }
bool Paciente::getActivo() const { return activo; }
int Paciente::getCantidadConsultas() const { return cantidadConsultas; }
int Paciente::getPrimerConsultaID() const { return primerConsultaID; }
int Paciente::getCantidadCitas() const { return cantidadCitas; }
const int* Paciente::getCitasIDs() const { return citasIDs; }
bool Paciente::getEliminado() const { return eliminado; }
time_t Paciente::getFechaCreacion() const { return fechaCreacion; }
time_t Paciente::getFechaModificacion() const { return fechaModificacion; }


#include "Paciente.hpp"
#include <cstring>
#include <ctime>
#include <iostream>

// Setter para ID
void Paciente::setId(int nuevoId) {
    if (nuevoId > 0) {
        id = nuevoId;
        fechaModificacion = time(nullptr);
    }
}

// Setter para nombre
void Paciente::setNombre(const char* nom) {
    if (nom != nullptr) {
        std::strncpy(nombre, nom, 49);
        nombre[49] = '\0';
        fechaModificacion = time(nullptr);
    }
}

// Setter para apellido
void Paciente::setApellido(const char* ape) {
    if (ape != nullptr) {
        std::strncpy(apellido, ape, 49);
        apellido[49] = '\0';
        fechaModificacion = time(nullptr);
    }
}

// Setter para cédula
void Paciente::setCedula(const char* ced) {
    if (ced != nullptr) {
        std::strncpy(cedula, ced, 19);
        cedula[19] = '\0';
        fechaModificacion = time(nullptr);
    }
}

// Setter para edad (validación 0–120 años)
void Paciente::setEdad(int nuevaEdad) {
    if (nuevaEdad >= 0 && nuevaEdad <= 120) {
        edad = nuevaEdad;
        fechaModificacion = time(nullptr);
    }
}

// Setter para sexo (solo M/F)
void Paciente::setSexo(char s) {
    if (s == 'M' || s == 'F') {
        sexo = s;
        fechaModificacion = time(nullptr);
    }
}

// Setter para tipo de sangre
void Paciente::setTipoSangre(const char* ts) {
    if (ts != nullptr) {
        std::strncpy(tipoSangre, ts, 4);
        tipoSangre[4] = '\0';
        fechaModificacion = time(nullptr);
    }
}

// Setter para teléfono
void Paciente::setTelefono(const char* tel) {
    if (tel != nullptr) {
        std::strncpy(telefono, tel, 14);
        telefono[14] = '\0';
        fechaModificacion = time(nullptr);
    }
}

// Setter para dirección
void Paciente::setDireccion(const char* dir) {
    if (dir != nullptr) {
        std::strncpy(direccion, dir, 99);
        direccion[99] = '\0';
        fechaModificacion = time(nullptr);
    }
}

// Setter para email (validación mínima con '@')
void Paciente::setEmail(const char* mail) {
    if (mail != nullptr && std::strchr(mail, '@') != nullptr) {
        std::strncpy(email, mail, 49);
        email[49] = '\0';
        fechaModificacion = time(nullptr);
    }
}

// Setter para alergias
void Paciente::setAlergias(const char* a) {
    if (a != nullptr) {
        std::strncpy(alergias, a, 499);
        alergias[499] = '\0';
        fechaModificacion = time(nullptr);
    }
}

// Setter para observaciones
void Paciente::setObservaciones(const char* o) {
    if (o != nullptr) {
        std::strncpy(observaciones, o, 499);
        observaciones[499] = '\0';
        fechaModificacion = time(nullptr);
    }
}

// Setter para activo
void Paciente::setActivo(bool a) {
    activo = a;
    fechaModificacion = time(nullptr);
}

// Setter para eliminado
void Paciente::setEliminado(bool e) {
    eliminado = e;
    fechaModificacion = time(nullptr);
}
#include "Paciente.hpp"
#include "../utilidades/Validaciones.hpp" // para validar cédula si lo deseas

// ================= RELACIONES =================
bool Paciente::agregarCitaID(int citaID) {
    if (cantidadCitas >= 20) return false; // límite de 20 citas
    citasIDs[cantidadCitas++] = citaID;
    fechaModificacion = time(nullptr);
    return true;
}

bool Paciente::eliminarCitaID(int citaID) {
    bool encontrado = false;
    for (int i = 0; i < cantidadCitas; i++) {
        if (citasIDs[i] == citaID) {
            // mover los siguientes hacia atrás
            for (int j = i; j < cantidadCitas - 1; j++) {
                citasIDs[j] = citasIDs[j + 1];
            }
            citasIDs[cantidadCitas - 1] = 0;
            cantidadCitas--;
            encontrado = true;
            break;
        }
    }
    if (encontrado) fechaModificacion = time(nullptr);
    return encontrado;
}

bool Paciente::tieneCitas() const {
    return cantidadCitas > 0;
}

// ================= VALIDACIONES =================
bool Paciente::validarDatos() const {
    if (std::strlen(nombre) == 0) return false;
    if (std::strlen(apellido) == 0) return false;
    if (std::strlen(cedula) == 0) return false;
    if (edad < 0 || edad > 120) return false;
    if (!(sexo == 'M' || sexo == 'F')) return false;
    if (!Validaciones::validarEmail(email)) return false;
    return true;
}

bool Paciente::esMayorDeEdad() const {
    return edad >= 18;
}

bool Paciente::cedulaEsValida() const {
    return Validaciones::validarCedula(cedula);
}

// ================= PRESENTACIÓN =================
void Paciente::mostrarInformacionBasica() const {
    std::cout << "ID: " << id
              << " | Nombre: " << nombre << " " << apellido
              << " | Cédula: " << cedula << "\n";
}

void Paciente::mostrarInformacionCompleta() const {
    std::cout << "=== Información del Paciente ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Nombre: " << nombre << " " << apellido << "\n";
    std::cout << "Cédula: " << cedula << "\n";
    std::cout << "Edad: " << edad << "\n";
    std::cout << "Sexo: " << sexo << "\n";
    std::cout << "Tipo de sangre: " << tipoSangre << "\n";
    std::cout << "Teléfono: " << telefono << "\n";
    std::cout << "Dirección: " << direccion << "\n";
    std::cout << "Email: " << email << "\n";
    std::cout << "Alergias: " << alergias << "\n";
    std::cout << "Observaciones: " << observaciones << "\n";
    std::cout << "Activo: " << (activo ? "Sí" : "No") << "\n";
    std::cout << "Eliminado: " << (eliminado ? "Sí" : "No") << "\n";
    std::cout << "Cantidad de consultas: " << cantidadConsultas << "\n";
    std::cout << "Cantidad de citas: " << cantidadCitas << "\n";
}

// ================= PERSISTENCIA =================
size_t Paciente::obtenerTamano() {
    return sizeof(Paciente);
}

//CLASE DOCTORES
#ifndef DOCTOR_HPP
#define DOCTOR_HPP

class Doctor {
private:
    int id;
    char nombre[50];
    char apellido[50];
    char cedulaProfesional[20];
    char especialidad[50];
    int aniosExperiencia;
    float costoConsulta;
    char horarioAtencion[50];
    char telefono[15];
    char email[50];
    bool disponible;
    int cantidadPacientes;
    int pacientesIDs[50];
    int cantidadCitas;
    int citasIDs[30];
    bool eliminado;
    time_t fechaCreacion;
    time_t fechaModificacion;

public:
    // Constructores y destructor
    Doctor();
    Doctor(int idInicial, const char* nom, const char* ape, const char* cedProf);
    Doctor(const Doctor& otro);
    ~Doctor();

    // Getters
    int getId() const;
    const char* getNombre() const;
    const char* getApellido() const;
    const char* getCedulaProfesional() const;
    const char* getEspecialidad() const;
    int getAniosExperiencia() const;
    float getCostoConsulta() const;
    const char* getHorarioAtencion() const;
    const char* getTelefono() const;
    const char* getEmail() const;
    bool getDisponible() const;
    int getCantidadPacientes() const;
    const int* getPacientesIDs() const;
    int getCantidadCitas() const;
    const int* getCitasIDs() const;
    bool getEliminado() const;
    time_t getFechaCreacion() const;
    time_t getFechaModificacion() const;

    // Setters
    void setId(int nuevoId);
    void setNombre(const char* nom);
    void setApellido(const char* ape);
    void setCedulaProfesional(const char* cedProf);
    void setEspecialidad(const char* esp);
    void setAniosExperiencia(int anios);
    void setCostoConsulta(float costo);
    void setHorarioAtencion(const char* horario);
    void setTelefono(const char* tel);
    void setEmail(const char* mail);
    void setDisponible(bool d);
    void setEliminado(bool e);

    // Gestión de relaciones
    bool agregarPacienteID(int pacienteID);
    bool eliminarPacienteID(int pacienteID);
    bool agregarCitaID(int citaID);
    bool eliminarCitaID(int citaID);

    // Validaciones
    bool validarDatos() const;
    bool especialidadEsValida() const;
    bool cedulaProfesionalValida() const;
    bool costoConsultaValido() const;

    // Presentación
    void mostrarInformacionBasica() const;
    void mostrarInformacionCompleta() const;

    // Persistencia
    static size_t obtenerTamano();
};

#endif


#include "Doctor.hpp"
#include "../utilidades/Validaciones.hpp"

// ================= CONSTRUCTORES =================
Doctor::Doctor() : id(0), aniosExperiencia(0), costoConsulta(0.0f), disponible(true),
    cantidadPacientes(0), cantidadCitas(0), eliminado(false),
    fechaCreacion(0), fechaModificacion(0) {
    nombre[0] = apellido[0] = cedulaProfesional[0] = especialidad[0] = horarioAtencion[0] = telefono[0] = email[0] = '\0';
    for (int i = 0; i < 50; ++i) pacientesIDs[i] = 0;
    for (int i = 0; i < 30; ++i) citasIDs[i] = 0;
}

Doctor::Doctor(int idInicial, const char* nom, const char* ape, const char* cedProf) : Doctor() {
    id = idInicial;
    setNombre(nom);
    setApellido(ape);
    setCedulaProfesional(cedProf);
    fechaCreacion = time(nullptr);
    fechaModificacion = fechaCreacion;
}

Doctor::Doctor(const Doctor& otro) { std::memcpy(this, &otro, sizeof(Doctor)); }
Doctor::~Doctor() {}

// ================= GETTERS =================
int Doctor::getId() const { return id; }
const char* Doctor::getNombre() const { return nombre; }
const char* Doctor::getApellido() const { return apellido; }
const char* Doctor::getCedulaProfesional() const { return cedulaProfesional; }
const char* Doctor::getEspecialidad() const { return especialidad; }
int Doctor::getAniosExperiencia() const { return aniosExperiencia; }
float Doctor::getCostoConsulta() const { return costoConsulta; }
const char* Doctor::getHorarioAtencion() const { return horarioAtencion; }
const char* Doctor::getTelefono() const { return telefono; }
const char* Doctor::getEmail() const { return email; }
bool Doctor::getDisponible() const { return disponible; }
int Doctor::getCantidadPacientes() const { return cantidadPacientes; }
const int* Doctor::getPacientesIDs() const { return pacientesIDs; }
int Doctor::getCantidadCitas() const { return cantidadCitas; }
const int* Doctor::getCitasIDs() const { return citasIDs; }
bool Doctor::getEliminado() const { return eliminado; }
time_t Doctor::getFechaCreacion() const { return fechaCreacion; }
time_t Doctor::getFechaModificacion() const { return fechaModificacion; }

// ================= SETTERS =================
void Doctor::setId(int nuevoId) { 
if (nuevoId > 0) { 
id = nuevoId; fechaModificacion = time(nullptr);}
  }
  
void Doctor::setNombre(const char* nom) {
 if (nom) { 
 std::strncpy(nombre, nom, 49); nombre[49] = '\0'; 
 fechaModificacion = time(nullptr); } 
 }
 
void Doctor::setApellido(const char* ape) { 
if (ape) { std::strncpy(apellido, ape, 49); apellido[49] = '\0';
 fechaModificacion = time(nullptr); } 
}

void Doctor::setCedulaProfesional(const char* cedProf) {
 if (cedProf) { std::strncpy(cedulaProfesional, cedProf, 19); 
 cedulaProfesional[19] = '\0'; 
 fechaModificacion = time(nullptr); } 
 }
 
void Doctor::setEspecialidad(const char* esp) { 
if (esp) { std::strncpy(especialidad, esp, 49); 
especialidad[49] = '\0'; 
fechaModificacion = time(nullptr); } 
}

void Doctor::setAniosExperiencia(int anios) { 
if (anios >= 0) { 
aniosExperiencia = anios; 
fechaModificacion = time(nullptr); }
 
 }
void Doctor::setCostoConsulta(float costo) { 
if (costo >= 0.0f) {
 costoConsulta = costo; 
 fechaModificacion = time(nullptr); }
  
  }
void Doctor::setHorarioAtencion(const char* horario) { 
if (horario) { 
std::strncpy(horarioAtencion, horario, 49);
 horarioAtencion[49] = '\0'; 
 fechaModificacion = time(nullptr); }
  }
  
void Doctor::setTelefono(const char* tel) { 
if (tel) { 
std::strncpy(telefono, tel, 14); 
telefono[14] = '\0'; 
fechaModificacion = time(nullptr); } 
}

void Doctor::setEmail(const char* mail) {
 if (mail && std::strchr(mail, '@')) { 
 std::strncpy(email, mail, 49); 
 email[49] = '\0'; 
 fechaModificacion = time(nullptr); } 
 }
 
void Doctor::setDisponible(bool d) {
 disponible = d; fechaModificacion = time(nullptr); }
 
void Doctor::setEliminado(bool e) { 
eliminado = e; fechaModificacion = time(nullptr); }

// ================= RELACIONES =================
bool Doctor::agregarPacienteID(int pacienteID) {
    if (cantidadPacientes >= 50) return false;
    pacientesIDs[cantidadPacientes++] = pacienteID;
    fechaModificacion = time(nullptr);
    return true;
}

bool Doctor::eliminarPacienteID(int pacienteID) {
    bool encontrado = false;
    for (int i = 0; i < cantidadPacientes; i++) {
        if (pacientesIDs[i] == pacienteID) {
            for (int j = i; j < cantidadPacientes - 1; j++) {
                pacientesIDs[j] = pacientesIDs[j + 1];
            }
            pacientesIDs[cantidadPacientes - 1] = 0;
            cantidadPacientes--;
            encontrado = true;
            break;
        }
    }
    if (encontrado) fechaModificacion = time(nullptr);
    return encontrado;
}

bool Doctor::agregarCitaID(int citaID) {
    if (cantidadCitas >= 30) return false;
    citasIDs[cantidadCitas++] = citaID;
    fechaModificacion = time(nullptr);
    return true;
}

bool Doctor::eliminarCitaID(int citaID) {
    bool encontrado = false;
    for (int i = 0; i < cantidadCitas; i++) {
        if (citasIDs[i] == citaID) {
            for (int j = i; j < cantidadCitas - 1; j++) {
                citasIDs[j] = citasIDs[j + 1];
            }
            citasIDs[cantidadCitas - 1] = 0;
            cantidadCitas--;
            encontrado = true;
            break;
        }
    }
    if (encontrado) fechaModificacion = time(nullptr);
    return encontrado;
}

// ================= VALIDACIONES =================
bool Doctor::validarDatos() const {
    if (std::strlen(nombre) == 0) return false;
    if (std::strlen(apellido) == 0) return false;
    if (std::strlen(cedulaProfesional) == 0) return false;
    if (aniosExperiencia < 0) return false;
    if (!costoConsultaValido()) return false;
    if (!Validaciones::validarEmail(email)) return false;
    return true;
}

bool Doctor::especialidadEsValida() const {
    // Validación básica: no vacío
    return std::strlen(especialidad) > 0;
}

bool Doctor::cedulaProfesionalValida() const {
    // Validación básica: longitud mínima > 5
    return std::strlen(cedulaProfesional) >= 5;
}

bool Doctor::costoConsultaValido() const {
    // Validación: costo entre 0 y 1000 (ejemplo)
    return costoConsulta >= 0.0f && costoConsulta <= 1000.0f;
}

// ================= PRESENTACIÓN =================
void Doctor::mostrarInformacionBasica() const {
    std::cout << "ID: " << id
              << " | Nombre: " << nombre << " " << apellido
              << " | Especialidad: " << especialidad << "\n";
}

void Doctor::mostrarInformacionCompleta() const {
    std::cout << "=== Información del Doctor ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Nombre: " << nombre << " " << apellido << "\n";
    std::cout << "Cédula Profesional: " << cedulaProfesional << "\n";
    std::cout << "Especialidad: " << especialidad << "\n";
    std::cout << "Años de experiencia: " << aniosExperiencia << "\n";
    std::cout << "Costo de consulta: " << costoConsulta << "\n";
    std::cout << "Horario de atención: " << horarioAtencion << "\n";
    std::cout << "Teléfono: " << telefono << "\n";
    std::cout << "Email: " << email << "\n";
    std::cout << "Disponible: " << (disponible ? "Sí" : "No") << "\n";
    std::cout << "Eliminado: " << (eliminado ? "Sí" : "No") << "\n";
    std::cout << "Cantidad de pacientes: " << cantidadPacientes << "\n";
    std::cout << "Cantidad de citas: " << cantidadCitas << "\n";
}

// ================= PERSISTENCIA =================
size_t Doctor::obtenerTamano() {
    return sizeof(Doctor);
}

//CLASE CITAS
#ifndef CITA_HPP
#define CITA_HPP


class Cita {
private:
    int id;
    int idPaciente;
    int idDoctor;
    char fecha[11];       // YYYY-MM-DD
    char hora[6];         // HH:MM
    char motivo[150];
    char estado[20];      // Agendada, Atendida, Cancelada
    char observaciones[200];
    bool atendida;
    int consultaID;
    bool eliminado;
    time_t fechaCreacion;
    time_t fechaModificacion;

public:
    // Constructores y destructor
    Cita();
    Cita(int idInicial, int pacienteID, int doctorID, const char* f, const char* h, const char* mot);
    Cita(const Cita& otra);
    ~Cita();

    // Getters
    int getId() const;
    int getIdPaciente() const;
    int getIdDoctor() const;
    const char* getFecha() const;
    const char* getHora() const;
    const char* getMotivo() const;
    const char* getEstado() const;
    const char* getObservaciones() const;
    bool getAtendida() const;
    int getConsultaID() const;
    bool getEliminado() const;
    time_t getFechaCreacion() const;
    time_t getFechaModificacion() const;

    // Setters
    void setId(int nuevoId);
    void setIdPaciente(int pacienteID);
    void setIdDoctor(int doctorID);
    void setFecha(const char* f);
    void setHora(const char* h);
    void setMotivo(const char* mot);
    void setEstado(const char* est);
    void setObservaciones(const char* obs);
    void setAtendida(bool a);
    void setConsultaID(int consulta);
    void setEliminado(bool e);

    // Validaciones
    bool validarDatos() const;
    bool fechaHoraValidas() const;

    // Gestión de estado
    void marcarComoAtendida();
    void cancelar();

    // Presentación
    void mostrarInformacionBasica() const;
    void mostrarInformacionCompleta() const;

    // Persistencia
    static size_t obtenerTamano();
};

#endif
#include "Cita.hpp"
#include "../utilidades/Validaciones.hpp"

// ================= CONSTRUCTORES =================
Cita::Cita() : id(0), idPaciente(0), idDoctor(0), atendida(false),
    consultaID(-1), eliminado(false), fechaCreacion(0), fechaModificacion(0) {
    fecha[0] = hora[0] = motivo[0] = estado[0] = observaciones[0] = '\0';
}

Cita::Cita(int idInicial, int pacienteID, int doctorID, const char* f, const char* h, const char* mot) : Cita() {
    id = idInicial;
    idPaciente = pacienteID;
    idDoctor = doctorID;
    setFecha(f);
    setHora(h);
    setMotivo(mot);
    std::strcpy(estado, "Agendada");
    fechaCreacion = time(nullptr);
    fechaModificacion = fechaCreacion;
}

Cita::Cita(const Cita& otra) { std::memcpy(this, &otra, sizeof(Cita)); }
Cita::~Cita() {}

// ================= GETTERS =================
int Cita::getId() const { return id; }
int Cita::getIdPaciente() const { return idPaciente; }
int Cita::getIdDoctor() const { return idDoctor; }
const char* Cita::getFecha() const { return fecha; }
const char* Cita::getHora() const { return hora; }
const char* Cita::getMotivo() const { return motivo; }
const char* Cita::getEstado() const { return estado; }
const char* Cita::getObservaciones() const { return observaciones; }
bool Cita::getAtendida() const { return atendida; }
int Cita::getConsultaID() const { return consultaID; }
bool Cita::getEliminado() const { return eliminado; }
time_t Cita::getFechaCreacion() const { return fechaCreacion; }
time_t Cita::getFechaModificacion() const { return fechaModificacion; }

// ================= SETTERS =================
void Cita::setId(int nuevoId) { 
if (nuevoId > 0) { 
id = nuevoId; 
fechaModificacion = time(nullptr); } 
}

void Cita::setIdPaciente(int pacienteID) { 
if (pacienteID > 0) { 
idPaciente = pacienteID; 
fechaModificacion = time(nullptr); }
 }
 
void Cita::setIdDoctor(int doctorID) { 
if (doctorID > 0) { 
idDoctor = doctorID; 
fechaModificacion = time(nullptr); }
 }
 
void Cita::setFecha(const char* f) { 
if (f && Validaciones::validarFecha(f)) { 
std::strncpy(fecha, f, 10); 
fecha[10] = '\0'; 
fechaModificacion = time(nullptr); }
 }
 
void Cita::setHora(const char* h) { 
if (h && Validaciones::validarHora(h)) { 
std::strncpy(hora, h, 5);
 hora[5] = '\0'; 
 fechaModificacion = time(nullptr); }
  }
  
void Cita::setMotivo(const char* mot) { 
if (mot) { 
std::strncpy(motivo, mot, 149);
 motivo[149] = '\0';
  fechaModificacion = time(nullptr); } 
  }
  
void Cita::setEstado(const char* est) { 
if (est) {
 std::strncpy(estado, est, 19); 
 estado[19] = '\0'; 
 fechaModificacion = time(nullptr); }
  }
  
void Cita::setObservaciones(const char* obs) { 
if (obs) { 
std::strncpy(observaciones, obs, 199); 
observaciones[199] = '\0';
 fechaModificacion = time(nullptr); }
  }
  
void Cita::setAtendida(bool a) { 
atendida = a; 
fechaModificacion = time(nullptr); }

void Cita::setConsultaID(int consulta) { 
consultaID = consulta; 
fechaModificacion = time(nullptr); }

void Cita::setEliminado(bool e) { 
eliminado = e; 
fechaModificacion = time(nullptr); }

// ================= VALIDACIONES =================
bool Cita::validarDatos() const {
    if (idPaciente <= 0 || idDoctor <= 0) return false;
    if (!Validaciones::validarFecha(fecha)) return false;
    if (!Validaciones::validarHora(hora)) return false;
    if (std::strlen(motivo) == 0) return false;
    return true;
}

bool Cita::fechaHoraValidas() const {
    return Validaciones::validarFecha(fecha) && Validaciones::validarHora(hora);
}

// ================= GESTIÓN DE ESTADO =================
void Cita::marcarComoAtendida() {
    atendida = true;
    std::strcpy(estado, "Atendida");
    fechaModificacion = time(nullptr);
}

void Cita::cancelar() {
    std::strcpy(estado, "Cancelada");
    atendida = false;
    fechaModificacion = time(nullptr);
}

// ================= PRESENTACIÓN =================
void Cita::mostrarInformacionBasica() const {
    std::cout << "ID: " << id
              << " | Fecha: " << fecha
              << " | Hora: " << hora
              << " | Estado: " << estado << "\n";
}

void Cita::mostrarInformacionCompleta() const {
    std::cout << "=== Información de la Cita ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Paciente ID: " << idPaciente << "\n";
    std::cout << "Doctor ID: " << idDoctor << "\n";
    std::cout << "Fecha: " << fecha << "\n";
    std::cout << "Hora: " << hora << "\n";
    std::cout << "Motivo: " << motivo << "\n";
    std::cout << "Estado: " << estado << "\n";
    std::cout << "Observaciones: " << observaciones << "\n";
    std::cout << "Atendida: " << (atendida ? "Sí" : "No") << "\n";
    std::cout << "Consulta ID: " << consultaID << "\n";
    std::cout << "Eliminado: " << (eliminado ? "Sí" : "No") << "\n";
}

// ================= PERSISTENCIA =================
size_t Cita::obtenerTamano() {
    return sizeof(Cita);
}

//CLASE DE HISTORIAL MEDICO
#ifndef HISTORIAL_MEDICO_HPP
#define HISTORIAL_MEDICO_HPP

class HistorialMedico {
private:
    int id;
    int idPaciente;
    char fecha[11];        // YYYY-MM-DD
    char hora[6];          // HH:MM
    char diagnostico[200];
    char tratamiento[200];
    char medicamentos[150];
    int doctorID;
    float costo;
    int siguienteConsultaID; // para enlazar consultas
    bool eliminado;
    time_t fechaRegistro;
    time_t fechaCreacion;
    time_t fechaModificacion;

public:
    // Constructores y destructor
    HistorialMedico();
    HistorialMedico(int idInicial, int pacienteID, int doctor, const char* f, const char* h, const char* diag);
    HistorialMedico(const HistorialMedico& otro);
    ~HistorialMedico();

    // Getters
    int getId() const;
    int getIdPaciente() const;
    int getDoctorID() const;
    const char* getFecha() const;
    const char* getHora() const;
    const char* getDiagnostico() const;
    const char* getTratamiento() const;
    const char* getMedicamentos() const;
    float getCosto() const;
    int getSiguienteConsultaID() const;
    bool getEliminado() const;
    time_t getFechaRegistro() const;
    time_t getFechaCreacion() const;
    time_t getFechaModificacion() const;

    // Setters
    void setId(int nuevoId);
    void setIdPaciente(int pacienteID);
    void setDoctorID(int doctor);
    void setFecha(const char* f);
    void setHora(const char* h);
    void setDiagnostico(const char* diag);
    void setTratamiento(const char* trat);
    void setMedicamentos(const char* meds);
    void setCosto(float c);
    void setSiguienteConsultaID(int siguiente);
    void setEliminado(bool e);

    // Validaciones
    bool validarDatos() const;

    // Presentación
    void mostrarInformacionBasica() const;
    void mostrarInformacionCompleta() const;

    // Persistencia
    static size_t obtenerTamano();
};

#endif
#include "HistorialMedico.hpp"
#include "../utilidades/Validaciones.hpp"

// ================= CONSTRUCTORES =================
HistorialMedico::HistorialMedico() : id(0), idPaciente(0), doctorID(0), costo(0.0f),
    siguienteConsultaID(-1), eliminado(false), fechaRegistro(0),
    fechaCreacion(0), fechaModificacion(0) {
    fecha[0] = hora[0] = diagnostico[0] = tratamiento[0] = medicamentos[0] = '\0';
}

HistorialMedico::HistorialMedico(int idInicial, int pacienteID, int doctor, const char* f, const char* h, const char* diag) : HistorialMedico() {
    id = idInicial;
    idPaciente = pacienteID;
    doctorID = doctor;
    setFecha(f);
    setHora(h);
    setDiagnostico(diag);
    fechaRegistro = time(nullptr);
    fechaCreacion = fechaRegistro;
    fechaModificacion = fechaRegistro;
}

HistorialMedico::HistorialMedico(const HistorialMedico& otro) { std::memcpy(this, &otro, sizeof(HistorialMedico)); }
HistorialMedico::~HistorialMedico() {}

// ================= GETTERS =================
int HistorialMedico::getId() const { return id; }
int HistorialMedico::getIdPaciente() const { return idPaciente; }
int HistorialMedico::getDoctorID() const { return doctorID; }
const char* HistorialMedico::getFecha() const { return fecha; }
const char* HistorialMedico::getHora() const { return hora; }
const char* HistorialMedico::getDiagnostico() const { return diagnostico; }
const char* HistorialMedico::getTratamiento() const { return tratamiento; }
const char* HistorialMedico::getMedicamentos() const { return medicamentos; }
float HistorialMedico::getCosto() const { return costo; }
int HistorialMedico::getSiguienteConsultaID() const { return siguienteConsultaID; }
bool HistorialMedico::getEliminado() const { return eliminado; }
time_t HistorialMedico::getFechaRegistro() const { return fechaRegistro; }
time_t HistorialMedico::getFechaCreacion() const { return fechaCreacion; }
time_t HistorialMedico::getFechaModificacion() const { return fechaModificacion; }

// ================= SETTERS =================
void HistorialMedico::setId(int nuevoId) { 
if (nuevoId > 0) { 
id = nuevoId; 
fechaModificacion = time(nullptr); }
 }
 
void HistorialMedico::setIdPaciente(int pacienteID) { 
if (pacienteID > 0) { 
idPaciente = pacienteID; 
fechaModificacion = time(nullptr); } 
}

void HistorialMedico::setDoctorID(int doctor) { 
if (doctor > 0) { 
doctorID = doctor; 
fechaModificacion = time(nullptr); } 
}

void HistorialMedico::setFecha(const char* f) { 
if (f && Validaciones::validarFecha(f)) { 
std::strncpy(fecha, f, 10); 
fecha[10] = '\0'; 
fechaModificacion = time(nullptr); }
}

void HistorialMedico::setHora(const char* h) { 
if (h && Validaciones::validarHora(h)) { 
std::strncpy(hora, h, 5); 
hora[5] = '\0'; 
fechaModificacion = time(nullptr); } 
}

void HistorialMedico::setDiagnostico(const char* diag) { 
if (diag) { 
std::strncpy(diagnostico, diag, 199); 
diagnostico[199] = '\0'; 
fechaModificacion = time(nullptr); } 
}

void HistorialMedico::setTratamiento(const char* trat) { 
if (trat) { 
std::strncpy(tratamiento, trat, 199); 
tratamiento[199] = '\0'; 
fechaModificacion = time(nullptr); } 
}

void HistorialMedico::setMedicamentos(const char* meds) { 
if (meds) { 
std::strncpy(medicamentos, meds, 149); 
medicamentos[149] = '\0'; 
fechaModificacion = time(nullptr); } 
}

void HistorialMedico::setCosto(float c) { 
if (c >= 0.0f) { 
costo = c; fechaModificacion = time(nullptr); }
}

void HistorialMedico::setSiguienteConsultaID(int siguiente) { 
siguienteConsultaID = siguiente; 
fechaModificacion = time(nullptr); }

void HistorialMedico::setEliminado(bool e) { 
eliminado = e; fechaModificacion = time(nullptr); }

// ================= VALIDACIONES =================
bool HistorialMedico::validarDatos() const {
    if (idPaciente <= 0 || doctorID <= 0) return false;
    if (!Validaciones::validarFecha(fecha)) return false;
    if (!Validaciones::validarHora(hora)) return false;
    if (std::strlen(diagnostico) == 0) return false;
    return true;
}

// ================= PRESENTACIÓN =================
void HistorialMedico::mostrarInformacionBasica() const {
    std::cout << "ID: " << id
              << " | Paciente ID: " << idPaciente
              << " | Doctor ID: " << doctorID
              << " | Fecha: " << fecha
              << " | Hora: " << hora << "\n";
}

void HistorialMedico::mostrarInformacionCompleta() const {
    std::cout << "=== Historial Médico ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Paciente ID: " << idPaciente << "\n";
    std::cout << "Doctor ID: " << doctorID << "\n";
    std::cout << "Fecha: " << fecha << "\n";
    std::cout << "Hora: " << hora << "\n";
    std::cout << "Diagnóstico: " << diagnostico << "\n";
    std::cout << "Tratamiento: " << tratamiento << "\n";
    std::cout << "Medicamentos: " << medicamentos << "\n";
    std::cout << "Costo: " << costo << "\n";
    std::cout << "Siguiente Consulta ID: " << siguienteConsultaID << "\n";
    std::cout << "Eliminado: " << (eliminado ? "Sí" : "No") << "\n";
}

// ================= PERSISTENCIA =================
size_t HistorialMedico::obtenerTamano() {
    return sizeof(HistorialMedico);
}

#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

class Hospital {
private:
    char nombre[100];
    char direccion[150];
    char telefono[15];
    int siguienteIDPaciente;
    int siguienteIDDoctor;
    int siguienteIDCita;
    int siguienteIDConsulta;
    int totalPacientesRegistrados;
    int totalDoctoresRegistrados;
    int totalCitasAgendadas;
    int totalConsultasRealizadas;

public:
    // Constructores y destructor
    Hospital();
    Hospital(const char* nom, const char* dir, const char* tel);
    Hospital(const Hospital& otro);
    ~Hospital();

    // Getters
    const char* getNombre() const;
    const char* getDireccion() const;
    const char* getTelefono() const;
    int getSiguienteIDPaciente() const;
    int getSiguienteIDDoctor() const;
    int getSiguienteIDCita() const;
    int getSiguienteIDConsulta() const;
    int getTotalPacientesRegistrados() const;
    int getTotalDoctoresRegistrados() const;
    int getTotalCitasAgendadas() const;
    int getTotalConsultasRealizadas() const;

    // Setters
    void setNombre(const char* n);
    void setDireccion(const char* d);
    void setTelefono(const char* t);

    // Generadores de IDs
    int generarNuevoIDPaciente();
    int generarNuevoIDDoctor();
    int generarNuevoIDCita();
    int generarNuevoIDConsulta();

    // Incrementadores de estadísticas
    void incrementarPacientesRegistrados();
    void incrementarDoctoresRegistrados();
    void incrementarCitasAgendadas();
    void incrementarConsultasRealizadas();

    // Presentación
    void mostrarEstadisticas() const;

    // Persistencia
    static size_t obtenerTamano();
};

#endif

//CLASE HOSPITAL
#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

class Hospital {
private:
    char nombre[100];
    char direccion[150];
    char telefono[15];
    int siguienteIDPaciente;
    int siguienteIDDoctor;
    int siguienteIDCita;
    int siguienteIDConsulta;
    int totalPacientesRegistrados;
    int totalDoctoresRegistrados;
    int totalCitasAgendadas;
    int totalConsultasRealizadas;

public:
    // Constructores y destructor
    Hospital();
    Hospital(const char* nom, const char* dir, const char* tel);
    Hospital(const Hospital& otro);
    ~Hospital();

    // Getters
    const char* getNombre() const;
    const char* getDireccion() const;
    const char* getTelefono() const;
    int getSiguienteIDPaciente() const;
    int getSiguienteIDDoctor() const;
    int getSiguienteIDCita() const;
    int getSiguienteIDConsulta() const;
    int getTotalPacientesRegistrados() const;
    int getTotalDoctoresRegistrados() const;
    int getTotalCitasAgendadas() const;
    int getTotalConsultasRealizadas() const;

    // Setters
    void setNombre(const char* n);
    void setDireccion(const char* d);
    void setTelefono(const char* t);

    // Generadores de IDs
    int generarNuevoIDPaciente();
    int generarNuevoIDDoctor();
    int generarNuevoIDCita();
    int generarNuevoIDConsulta();

    // Incrementadores de estadísticas
    void incrementarPacientesRegistrados();
    void incrementarDoctoresRegistrados();
    void incrementarCitasAgendadas();
    void incrementarConsultasRealizadas();

    // Presentación
    void mostrarEstadisticas() const;

    // Persistencia
    static size_t obtenerTamano();
};

#endif

#include "Hospital.hpp"
#include <iostream>
#include <cstring>

// ================= CONSTRUCTORES =================
Hospital::Hospital() : siguienteIDPaciente(1), siguienteIDDoctor(1),
    siguienteIDCita(1), siguienteIDConsulta(1),
    totalPacientesRegistrados(0), totalDoctoresRegistrados(0),
    totalCitasAgendadas(0), totalConsultasRealizadas(0) {
    std::strcpy(nombre, "Hospital Universitario de Caracas");
    std::strcpy(direccion, "Av. Minerva, UCV Caracas, Distrito Capital (Venezuela), 1040");
    std::strcpy(telefono, "04126067652");
}

Hospital::Hospital(const char* nom, const char* dir, const char* tel) : Hospital() {
    setNombre(nom);
    setDireccion(dir);
    setTelefono(tel);
}

Hospital::Hospital(const Hospital& otro) { std::memcpy(this, &otro, sizeof(Hospital)); }
Hospital::~Hospital() {}

// ================= GETTERS =================
const char* Hospital::getNombre() const { return nombre; }
const char* Hospital::getDireccion() const { return direccion; }
const char* Hospital::getTelefono() const { return telefono; }
int Hospital::getSiguienteIDPaciente() const { return siguienteIDPaciente; }
int Hospital::getSiguienteIDDoctor() const { return siguienteIDDoctor; }
int Hospital::getSiguienteIDCita() const { return siguienteIDCita; }
int Hospital::getSiguienteIDConsulta() const { return siguienteIDConsulta; }
int Hospital::getTotalPacientesRegistrados() const { return totalPacientesRegistrados; }
int Hospital::getTotalDoctoresRegistrados() const { return totalDoctoresRegistrados; }
int Hospital::getTotalCitasAgendadas() const { return totalCitasAgendadas; }
int Hospital::getTotalConsultasRealizadas() const { return totalConsultasRealizadas; }

// ================= SETTERS =================
void Hospital::setNombre(const char* n) {
    if (n) { std::strncpy(nombre, n, 99); nombre[99] = '\0'; }
}
void Hospital::setDireccion(const char* d) {
    if (d) { std::strncpy(direccion, d, 149); direccion[149] = '\0'; }
}
void Hospital::setTelefono(const char* t) {
    if (t) { std::strncpy(telefono, t, 14); telefono[14] = '\0'; }
}

// ================= GENERADORES DE IDs =================
int Hospital::generarNuevoIDPaciente() { return siguienteIDPaciente++; }
int Hospital::generarNuevoIDDoctor() { return siguienteIDDoctor++; }
int Hospital::generarNuevoIDCita() { return siguienteIDCita++; }
int Hospital::generarNuevoIDConsulta() { return siguienteIDConsulta++; }

// ================= INCREMENTADORES =================
void Hospital::incrementarPacientesRegistrados() { totalPacientesRegistrados++; }
void Hospital::incrementarDoctoresRegistrados() { totalDoctoresRegistrados++; }
void Hospital::incrementarCitasAgendadas() { totalCitasAgendadas++; }
void Hospital::incrementarConsultasRealizadas() { totalConsultasRealizadas++; }

// ================= PRESENTACIÓN =================
void Hospital::mostrarEstadisticas() const {
    std::cout << "=== Estadísticas del Hospital ===\n";
    std::cout << "Nombre: " << nombre << "\n";
    std::cout << "Dirección: " << direccion << "\n";
    std::cout << "Teléfono: " << telefono << "\n";
    std::cout << "Pacientes registrados: " << totalPacientesRegistrados << "\n";
    std::cout << "Doctores registrados: " << totalDoctoresRegistrados << "\n";
    std::cout << "Citas agendadas: " << totalCitasAgendadas << "\n";
    std::cout << "Consultas realizadas: " << totalConsultasRealizadas << "\n";
}

// ================= PERSISTENCIA =================
size_t Hospital::obtenerTamano() {
    return sizeof(Hospital);
}

//CLASE GESTION ARCHIVOS
#ifndef GESTOR_ARCHIVOS_HPP
#define GESTOR_ARCHIVOS_HPP
#include "Constantes.hpp"

class GestorArchivos {
private:
    static std::streampos calcularPosicion(int indice, size_t tamRegistro);

public:
    // Inicialización y verificación
    static bool inicializarArchivo(const char* nombreArchivo);
    static bool verificarArchivo(const char* nombreArchivo);
    static ArchivoHeader leerHeader(const char* nombreArchivo);
    static bool actualizarHeader(const char* nombreArchivo, const ArchivoHeader& header);

    // CRUD genérico
    static bool guardarRegistro(const char* nombreArchivo, void* registro, size_t tamRegistro);
    static int  buscarIndicePorID(const char* nombreArchivo, int idBuscado, size_t tamRegistro);
    static bool leerRegistroPorIndice(const char* nombreArchivo, int indice, void* registro, size_t tamRegistro);
    static bool actualizarRegistro(const char* nombreArchivo, const void* registro, size_t tamRegistro, int indice);
    static bool eliminarRegistro(const char* nombreArchivo, int id, size_t tamRegistro);

    // Listar registros activos
    static void listarRegistrosActivos(const char* nombreArchivo, size_t tamRegistro,
                                       void (*mostrar)(const void*));

    // Mantenimiento
    static bool compactarArchivo(const char* nombreArchivo, size_t tamRegistro);
};

#endif

#include "GestorArchivos.hpp"
#include <cstring>
#include <cstdio>

// ================= AUXILIAR =================
std::streampos GestorArchivos::calcularPosicion(int indice, size_t tamRegistro) {
    return std::streampos(sizeof(ArchivoHeader)) + std::streampos(indice * tamRegistro);
}

// ================= INICIALIZACIÓN =================
bool GestorArchivos::inicializarArchivo(const char* nombreArchivo) {
    std::ofstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo.is_open()) return false;
    ArchivoHeader header = {0, 1, 0, 1, 0};
    archivo.write((char*)&header, sizeof(header));
    archivo.close();
    return true;
}

bool GestorArchivos::verificarArchivo(const char* nombreArchivo) {
    std::ifstream archivo(nombreArchivo, std::ios::binary);
    if (!archivo.is_open()) return false;
    ArchivoHeader h{};
    archivo.read((char*)&h, sizeof(h));
    archivo.close();
    return h.version == 1;
}

ArchivoHeader GestorArchivos::leerHeader(const char* nombreArchivo) {
    std::ifstream f(nombreArchivo, std::ios::binary);
    ArchivoHeader h{};
    if (!f.is_open()) return h;
    f.read((char*)&h, sizeof(h));
    f.close();
    return h;
}

bool GestorArchivos::actualizarHeader(const char* nombreArchivo, const ArchivoHeader& header) {
    std::fstream f(nombreArchivo, std::ios::binary | std::ios::in | std::ios::out);
    if (!f.is_open()) return false;
    f.seekp(0);
    f.write((char*)&header, sizeof(header));
    f.close();
    return true;
}

// ================= CRUD =================
bool GestorArchivos::guardarRegistro(const char* nombreArchivo, void* registro, size_t tamRegistro) {
    ArchivoHeader h = leerHeader(nombreArchivo);
    std::ofstream f(nombreArchivo, std::ios::binary | std::ios::app);
    if (!f.is_open()) return false;
    f.write((char*)registro, tamRegistro);
    f.close();
    h.cantidadRegistros++;
    h.registrosActivos++;
    h.proximoID++;
    return actualizarHeader(nombreArchivo, h);
}

int GestorArchivos::buscarIndicePorID(const char* nombreArchivo, int idBuscado, size_t tamRegistro) {
    std::ifstream f(nombreArchivo, std::ios::binary);
    if (!f.is_open()) return -1;
    ArchivoHeader h{};
    f.read((char*)&h, sizeof(h));
    char* buffer = new char[tamRegistro];
    for (int i = 0; i < h.cantidadRegistros; ++i) {
        f.read(buffer, tamRegistro);
        int id = 0; std::memcpy(&id, buffer, sizeof(int));
        bool eliminado = false;
        std::memcpy(&eliminado, buffer + tamRegistro - sizeof(bool) - sizeof(time_t)*2, sizeof(bool));
        if (id == idBuscado && !eliminado) { delete[] buffer; f.close(); return i; }
    }
    delete[] buffer; f.close();
    return -1;
}

bool GestorArchivos::leerRegistroPorIndice(const char* nombreArchivo, int indice, void* registro, size_t tamRegistro) {
    std::ifstream f(nombreArchivo, std::ios::binary);
    if (!f.is_open()) return false;
    f.seekg(calcularPosicion(indice, tamRegistro));
    f.read((char*)registro, tamRegistro);
    f.close();
    return true;
}

bool GestorArchivos::actualizarRegistro(const char* nombreArchivo, const void* registro, size_t tamRegistro, int indice) {
    std::fstream f(nombreArchivo, std::ios::binary | std::ios::in | std::ios::out);
    if (!f.is_open()) return false;
    f.seekp(calcularPosicion(indice, tamRegistro));
    f.write((const char*)registro, tamRegistro);
    f.close();
    return true;
}

bool GestorArchivos::eliminarRegistro(const char* nombreArchivo, int id, size_t tamRegistro) {
    int idx = buscarIndicePorID(nombreArchivo, id, tamRegistro);
    if (idx == -1) return false;
    std::fstream f(nombreArchivo, std::ios::binary | std::ios::in | std::ios::out);
    if (!f.is_open()) return false;
    char* buffer = new char[tamRegistro];
    f.seekg(calcularPosicion(idx, tamRegistro));
    f.read(buffer, tamRegistro);
    bool flag = true;
    std::memcpy(buffer + tamRegistro - sizeof(bool) - sizeof(time_t)*2, &flag, sizeof(bool));
    f.seekp(calcularPosicion(idx, tamRegistro));
    f.write(buffer, tamRegistro);
    delete[] buffer;
    f.close();
    ArchivoHeader h = leerHeader(nombreArchivo);
    h.registrosActivos--;
    return actualizarHeader(nombreArchivo, h);
}

// ================= LISTAR =================
void GestorArchivos::listarRegistrosActivos(const char* nombreArchivo, size_t tamRegistro,
                                            void (*mostrar)(const void*)) {
    std::ifstream f(nombreArchivo, std::ios::binary);
    if (!f.is_open()) return;
    ArchivoHeader h{};
    f.read((char*)&h, sizeof(h));
    char* buffer = new char[tamRegistro];
    for (int i = 0; i < h.cantidadRegistros; ++i) {
        f.read(buffer, tamRegistro);
        bool eliminado = false;
        std::memcpy(&eliminado, buffer + tamRegistro - sizeof(bool) - sizeof(time_t)*2, sizeof(bool));
        if (!eliminado) mostrar(buffer);
    }
    delete[] buffer;
    f.close();
}

// ================= COMPACTAR =================
bool GestorArchivos::compactarArchivo(const char* nombreArchivo, size_t tamRegistro) {
    std::ifstream original(nombreArchivo, std::ios::binary);
    if (!original.is_open()) return false;

    ArchivoHeader hOriginal{};
    original.read((char*)&hOriginal, sizeof(hOriginal));

    std::ofstream temp("temp.bin", std::ios::binary | std::ios::trunc);
    if (!temp.is_open()) {
        original.close();
        return false;
    }

    ArchivoHeader nuevoHeader = {};
    nuevoHeader.version = hOriginal.version;
    temp.write((char*)&nuevoHeader, sizeof(nuevoHeader));

    char* buffer = new char[tamRegistro];
    int nuevoID = 1;
    int activos = 0;

    for (int i = 0; i < hOriginal.cantidadRegistros; ++i) {
        original.read(buffer, tamRegistro);
        bool eliminado = false;
        std::memcpy(&eliminado, buffer + tamRegistro - sizeof(bool) - sizeof(time_t)*2, sizeof(bool));

        if (!eliminado) {
            // reasignar ID consecutivo
            std::memcpy(buffer, &nuevoID, sizeof(int));
            nuevoID++;
            activos++;
            temp.write(buffer, tamRegistro);
        }
    }

    delete[] buffer;
    original.close();

    // actualizar header
    nuevoHeader.cantidadRegistros = activos;
    nuevoHeader.registrosActivos = activos;
    nuevoHeader.proximoID = nuevoID;

    temp.seekp(0);
    temp.write((char*)&nuevoHeader, sizeof(nuevoHeader));
    temp.close();

    // reemplazar archivo original
    std::remove(nombreArchivo);
    std::rename("temp.bin", nombreArchivo);

    return true;
}

//OPERACIONES PACIENTES
#ifndef OPERACIONES_PACIENTES_HPP
#define OPERACIONES_PACIENTES_HPP

#include "../pacientes/Paciente.hpp"
#include "../persistencia/GestorArchivos.hpp"
#include "../persistencia/Constantes.hpp"
#include "../utilidades/Validaciones.hpp"

// Operaciones principales
void registrarPacienteInteractivo(const char* cedulaInicial);
Paciente leerPacientePorID(int id);
void buscarPacientePorID();
Paciente buscarPacientePorCedula(const char* cedulaBuscada);
void buscarPacientesPorNombre(const char* fragmento);
void actualizarPacienteInteractivo();
void eliminarPacienteInteractivo();
void listarPacientesActivos();

#endif

#include "operacionesPacientes.hpp"

// Registrar paciente interactivo
void registrarPacienteInteractivo(const char* cedulaInicial) {
    Paciente p;
    char buffer[500];

    std::cin.ignore();
    std::cout << "Nombre: "; std::cin.getline(buffer, 50); p.setNombre(buffer);
    std::cout << "Apellido: "; std::cin.getline(buffer, 50); p.setApellido(buffer);
    p.setCedula(cedulaInicial);

    int edad; char sexo;
    std::cout << "Edad: "; std::cin >> edad; p.setEdad(edad);
    std::cout << "Sexo (M/F): "; std::cin >> sexo; p.setSexo(sexo);
    std::cin.ignore();

    std::cout << "Tipo de sangre: "; std::cin.getline(buffer, 5); p.setTipoSangre(buffer);
    std::cout << "Teléfono: "; std::cin.getline(buffer, 15); p.setTelefono(buffer);
    std::cout << "Dirección: "; std::cin.getline(buffer, 100); p.setDireccion(buffer);

    do {
        std::cout << "Email: "; std::cin.getline(buffer, 50);
        if (!Validaciones::validarEmail(buffer)) std::cout << "Email inválido.\n";
    } while (!Validaciones::validarEmail(buffer));
    p.setEmail(buffer);

    std::cout << "Alergias: "; std::cin.getline(buffer, 500); p.setAlergias(buffer);
    std::cout << "Observaciones: "; std::cin.getline(buffer, 500); p.setObservaciones(buffer);

    p.setActivo(true);
    p.setEliminado(false);

    // Asignar ID desde header
    ArchivoHeader h = GestorArchivos::leerHeader(Rutas::PACIENTES);
    p.setId(h.proximoID);

    // Guardar
    if (GestorArchivos::guardarRegistro(Rutas::PACIENTES, (void*)&p, Paciente::obtenerTamano())) {
        std::cout << "Paciente registrado con ID: " << p.getId() << "\n";
    } else {
        std::cout << "Error al registrar paciente.\n";
    }
}

// Leer paciente por ID
Paciente leerPacientePorID(int id) {
    int idx = GestorArchivos::buscarIndicePorID(Rutas::PACIENTES, id, Paciente::obtenerTamano());
    Paciente p;
    if (idx == -1) return p;
    GestorArchivos::leerRegistroPorIndice(Rutas::PACIENTES, idx, (void*)&p, Paciente::obtenerTamano());
    return p;
}

// Buscar paciente por ID interactivo
void buscarPacientePorID() {
    int id; std::cout << "Ingrese ID del paciente: "; std::cin >> id;
    Paciente p = leerPacientePorID(id);
    if (p.getId() == 0 || p.getEliminado()) {
        std::cout << "Paciente no encontrado.\n";
        return;
    }
    p.mostrarInformacionCompleta();
}

// Buscar paciente por cédula
Paciente buscarPacientePorCedula(const char* cedulaBuscada) {
    std::ifstream archivo(Rutas::PACIENTES, std::ios::binary);
    Paciente paciente = {};
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir pacientes.bin\n";
        paciente.setId(-1);
        return paciente;
    }

    ArchivoHeader header;
    archivo.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read(reinterpret_cast<char*>(&paciente), sizeof(Paciente));
        if (!paciente.getEliminado() && std::strcmp(paciente.getCedula(), cedulaBuscada) == 0) {
            archivo.close();
            return paciente;
        }
    }
    archivo.close();
    paciente.setId(-1);
    return paciente;
}

// Buscar pacientes por nombre (fragmento)
void buscarPacientesPorNombre(const char* fragmento) {
    std::ifstream archivo(Rutas::PACIENTES, std::ios::binary);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir pacientes.bin\n";
        return;
    }

    ArchivoHeader header;
    archivo.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
    Paciente paciente;
    bool encontrado = false;

    std::cout << "Pacientes que coinciden con \"" << fragmento << "\":\n";
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read(reinterpret_cast<char*>(&paciente), sizeof(Paciente));
        if (!paciente.getEliminado() && std::strstr(paciente.getNombre(), fragmento) != nullptr) {
            paciente.mostrarInformacionBasica();
            encontrado = true;
        }
    }

    if (!encontrado) std::cout << "No se encontraron pacientes.\n";
    archivo.close();
}

// Actualizar paciente interactivo
void actualizarPacienteInteractivo() {
    int id;
    std::cout << "ID del paciente a actualizar: ";
    std::cin >> id;
    Paciente p = leerPacientePorID(id);
    if (p.getId() == 0 || p.getEliminado()) {
        std::cout << "Paciente no encontrado.\n";
        return;
    }

    char buffer[500];
    std::cin.ignore();
    std::cout << "Nuevo nombre (" << p.getNombre() << "): "; std::cin.getline(buffer, 50); p.setNombre(buffer);
    std::cout << "Nuevo apellido (" << p.getApellido() << "): "; std::cin.getline(buffer, 50); p.setApellido(buffer);
    std::cout << "Nueva cédula (" << p.getCedula() << "): "; std::cin.getline(buffer, 20); p.setCedula(buffer);
    int edad; std::cout << "Nueva edad (" << p.getEdad() << "): "; std::cin >> edad; p.setEdad(edad);
    char sexo; std::cout << "Nuevo sexo (" << p.getSexo() << "): "; std::cin >> sexo; p.setSexo(sexo);
    std::cin.ignore();
    std::cout << "Nuevo tipo de sangre (" << p.getTipoSangre() << "): "; std::cin.getline(buffer, 5); p.setTipoSangre(buffer);
    std::cout << "Nuevo teléfono (" << p.getTelefono() << "): "; std::cin.getline(buffer, 15); p.setTelefono(buffer);
    std::cout << "Nueva dirección (" << p.getDireccion() << "): "; std::cin.getline(buffer, 100); p.setDireccion(buffer);
    std::cout << "Nueva alergia (" << p.getAlergias() << "): "; std::cin.getline(buffer, 500); p.setAlergias(buffer);
    std::cout << "Nuevo email (" << p.getEmail() << "): "; std::cin.getline(buffer, 50); p.setEmail(buffer);
    std::cout << "Nuevas observaciones (" << p.getObservaciones() << "): "; std::cin.getline(buffer, 500); p.setObservaciones(buffer);

    p.setActivo(true);

    int idx = GestorArchivos::buscarIndicePorID(Rutas::PACIENTES, p.getId(), Paciente::obtenerTamano());
    if (idx != -1 && GestorArchivos::actualizarRegistro(Rutas::PACIENTES, (void*)&p, Paciente::obtenerTamano(), idx)) {
        std::cout << "Paciente actualizado.\n";
    } else {
        std::cout << "Error al actualizar.\n";
    }
}

// Eliminar paciente interactivo
void eliminarPacienteInteractivo() {
    int id;
    std::cout << "ID del paciente a eliminar: ";
    std::cin >> id;

    if (GestorArchivos::eliminarRegistro(Rutas::PACIENTES, id, Paciente::obtenerTamano())) {
        std::cout << "Paciente eliminado lógicamente.\n";
        // Compactar archivo para reorganizar IDs y eliminar registros marcados
        GestorArchivos::compactarArchivo(Rutas::PACIENTES, Paciente::obtenerTamano());
    } else {
        std::cout << "No se pudo eliminar.\n";
    }
}

// Listar pacientes activos
void listarPacientesActivos() {
    std::cout << "=== Lista de Pacientes Activos ===\n";

    auto mostrarPaciente = [](const void* registro) {
        const Paciente* p = reinterpret_cast<const Paciente*>(registro);
        p->mostrarInformacionBasica();
    };

    GestorArchivos::listarRegistrosActivos(Rutas::PACIENTES, Paciente::obtenerTamano(), mostrarPaciente);
}

//OPERACIONES DOCTORES
#ifndef OPERACIONES_DOCTORES_HPP
#define OPERACIONES_DOCTORES_HPP

#include "../doctores/Doctor.hpp"
#include "../persistencia/GestorArchivos.hpp"
#include "../persistencia/Constantes.hpp"
#include "../utilidades/Validaciones.hpp"

// Operaciones principales
void registrarDoctorInteractivo();
Doctor leerDoctorPorID(int id);
void buscarDoctorPorID();
void buscarDoctoresPorEspecialidad(const char* especialidadBuscada);
void actualizarDoctorInteractivo();
void eliminarDoctorInteractivo();
void listarDoctoresActivos();

#endif

#include "operacionesDoctores.hpp"
#include <cstring>
#include <ctime>

// Registrar doctor interactivo
void registrarDoctorInteractivo() {
    Doctor d;
    char buffer[200];

    std::cin.ignore();
    std::cout << "Nombre: "; std::cin.getline(buffer, 50); d.setNombre(buffer);
    std::cout << "Apellido: "; std::cin.getline(buffer, 50); d.setApellido(buffer);
    std::cout << "Cédula profesional: "; std::cin.getline(buffer, 20); d.setCedulaProfesional(buffer);
    std::cout << "Especialidad: "; std::cin.getline(buffer, 50); d.setEspecialidad(buffer);

    int anios; std::cout << "Años de experiencia: "; std::cin >> anios; d.setAniosExperiencia(anios);
    float costo; std::cout << "Costo de consulta: "; std::cin >> costo; d.setCostoConsulta(costo);
    std::cin.ignore();

    std::cout << "Horario de atención: "; std::cin.getline(buffer, 50); d.setHorarioAtencion(buffer);
    std::cout << "Teléfono: "; std::cin.getline(buffer, 15); d.setTelefono(buffer);

    do {
        std::cout << "Email: "; std::cin.getline(buffer, 50);
        if (!Validaciones::validarEmail(buffer)) std::cout << "Email inválido.\n";
    } while (!Validaciones::validarEmail(buffer));
    d.setEmail(buffer);

    d.setDisponible(true);
    d.setEliminado(false);

    // Asignar ID desde header
    ArchivoHeader h = GestorArchivos::leerHeader(Rutas::DOCTORES);
    d.setId(h.proximoID);

    // Guardar
    if (GestorArchivos::guardarRegistro(Rutas::DOCTORES, (void*)&d, Doctor::obtenerTamano())) {
        std::cout << "Doctor registrado con ID: " << d.getId() << "\n";
    } else {
        std::cout << "Error al registrar doctor.\n";
    }
}

// Leer doctor por ID
Doctor leerDoctorPorID(int id) {
    int idx = GestorArchivos::buscarIndicePorID(Rutas::DOCTORES, id, Doctor::obtenerTamano());
    Doctor d;
    if (idx == -1) return d;
    GestorArchivos::leerRegistroPorIndice(Rutas::DOCTORES, idx, (void*)&d, Doctor::obtenerTamano());
    return d;
}

// Buscar doctor por ID interactivo
void buscarDoctorPorID() {
    int id; std::cout << "Ingrese ID del doctor: "; std::cin >> id;
    Doctor d = leerDoctorPorID(id);
    if (d.getId() == 0 || d.getEliminado()) {
        std::cout << "Doctor no encontrado.\n";
        return;
    }
    d.mostrarInformacionCompleta();
}

// Buscar doctores por especialidad
void buscarDoctoresPorEspecialidad(const char* especialidadBuscada) {
    std::ifstream archivo(Rutas::DOCTORES, std::ios::binary);
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir doctores.bin\n";
        return;
    }

    ArchivoHeader header;
    archivo.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
    Doctor d;
    bool encontrados = false;

    std::cout << "Doctores con especialidad \"" << especialidadBuscada << "\":\n";
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read(reinterpret_cast<char*>(&d), sizeof(Doctor));
        if (!d.getEliminado() && std::strcmp(d.getEspecialidad(), especialidadBuscada) == 0) {
            d.mostrarInformacionBasica();
            encontrados = true;
        }
    }

    if (!encontrados) std::cout << "No se encontraron doctores.\n";
    archivo.close();
}

// Actualizar doctor interactivo
void actualizarDoctorInteractivo() {
    int id;
    std::cout << "ID del doctor a actualizar: ";
    std::cin >> id;
    Doctor d = leerDoctorPorID(id);
    if (d.getId() == 0 || d.getEliminado()) {
        std::cout << "Doctor no encontrado.\n";
        return;
    }

    char buffer[200];
    std::cin.ignore();
    std::cout << "Nuevo nombre (" << d.getNombre() << "): "; std::cin.getline(buffer, 50); d.setNombre(buffer);
    std::cout << "Nuevo apellido (" << d.getApellido() << "): "; std::cin.getline(buffer, 50); d.setApellido(buffer);
    std::cout << "Nueva cédula profesional (" << d.getCedulaProfesional() << "): "; std::cin.getline(buffer, 20); d.setCedulaProfesional(buffer);
    std::cout << "Nueva especialidad (" << d.getEspecialidad() << "): "; std::cin.getline(buffer, 50); d.setEspecialidad(buffer);
    int anios; std::cout << "Nuevos años de experiencia (" << d.getAniosExperiencia() << "): "; std::cin >> anios; d.setAniosExperiencia(anios);
    float costo; std::cout << "Nuevo costo de consulta (" << d.getCostoConsulta() << "): "; std::cin >> costo; d.setCostoConsulta(costo);
    std::cin.ignore();
    std::cout << "Nuevo horario de atención (" << d.getHorarioAtencion() << "): "; std::cin.getline(buffer, 50); d.setHorarioAtencion(buffer);
    std::cout << "Nuevo teléfono (" << d.getTelefono() << "): "; std::cin.getline(buffer, 15); d.setTelefono(buffer);
    std::cout << "Nuevo email (" << d.getEmail() << "): "; std::cin.getline(buffer, 50); d.setEmail(buffer);

    int idx = GestorArchivos::buscarIndicePorID(Rutas::DOCTORES, d.getId(), Doctor::obtenerTamano());
    if (idx != -1 && GestorArchivos::actualizarRegistro(Rutas::DOCTORES, (void*)&d, Doctor::obtenerTamano(), idx)) {
        std::cout << "Doctor actualizado.\n";
    } else {
        std::cout << "Error al actualizar.\n";
    }
}

// Eliminar doctor interactivo
void eliminarDoctorInteractivo() {
    int id;
    std::cout << "ID del doctor a eliminar: ";
    std::cin >> id;
    if (GestorArchivos::eliminarRegistro(Rutas::DOCTORES, id, Doctor::obtenerTamano())) {
        std::cout << "Doctor eliminado lógicamente.\n";
        GestorArchivos::compactarArchivo(Rutas::DOCTORES, Doctor::obtenerTamano());
    } else {
        std::cout << "No se pudo eliminar.\n";
    }
}

// Listar doctores activos
void listarDoctoresActivos() {
    std::cout << "=== Lista de Doctores Activos ===\n";

    auto mostrarDoctor = [](const void* registro) {
        const Doctor* d = reinterpret_cast<const Doctor*>(registro);
        d->mostrarInformacionBasica();
    };

    GestorArchivos::listarRegistrosActivos(Rutas::DOCTORES, Doctor::obtenerTamano(), mostrarDoctor);
}

//OPERACIONES CITAS
#ifndef OPERACIONES_CITAS_HPP
#define OPERACIONES_CITAS_HPP

#include "../citas/Cita.hpp"
#include "../persistencia/GestorArchivos.hpp"
#include "../persistencia/Constantes.hpp"
#include "../utilidades/Validaciones.hpp"

// Operaciones principales
void agendarCitaInteractivo();
Cita leerCitaPorID(int id);
void buscarCitaPorID();
void listarCitasActivas();
void cancelarCitaInteractivo();
void marcarCitaAtendidaInteractivo();

#endif
#include "operacionesCitas.hpp"

// Agendar cita interactivo
void agendarCitaInteractivo() {
    Cita c;
    char buffer[200];

    int idPaciente, idDoctor;
    std::cout << "ID del paciente: "; std::cin >> idPaciente; c.setIdPaciente(idPaciente);
    std::cout << "ID del doctor: "; std::cin >> idDoctor; c.setIdDoctor(idDoctor);
    std::cin.ignore();

    std::cout << "Fecha (YYYY-MM-DD): "; std::cin.getline(buffer, 11); c.setFecha(buffer);
    std::cout << "Hora (HH:MM): "; std::cin.getline(buffer, 6); c.setHora(buffer);
    std::cout << "Motivo: "; std::cin.getline(buffer, 150); c.setMotivo(buffer);

    c.setEstado("Agendada");
    c.setAtendida(false);
    c.setEliminado(false);

    // Asignar ID desde header
    ArchivoHeader h = GestorArchivos::leerHeader(Rutas::CITAS);
    c.setId(h.proximoID);

    // Guardar
    if (GestorArchivos::guardarRegistro(Rutas::CITAS, (void*)&c, Cita::obtenerTamano())) {
        std::cout << "Cita registrada con ID: " << c.getId() << "\n";
    } else {
        std::cout << "Error al registrar cita.\n";
    }
}

// Leer cita por ID
Cita leerCitaPorID(int id) {
    int idx = GestorArchivos::buscarIndicePorID(Rutas::CITAS, id, Cita::obtenerTamano());
    Cita c;
    if (idx == -1) return c;
    GestorArchivos::leerRegistroPorIndice(Rutas::CITAS, idx, (void*)&c, Cita::obtenerTamano());
    return c;
}

// Buscar cita por ID interactivo
void buscarCitaPorID() {
    int id; std::cout << "Ingrese ID de la cita: "; std::cin >> id;
    Cita c = leerCitaPorID(id);
    if (c.getId() == 0 || c.getEliminado()) {
        std::cout << "Cita no encontrada.\n";
        return;
    }
    c.mostrarInformacionCompleta();
}

// Listar citas activas
void listarCitasActivas() {
    std::cout << "=== Lista de Citas Activas ===\n";

    auto mostrarCita = [](const void* registro) {
        const Cita* c = reinterpret_cast<const Cita*>(registro);
        c->mostrarInformacionBasica();
    };

    GestorArchivos::listarRegistrosActivos(Rutas::CITAS, Cita::obtenerTamano(), mostrarCita);
}

// Cancelar cita interactivo
void cancelarCitaInteractivo() {
    int id;
    std::cout << "ID de la cita a cancelar: ";
    std::cin >> id;
    Cita c = leerCitaPorID(id);
    if (c.getId() == 0 || c.getEliminado()) {
        std::cout << "Cita no encontrada.\n";
        return;
    }
    c.cancelar();

    int idx = GestorArchivos::buscarIndicePorID(Rutas::CITAS, c.getId(), Cita::obtenerTamano());
    if (idx != -1 && GestorArchivos::actualizarRegistro(Rutas::CITAS, (void*)&c, Cita::obtenerTamano(), idx)) {
        std::cout << "Cita cancelada.\n";
    } else {
        std::cout << "Error al cancelar.\n";
    }
}

// Marcar cita como atendida
void marcarCitaAtendidaInteractivo() {
    int id;
    std::cout << "ID de la cita a marcar como atendida: ";
    std::cin >> id;
    Cita c = leerCitaPorID(id);
    if (c.getId() == 0 || c.getEliminado()) {
        std::cout << "Cita no encontrada.\n";
        return;
    }
    c.marcarComoAtendida();

    int idx = GestorArchivos::buscarIndicePorID(Rutas::CITAS, c.getId(), Cita::obtenerTamano());
    if (idx != -1 && GestorArchivos::actualizarRegistro(Rutas::CITAS, (void*)&c, Cita::obtenerTamano(), idx)) {
        std::cout << "Cita marcada como atendida.\n";
    } else {
        std::cout << "Error al actualizar.\n";
    }
}

//OPERACIONES HISTORIAL MEDICO
#ifndef OPERACIONES_HISTORIAL_HPP
#define OPERACIONES_HISTORIAL_HPP

#include "../historial/HistorialMedico.hpp"
#include "../persistencia/GestorArchivos.hpp"
#include "../persistencia/Constantes.hpp"
#include "../utilidades/Validaciones.hpp"
#include <iostream>

// Operaciones principales
void registrarHistorialInteractivo();
HistorialMedico leerHistorialPorID(int id);
void buscarHistorialPorID();
void listarHistorialesActivos();

#endif
#include "operacionesHistorial.hpp"

// Registrar historial interactivo
void registrarHistorialInteractivo() {
    HistorialMedico h;
    char buffer[200];

    int idPaciente, idDoctor;
    std::cout << "ID del paciente: "; std::cin >> idPaciente; h.setIdPaciente(idPaciente);
    std::cout << "ID del doctor: "; std::cin >> idDoctor; h.setDoctorID(idDoctor);
    std::cin.ignore();

    std::cout << "Fecha (YYYY-MM-DD): "; std::cin.getline(buffer, 11); h.setFecha(buffer);
    std::cout << "Hora (HH:MM): "; std::cin.getline(buffer, 6); h.setHora(buffer);
    std::cout << "Diagnóstico: "; std::cin.getline(buffer, 200); h.setDiagnostico(buffer);
    std::cout << "Tratamiento: "; std::cin.getline(buffer, 200); h.setTratamiento(buffer);
    std::cout << "Medicamentos: "; std::cin.getline(buffer, 150); h.setMedicamentos(buffer);

    float costo; std::cout << "Costo: "; std::cin >> costo; h.setCosto(costo);
    std::cin.ignore();

    h.setEliminado(false);

    // Asignar ID desde header
    ArchivoHeader header = GestorArchivos::leerHeader(Rutas::HISTORIALES);
    h.setId(header.proximoID);

    // Guardar
    if (GestorArchivos::guardarRegistro(Rutas::HISTORIALES, (void*)&h, HistorialMedico::obtenerTamano())) {
        std::cout << "Historial registrado con ID: " << h.getId() << "\n";
    } else {
        std::cout << "Error al registrar historial.\n";
    }
}

// Leer historial por ID
HistorialMedico leerHistorialPorID(int id) {
    int idx = GestorArchivos::buscarIndicePorID(Rutas::HISTORIALES, id, HistorialMedico::obtenerTamano());
    HistorialMedico h;
    if (idx == -1) return h;
    GestorArchivos::leerRegistroPorIndice(Rutas::HISTORIALES, idx, (void*)&h, HistorialMedico::obtenerTamano());
    return h;
}

// Buscar historial por ID interactivo
void buscarHistorialPorID() {
    int id; std::cout << "Ingrese ID del historial: "; std::cin >> id;
    HistorialMedico h = leerHistorialPorID(id);
    if (h.getId() == 0 || h.getEliminado()) {
        std::cout << "Historial no encontrado.\n";
        return;
    }
    h.mostrarInformacionCompleta();
}

// Listar historiales activos
void listarHistorialesActivos() {
    std::cout << "=== Lista de Historiales Médicos Activos ===\n";

    auto mostrarHistorial = [](const void* registro) {
        const HistorialMedico* h = reinterpret_cast<const HistorialMedico*>(registro);
        h->mostrarInformacionBasica();
    };

    GestorArchivos::listarRegistrosActivos(Rutas::HISTORIALES, HistorialMedico::obtenerTamano(), mostrarHistorial);
}

#include "hospital/Hospital.hpp"
#include "pacientes/operacionesPacientes.hpp"
#include "doctores/operacionesDoctores.hpp"
#include "citas/operacionesCitas.hpp"
#include "historial/operacionesHistorial.hpp"
#include "persistencia/GestorArchivos.hpp"
#include "persistencia/Constantes.hpp"
#include <iostream>
#include <locale.h>

// Menús
void mostrarMenuPrincipal();
void menuPacientes(Hospital& hospital);
void menuDoctores(Hospital& hospital);
void menuCitas(Hospital& hospital);
void menuHistorial();


// ================= MENÚS =================
void mostrarMenuPrincipal() {
    cout << "\n=== SISTEMA DE GESTIÓN HOSPITALARIA v3 ===\n";
    cout << "1. Gestión de Pacientes\n";
    cout << "2. Gestión de Doctores\n";
    cout << "3. Gestión de Citas\n";
    cout << "4. Historial Médico\n";
    cout << "5. Salir\n";
    cout << "Opción: ";
}

void menuPacientes(Hospital& hospital) {
    int opcion;
    do {
        cout << "\n=== GESTIÓN DE PACIENTES ===\n";
        cout << "1. Registrar nuevo paciente\n";
        cout << "2. Buscar por ID\n";
        cout << "3. Buscar por cédula\n";
        cout << "4. Buscar por nombre\n";
        cout << "5. Modificar datos\n";
        cout << "6. Eliminar\n";
        cout << "7. Listar todos\n";
        cout << "8. Volver\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                char cedula[20];
                cout << "Ingrese cédula: "; cin.getline(cedula, 20);
                registrarPacienteInteractivo(cedula);
                break;
            }
            case 2: buscarPacientePorID(); break;
            case 3: {
                char cedula[20];
                cout << "Ingrese cédula: "; cin.getline(cedula, 20);
                Paciente p = buscarPacientePorCedula(cedula);
                if (p.getId() == -1) cout << "No encontrado.\n";
                else p.mostrarInformacionCompleta();
                break;
            }
            case 4: {
                char fragmento[50];
                cout << "Ingrese fragmento de nombre: "; cin.getline(fragmento, 50);
                buscarPacientesPorNombre(fragmento);
                break;
            }
            case 5: actualizarPacienteInteractivo(); break;
            case 6: eliminarPacienteInteractivo(); break;
            case 7: listarPacientesActivos(); break;
            case 8: cout << "Volviendo...\n"; break;
            default: cout << "Opción inválida.\n";
        }
    } while (opcion != 8);
}

void menuDoctores(Hospital& hospital) {
    int opcion;
    do {
        cout << "\n=== GESTIÓN DE DOCTORES ===\n";
        cout << "1. Registrar nuevo doctor\n";
        cout << "2. Buscar por ID\n";
        cout << "3. Buscar por especialidad\n";
        cout << "4. Modificar datos\n";
        cout << "5. Eliminar\n";
        cout << "6. Listar todos\n";
        cout << "7. Volver\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: registrarDoctorInteractivo(); break;
            case 2: buscarDoctorPorID(); break;
            case 3: {
                char esp[50];
                cout << "Ingrese especialidad: "; cin.getline(esp, 50);
                buscarDoctoresPorEspecialidad(esp);
                break;
            }
            case 4: actualizarDoctorInteractivo(); break;
            case 5: eliminarDoctorInteractivo(); break;
            case 6: listarDoctoresActivos(); break;
            case 7: cout << "Volviendo...\n"; break;
            default: cout << "Opción inválida.\n";
        }
    } while (opcion != 7);
}

void menuCitas(Hospital& hospital) {
    int opcion;
    do {
        cout << "\n=== GESTIÓN DE CITAS ===\n";
        cout << "1. Agendar cita\n";
        cout << "2. Buscar por ID\n";
        cout << "3. Cancelar cita\n";
        cout << "4. Marcar como atendida\n";
        cout << "5. Listar todas\n";
        cout << "6. Volver\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: agendarCitaInteractivo(); break;
            case 2: buscarCitaPorID(); break;
            case 3: cancelarCitaInteractivo(); break;
            case 4: marcarCitaAtendidaInteractivo(); break;
            case 5: listarCitasActivas(); break;
            case 6: cout << "Volviendo...\n"; break;
            default: cout << "Opción inválida.\n";
        }
    } while (opcion != 6);
}

void menuHistorial() {
    int opcion;
    do {
        cout << "\n=== HISTORIAL MÉDICO ===\n";
        cout << "1. Registrar historial\n";
        cout << "2. Buscar por ID\n";
        cout << "3. Listar todos\n";
        cout << "4. Volver\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: registrarHistorialInteractivo(); break;
            case 2: buscarHistorialPorID(); break;
            case 3: listarHistorialesActivos(); break;
            case 4: cout << "Volviendo...\n"; break;
            default: cout << "Opción inválida.\n";
        }
    } while (opcion != 4);
}

int main() {
    setlocale(LC_ALL, "");

    // Inicializar archivos si no existen
    const char* archivos[] = { Rutas::HOSPITAL, Rutas::PACIENTES, Rutas::DOCTORES, Rutas::CITAS, Rutas::HISTORIALES };
    for (int i = 0; i < 5; ++i) {
        if (!GestorArchivos::verificarArchivo(archivos[i])) {
            cout << "Inicializando archivo: " << archivos[i] << "\n";
            GestorArchivos::inicializarArchivo(archivos[i]);
        }
    }

    // Crear hospital por defecto
    Hospital hospital("Hospital Universitario de Caracas",
                      "Av. Minerva, UCV Caracas, Distrito Capital (Venezuela), 1040",
                      "04126067652");

    int opcion;
    do {
        mostrarMenuPrincipal();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: menuPacientes(hospital); break;
            case 2: menuDoctores(hospital); break;
            case 3: menuCitas(hospital); break;
            case 4: menuHistorial(); break;
            case 5: cout << "Guardando y saliendo...\n"; break;
            default: cout << "Opción inválida.\n";
        }
    } while (opcion != 5);

    return 0;
}

