package ppss;

import org.easymock.EasyMock;
import org.easymock.IMocksControl;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import ppss.excepciones.IsbnInvalidoException;
import ppss.excepciones.JDBCException;
import ppss.excepciones.ReservaException;
import ppss.excepciones.SocioInvalidoException;

import static org.junit.jupiter.api.Assertions.*;

class ReservaMockTest {

    private Reserva mockReserva;
    private FactoriaBOs mockFactoriaBOs;
    private IOperacionBO mockOperacion;
    IMocksControl ctrl;

    String login, password, socio;
    String[] isbns;

    @BeforeEach
    public void setup() {
        ctrl = EasyMock.createStrictControl();
        mockReserva = EasyMock.partialMockBuilder(Reserva.class)
                .addMockedMethod("compruebaPermisos").mock(ctrl);
        mockFactoriaBOs = ctrl.mock(FactoriaBOs.class);
        mockOperacion = ctrl.mock(IOperacionBO.class);
        mockReserva.setFd(mockFactoriaBOs);
    }

    @Test
    void realizaReserva_C1() {
        // preparar datos de entrada
        login = "xxxx";
        password = "xxxx";
        socio = "Pepe";
        isbns = new String[]{"11111"};

        // crear mocks --> @BeforeEach

        // preparar las expectativas
        EasyMock.expect(mockReserva.compruebaPermisos(login, password, Usuario.BIBLIOTECARIO)).andReturn(false);
        // no se invoca a io.operacionReserva()

        // activamos los mocks
        ctrl.replay();

        // invocamos a la SUT
        ReservaException exception = assertThrows(ReservaException.class,
                () -> mockReserva.realizaReserva(login, password, socio, isbns));

        // verificamos
        ctrl.verify();

        String mensajeEsperado = "ERROR de permisos; ";

        // informe
        assertEquals(mensajeEsperado, exception.getMessage());
    }

    @Test
    void realizaReserva_C2() {
        // preparar datos de entrada
        login = "ppss";
        password = "ppss";
        socio = "Pepe";
        isbns = new String[]{"22222", "33333"};

        // crear mocks --> @BeforeEach

        // preparar las expectativas
        EasyMock.expect(mockReserva.compruebaPermisos(login, password, Usuario.BIBLIOTECARIO)).andReturn(true);
        EasyMock.expect(mockFactoriaBOs.getOperacionBO()).andReturn(mockOperacion);
        assertDoesNotThrow(() -> mockOperacion.operacionReserva(socio, isbns[0]));
        assertDoesNotThrow(() -> mockOperacion.operacionReserva(socio, isbns[1]));

        // activamos los mocks
        ctrl.replay();

        // invocamos a la SUT
        assertDoesNotThrow(() ->
                mockReserva.realizaReserva(login, password, socio, isbns), "Excepción lanzada");

        // verificamos
        ctrl.verify();
    }

    @Test
    void realizaReserva_C3() {
        // preparar datos de entrada
        login = "ppss";
        password = "ppss";
        socio = "Pepe";
        isbns = new String[]{"11111"};

        // crear mocks --> @BeforeEach

        // preparar las expectativas
        EasyMock.expect(mockReserva.compruebaPermisos(login, password, Usuario.BIBLIOTECARIO)).andReturn(true);
        EasyMock.expect(mockFactoriaBOs.getOperacionBO()).andReturn(mockOperacion);
        assertDoesNotThrow(() -> mockOperacion.operacionReserva(socio, isbns[0]));
        EasyMock.expectLastCall().andThrow(new IsbnInvalidoException());

        // activamos los mocks
        ctrl.replay();

        // invocamos a la SUT
        ReservaException exception = assertThrows(ReservaException.class,
                () -> mockReserva.realizaReserva(login, password, socio, isbns));

        // verificamos
        ctrl.verify();

        String mensajeEsperado = "ISBN invalido:" + isbns[0] + "; ";

        // informe
        assertEquals(mensajeEsperado, exception.getMessage());
    }

    @Test
    void realizaReserva_C4() {
        // preparar datos de entrada
        login = "ppss";
        password = "ppss";
        socio = "Luis";
        isbns = new String[]{"22222"};

        // crear mocks --> @BeforeEach

        // preparar las expectativas
        EasyMock.expect(mockReserva.compruebaPermisos(login, password, Usuario.BIBLIOTECARIO)).andReturn(true);
        EasyMock.expect(mockFactoriaBOs.getOperacionBO()).andReturn(mockOperacion);
        assertDoesNotThrow(() -> mockOperacion.operacionReserva(socio, isbns[0]));
        EasyMock.expectLastCall().andThrow(new SocioInvalidoException());

        // activamos los mocks
        ctrl.replay();

        // invocamos a la SUT
        ReservaException exception = assertThrows(ReservaException.class,
                () -> mockReserva.realizaReserva(login, password, socio, isbns));

        // verificamos
        ctrl.verify();

        String mensajeEsperado = "SOCIO invalido; ";

        // informe
        assertEquals(mensajeEsperado, exception.getMessage());
    }

    @Test
    void realizaReserva_C5() {
        // preparar datos de entrada
        login = "ppss";
        password = "ppss";
        socio = "Pepe";
        isbns = new String[]{"11111", "22222", "33333"};

        // crear mocks --> @BeforeEach

        // preparar las expectativas
        EasyMock.expect(mockReserva.compruebaPermisos(login, password, Usuario.BIBLIOTECARIO)).andReturn(true);
        EasyMock.expect(mockFactoriaBOs.getOperacionBO()).andReturn(mockOperacion);
        assertDoesNotThrow(() -> mockOperacion.operacionReserva(socio, isbns[0]));
        EasyMock.expectLastCall().andThrow(new IsbnInvalidoException());
        assertDoesNotThrow(() -> mockOperacion.operacionReserva(socio, isbns[1]));
        assertDoesNotThrow(() -> mockOperacion.operacionReserva(socio, isbns[2]));
        EasyMock.expectLastCall().andThrow(new JDBCException());

        // activamos los mocks
        ctrl.replay();

        // invocamos a la SUT
        ReservaException exception = assertThrows(ReservaException.class,
                () -> mockReserva.realizaReserva(login, password, socio, isbns));

        // verificamos
        ctrl.verify();

        String mensajeEsperado = "ISBN invalido:" + isbns[0] + "; CONEXION invalida; ";

        // informe
        assertEquals(mensajeEsperado, exception.getMessage());
    }
}