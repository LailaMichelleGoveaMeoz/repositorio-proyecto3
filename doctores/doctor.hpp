#ifndef DOCTOR_HPP
#define DOCTOR_HPP

#include <ctime>   // para time_t

class Doctor {
private:
    int id;
    char nombre[50];
    char apellido[50];
    char cedula[20];
    char especialidad[50];
    int aniosExperiencia;
    float costoConsulta;
    char horarioAtencion[50];
    char telefono[15];
    char email[50];
    bool disponible;
    int cantidadPacientes;
    int cantidadCitas;
    int pacientesIDs[50];
    int citasIDs[30];
    bool eliminado;
    time_t fechaCreacion;
    time_t fechaModificacion;

public:
    // Constructor
    Doctor();

    // Getters
    int getId() const;
    const char* getNombre() const;
    const char* getApellido() const;
    const char* getEspecialidad() const;
    float getCostoConsulta() const;
    bool getDisponible() const;
    bool getEliminado() const;
    int getCantidadPacientes() const;
    int getCantidadCitas() const;
    time_t getFechaModificacion() const;
    int getAniosExperiencia() const;
    const char* getTelefono() const;

    // Setters
    void setId(int id);
    void setNombre(const char* nombre);
    void setApellido(const char* apellido);
    void setEspecialidad(const char* especialidad);
    void setCostoConsulta(float costo);
    void setDisponible(bool disp);
    void setEliminado(bool elim);
    void setFechaModificacion(time_t tiempo);
    void setFechaCreacion(time_t tiempo);
    void setAniosExperiencia(int anos);
    void setTelefono(const char* telefono);

    // Métodos de gestión
    bool agregarPacienteID(int pacienteID);
    bool agregarCitaID(int citaID);
    bool actualizarPacientesIDs(int mapaIDs[]);
    bool validarDatos() const;
    size_t obtenerTamano();
};

#endif // DOCTOR_HPP

