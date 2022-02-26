public class ThreadConRunnable implements Runnable {
    String palabra;
    int veces = 10;
    
    public ThreadConRunnable(String p) {
        palabra = p;
    }

    public void run() {
        for(int i = 0; i < veces; i++) {
            System.out.println(palabra);
        }
    }

    public static void main(String[] args) {
        ThreadConRunnable a = new ThreadConRunnable("hilo1");
        ThreadConRunnable b = new ThreadConRunnable("hilo2");

        Thread t1 = new Thread(a);
        Thread t2 = new Thread(b);

        t1.setPriority(1);

        t1.start();
        t2.start();

        System.out.println("Fin del hilo principal");
    }
    
}
