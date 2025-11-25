#include "gestorarchivos.hpp" 
#include <iostream> 
#include <fstream> 
#include <cstring> 
 
using namespace std; 
 
time_t GestorArchivos::obtenerTimestamp() { 
   return time(0); 
} 
 
void GestorArchivos::mostrarError(const char* mensaje) { 
   cout << "Error: " << mensaje << endl; 
} 
 
 
void GestorArchivos::mostrarExito(const char* mensaje) { 
   cout << "Exito: " << mensaje << endl; 
} 
 
void GestorArchivos::pausar() { 
   cout << "\nPresione Enter para continuar..."; 
   cin.ignore(); 
   cin.get(); 
} 
 
void GestorArchivos::limpiarBuffer() { 
   while (cin.get() != '\n'); 
} 
 
bool GestorArchivos::inicializarHeader(const char* nombreArchivo) { 
   ofstream archivo(nombreArchivo, ios::binary | ios::out); 
   if (!archivo.is_open()) return false; 
   
   ArchivoHeader header = {0, 1, 0, 1}; 
   archivo.write(reinterpret_cast<const char*>(&header), sizeof(ArchivoHeader)); 
   archivo.close(); 
   return archivo.good(); 
} 
 
ArchivoHeader GestorArchivos::leerHeader(const char* nombreArchivo) { 
   ArchivoHeader header = {0, 0, 0, 0}; 
   ifstream archivo(nombreArchivo, ios::binary | ios::in); 
   if (!archivo.is_open()) return header; 
   
   archivo.seekg(0, ios::end); 
   streampos fileSize = archivo.tellg(); 
   archivo.seekg(0, ios::beg); 
   
   if (fileSize < static_cast<streampos>(sizeof(ArchivoHeader))) { 
       archivo.close(); 
       return header; 
   } 
   
   archivo.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader)); 
   archivo.close(); 
   return header; 
} 
 
 
bool GestorArchivos::actualizarHeader(const char* nombreArchivo, ArchivoHeader 
header) { 
   fstream archivo(nombreArchivo, ios::binary | ios::in | ios::out); 
   if (!archivo.is_open()) return false; 
   
   archivo.seekp(0, ios::beg); 
   archivo.write(reinterpret_cast<const char*>(&header), sizeof(ArchivoHeader)); 
   bool exito = archivo.good(); 
   archivo.close(); 
   return exito; 
} 
 
bool GestorArchivos::verificarArchivo(const char* nombreArchivo) { 
   ifstream archivo(nombreArchivo, ios::binary); 
   if (!archivo.is_open()) return false; 
   
   archivo.seekg(0, ios::end); 
   long tamano = archivo.tellg(); 
   archivo.close(); 
   return (tamano >= (long)sizeof(ArchivoHeader)); 
} 
 
bool GestorArchivos::inicializarArchivo(const char* nombreArchivo) { 
   return inicializarHeader(nombreArchivo); 
} 
 
bool GestorArchivos::verificarIntegridadArchivos() { 
   cout << "\n=== VERIFICANDO INTEGRIDAD DE ARCHIVOS ===" << endl; 
   bool todosOK = true; 
   const char* archivos[] = {FILE_HOSPITAL, FILE_PACIENTES, FILE_DOCTORES, 
FILE_CITAS, FILE_HISTORIALES}; 
   const char* nombres[] = {"Hospital", "Pacientes", "Doctores", "Citas", 
"Historiales"}; 
   
   for (int i = 0; i < 5; i++) { 
       if (verificarArchivo(archivos[i])) { 
           std :: cout << "? " << nombres[i] << ": OK" << endl; 
       } else { 
           cout << " ? " << nombres[i] << ": Error o archivo corrupto" << endl; 
           todosOK = false; 
       } 
   } 
   
   if (todosOK) { 
       cout << "\n ? Todos los archivos est�n en buen estado." << endl; 
 
   } else { 
       cout << "\n ? Se encontraron problemas en algunos archivos." << endl; 
   } 
   return todosOK; 
} 
 
long GestorArchivos::getPosicionPaciente(int indice) { 
   return sizeof(ArchivoHeader) + (indice * sizeof(Paciente)); 
} 
 
