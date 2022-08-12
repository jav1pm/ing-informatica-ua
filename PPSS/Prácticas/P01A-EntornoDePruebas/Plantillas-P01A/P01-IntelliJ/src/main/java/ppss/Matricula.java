package ppss;

public class Matricula {
    public float calculaTasaMatricula(int edad, boolean familiaNumerosa,
                                      boolean repetidor) {
        float tasa = 500.00f;

        if ((edad < 25) && (!familiaNumerosa) && (repetidor)) {
            tasa = tasa + 1500.00f;
        } else {
            if ((edad > 50) && (edad < 65)) {
                tasa = tasa - 100.00f;
            }
            else {
                if ((familiaNumerosa) ||  (edad >= 65)) {
                    tasa = tasa / 2;
                }
            }
        }
        return tasa;
    }

    // ruta local: /home/ppss/.m2/repository/practica1/ppss/P01-IntelliJ/1.0-SNAPSHOT/P01-IntelliJ-1.0-SNAPSHOT.pom
}
