package ppss;

import org.easymock.EasyMock;
import org.easymock.IMocksControl;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.FileReader;
import java.io.IOException;

import static org.junit.jupiter.api.Assertions.*;

class FicheroTextoTest {

    private FicheroTexto mock1;
    private FileReader mock2;
    IMocksControl ctrl;
    String nombreFichero, resultadoEsperado;

    @BeforeEach
    public void setup() {
        ctrl = EasyMock.createStrictControl();
        mock1 = EasyMock.partialMockBuilder(FicheroTexto.class)
                .addMockedMethod("getFichero").mock(ctrl);
        mock2 = ctrl.mock(FileReader.class);
    }

    @Test
    void contarCaracteres_C1() {

        // preparar datos de entrada
        nombreFichero = "src/test/resources/ficheroC1.txt";
        resultadoEsperado = nombreFichero + " (Error al leer el archivo)";

        // crear mocks --> @BeforeEach

        // preparar las expectativas
        assertDoesNotThrow(() -> EasyMock.expect(mock1.getFichero(nombreFichero)).andReturn(mock2));
        assertDoesNotThrow(() -> EasyMock.expect(mock2.read())
                        .andReturn((int) 'a')
                        .andReturn((int) 'b')
                        .andThrow(new IOException()));

        // activamos los mocks
        ctrl.replay();

        // invocamos a la SUT
        FicheroException exception = assertThrows(FicheroException.class,
                () -> mock1.contarCaracteres(nombreFichero));

        // verificamos
        ctrl.verify();

        // informe
        assertEquals(resultadoEsperado, exception.getMessage());
    }

    @Test
    void contarCaracteres_C2() {

        // preparar datos de entrada
        nombreFichero = "src/test/resources/ficheroC2.txt";
        resultadoEsperado = nombreFichero + " (Error al cerrar el archivo)";

        // crear mocks --> @BeforeEach

        // preparar las expectativas
        assertDoesNotThrow(() -> EasyMock.expect(mock1.getFichero(nombreFichero)).andReturn(mock2));
        assertDoesNotThrow(() -> EasyMock.expect(mock2.read())
                .andReturn((int) 'a')
                .andReturn((int) 'b')
                .andReturn((int) 'c')
                .andReturn(-1));

        assertDoesNotThrow(() -> mock2.close());
        EasyMock.expectLastCall().andThrow(new IOException());

        // activamos los mocks
        ctrl.replay();

        // invocamos a la SUT
        FicheroException exception = assertThrows(FicheroException.class,
                () -> mock1.contarCaracteres(nombreFichero));

        // verificamos
        ctrl.verify();

        // informe
        assertEquals(resultadoEsperado, exception.getMessage());
    }
}