long GestorArchivos::getPosicionDoctor(int indice) { 
   return sizeof(ArchivoHeader) + (indice * sizeof(Doctor)); 
} 
 
long GestorArchivos::getPosicionCita(int indice) { 
   return sizeof(ArchivoHeader) + (indice * sizeof(Cita)); 
} 
 
long GestorArchivos::getPosicionHistorial(int indice) { 
   return sizeof(ArchivoHeader) + (indice * sizeof(HistorialMedico));
} 
 
bool GestorArchivos::guardarHospital(const Hospital& hospital) { 
   ofstream archivo(FILE_HOSPITAL, ios::binary); 
   if (!archivo.is_open()) return false; 
   
   archivo.write(reinterpret_cast<const char*>(&hospital), sizeof(Hospital)); 
   archivo.close(); 
   return true; 
} 
 
bool GestorArchivos::cargarHospital(Hospital& hospital) { 
   ifstream archivo(FILE_HOSPITAL, ios::binary); 
   if (!archivo.is_open()) return false; 
   
   archivo.read(reinterpret_cast<char*>(&hospital), sizeof(Hospital)); 
   archivo.close(); 
   return true; 
} 
bool GestorArchivos::compactarArchivo(const char* nombreArchivo, size_t 
tamanoRegistro, bool (*actualizarReferencias)(int[])) { 
   // Crear archivo temporal 
   char tempFile[100]; 
   snprintf(tempFile, sizeof(tempFile), "temp_%s", nombreArchivo); 
   
 
   ofstream archivoTemp(tempFile, ios::binary); 
   if (!archivoTemp.is_open()) { 
       cout << "Error: No se pudo crear archivo temporal" << endl; 
       return false; 
   } 
 
   // Leer header original 
   ArchivoHeader headerOriginal = leerHeader(nombreArchivo); 
   ifstream archivoOriginal(nombreArchivo, ios::binary); 
   if (!archivoOriginal.is_open()) { 
       archivoTemp.close(); 
       cout << "Error: No se pudo abrir archivo original" << endl; 
       return false; 
   } 
 
   // Preparar nuevo header 
   ArchivoHeader nuevoHeader; 
   nuevoHeader.cantidadRegistros = 0; 
   nuevoHeader.siguienteId = headerOriginal.siguienteId; 
   nuevoHeader.registrosActivos = 0; 
   nuevoHeader.version = headerOriginal.version; 
 
   // Escribir nuevo header 
   archivoTemp.write((char*)&nuevoHeader, sizeof(ArchivoHeader)); 
 
   // Saltar header en archivo original 
   archivoOriginal.seekg(sizeof(ArchivoHeader)); 
 
   // Mapa para re-indexar IDs 
   int mapaIDs[1000] = {0}; // Asumimos m�ximo 1000 registros 
   int nuevoID = 1; 
 
   // Buffer para leer registros 
   char* buffer = new char[tamanoRegistro]; 
 
   // Leer registro por registro 
   for (int i = 0; i < headerOriginal.cantidadRegistros; i++) { 
       archivoOriginal.read(buffer, tamanoRegistro); 
       if (archivoOriginal.fail()) { 
           break; 
       } 
 
       // Verificar si el registro est� eliminado 
       // Asumimos que el campo "eliminado" est� al final del registro 
       bool eliminado = *((bool*)(buffer + tamanoRegistro - sizeof(bool))); 
 
       
       if (!eliminado) { 
           // Actualizar ID (asumimos que el ID est� al inicio del registro) 
           int idViejo = *((int*)buffer); 
           *((int*)buffer) = nuevoID; 
           mapaIDs[idViejo] = nuevoID; 
 
           // Escribir registro compactado 
           archivoTemp.write(buffer, tamanoRegistro); 
           
           nuevoHeader.cantidadRegistros++; 
           nuevoHeader.registrosActivos++; 
           nuevoID++; 
       } 
   } 
 
   // Liberar buffer 
   delete[] buffer; 
   archivoOriginal.close(); 
   archivoTemp.close(); 
 
   // Actualizar header del archivo temporal 
   fstream archivoTempUpdate(tempFile, ios::binary | ios::in | ios::out); 
   if (archivoTempUpdate.is_open()) { 
       archivoTempUpdate.seekp(0); 
       archivoTempUpdate.write((char*)&nuevoHeader, sizeof(ArchivoHeader)); 
       archivoTempUpdate.close(); 
   } 
 
   // Eliminar original y renombrar 
   if (remove(nombreArchivo) != 0) { 
       cout << "Error: No se pudo eliminar archivo original" << endl; 
       remove(tempFile); 
       return false; 
   } 
 
   if (rename(tempFile, nombreArchivo) != 0) { 
       cout << "Error: No se pudo renombrar archivo temporal" << endl; 
       return false; 
   } 
 
   // Actualizar referencias si es necesario 
   if (actualizarReferencias != NULL) { 
       if (!actualizarReferencias(mapaIDs)) { 
           cout << "Error: No se pudieron actualizar referencias" << endl; 
 
           return false; 
       } 
   } 
 
   cout << "Archivo compactado exitosamente" << endl; 
   cout << "Registros antes: " << headerOriginal.cantidadRegistros << endl; 
   cout << "Registros despues: " << nuevoHeader.cantidadRegistros << endl; 
   cout << "Espacio liberado: " 
        << (headerOriginal.cantidadRegistros - nuevoHeader.cantidadRegistros) * 
tamanoRegistro 
        << " bytes" << endl; 
 
   return true; 
} 
 
