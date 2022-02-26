/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg2021_p2si;

import java.util.ArrayList;

/**
 *
 * @author Francisco Javier Pérez Martínez
 */
public class clasificadorFuerte {
    
    private final ArrayList<clasificadorDebil> cDebiles;
    private int [] pertenece;

    public clasificadorFuerte(ArrayList<clasificadorDebil> cDebiles, int size) {
        this.cDebiles = cDebiles;
        this.pertenece = new int [size];
    }
    
    public clasificadorFuerte(ArrayList<clasificadorDebil> cDebiles) {
        this.cDebiles = cDebiles;
    }
    
    /**
     * Aplicamos todos los clasificadores débiles imagen por imagen
     * @param X 
     */
    public void aplicarClasificadorFuerte(ArrayList<Imagen> X) {
        
        for(int i=0;i<X.size();i++){
            double H = 0.0;
            for(int j=0;j<this.cDebiles.size();j++){
                if(cDebiles.get(j).getDireccion() == 1){
                    if(Adaboost.Byte2Unsigned(X.get(i).getImageData()[cDebiles.get(j).getPixel()]) > cDebiles.get(j).getUmbral()) {
                        H += cDebiles.get(j).getConfianza();
                    }
                    else {
                        H -= cDebiles.get(j).getConfianza();
                    }
                } else {
                    if(Adaboost.Byte2Unsigned(X.get(i).getImageData()[cDebiles.get(j).getPixel()]) < cDebiles.get(j).getUmbral()) {
                        H += cDebiles.get(j).getConfianza();
                    }
                    else {
                        H -= cDebiles.get(j).getConfianza();
                    }
                }
            }
            if(H > 0) {
                pertenece[i] = 1;
            }
            else {
                pertenece[i] = -1;
            }
        }
    }
    
    /**
     * Función que devuelve la Hipotesis final para poder ver después la mayor y así decir de que tipo es una imagen.
     * @param X
     * @return 
     */
    public double obtenerHipotesisFinal(ArrayList<Imagen> X) {
        
        double H = 0.0;
        for(int i=0;i<X.size();i++){
            H = 0.0;
            for(int j=0;j<this.cDebiles.size();j++){
                if(cDebiles.get(j).getDireccion() == 1){
                    if(Adaboost.Byte2Unsigned(X.get(i).getImageData()[cDebiles.get(j).getPixel()]) > cDebiles.get(j).getUmbral()) {
                        H += cDebiles.get(j).getConfianza();
                    }
                    else {
                        H -= cDebiles.get(j).getConfianza();
                    }
                } else {
                    if(Adaboost.Byte2Unsigned(X.get(i).getImageData()[cDebiles.get(j).getPixel()]) < cDebiles.get(j).getUmbral()) {
                        H += cDebiles.get(j).getConfianza();
                    }
                    else {
                        H -= cDebiles.get(j).getConfianza();
                    }
                }
            }
        }
        return H;
    }
    
    /**
     * Metodo que devuelva el nº de errores que hace el clasificador fuerte.
     * @param X
     * @param Y
     * @return 
     */
    public int obtenerErrorClasif(ArrayList<Imagen> X, int[] Y)
    {
        int auxError = 0;
        for(int i=0;i<X.size();i++){
            if(Y[i] != pertenece[i]){
                auxError++;
            }
        }
        return auxError;
    }

    @Override
    public String toString() {
        String out = "";
        
        for(int i=0;i<cDebiles.size();i++){
            out += cDebiles.get(i).toString();
        }
        return out;
    }
    
    public ArrayList<clasificadorDebil> getcDebiles() {
        return cDebiles;
    }

    public int[] getPertenece() {
        return pertenece;
    }
}
