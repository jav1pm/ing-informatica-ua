use std::thread;
use std::time::Duration;

// compilación: rustc nombre

# [allow(dead_code, unused_variables)]
fn thrfn(c: char, n: u8) {
    for i in 0..n {
        println!("{}", c);
        thread::sleep(Duration::from_millis(1));
    }
}

fn main() {
    std::thread::spawn(move || {
        for i in 1..10 {
            println!("hi number {} from the spawned thread!", i);
            thread::sleep(Duration::from_millis(1));
        }
    });

    for i in 1..=3 {
        println!("hi numer {} from the main thread!", i);

        // _ no se va a usar la variable, en este caso sencillo no es necesario.
        let _ = match i { // equivalente a un switch en c++
            1 => std::thread::spawn(move || {
                thrfn('A', 50);
            }),
            2 => std::thread::spawn(move || {
                thrfn('B', 100);
            }),
            3 => std::thread::spawn(move || {
                thrfn('C', 150);
            }),
            _ => std::thread::spawn(move || {})
        }.join();
    }

    thread::sleep(Duration::from_millis(1));
}