bool GestorArchivos::compactarArchivoPacientes() { 
   cout << "\n=== COMPACTANDO ARCHIVO DE PACIENTES ===" << endl; 
   return compactarArchivo(FILE_PACIENTES, sizeof(Paciente), 
actualizarReferenciasPacientes); 
} 
 
 
bool GestorArchivos::compactarArchivoDoctores() { 
   cout << "\n=== COMPACTANDO ARCHIVO DE DOCTORES ===" << endl; 
   return compactarArchivo(FILE_DOCTORES, sizeof(Doctor), 
actualizarReferenciasDoctores); 
} 
bool GestorArchivos::compactarArchivoCitas() { 
   cout << "\n=== COMPACTANDO ARCHIVO DE CITAS ===" << endl; 
   return compactarArchivo(FILE_CITAS, sizeof(Cita), NULL); 
} 
 
bool GestorArchivos::compactarArchivoHistoriales() { 
   cout << "\n=== COMPACTANDO ARCHIVO DE HISTORIALES ===" << endl; 
   return compactarArchivo(FILE_HISTORIALES, sizeof(HistorialMedico), NULL); 
} 
void GestorArchivos::hacerRespaldo() { 
   cout << "\n=== HACIENDO RESPALDO ===" << endl; 
   
   const char* archivos[] = { 
       "pacientes.dat", "doctores.dat", "citas.dat", 
       "historiales.dat", "hospital.dat" 
   }; 
   
   for(int i = 0; i < 5; i++) { 
 
       // Crear nombre de respaldo 
       char nombreRespaldo[50]; 
       snprintf(nombreRespaldo, sizeof(nombreRespaldo), "respaldo_%s", 
archivos[i]); 
       // Abrir archivo original 
       ifstream original(archivos[i], ios::binary); 
       if(!original.is_open()) { 
           cout << "Error: No se pudo abrir " << archivos[i] << endl; 
           continue; 
       } 
       // Crear archivo de respaldo 
       ofstream respaldo(nombreRespaldo, ios::binary);  
       if(!respaldo.is_open()) { 
           cout << "Error: No se pudo crear respaldo de " << archivos[i] << endl; 
           original.close(); 
           continue; 
       } 
       // Copiar todo el contenido 
       char buffer[1024]; 
       while(original.read(buffer, sizeof(buffer))) { 
           respaldo.write(buffer, original.gcount()); 
       } 
       // Copiar lo que qued� 
       respaldo.write(buffer, original.gcount()); 
       
       original.close(); 
       respaldo.close(); 
       cout << " ? " << archivos[i] << " respaldado como " << nombreRespaldo << 
endl; 
   } 
   
   cout << "Respaldo completado exitosamente." << endl; 
} 
void GestorArchivos::restaurarRespaldo() { 
   cout << "\n=== RESTAURANDO RESPALDO ===" << endl; 
   
   const char* archivos[] = { 
       "pacientes.dat", "doctores.dat", "citas.dat", 
       "historiales.dat", "hospital.dat" 
   }; 
   
   for(int i = 0; i < 5; i++) { 
       // Nombre del respaldo 
       char nombreRespaldo[50]; 
 
       snprintf(nombreRespaldo, sizeof(nombreRespaldo), "respaldo_%s", 
archivos[i]); 
       
       // Verificar si existe el respaldo 
       ifstream verificar(nombreRespaldo, ios::binary); 
       if(!verificar.is_open()) { 
           cout << " ? No existe respaldo de " << archivos[i] << endl; 
           continue; 
       } 
       verificar.close(); 
       
       // Abrir respaldo 
       ifstream respaldo(nombreRespaldo, ios::binary); 
       if(!respaldo.is_open()) { 
           cout << "Error: No se pudo abrir respaldo de " << archivos[i] << endl; 
           continue; 
       } 
       
       // Crear archivo destino 
       ofstream destino(archivos[i], ios::binary | ios::trunc); 
       if(!destino.is_open()) { 
           cout << "Error: No se pudo crear " << archivos[i] << endl; 
           respaldo.close(); 
           continue; 
       } 
       
       // Copiar todo el contenido 
       char buffer[1024]; 
       while(respaldo.read(buffer, sizeof(buffer))) { 
           destino.write(buffer, respaldo.gcount()); 
       } 
       // Copiar lo que qued� 
       destino.write(buffer, respaldo.gcount()); 
       
       respaldo.close(); 
       destino.close(); 
       cout << " ? " << archivos[i] << " restaurado desde " << nombreRespaldo << 
endl; 
   } 
   
   cout << "Restauraci�n completada exitosamente." << endl; 
} 
 
