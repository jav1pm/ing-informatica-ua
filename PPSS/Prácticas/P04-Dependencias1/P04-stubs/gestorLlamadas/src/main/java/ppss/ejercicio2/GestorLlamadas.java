package ppss.ejercicio2;

public class GestorLlamadas {
    static double TARIFA_NOCTURNA=10.5;
    static double TARIFA_DIURNA=20.8;

    public Calendario getCalendario() {
        Calendario c = new Calendario();
        return c;
    }

    public double calculaConsumo(int minutos) {
        Calendario c = getCalendario(); // dep1: creamos una clase que extiende de GestorLlamadas
        int hora = c.getHoraActual(); // dep2: creamos un doble que extiende de Calendario
        if (hora < 8 || hora > 20) {
            return minutos * TARIFA_NOCTURNA;
        } else {
            return minutos * TARIFA_DIURNA;
        }
    }
}
