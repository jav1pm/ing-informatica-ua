package ppss.ejercicio2;

public class CalendarioStub extends Calendario {

    int result;

    public CalendarioStub(int salida) {
        this.result = salida;
    }

    @Override
    public int getHoraActual() {
        return result;
    }
}

