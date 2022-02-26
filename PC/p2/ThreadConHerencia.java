public class ThreadConHerencia extends Thread {
    String palabra;
    int veces = 10;

    public ThreadConHerencia (String p) {
        palabra = p;
    }

    public void run() {
        for(int i = 0; i < veces; i++){
            System.out.println(palabra);
        }
    }

    public static void main(String[] args) {
        Thread a = new ThreadConHerencia("hilo1");
        Thread b = new ThreadConHerencia("hilo2");

        a.start();
        b.start();

        System.out.println("Fin del hilo principal");
    }
}