#include "hospital/hospital.hpp" 
#include "pacientes/operacionespacientes.hpp" 
#include "doctores/operacionesdoctores.hpp" 
#include "citas/operacionescitas.hpp" 
#include "persistencia/gestorarchivos.hpp" 
#include "persistencia/constantes.hpp" 
#include "utilidades/validaciones.hpp" 
 
using namespace std; 
 
// Declaraciones de funciones 
void mostrarMenuPrincipal(); 
void menuPacientes(Hospital& hospital); 
void menuDoctores(Hospital& hospital); 
void menuCitas(Hospital& hospital); 
void menuMantenimiento(Hospital& hospital); 
Paciente capturarDatosPaciente(); 
Doctor capturarDatosDoctor(); 
Cita capturarDatosCita(); 
Hospital inicializarHospital(); 
 
int main() { 
   Hospital hospital = inicializarHospital(); 
   
   int opcion; 
   do { 
       mostrarMenuPrincipal(); 
       cin >> opcion; 
       GestorArchivos::limpiarBuffer(); 
       
       switch(opcion) { 
 
           case 1: 
               menuPacientes(hospital); 
               break; 
           case 2: 
               menuDoctores(hospital); 
               break; 
           case 3: 
               menuCitas(hospital); 
               break; 
           case 4: 
               menuMantenimiento(hospital); 
               break; 
           case 5: 
               cout << "Saliendo del sistema..." << endl; 
               break; 
           default: 
               cout << "Opci�n inv�lida" << endl; 
       } 
   } while (opcion != 5); 
   
   return 0; 
} 
 
void mostrarMenuPrincipal() { 
   cout << "\n=== SISTEMA HOSPITALARIO ===" << endl; 
   cout << "1. Pacientes" << endl; 
   cout << "2. Doctores" << endl; 
   cout << "3. Citas" << endl; 
   cout << "4. Mantenimiento" << endl; 
   cout << "5. Salir" << endl; 
   cout << "Opcion: "; 
} 
Hospital inicializarHospital() { 
   Hospital hospital; 
   ifstream archivo(FILE_HOSPITAL, ios::binary); 
   if (!archivo.is_open()) { 
       cout << "Inicializando sistema hospitalario por primera vez..." << endl; 
       hospital.setNombre("Hospital Coco 2"); 
       hospital.setDireccion(""); 
       hospital.setTelefono(""); 
       
       // Inicializar archivos si no existen 
       GestorArchivos::inicializarArchivo(FILE_PACIENTES); 
       GestorArchivos::inicializarArchivo(FILE_DOCTORES); 
       GestorArchivos::inicializarArchivo(FILE_CITAS); 
 
       GestorArchivos::inicializarArchivo(FILE_HISTORIALES); 
       GestorArchivos::guardarHospital(hospital); 
       
       return hospital; 
   } 
   
   archivo.read(reinterpret_cast<char*>(&hospital), sizeof(Hospital)); 
   archivo.close(); 
   return hospital; 
} 
 
Paciente capturarDatosPaciente() { 
   Paciente p; 
   char buffer[100]; 
   
   cout << "Nombre: "; 
   cin.getline(buffer, 100); 
   p.setNombre(buffer); 
   
   cout << "Apellido: "; 
   cin.getline(buffer, 100); 
   p.setApellido(buffer); 
   
   cout << "C�dula: "; 
   cin.getline(buffer, 100); 
   p.setCedula(buffer); 
   
   cout << "Edad: "; 
   int edad; 
   cin >> edad; 
   p.setEdad(edad); 
   GestorArchivos::limpiarBuffer(); 
   
   cout << "Sexo (M/F): "; 
   char sexo; 
   cin >> sexo; 
   p.setSexo(sexo); 
   GestorArchivos::limpiarBuffer(); 
   
   cout << "Tel�fono (opcional): "; 
   cin.getline(buffer, 100); 
   p.setTelefono(buffer); 
   
   cout << "Email (opcional): "; 
   cin.getline(buffer, 100); 
 
   p.setEmail(buffer); 
   
   return p; 
} 
 
