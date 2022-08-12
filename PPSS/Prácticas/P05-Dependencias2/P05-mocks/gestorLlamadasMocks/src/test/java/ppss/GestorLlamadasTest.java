package ppss;

import org.easymock.EasyMock;

import static org.easymock.EasyMock.partialMockBuilder;
import org.easymock.IMocksControl;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class GestorLlamadasTest {
    Calendario mockCalendario;
    GestorLlamadas mockGestorLLamadas;
    IMocksControl ctrl;
    double consumoEsperado, consumoReal;
    int minutos, hora;

    @BeforeEach
    public void setup () {
        ctrl = EasyMock.createStrictControl();
        mockGestorLLamadas = partialMockBuilder(GestorLlamadas.class)
                .addMockedMethod("getCalendario").mock(ctrl);
        mockCalendario = ctrl.mock(Calendario.class);
    }

    @Test
    void calculaConsumo_C1() {

        // preparar datos de entrada
        consumoEsperado = 457.6;
        minutos = 22;
        hora = 10;

        // crear mocks --> @BeforeEach

        // preparar las expectativas
        EasyMock.expect(mockGestorLLamadas.getCalendario()).andReturn(mockCalendario);
        assertDoesNotThrow(() -> EasyMock.expect(mockCalendario.getHoraActual()).andReturn(hora));

        // activamos los mocks
        ctrl.replay();

        // invocamos a la SUT
         consumoReal = mockGestorLLamadas.calculaConsumo(minutos);

        // SIEMPRE verificar que nuestra SUT ha invocado a los mocks, si no --> throw AssertionError
        ctrl.verify();

        // informe
        assertEquals(consumoEsperado, consumoReal);

    }

    @Test
    void calculaConsumo_C2() {

        // preparar datos de entrada
        consumoEsperado = 136.5;
        minutos = 13;
        hora = 21;

        // crear mocks --> @BeforeEach

        // preparar las expectativas
        EasyMock.expect(mockGestorLLamadas.getCalendario()).andReturn(mockCalendario);
        assertDoesNotThrow(() -> EasyMock.expect(mockCalendario.getHoraActual()).andReturn(hora));

        // activamos los mocks
        ctrl.replay();

        // invocamos a la SUT
        consumoReal = mockGestorLLamadas.calculaConsumo(minutos);

        // SIEMPRE verificar que nuestra SUT ha invocado a los mocks, si no --> throw AssertionError
        ctrl.verify();

        // informe
        assertEquals(consumoEsperado, consumoReal);

    }
}