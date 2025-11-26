#ifndef CONSTANTES_HPP
#define CONSTANTES_HPP

const char FILE_HOSPITAL[]    = "hospital.bin";
const char FILE_PACIENTES[]   = "pacientes.bin";
const char FILE_DOCTORES[]    = "doctores.bin";
const char FILE_CITAS[]       = "citas.bin";
const char FILE_HISTORIALES[] = "historiales.bin";

struct ArchivoHeader {
    int cantidadRegistros;
    int siguienteId;
    int registrosActivos;
    int version;
};

#endif // CONSTANTES_HPP
