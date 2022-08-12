package ppss;

public class Factoria {
    private static IOperacionBO servicio = null;
    public static IOperacionBO create() {
        if (servicio != null) {
            return servicio;
        } else {
            return new Operacion();
        }
    }
    static void setServicio(IOperacionBO srv) {
        servicio = srv;
    }
}
