package ppss;

import org.easymock.EasyMock;
import org.easymock.IMocksControl;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.easymock.EasyMock.partialMockBuilder;
import static org.junit.jupiter.api.Assertions.*;

class PremioTest {

    private Premio mockPremio;
    private ClienteWebService mockCliente;
    IMocksControl ctrl;
    String resultadoEsperado, resultadoReal, premio;

    @BeforeEach
    public void setup() {
        ctrl = EasyMock.createStrictControl();
        mockPremio = partialMockBuilder(Premio.class)
                .addMockedMethod("generaNumero").mock(ctrl);
        mockCliente = ctrl.mock(ClienteWebService.class);
        // inyectamos el doble
        mockPremio.cliente = mockCliente;
    }

    @Test
    void compruebaPremio_A() {

        // preparar datos de entrada
        premio = "entrada final Champions";
        resultadoEsperado = "Premiado con entrada final Champions";
        float rand = 0.07f;

        // creamos mocks --> en @BeforeEach

        // preparamos las expectativas
        EasyMock.expect(mockPremio.generaNumero()).andReturn(rand);
        assertDoesNotThrow(() -> EasyMock.expect(mockCliente.obtenerPremio()).andReturn(premio));

        // activamos el mock
        ctrl.replay();

        // invocamos al SUT
        resultadoReal = mockPremio.compruebaPremio();

        // verificamos que nuestra SUT ha invocado a los mocks
        ctrl.verify();

        // informe
        assertEquals(resultadoEsperado, resultadoReal);
    }

    @Test
    void compruebaPremio_B() {

        // preparar datos de entrada
        resultadoEsperado = "No se ha podido obtener el premio";
        float rand = 0.03f;

        // creamos mocks --> en @BeforeEach

        // preparamos las expectativas
        EasyMock.expect(mockPremio.generaNumero()).andReturn(rand);
        assertDoesNotThrow(() -> EasyMock.expect(mockCliente.obtenerPremio())
                .andThrow(new ClienteWebServiceException()), "Excepción lanzada");

        // activamos el mock
        ctrl.replay();

        // invocamos al SUT
        resultadoReal = mockPremio.compruebaPremio();

        // verificamos que nuestra SUT ha invocado a los mocks
        ctrl.verify();

        // informe
        assertEquals(resultadoEsperado, resultadoReal);
    }

    @Test
    void compruebaPremio_C() {

        // preparar datos de entrada
        resultadoEsperado = "Sin premio";
        float rand = 0.3f;

        // creamos mocks --> en @BeforeEach

        // preparamos las expectativas
        EasyMock.expect(mockPremio.generaNumero()).andReturn(rand);

        // activamos el mock
        ctrl.replay();

        // invocamos al SUT
        resultadoReal = mockPremio.compruebaPremio();

        // verificamos que nuestra SUT ha invocado a los mocks
        ctrl.verify();

        // informe
        assertEquals(resultadoEsperado, resultadoReal);
    }
}