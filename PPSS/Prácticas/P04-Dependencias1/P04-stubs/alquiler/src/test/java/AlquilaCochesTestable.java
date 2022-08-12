public class AlquilaCochesTestable extends AlquilaCoches {

    IService servicio;

    @Override
    public IService getServicio() {
        return servicio;
    }

    public void setServicio(IService s) {
        this.servicio = s;
    }
}