Doctor capturarDatosDoctor() { 
   Doctor d; 
   char buffer[100]; 
   
   cout << "Nombre: "; 
   cin.getline(buffer, 100); 
   d.setNombre(buffer); 
   
   cout << "Apellido: "; 
   cin.getline(buffer, 100); 
   d.setApellido(buffer); 
   
   cout << "C�dula profesional: "; 
   cin.getline(buffer, 100); 
   
   cout << "Especialidad: "; 
   cin.getline(buffer, 100); 
   d.setEspecialidad(buffer); 
   
   cout << "A�os de experiencia: "; 
   int experiencia; 
   cin >> experiencia; 
   d.setAniosExperiencia(experiencia); 
   GestorArchivos::limpiarBuffer(); 
   
   cout << "Costo de consulta: "; 
   float costo; 
   cin >> costo; 
   d.setCostoConsulta(costo); 
   GestorArchivos::limpiarBuffer(); 
   
   cout << "Tel�fono (opcional): "; 
   cin.getline(buffer, 100); 
   d.setTelefono(buffer); 
   
   return d; 
} 
 
Cita capturarDatosCita() { 
   Cita c; 
 
   char buffer[100]; 
   
   cout << "ID del Paciente: "; 
   int pacienteID; 
   cin >> pacienteID; 
   c.setPacienteID(pacienteID); 
   GestorArchivos::limpiarBuffer(); 
   
   cout << "ID del Doctor: "; 
   int doctorID; 
   cin >> doctorID; 
   c.setDoctorID(doctorID); 
   GestorArchivos::limpiarBuffer(); 
   
   cout << "Fecha (YYYY-MM-DD): "; 
   cin.getline(buffer, 100); 
   c.setFecha(buffer); 
   
   cout << "Hora (HH:MM): "; 
   cin.getline(buffer, 100); 
   c.setHora(buffer); 
   
   cout << "Motivo: "; 
   cin.getline(buffer, 100); 
   c.setMotivo(buffer); 
   
   return c; 
} 
 
