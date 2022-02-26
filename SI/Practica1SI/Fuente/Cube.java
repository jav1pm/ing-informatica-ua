/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package AEstrella;

import static java.lang.Math.abs;

/**
 *
 * @author Javier Perez
 */
public class Cube {
    
    int x;
    int y;
    int z;

    public Cube(int x, int y, int z) {
        this.x = x;
        this.y = y;
        this.z = z;
    }
    
    public Cube(){
        x = 0;
        y = 0;
        z = 0;
    }
    
    /**
     * Método para calcular la distancia entre dos cubos.
     * @param a
     * @param b
     * @return 
     */
    public int distanciaMapasHex(Cube a, Cube b){
        return (abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z)) / 2;
    }
}
