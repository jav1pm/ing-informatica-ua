/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package AEstrella;

import java.util.Objects;

/**
 *
 * @author Javier Perez
 */
public class Estado {
    
    private Estado padre;
    private Coordenada c;
    private int f, g, h;
    
    public Estado(Coordenada c, Estado e) {
        this.padre = e;
        this.c = c;
    }
    
    public Estado(Coordenada c){
        this.c = c;
    }

    public Estado getPadre() {
        return padre;
    }

    public void setPadre(Estado padre) {
        this.padre = padre;
    }

    public Coordenada getC() {
        return c;
    }

    public void setN(Coordenada c) {
        this.c = c;
    }

    public int getF() {
        return f;
    }

    public int getG() {
        return g;
    }

    public void setG(int g) {
        this.g = g;
        this.f = g + h;
    }

    public int getH() {
        return h;
    }

    public void setH(int h) {
        this.h = h;
        this.f = g + h;
    }  
}
