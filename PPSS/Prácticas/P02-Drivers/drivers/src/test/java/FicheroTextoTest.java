import org.junit.jupiter.api.Tag;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class FicheroTextoTest {

    FicheroTexto sut = new FicheroTexto();

    @Test
    void contarCaracteresC1() {

        FicheroException exception = assertThrows(FicheroException.class,
                () -> sut.contarCaracteres("ficheroC1.txt"));

        assertEquals("ficheroC1.txt (No existe el archivo o el directorio)", exception.getMessage());
    }

    @Test
    void contarCaracteresC2() {

        assertDoesNotThrow(()
                -> assertEquals(3, sut.contarCaracteres("src/test/resources/ficheroCorrecto.txt")));
    }

    @Tag("excluido")
    @Test
    void contarCaracteresC3() {
        fail();
    }

    @Tag("excluido")
    @Test
    void contarCaracteresC4() {
        fail();
    }
}