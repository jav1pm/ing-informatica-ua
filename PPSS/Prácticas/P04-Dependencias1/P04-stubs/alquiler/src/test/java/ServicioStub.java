public class ServicioStub implements IService {

    float result;

    public void setPrecio(float salida) {
        this.result = salida;
    }

    @Override
    public float consultaPrecio(TipoCoche tipo) {
        return result;
    }
}
