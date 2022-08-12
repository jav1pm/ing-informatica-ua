package ppss;

public class ReservaTestable extends Reserva {

    boolean result;

    public void setPermisos(boolean b) {
        this.result = b;
    }

    @Override
    public boolean compruebaPermisos(String login, String password, Usuario tipoUsu){
        return result;
    }

}