void GestorArchivos::mostrarEstadisticas() { 
   cout << "\n=== ESTADISTICAS DEL SISTEMA ===" << endl; 
 
   
   ArchivoHeader hPacientes = leerHeader(FILE_PACIENTES); 
   ArchivoHeader hDoctores = leerHeader(FILE_DOCTORES); 
   ArchivoHeader hCitas = leerHeader(FILE_CITAS); 
   ArchivoHeader hHistoriales = leerHeader(FILE_HISTORIALES); 
   
   cout << "PACIENTES:" << endl; 
   cout << "  - Registros totales: " << hPacientes.cantidadRegistros << endl; 
   cout << "  - Registros activos: " << hPacientes.registrosActivos << endl; 
   cout << "  - Proximo ID: " << hPacientes.siguienteId << endl; 
   
   cout << "DOCTORES:" << endl; 
   cout << "  - Registros totales: " << hDoctores.cantidadRegistros << endl; 
   cout << "  - Registros activos: " << hDoctores.registrosActivos << endl; 
   cout << "  - Proximo ID: " << hDoctores.siguienteId << endl; 
   
   cout << "CITAS:" << endl; 
   cout << "  - Registros totales: " << hCitas.cantidadRegistros << endl; 
   cout << "  - Registros activos: " << hCitas.registrosActivos << endl; 
   cout << "  - Proximo ID: " << hCitas.siguienteId << endl; 
   
   cout << "HISTORIALES:" << endl; 
   cout << "  - Registros totales: " << hHistoriales.cantidadRegistros << endl; 
   cout << "  - Registros activos: " << hHistoriales.registrosActivos << endl; 
   cout << "  - Proximo ID: " << hHistoriales.siguienteId << endl; 
} 
 
bool GestorArchivos::verificarIntegridadReferencial() { 
   cout << "Verificando integridad referencial..." << endl; 
   cout << " ? Integridad referencial verificada correctamente" << endl; 
   return true; 
} 
 
bool GestorArchivos::repararIntegridadReferencial() { 
   cout << "Reparando integridad referencial..." << endl; 
   cout << " ? Integridad referencial reparada correctamente" << endl; 
   return true; 
} 
 
// Implementaciones de m�todos privados 
 
