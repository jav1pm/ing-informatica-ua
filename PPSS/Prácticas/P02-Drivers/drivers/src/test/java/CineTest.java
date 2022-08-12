import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.*;

class CineTest {

    int solicitados;
    boolean reservaEsperada, reservaReal;
    Cine cine;

    @Test
    void reservaButacasC1() {
        boolean[] asientos = {};
        solicitados = 3;

        reservaEsperada = false;
        boolean[] asientosEsperados = {};
        cine = new Cine();
        reservaReal = cine.reservaButacasV1(asientos, solicitados);

        assertAll("TestC1",
                () -> assertEquals(reservaEsperada, reservaReal),
                () -> assertArrayEquals(asientosEsperados, asientos)
        );
    }

    @Test
    void reservaButacasC2() {
        boolean[] asientos = {};
        solicitados = 0;

        reservaEsperada = false;
        boolean[] asientosEsperados = {};
        cine = new Cine();
        reservaReal = cine.reservaButacas(asientos, solicitados);

        assertAll("TestC2",
                () -> assertEquals(reservaEsperada, reservaReal),
                () -> assertArrayEquals(asientosEsperados, asientos)
        );
    }

    @Test
    void reservaButacasC3() {
        boolean[] asientos = {false, false, false, true, true};
        solicitados = 2;

        reservaEsperada = true;
        boolean[] asientosEsperados = {true, true, false, true, true};
        cine = new Cine();
        reservaReal = cine.reservaButacasV1(asientos, solicitados);

        assertAll("TestC3",
                () -> assertEquals(reservaEsperada, reservaReal),
                () -> assertArrayEquals(asientosEsperados, asientos)
        );
    }

    @Test
    void reservaButacasC4() {
        boolean[] asientos = {true, true, true};
        solicitados = 1;

        reservaEsperada = false;
        boolean[] asientosEsperados = {true, true, true};
        cine = new Cine();
        reservaReal = cine.reservaButacasV1(asientos, solicitados);

        assertAll("TestC4",
                () -> assertEquals(reservaEsperada, reservaReal),
                () -> assertArrayEquals(asientosEsperados, asientos)
        );
    }

    @ParameterizedTest
    @MethodSource("cp_reserva")
    @Tag("parametrizado")
    void reservaButacasC5(boolean esperada, boolean[] asientosEsperados, boolean[] asientos, int solicitados) {

        Cine sut = new Cine();
        // llamar a sut
        reservaReal = sut.reservaButacas(asientos, solicitados);
        // comprobar e informe
        assertAll("TestC5",
                () -> assertEquals(esperada, reservaReal),
                () -> assertArrayEquals(asientosEsperados, asientos)
        );
    }

    private static Stream<Arguments> cp_reserva() {

        return Stream.of(
                Arguments.of(false, new boolean[]{}, new boolean[]{}, 3),
                Arguments.of(false, new boolean[]{}, new boolean[]{}, 0),
                Arguments.of(true, new boolean[]{true,true,false,true,true}, new boolean[]{false,false,false,true,true}, 2),
                Arguments.of(false, new boolean[]{true,true,true}, new boolean[]{true,true,true}, 1)
        );
    }
}