package ppss.ejercicio1;

import org.junit.jupiter.api.Test;
import ppss.ejercicio2.GestorLlamadas;

import static org.junit.jupiter.api.Assertions.*;

class GestorLlamadasTest {

    double resultadoEsperado, resultadoReal;

    @Test
    void calculaConsumoC1() {

        // preparar datos de entrada
        ppss.ejercicio1.GestorLlamadasTestable sut = new ppss.ejercicio1.GestorLlamadasTestable(); // crear doble
        sut.setHora(15);
        int minutos = 10;

        resultadoEsperado = 208;
        resultadoReal = sut.calculaConsumo(minutos); // inyectar doble

        // verificar resultados
        assertEquals(resultadoEsperado, resultadoReal);
    }

    @Test
    void calculaConsumoC2() {

        // preparar datos de entrada
        ppss.ejercicio1.GestorLlamadasTestable sut = new GestorLlamadasTestable();
        sut.setHora(22);
        int minutos = 10;

        resultadoEsperado = 105;
        resultadoReal = sut.calculaConsumo(minutos); // inyectar doble

        // verificar resultados
        assertEquals(resultadoEsperado, resultadoReal);
    }
}