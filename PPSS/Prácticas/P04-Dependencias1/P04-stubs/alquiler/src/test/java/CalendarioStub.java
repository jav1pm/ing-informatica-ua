import java.lang.reflect.Array;
import java.time.LocalDate;
import java.util.ArrayList;

public class CalendarioStub extends Calendario {

    ArrayList<LocalDate> festivos = new ArrayList<>();
    ArrayList<LocalDate> exception = new ArrayList<>();

    public void setFestivos(ArrayList<LocalDate> date) {
        this.festivos = date;
    }

    public void setException(ArrayList<LocalDate> date) {
        this.exception = date;
    }

    @Override
    public boolean es_festivo(LocalDate date) throws CalendarioException {
        if(festivos.contains(date)) {
            return true;
        }
        else if (exception.contains(date)) {
            throw new CalendarioException();
        }
        else {
            return false;
        }
    }
}
