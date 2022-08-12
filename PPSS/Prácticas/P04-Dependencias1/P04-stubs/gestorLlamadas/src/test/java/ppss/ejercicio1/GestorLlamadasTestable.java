package ppss.ejercicio1;

public class GestorLlamadasTestable extends GestorLlamadas {
    int result;

    public void setHora(int hora) {
        this.result = hora;
    }

    @Override
    public int getHoraActual() {
        return result;
    }
}
