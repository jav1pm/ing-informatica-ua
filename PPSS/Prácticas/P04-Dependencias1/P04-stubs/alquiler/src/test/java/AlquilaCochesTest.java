import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.time.LocalDate;
import java.time.Month;
import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;

class AlquilaCochesTest {

    CalendarioStub calStub;
    ServicioStub servStub;
    AlquilaCochesTestable sut;

    @BeforeEach
    void setup() {
        calStub = new CalendarioStub();
        servStub = new ServicioStub();
        sut = new AlquilaCochesTestable();

        // inyectamos
        sut.calendario = calStub;
        sut.setServicio(servStub);
    }

    @Test
    void calculaPrecioC1() {
        // preparar datos de entrada
        TipoCoche tipo = TipoCoche.TURISMO;
        float precioDia = 10;
        int ndias = 10;
        LocalDate inicio = LocalDate.of(2022, Month.MAY, 18);

        servStub.setPrecio(precioDia);

        // resultado esperado
        Ticket ticketEsperado = new Ticket();
        ticketEsperado.setPrecio_final(75);

        Ticket ticketReal = assertDoesNotThrow(
                () -> sut.calculaPrecio(tipo,inicio,ndias), "Excepción lanzada"
        );

        // verificamos
        assertEquals(ticketEsperado.getPrecio_final(), ticketReal.getPrecio_final());

    }

    @Test
    void calculaPrecioC2() {

        // preparar datos de entrada
        TipoCoche tipo = TipoCoche.CARAVANA;
        float precioDia = 10;
        int ndias = 7;
        LocalDate inicio = LocalDate.of(2022, Month.JUNE, 19);

        servStub.setPrecio(precioDia);
        ArrayList<LocalDate> festivos = new ArrayList<>();
        festivos.add(LocalDate.of(2022, Month.JUNE, 20));
        festivos.add(LocalDate.of(2022, Month.JUNE, 24));
        calStub.setFestivos(festivos);

        // resultado esperado
        Ticket ticketEsperado = new Ticket();
        ticketEsperado.setPrecio_final(62.5f);

        Ticket ticketReal = assertDoesNotThrow(
                () -> sut.calculaPrecio(tipo,inicio,ndias), "Excepción lanzada"
        );

        // verificamos
        assertEquals(ticketEsperado.getPrecio_final(), ticketReal.getPrecio_final());
    }

    @Test
    void calculaPrecioC3() {

        // preparar datos de entrada
        TipoCoche tipo = TipoCoche.TURISMO;
        float precioDia = 10;
        int ndias = 8;
        LocalDate inicio = LocalDate.of(2022, Month.APRIL, 17);

        servStub.setPrecio(precioDia);
        ArrayList<LocalDate> exception = new ArrayList<>();
        exception.add(LocalDate.of(2022, Month.APRIL, 18));
        exception.add(LocalDate.of(2022, Month.APRIL, 21));
        exception.add(LocalDate.of(2022, Month.APRIL, 22));
        calStub.setException(exception);

        // resultado esperado
        String mensajeEsperado = "Error en dia: 2022-04-18; Error en dia: 2022-04-21; Error en dia: 2022-04-22; ";

        MensajeException messException = assertThrows(MensajeException.class,
                () -> sut.calculaPrecio(tipo, inicio, ndias));

        // verificamos
        assertEquals(mensajeEsperado, messException.getMessage());
    }
}