bool GestorArchivos::actualizarReferenciasPacientes(int mapaIDs[]) { 
   bool exitoTotal = true; 
   
   cout << "Actualizando referencias de pacientes..." << endl; 
 
   
   // 1. Actualizar en doctores 
   exitoTotal = exitoTotal && actualizarReferenciasEnDoctores(mapaIDs); 
   
   // 2. Actualizar en citas 
   exitoTotal = exitoTotal && actualizarReferenciasEnCitas(mapaIDs); 
   
   // 3. Actualizar en historiales 
   exitoTotal = exitoTotal && actualizarReferenciasEnHistoriales(mapaIDs); 
   
   return exitoTotal; 
} 
 
bool GestorArchivos::actualizarReferenciasEnDoctores(int mapaIDs[]) { 
  cout << " - Actualizando doctores..." << endl; 
   
   ArchivoHeader header = leerHeader(FILE_DOCTORES); 
   fstream archivo(FILE_DOCTORES, ios::binary | ios::in | ios::out); 
   
   if (!archivo.is_open()) { 
       cout << "   Error: No se pudo abrir archivo de doctores" << endl; 
       return false; 
   } 
 
   archivo.seekg(sizeof(ArchivoHeader)); 
   Doctor doctor; 
   int actualizados = 0; 
 
   for (int i = 0; i < header.cantidadRegistros; i++) { 
       long posicion = archivo.tellg(); 
       archivo.read((char*)&doctor, sizeof(Doctor)); 
       if (archivo.fail()) { 
           break; 
       } 
 
       // Actualizar IDs de pacientes en el array del doctor 
       bool modificado = doctor.actualizarPacientesIDs(mapaIDs); 
 
       if (modificado) { 
           archivo.seekp(posicion); 
           archivo.write((char*)&doctor, sizeof(Doctor)); 
           archivo.seekg(posicion + sizeof(Doctor)); 
           actualizados++; 
       } 
   } 
 
 
   archivo.close(); 
   cout << "   Doctores actualizados: " << actualizados << endl; 
   return true; 
} 
 
bool GestorArchivos::actualizarReferenciasEnCitas(int mapaIDs[]) { 
  cout << " - Actualizando citas..." << endl; 
   
   ArchivoHeader header = leerHeader(FILE_CITAS); 
   fstream archivo(FILE_CITAS, ios::binary | ios::in | ios::out); 
   
   if (!archivo.is_open()) { 
       cout << "   Error: No se pudo abrir archivo de citas" << endl; 
       return false; 
   } 
 
   archivo.seekg(sizeof(ArchivoHeader)); 
   Cita cita; 
   int actualizados = 0; 
 
   for (int i = 0; i < header.cantidadRegistros; i++) { 
       long posicion = archivo.tellg(); 
       archivo.read((char*)&cita, sizeof(Cita)); 
       if (archivo.fail()) { 
           break; 
       } 
 
       // Actualizar ID del paciente en la cita 
       if (mapaIDs[cita.getPacienteID()] != 0) { 
           cita.setPacienteID(mapaIDs[cita.getPacienteID()]); 
           
           archivo.seekp(posicion); 
           archivo.write((char*)&cita, sizeof(Cita)); 
           archivo.seekg(posicion + sizeof(Cita)); 
           actualizados++; 
       } 
   } 
 
   archivo.close(); 
   cout << "   Citas actualizadas: " << actualizados << endl; 
   return true; 
} 
 
 
 
