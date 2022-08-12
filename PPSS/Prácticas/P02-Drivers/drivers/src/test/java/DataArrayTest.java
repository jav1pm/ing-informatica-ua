import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import javax.xml.crypto.Data;
import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.*;

class DataArrayTest {

    @Test
    void deleteC1() {
        // datos de entrada
        DataArray sut = new DataArray(new int[]{1,3,5,7});

        // resultados esperados
        int[] arrayEsperado = {1,3,7};
        int numElemEsperado = 3;

        // llamar a sut
        assertDoesNotThrow(() -> sut.delete(5), "Excepción lanzada");
        assertAll("TestC1",
                () -> assertArrayEquals(arrayEsperado, sut.getColeccion()),
                () -> assertEquals(numElemEsperado, sut.size())
        );
    }

    @Test
    void deleteC2() {
        // datos de entrada
        DataArray sut = new DataArray(new int[]{1,3,3,5,7});

        // resultados esperados
        int[] arrayEsperado = {1,3,5,7};
        int numElemEsperado = 4;

        // llamar a sut
        assertDoesNotThrow(() -> sut.delete(3), "Excepción lanzada");
        assertAll("TestC1",
                () -> assertArrayEquals(arrayEsperado, sut.getColeccion()),
                () -> assertEquals(numElemEsperado, sut.size())
        );
    }

    @Test
    void deleteC3() {
        // datos de entrada
        DataArray sut = new DataArray(new int[]{1,2,3,4,5,6,7,8,9,10});

        // resultados esperados
        int[] arrayEsperado = {1,2,3,5,6,7,8,9,10};
        int numElemEsperado = 9;

        // llamar a sut
        assertDoesNotThrow(() -> sut.delete(4), "Excepción lanzada");
        assertAll("TestC1",
                () -> assertArrayEquals(arrayEsperado, sut.getColeccion()),
                () -> assertEquals(numElemEsperado, sut.size())
        );
    }

    @Test
    void deleteC4() {
        // datos de entrada
        DataArray sut = new DataArray();
        // resultados esperados
        // llamar a sut
        DataException exception = assertThrows(DataException.class,
                () -> sut.delete(8));
        assertEquals("No hay elementos en la colección", exception.getMessage());
    }

    @Test
    void deleteC5() {
        // datos de entrada
        DataArray sut = new DataArray(new int[]{1,3,5,7});
        // resultados esperados
        // llamar a sut
        DataException exception = assertThrows(DataException.class,
                () -> sut.delete(-5));
        assertEquals("El valor a borrar debe ser > 0", exception.getMessage());
    }

    @Test
    void deleteC6() {
        // datos de entrada
        DataArray sut = new DataArray();
        // resultados esperados
        // llamar a sut
        DataException exception = assertThrows(DataException.class,
                () -> sut.delete(0));
        assertEquals("Colección vacía. Y el valor a borrar debe ser > 0", exception.getMessage());
    }

    @Test
    void deleteC7() {
        // datos de entrada
        DataArray sut = new DataArray(new int[]{1,3,5,7});
        // resultados esperados
        // llamar a sut
        DataException exception = assertThrows(DataException.class,
                () -> sut.delete(8));
        assertEquals("Elemento no encontrado", exception.getMessage());
    }

    //@Tags({@Tag("parametrizado"), @Tag("conExcepciones")})
    @ParameterizedTest
    @MethodSource("cp_dataArray1")
    @Tag("parametrizado")
    @Tag("conExcepciones")
    void testParametrizadoC8(String message, int[] data, int elem) {

        DataArray sut = new DataArray(data);
        // llamar a sut
        DataException exception = assertThrows(DataException.class,
                () -> sut.delete(elem));
        assertEquals(message, exception.getMessage());
    }

    private static Stream<Arguments> cp_dataArray1() {

        return Stream.of(
                Arguments.of("No hay elementos en la colección", new int[]{}, 8),
                Arguments.of("El valor a borrar debe ser > 0", new int[]{1,3,5,7}, -5),
                Arguments.of("Colección vacía. Y el valor a borrar debe ser > 0", new int[]{}, 0),
                Arguments.of("Elemento no encontrado", new int[]{1,3,5,7}, 8)
        );
    }

    @ParameterizedTest
    @MethodSource("cp_dataArray2")
    @Tag("parametrizado")
    void testParametrizadoC9(int[] esperado, int numElem, int[] data, int elemBorrar) {

        DataArray sut = new DataArray(data);
        // llamar a sut

        assertDoesNotThrow(() -> sut.delete(elemBorrar), "Excepción lanzada");
        assertAll("TestC9",
                () -> assertArrayEquals(esperado, sut.getColeccion()),
                () -> assertEquals(numElem, sut.size())
        );

    }

    private static Stream<Arguments> cp_dataArray2() {

        return Stream.of(
                Arguments.of(new int[]{1,3,7}, 3, new int[]{1,3,5,7}, 5),
                Arguments.of(new int[]{1,3,5,7}, 4, new int[]{1,3,3,5,7}, 3),
                Arguments.of(new int[]{1,2,3,5,6,7,8,9,10}, 9, new int[]{1,2,3,4,5,6,7,8,9,10}, 4)
        );
    }
}