void menuPacientes(Hospital& hospital) { 
   int opcion; 
   do { 
       cout << "\n=== GESTION DE PACIENTES ===" << endl; 
       cout << "1. Registrar paciente" << endl; 
       cout << "2. Buscar por ID" << endl; 
       cout << "3. Buscar por cedula" << endl; 
       cout << "4. Listar todos" << endl; 
       cout << "5. Actualizar" << endl; 
       cout << "6. Eliminar" << endl; 
       cout << "0. Volver" << endl; 
       cout << "Opcion: "; 
       cin >> opcion; 
       GestorArchivos::limpiarBuffer(); 
       
       switch(opcion) { 
 
           case 1:{ 
   cout << "\n=== REGISTRAR NUEVO PACIENTE ===" << endl; 
   
   // Crear nuevo paciente 
   Paciente nuevoPaciente; 
   char buffer[100]; 
   
   // Capturar datos 
   cout << "Nombre: "; 
   cin.getline(buffer, 100); 
   nuevoPaciente.setNombre(buffer); 
   
   cout << "Apellido: "; 
   cin.getline(buffer, 100); 
   nuevoPaciente.setApellido(buffer); 
   
   cout << "C�dula: "; 
   cin.getline(buffer, 100); 
   nuevoPaciente.setCedula(buffer); 
   
   cout << "Edad: "; 
   int edad; 
   cin >> edad; 
   nuevoPaciente.setEdad(edad); 
   cin.ignore();  // Limpiar buffer 
   
   cout << "Sexo (M/F): "; 
   char sexo; 
   cin >> sexo; 
   nuevoPaciente.setSexo(sexo); 
   cin.ignore(); 
   
   cout << "Tel�fono: "; 
   cin.getline(buffer, 100); 
   nuevoPaciente.setTelefono(buffer); 
   
   cout << "Email: "; 
   cin.getline(buffer, 100); 
   nuevoPaciente.setEmail(buffer); 
   
   // Validar y guardar 
   if (OperacionesPacientes::existePacienteConCedula(nuevoPaciente.getCedula())) { 
       cout << "? Error: Ya existe un paciente con esta c�dula" << endl; 
   } else if (OperacionesPacientes::agregarPaciente(nuevoPaciente)) { 
       hospital.incrementarPacientesRegistrados(); 
 
       cout << " ? Paciente registrado correctamente" << endl; 
   } else { 
       cout << "? Error al registrar paciente" << endl; 
   } 
   break; 
} 
           case 2: { 
               cout << "\n=== BUSCAR POR ID ===" << endl; 
               int id; 
               cout << "ID: "; 
               cin >> id; 
               cin.ignore(); 
               // Aqu� ir�a la b�squeda 
               cout << "Buscar paciente con ID: " << id << endl; 
               break; 
           } 
           case 3: { 
                  cout << "\n=== BUSCAR POR CEDULA ===" << endl; 
               char cedula[20]; 
               cout << "C�dula: "; 
               cin.getline(cedula, 20); 
               
               Paciente paciente = 
OperacionesPacientes::buscarPacientePorCedula(cedula); 
               if (paciente.getId() != 0) { 
                   cout << "\n--- PACIENTE ENCONTRADO ---" << endl; 
                   cout << "ID: " << paciente.getId() << endl; 
                   cout << "Nombre: " << paciente.getNombre() << " " << 
paciente.getApellido() << endl; 
                   cout << "C�dula: " << paciente.getCedula() << endl; 
                   cout << "Edad: " << paciente.getEdad() << endl; 
               } else { 
                   cout << "? Paciente no encontrado" << endl; 
               } 
               break; 
           } 
           case 4: 
               OperacionesPacientes::listarTodosPacientes(); 
               break; 
           case 5:{ 
                int id; 
               cout << "ID del paciente a actualizar: "; 
               cin >> id; 
               cin.ignore(); 
               
 
               Paciente paciente = OperacionesPacientes::buscarPacientePorID(id); 
               if (paciente.getId() == 0) { 
                   cout << " ? Paciente no encontrado" << endl; 
                   break; 
               } 
               
               cout << "Actualizando paciente: " << paciente.getNombre() << " " << 
paciente.getApellido() << endl; 
               
               char buffer[100]; 
               cout << "Nuevo nombre: "; 
               cin.getline(buffer, 100); 
               paciente.setNombre(buffer); 
               
               cout << "Nuevo apellido: "; 
               cin.getline(buffer, 100); 
               paciente.setApellido(buffer); 
               
               cout << "Nueva edad: "; 
               int edad; 
               cin >> edad; 
               paciente.setEdad(edad); 
               cin.ignore(); 
               
               if (OperacionesPacientes::actualizarPaciente(paciente)) { 
                   cout << " ? Paciente actualizado correctamente" << endl; 
               } else { 
                   cout << " ? Error al actualizar paciente" << endl; 
               } 
               break; 
           } 
           case 6:{ 
               int id; 
               cout << "ID del paciente a eliminar: "; 
               cin >> id; 
               cin.ignore(); 
               
               cout << "�Est� seguro de eliminar este paciente? (s/n): "; 
               char confirmacion; 
               cin >> confirmacion; 
               cin.ignore(); 
               
               if (confirmacion == 's' || confirmacion == 'S') { 
                   if (OperacionesPacientes::eliminarPaciente(id)) { 
                       cout << " ? Paciente eliminado correctamente" << endl; 
 
                   } else { 
                       cout << " ? Error al eliminar paciente" << endl; 
                   } 
               } else { 
                   cout << "Eliminaci�n cancelada" << endl; 
               } 
               break; 
           } 
           case 0: 
               cout << "Volviendo..." << endl; 
               break; 
           default: 
               cout << "Opcion invalida" << endl; 
       } 
   } while(opcion != 0); 
} 
void menuDoctores(Hospital& hospital) { 
   int opcion; 
   do { 
       cout << "\n=== GESTION DE DOCTORES ===" << endl; 
       cout << "1. Registrar doctor" << endl; 
       cout << "2. Buscar por ID" << endl; 
       cout << "3. Listar todos" << endl; 
       cout << "4. Listar por especialidad" << endl; 
       cout << "5. Actualizar" << endl; 
       cout << "6. Eliminar" << endl; 
       cout << "0. Volver" << endl; 
       cout << "Opcion: "; 
       cin >> opcion; 
       GestorArchivos::limpiarBuffer(); 
       
       switch(opcion) { 
           case 1:{ 
              cout << "\n=== REGISTRAR DOCTOR ===" << endl; 
               Doctor d; 
               char buffer[100]; 
               
               cout << "Nombre: "; 
               cin.getline(buffer, 100); 
               d.setNombre(buffer); 
               
               cout << "Apellido: "; 
               cin.getline(buffer, 100); 
               d.setApellido(buffer); 
               
 
               cout << "Especialidad: "; 
               cin.getline(buffer, 100); 
               d.setEspecialidad(buffer); 
               
               cout << "A�os experiencia: "; 
               int exp; 
               cin >> exp; 
               d.setAniosExperiencia(exp); 
               cin.ignore(); 
               
               cout << "Costo consulta: "; 
               float costo; 
               cin >> costo; 
               d.setCostoConsulta(costo); 
               cin.ignore(); 
               
               if (OperacionesDoctores::agregarDoctor(d)) { 
                   cout << " ? Doctor registrado!" << endl; 
               } else { 
                   cout << " ? Error al registrar" << endl; 
               } 
               break; 
           } 
           case 2:{ 
                int id; 
               cout << "ID del doctor: "; 
               cin >> id; 
               cin.ignore(); 
               
               Doctor doctor = OperacionesDoctores::buscarDoctorPorID(id); 
               if (doctor.getId() != 0) { 
                   cout << "\n--- DOCTOR ENCONTRADO ---" << endl; 
                   cout << "ID: " << doctor.getId() << endl; 
                   cout << "Nombre: " << doctor.getNombre() << " " << 
doctor.getApellido() << endl; 
                   cout << "Especialidad: " << doctor.getEspecialidad() << endl; 
                   cout << "Experiencia: " << doctor.getAniosExperiencia() << " anos" << endl; 
                   cout << "Costo: $" << doctor.getCostoConsulta() << endl; 
               } else { 
                   cout << " ? Doctor no encontrado" << endl; 
               } 
               break; 
           } 
           case 3: 
 
               OperacionesDoctores::listarTodosDoctores(); 
               break; 
           case 4:{ 
                char especialidad[50]; 
               cout << "Especialidad: "; 
               cin.getline(especialidad, 50); 
               
               Doctor resultados[100]; 
               int cantidad = 
OperacionesDoctores::buscarDoctoresPorEspecialidad(especialidad, resultados, 100); 
               OperacionesDoctores::mostrarDoctoresArray(resultados, cantidad); 
               break; 
           } 
           case 5:{ 
                 int id; 
               cout << "ID del doctor a actualizar: "; 
               cin >> id; 
               cin.ignore(); 
               
               Doctor doctor = OperacionesDoctores::buscarDoctorPorID(id); 
               if (doctor.getId() == 0) { 
                   cout << " ? Doctor no encontrado" << endl; 
                   break; 
               } 
               
               char buffer[100]; 
               cout << "Nuevo nombre: "; 
               cin.getline(buffer, 100); 
               doctor.setNombre(buffer); 
               
               cout << "Nuevo apellido: "; 
               cin.getline(buffer, 100); 
               doctor.setApellido(buffer); 
               
               cout << "Nueva especialidad: "; 
               cin.getline(buffer, 100); 
               doctor.setEspecialidad(buffer); 
               
               if (OperacionesDoctores::actualizarDoctor(doctor)) { 
                   cout << " ? Doctor actualizado correctamente" << endl; 
               } else { 
                   cout << " ? Error al actualizar doctor" << endl; 
               } 
               break; 
           } 
 
           case 6:{ 
                int id; 
               cout << "ID del doctor a eliminar: "; 
               cin >> id; 
               cin.ignore(); 
               cout << "�Est� seguro de eliminar este doctor? (s/n): "; 
               char confirmacion; 
               cin >> confirmacion; 
               cin.ignore(); 
               if (confirmacion == 's' || confirmacion == 'S') { 
                   if (OperacionesDoctores::eliminarDoctor(id)) { 
                       cout << " ? Doctor eliminado correctamente" << endl; 
                   } else { 
                       cout << " ? Error al eliminar doctor" << endl; 
                   } 
               } else { 
                   cout << "Eliminaci�n cancelada" << endl; 
               } 
               break; 
           } 
           case 0: 
               cout << "Volviendo..." << endl; 
               break; 
           default: 
               cout << "Opcion invalida" << endl; 
       } 
   } while(opcion != 0); 
} 
void menuCitas(Hospital& hospital) { 
   int opcion; 
   do { 
       cout << "\n=== GESTION DE CITAS ===" << endl; 
       cout << "1. Agendar cita" << endl; 
       cout << "2. Buscar cita" << endl; 
       cout << "3. Cancelar cita" << endl; 
       cout << "4. Atender cita" << endl; 
       cout << "5. Listar citas pendientes" << endl; 
       cout << "0. Volver" << endl; 
       cout << "Opcion: "; 
       cin >> opcion; 
       GestorArchivos::limpiarBuffer(); 
       
       switch(opcion) { 
           case 1:{ 
                  Cita c; 
 
               char buffer[100]; 
               int idPaciente, idDoctor; 
               
               cout << "ID del Paciente: "; 
               cin >> idPaciente; 
               cin.ignore(); 
               
               cout << "ID del Doctor: "; 
               cin >> idDoctor; 
               cin.ignore(); 
               
               cout << "Fecha (YYYY-MM-DD): "; 
               cin.getline(buffer, 100); 
               c.setFecha(buffer); 
               
               cout << "Hora (HH:MM): "; 
               cin.getline(buffer, 100); 
               c.setHora(buffer); 
               
               cout << "Motivo: "; 
               cin.getline(buffer, 100); 
               c.setMotivo(buffer); 
               
               c.setPacienteID(idPaciente); 
               c.setDoctorID(idDoctor); 
               c.setEstado("PENDIENTE"); 
               
               if (OperacionesCitas::agregarCita(c)) { 
                   cout << " ? Cita agendada correctamente" << endl; 
               } else { 
                   cout << "? Error al agendar cita" << endl; 
               } 
               break; 
           } 
           case 2:{ 
                 int id; 
               cout << "ID de la cita: "; 
               cin >> id; 
               cin.ignore(); 
               
               Cita cita = OperacionesCitas::buscarCitaPorID(id); 
               if (cita.getId() != 0) { 
                   cout << "\n--- CITA ENCONTRADA ---" << endl; 
                   cout << "ID: " << cita.getId() << endl; 
                   cout << "Paciente ID: " << cita.getPacienteID() << endl; 
 
                   cout << "Doctor ID: " << cita.getDoctorID() << endl; 
                   cout << "Fecha: " << cita.getFecha() << endl; 
                   cout << "Hora: " << cita.getHora() << endl; 
                   cout << "Motivo: " << cita.getMotivo() << endl; 
                   cout << "Estado: " << cita.getEstado() << endl; 
               } else { 
                   cout << "? Cita no encontrada" << endl; 
               } 
               break; 
           } 
           case 3:{ 
               int id; 
               cout << "ID de la cita a cancelar: "; 
               cin >> id; 
               cin.ignore(); 
               
               Cita cita = OperacionesCitas::buscarCitaPorID(id); 
               if (cita.getId() == 0) { 
                   cout << " ? Cita no encontrada" << endl; 
                   break; 
               } 
               
               cout << "Cita encontrada - Paciente: " << cita.getPacienteID() << ", Doctor: " << cita.getDoctorID() << endl; 
               cout << "�Est� seguro de cancelar esta cita? (s/n): "; 
               char confirmacion; 
               cin >> confirmacion; 
               cin.ignore(); 
               
               if (confirmacion == 's' || confirmacion == 'S') { 
                   if (OperacionesCitas::cancelarCita(id)) { 
                       cout << " ? Cita cancelada correctamente" << endl; 
                   } else { 
                       cout << "? Error al cancelar cita" << endl; 
                   } 
               } else { 
                   cout << "Cancelaci�n cancelada" << endl; 
               } 
               break; 
           } 
           case 4:{ 
                int id; 
               cout << "ID de la cita a atender: "; 
               cin >> id; 
               cin.ignore(); 
 
               
               Cita cita = OperacionesCitas::buscarCitaPorID(id); 
               if (cita.getId() == 0) { 
                   cout << " ? Cita no encontrada" << endl; 
                   break; 
               } 
               
               cout << "Atendiendo cita - Paciente: " << cita.getPacienteID() << 
endl; 
               
               char diagnostico[100], tratamiento[100], medicamentos[100]; 
               float costo; 
               
               cout << "Diagn�stico: "; 
               cin.getline(diagnostico, 100); 
               
               cout << "Tratamiento: "; 
               cin.getline(tratamiento, 100); 
               
               cout << "Medicamentos: "; 
               cin.getline(medicamentos, 100); 
               
               cout << "Costo de la consulta: "; 
               cin >> costo; 
               cin.ignore(); 
               
               if (OperacionesCitas::atenderCita(id, diagnostico, tratamiento, 
medicamentos, costo)) { 
                   cout << "? Cita atendida correctamente" << endl; 
               } else { 
                   cout << "?Error al atender cita" << endl; 
               } 
               break; 
           } 
           case 5:{ 
   cout << "\n=== CITAS PENDIENTES ===" << endl; 
   OperacionesCitas::listarCitasPendientes();  // 

   break; 
} 
           case 0: 
               cout << "Volviendo..." << endl; 
               break; 
           default: 
               cout << "Opcion invalida" << endl; 
       } 
 
   } while(opcion != 0); 
} 
void menuMantenimiento(Hospital& hospital) { 
   int opcion; 
   do { 
       cout << "\n=== MANTENIMIENTO ===" << endl; 
       cout << "1. Verificar archivos" << endl; 
       cout << "2. Verificar referencias" << endl; 
       cout << "3. Compactar pacientes" << endl; 
       cout << "4. Compactar doctores" << endl; 
       cout << "5. Compactar citas" << endl; 
       cout << "6. Compactar historiales" << endl; 
       cout << "7. Hacer respaldo" << endl; 
       cout << "8. Restaurar respaldo" << endl; 
       cout << "9. Ver estadisticas" << endl; 
       cout << "10. Volver" << endl; 
       cout << "Opci�n: "; 
       cin >> opcion; 
       GestorArchivos::limpiarBuffer(); 
       
       switch(opcion) { 
           case 1: 
               GestorArchivos::verificarIntegridadArchivos(); 
               break; 
           case 2: 
               GestorArchivos::verificarIntegridadReferencial(); 
               break; 
           case 3: 
               GestorArchivos::compactarArchivoPacientes(); 
               break; 
           case 4: 
               GestorArchivos::compactarArchivoDoctores(); 
               break; 
           case 5: 
               GestorArchivos::compactarArchivoCitas(); 
               break; 
           case 6: 
               GestorArchivos::compactarArchivoHistoriales(); 
               break; 
           case 7: 
               GestorArchivos::hacerRespaldo(); 
               break; 
           case 8: 
               GestorArchivos::restaurarRespaldo(); 
               break; 
case 9: 
hospital.mostrarEstadisticas(); 
GestorArchivos::mostrarEstadisticas(); 
break; 
case 10: 
cout << "Volviendo..." << endl; 
break; 
default: 
cout << "Opci�n inv�lida" << endl; 
} 
} while(opcion != 10); 
}
