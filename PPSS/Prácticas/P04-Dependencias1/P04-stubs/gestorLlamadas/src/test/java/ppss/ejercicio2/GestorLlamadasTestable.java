package ppss.ejercicio2;

public class GestorLlamadasTestable extends GestorLlamadas {

    Calendario cal;

    public void setCalendario(Calendario cal) {
        this.cal = cal;
    }

    @Override
    public Calendario getCalendario() {
        return cal;
    }
}