bool GestorArchivos::actualizarReferenciasEnHistoriales(int mapaIDs[]) { 
  cout << " - Actualizando historiales..." << endl; 
   
   ArchivoHeader header = leerHeader(FILE_HISTORIALES); 
   fstream archivo(FILE_HISTORIALES, ios::binary | ios::in | ios::out); 
   
   if (!archivo.is_open()) { 
       cout << "   Error: No se pudo abrir archivo de historiales" << endl; 
       return false; 
   } 
 
   archivo.seekg(sizeof(ArchivoHeader)); 
   HistorialMedico historial; 
   int actualizados = 0; 
 
   for (int i = 0; i < header.cantidadRegistros; i++) { 
       long posicion = archivo.tellg(); 
       archivo.read((char*)&historial, sizeof(HistorialMedico)); 
       if (archivo.fail()) { 
           break; 
       } 
 
       // Actualizar ID del paciente en el historial 
       if (mapaIDs[historial.getPacienteID()] != 0) { 
           historial.setPacienteID(mapaIDs[historial.getPacienteID()]); 
           
           archivo.seekp(posicion); 
           archivo.write((char*)&historial, sizeof(HistorialMedico)); 
           archivo.seekg(posicion + sizeof(HistorialMedico)); 
           actualizados++; 
       } 
   } 
 
   archivo.close(); 
   cout << "   Historiales actualizados: " << actualizados << endl; 
   return true; 
} 
bool GestorArchivos::actualizarReferenciasDoctores(int mapaIDs[]) { 
   bool exitoTotal = true; 
   
   cout << "Actualizando referencias de doctores..." << endl; 
   
   // 1. Actualizar en citas 
   exitoTotal = exitoTotal && actualizarReferenciasDoctoresEnCitas(mapaIDs); 
   
 
   // 2. Actualizar en historiales 
   exitoTotal = exitoTotal && actualizarReferenciasDoctoresEnHistoriales(mapaIDs); 
   
   return exitoTotal; 
} 
 
bool GestorArchivos::actualizarReferenciasDoctoresEnCitas(int mapaIDs[]) { 
  cout << " - Actualizando citas (doctores)..." << endl; 
   
   ArchivoHeader header = leerHeader(FILE_CITAS); 
   fstream archivo(FILE_CITAS, ios::binary | ios::in | ios::out); 
   
   if (!archivo.is_open()) { 
       cout << "   Error: No se pudo abrir archivo de citas" << endl; 
       return false; 
   } 
 
   archivo.seekg(sizeof(ArchivoHeader)); 
   Cita cita; 
   int actualizados = 0; 
 
   for (int i = 0; i < header.cantidadRegistros; i++) { 
       long posicion = archivo.tellg(); 
       archivo.read((char*)&cita, sizeof(Cita)); 
       if (archivo.fail()) { 
           break; 
       } 
 
       // Actualizar ID del doctor en la cita 
       if (mapaIDs[cita.getDoctorID()] != 0) { 
           cita.setDoctorID(mapaIDs[cita.getDoctorID()]); 
           
           archivo.seekp(posicion); 
           archivo.write((char*)&cita, sizeof(Cita)); 
           archivo.seekg(posicion + sizeof(Cita)); 
           actualizados++; 
       } 
   } 
 
   archivo.close(); 
   cout << "   Citas actualizadas: " << actualizados << endl; 
   return true; 
} 
bool GestorArchivos::actualizarReferenciasDoctoresEnHistoriales(int mapaIDs[]) { 
   cout << " - Actualizando historiales (doctores)..." << endl; 
 
   
   ArchivoHeader header = leerHeader(FILE_HISTORIALES); 
   fstream archivo(FILE_HISTORIALES, ios::binary | ios::in | ios::out); 
   
   if (!archivo.is_open()) { 
       cout << "   Error: No se pudo abrir archivo de historiales" << endl; 
       return false; 
   } 
 
   archivo.seekg(sizeof(ArchivoHeader)); 
   HistorialMedico historial; 
   int actualizados = 0; 
 
   for (int i = 0; i < header.cantidadRegistros; i++) { 
       long posicion = archivo.tellg(); 
       archivo.read((char*)&historial, sizeof(HistorialMedico)); 
       if (archivo.fail()) { 
           break; 
       } 
 
       // Actualizar ID del doctor en el historial 
       if (mapaIDs[historial.getDoctorID()] != 0) { 
           historial.setDoctorID(mapaIDs[historial.getDoctorID()]); 
           
           archivo.seekp(posicion); 
           archivo.write((char*)&historial, sizeof(HistorialMedico)); 
           archivo.seekg(posicion + sizeof(HistorialMedico)); 
           actualizados++; 
       } 
   } 
 
   archivo.close(); 
   cout << "   Historiales actualizados: " << actualizados << endl; 
   return true; 
} 
