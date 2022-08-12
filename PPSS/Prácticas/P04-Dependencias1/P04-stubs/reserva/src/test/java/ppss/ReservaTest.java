package ppss;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import ppss.excepciones.ReservaException;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

class ReservaTest {

    OperacionStub opStub;
    ReservaTestable sut;

    @BeforeEach
    void setup() {
        opStub = new OperacionStub();
        sut = new ReservaTestable();

        // inyección
        Factoria.setServicio(opStub);
    }

    @Test
    void realizaReservaC1() {

        // preparar datos de entrada
        String login = "xxxx";
        String password = "xxxx";
        String socio = "Luis";
        String [] isbns = {"11111"};

        sut.setPermisos(false); // compruebaPermisos
        opStub.setSocio(socio);
        ArrayList<String> isbns_registrado = new ArrayList<>();
        isbns_registrado.add("11111");
        opStub.setIsbn(isbns_registrado);
        // no se invoca a método reserva()

        // resultado esperado
        String mensajeEsperado = "ERROR de permisos; ";

        ReservaException exception = assertThrows(ReservaException.class,
                () -> sut.realizaReserva(login,password,socio,isbns));

        // verificamos / informe
        assertEquals(mensajeEsperado, exception.getMessage());
    }

    @Test
    void realizaReservaC2() {

        // preparar datos de entrada
        String login = "ppss";
        String password = "ppss";
        String socio = "Luis";
        String [] isbns = {"11111", "22222"};

        sut.setPermisos(true); // compruebaPermisos
        opStub.setSocio(socio);
        ArrayList<String> isbns_registrado = new ArrayList<>();
        isbns_registrado.add("11111");
        isbns_registrado.add("22222");
        opStub.setIsbn(isbns_registrado);
        opStub.setBd_inactiva(false);

        // resultado esperado : No se lanza excepción

        assertDoesNotThrow(() -> sut.realizaReserva(login,password,socio,isbns), "Excepción lanzada");

    }

    @Test
    void realizaReservaC3() {
        // preparar datos de entrada
        String login = "ppss";
        String password = "ppss";
        String socio = "Luis";
        String [] isbns = {"33333"};

        sut.setPermisos(true); // compruebaPermisos
        opStub.setSocio(socio);
        opStub.setBd_inactiva(false);

        // resultado esperado
        String mensajeEsperado = "ISBN invalido:" + isbns[0].toString() + "; ";

        ReservaException exception = assertThrows(ReservaException.class,
                () -> sut.realizaReserva(login,password,socio,isbns));

        // verificamos / informe
        assertEquals(mensajeEsperado, exception.getMessage());
    }

    @Test
    void realizaReservaC4() {
        // preparar datos de entrada
        String login = "ppss";
        String password = "ppss";
        String socio = "Pepe";
        String [] isbns = {"11111"};

        sut.setPermisos(true); // compruebaPermisos
        opStub.setBd_inactiva(false);
        ArrayList<String> isbns_registrado = new ArrayList<>();
        isbns_registrado.add("11111");
        opStub.setIsbn(isbns_registrado);

        // resultado esperado
        String mensajeEsperado = "SOCIO invalido; ";

        ReservaException exception = assertThrows(ReservaException.class,
                () -> sut.realizaReserva(login,password,socio,isbns));

        // verificamos / informe
        assertEquals(mensajeEsperado, exception.getMessage());
    }

    @Test
    void realizaReservaC5() {
        // preparar datos de entrada
        String login = "ppss";
        String password = "ppss";
        String socio = "Luis";
        String [] isbns = {"11111"};

        sut.setPermisos(true); // compruebaPermisos
        opStub.setBd_inactiva(true); // invalidar conexión
        ArrayList<String> isbns_registrado = new ArrayList<>();
        isbns_registrado.add("11111");
        opStub.setIsbn(isbns_registrado);
        opStub.setSocio(socio);

        // resultado esperado
        String mensajeEsperado = "CONEXION invalida; ";

        ReservaException exception = assertThrows(ReservaException.class,
                () -> sut.realizaReserva(login,password,socio,isbns));

        // verificamos / informe
        assertEquals(mensajeEsperado, exception.getMessage());
    }
}