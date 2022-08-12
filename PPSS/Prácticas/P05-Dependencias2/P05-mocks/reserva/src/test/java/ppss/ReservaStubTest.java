package ppss;

import org.easymock.EasyMock;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import ppss.excepciones.IsbnInvalidoException;
import ppss.excepciones.JDBCException;
import ppss.excepciones.ReservaException;
import ppss.excepciones.SocioInvalidoException;

import static org.easymock.EasyMock.*;
import static org.junit.jupiter.api.Assertions.*;

class ReservaStubTest {

    private Reserva reservaStub;
    private FactoriaBOs factoriaStub;
    private IOperacionBO operacionStub;

    String login, password, socio;
    String[] isbns;

    @BeforeEach
    public void setup() {
        reservaStub = EasyMock.partialMockBuilder(Reserva.class)
                .addMockedMethod("compruebaPermisos").niceMock();
        factoriaStub = EasyMock.niceMock(FactoriaBOs.class);
        reservaStub.setFd(factoriaStub);
        operacionStub = EasyMock.niceMock(IOperacionBO.class);
    }

    @Test
    void realizaReserva_C1() {
        // preparar datos de entrada
        login = "xxxx";
        password = "xxxx";
        socio = "Pepe";
        isbns = new String[]{"11111"};

        // crear dobles --> @BeforeEach

        // programar las expectativas
        EasyMock.expect(reservaStub.compruebaPermisos(anyString(), anyString(), anyObject())).andStubReturn(false);
        // no se invoca a io.operacionReserva()

        // activamos el stub
        EasyMock.replay(reservaStub);

        // invocamos al SUT
        ReservaException exception = assertThrows(ReservaException.class,
                () -> reservaStub.realizaReserva(login, password, socio, isbns));

        // resultado esperado
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

        // crear doble --> @BeforeEach

        // programar las expectativas
        EasyMock.expect(reservaStub.compruebaPermisos(anyString(), anyString(), anyObject())).andStubReturn(true);
        EasyMock.expect(factoriaStub.getOperacionBO()).andStubReturn(operacionStub);
        assertDoesNotThrow(() -> operacionStub.operacionReserva(socio, isbns[0]));

        // activamos el stub
        EasyMock.replay(reservaStub, factoriaStub, operacionStub);

        // invocamos al SUT
        assertDoesNotThrow(() -> reservaStub.realizaReserva(login, password, socio, isbns));

        // resultado esperado
        // informe

    }

    @Test
    void realizaReserva_C3() {
        // preparar datos de entrada
        login = "ppss";
        password = "ppss";
        socio = "Pepe";
        isbns = new String[]{"11111"};

        // crear dobles --> @BeforeEach

        // programar las expectativas
        EasyMock.expect(reservaStub.compruebaPermisos(anyString(), anyString(), anyObject())).andStubReturn(true);
        EasyMock.expect(factoriaStub.getOperacionBO()).andStubReturn(operacionStub);
        assertDoesNotThrow(() -> operacionStub.operacionReserva(socio, isbns[0]));
        EasyMock.expectLastCall().andStubThrow(new IsbnInvalidoException());

        // activamos el stub
        EasyMock.replay(reservaStub, factoriaStub, operacionStub);

        // invocamos al SUT
        ReservaException exception = assertThrows(ReservaException.class,
                () -> reservaStub.realizaReserva(login, password, socio, isbns));

        // resultado esperado
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

        // crear dobles --> @BeforeEach

        // programar las expectativas
        EasyMock.expect(reservaStub.compruebaPermisos(anyString(), anyString(), anyObject())).andStubReturn(true);
        EasyMock.expect(factoriaStub.getOperacionBO()).andStubReturn(operacionStub);
        assertDoesNotThrow(() -> operacionStub.operacionReserva(socio, isbns[0]));
        EasyMock.expectLastCall().andStubThrow(new SocioInvalidoException());

        // activamos el stub
        EasyMock.replay(reservaStub, factoriaStub, operacionStub);

        // invocamos al SUT
        ReservaException exception = assertThrows(ReservaException.class,
                () -> reservaStub.realizaReserva(login, password, socio, isbns));

        // resultado esperado
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

        // crear dobles --> @BeforeEach

        // programar las expectativas
        EasyMock.expect(reservaStub.compruebaPermisos(anyString(), anyString(), anyObject())).andStubReturn(true);
        EasyMock.expect(factoriaStub.getOperacionBO()).andStubReturn(operacionStub);
        assertDoesNotThrow(() -> operacionStub.operacionReserva(socio, isbns[0]));
        EasyMock.expectLastCall().andStubThrow(new IsbnInvalidoException());
        assertDoesNotThrow(() -> operacionStub.operacionReserva(socio, isbns[1]));
        EasyMock.expectLastCall();
        assertDoesNotThrow(() -> operacionStub.operacionReserva(socio, isbns[2]));
        EasyMock.expectLastCall().andStubThrow(new JDBCException());

        // activamos el stub
        EasyMock.replay(reservaStub, factoriaStub, operacionStub);

        // invocamos al SUT
        ReservaException exception = assertThrows(ReservaException.class,
                () -> reservaStub.realizaReserva(login, password, socio, isbns));

        // resultado esperado
        String mensajeEsperado = "ISBN invalido:" + isbns[0] + "; CONEXION invalida; ";

        // informe
        assertEquals(mensajeEsperado, exception.getMessage());
    }
}