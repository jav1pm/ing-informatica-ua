package ppss.ejercicio2;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class GestorLlamadasTest {

    double resultadoEsperado, resultadoReal;
    GestorLlamadasTestable sut = new GestorLlamadasTestable();

    @Test
    void calculaConsumoC1() {

        // preparar datos de entrada
        CalendarioStub stub = new CalendarioStub(15); // crear doble
        int minutos = 10;
        sut.setCalendario(stub);

        resultadoEsperado = 208;
        resultadoReal = sut.calculaConsumo(minutos); // inyectar doble

        // verificar resultados
        assertEquals(resultadoEsperado, resultadoReal);
    }

    @Test
    void calculaConsumoC2() {

        // preparar datos de entrada
        CalendarioStub stub = new CalendarioStub(22);
        int minutos = 10;
        sut.setCalendario(stub);

        resultadoEsperado = 105;
        resultadoReal = sut.calculaConsumo(minutos); // inyectar doble6

        // verificar resultados
        assertEquals(resultadoEsperado, resultadoReal);
    }
}