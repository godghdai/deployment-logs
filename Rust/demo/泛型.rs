use std::fmt::Display;
use std::ops::Add;
fn add<T:Display+ std::ops::Add<Output = T>>(x:T,y:T)->T{
    x+y
}

fn main() {
    let res=add(1,2);
    println!("{}",res);
    let res=add(1.2,2.3);
    println!("{}",res);
}
