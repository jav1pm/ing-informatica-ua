use std::thread;
use std::sync::{Mutex,Arc};
// Cuando queremos compartir memoria en Rust tenemos que recurrir a una combinación de Mutex y Arc.
// Mutex provee de gestión del acceso a memoria
// Arc (Atomic Reference Counter) permite tener datos con múltiples dueños.

fn main(){
    let expected = 250000;
    let counter = Arc::new(Mutex::new(0)); // Contador
    let mut handles = vec![];

    for i in 0..5 { // 5 HILOS
        let counter = counter.clone(); // Copia del dato para trabajar libremente con él.
        let handle = thread::spawn(move || {
            let mut num = counter.lock().unwrap(); // para acceder al dato es necesario hacer lock().
            for _ in 0..50000 {
                *num += 1;
            }
            println!("Valor del contador en el hilo {}: {}", i, *num);
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }
    println!();
    println!("Valor final del contador: {}\nEsperado: {}", *counter.lock().unwrap(), expected);
}