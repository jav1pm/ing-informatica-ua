package ppss;

import ppss.excepciones.IsbnInvalidoException;
import ppss.excepciones.JDBCException;
import ppss.excepciones.SocioInvalidoException;

import java.util.ArrayList;

public class OperacionStub implements IOperacionBO {

    String socio;
    ArrayList<String> isbns = new ArrayList<>();
    boolean bd_inactiva;

    public void setSocio(String socio) {
        this.socio = socio;
    }

    public void setIsbn(ArrayList<String> isbns) {
        this.isbns = isbns;
    }

    public void setBd_inactiva(Boolean bd) {
        this.bd_inactiva = bd;
    }

    @Override
    public void operacionReserva(String socio, String isbn) throws IsbnInvalidoException, JDBCException, SocioInvalidoException {
        if (this.socio != socio) throw new SocioInvalidoException();
        if (!isbns.contains(isbn)) throw new IsbnInvalidoException();
        if (this.bd_inactiva) throw new JDBCException();
    }
}
