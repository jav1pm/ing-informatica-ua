/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg2021_p2si;

import java.util.ArrayList;
import java.util.Random;

/**
 *
 * @author Francisco Javier Pérez Martínez
 */
public class clasificadorDebil {
    
    private int pixel; // 0..3071
    private int umbral; // 0..255
    private int direccion; // 1 o -1
    private int [] pertenece;
    private double error;
    private double confianza;
    private int aciertos;

    public clasificadorDebil(int pixel, int umbral, int direccion, int size) {
        
        this.pixel = pixel;
        this.umbral = umbral;
        this.direccion = direccion;
        this.error = 0.0;
        this.pertenece = new int[size];
        this.confianza = 0.0;
    }
    
    public clasificadorDebil() {
        this.pixel = 0;
        this.umbral = 0;
        this.direccion = 0;
        this.confianza = 0.0;
    }
    
    public static clasificadorDebil generalClasifAzar(int size)
    {
        Random random = new Random();
       
        int pixelRand =  (random.nextInt(3072));
        int umbralRand = (random.nextInt(256));
        int direccionRand = (random.nextInt(2));
        
        if(direccionRand == 0) direccionRand = -1;
        return new clasificadorDebil(pixelRand, umbralRand, direccionRand, size);
    }
    
    public void aplicarClasifDebil(clasificadorDebil cD, ArrayList<Imagen> X)
    { 
        for(int i=0;i<X.size();i++){
            if(cD.direccion == 1){
                // Accedemos al imageData mediante el pixel
                if(Adaboost.Byte2Unsigned(X.get(i).getImageData()[cD.pixel]) > cD.umbral){
                    cD.pertenece[i] = 1;
                } else {
                    cD.pertenece[i] = -1;
                }
            } else {
                if(Adaboost.Byte2Unsigned(X.get(i).getImageData()[cD.pixel]) < cD.umbral){
                    cD.pertenece[i] = 1;
                } else {
                    cD.pertenece[i] = -1;
                }
            }
        }
    }
    
    public void obtenerErrorClasif(clasificadorDebil cD, ArrayList<Imagen> X, int[] Y, double[] D)
    {
        double auxError = 0.0;
        for(int i=0;i<X.size();i++){
            if(Y[i] != cD.pertenece[i]){
                auxError += D[i];
            }
            else{
                aciertos++;
            }
        }
        cD.error = auxError;
    }

    @Override
    public String toString() {
        return pixel + "," + umbral + "," + direccion + "," + confianza + "/";
    }
    
    public int getPixel() {
        return pixel;
    }

    public int getUmbral() {
        return umbral;
    }

    public int getDireccion() {
        return direccion;
    }
    
    public double getError(){
        return error;
    }

    public void setPixel(int pixel) {
        this.pixel = pixel;
    }

    public void setUmbral(int umbral) {
        this.umbral = umbral;
    }

    public void setDireccion(int direccion) {
        this.direccion = direccion;
    }

    public double getConfianza() {
        return confianza;
    }

    public void setConfianza(double confianza) {
        this.confianza = confianza;
    }
    
    public int getAciertos(){
        return aciertos;
    }

    public int[] getPertenece() {
        return pertenece;
    }
}
