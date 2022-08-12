package ejercicio1;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.stream.Stream;

class MultipathExampleTest {

    MultipathExample m = new MultipathExample();

    @Test
    void multiPath1_lineas() {
        int a = 6;
        int b = 6;
        int c = 0;

        int esperado = 12;

        // sut
        int real = m.multiPath1(a, b, c);

        //informe
        Assertions.assertEquals(esperado, real);
    }

    @Test
    void multiPath1_condiciones() {
        int a = 4;
        int b = 4;
        int c = 0;

        int esperado = 0;

        // sut
        int real = m.multiPath1(a, b, c);

        //informe
        Assertions.assertEquals(esperado, real);
    }

    @Test
    void multiPath1_apartadoC() {
        int a = 3;
        int b = 6;
        int c = 2;

        int esperado = 8;

        // sut
        int real = m.multiPath1(a, b, c);

        //informe
        Assertions.assertEquals(esperado, real);
    }

    @ParameterizedTest
    @MethodSource("apartado_D")
    void multiPath2(int a, int b, int c, int esperado) {
        int real = m.multiPath2(a, b, c);
        Assertions.assertEquals(esperado, real);
    }

    private static Stream<Arguments> apartado_D() {
        return Stream.of(
                Arguments.of(6,4,6,16),
                Arguments.of(4,5,5,5),
                Arguments.of(6,6,6,12)
        );
    }
    // CC MultiPath2 JaCoCo => B - D + 1 = 6 - 3 + 1 = 4

    @ParameterizedTest
    @MethodSource("apartado_E")
    void multiPath3(int a, int b, int c, int esperado) {
        int real = m.multiPath3(a, b, c);
        Assertions.assertEquals(esperado, real);
    }

    private static Stream<Arguments> apartado_E() {
        return Stream.of(
                Arguments.of(6,4,6,16),
                Arguments.of(4,5,5,5)
        );
    }
}