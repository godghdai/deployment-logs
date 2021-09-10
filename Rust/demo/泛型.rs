use std::fmt::Display;
use std::ops::Add;
fn add<T:Display+ std::ops::Add<Output = T>>(x:T,y:T)->T{
    x+y
}

fn opt<T>(fun:fn(T,T) -> T,x:T,y:T)->T{
    fun(x,y)
}

fn main() {
    let res=add(1,2);
    println!("{}",res);
    let res=add(1.2,2.3);
    println!("{}",res);
    
    println!("{}",opt::<i32>(|x,y|x+y,1,2));
    println!("{}",opt::<i32>(|x,y|x*y,3,2));
}
