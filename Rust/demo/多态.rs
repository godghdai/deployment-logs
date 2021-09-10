trait Shape {
    fn to_string(&self) -> String;
}

struct Point<T> {
    x: T,
    y: T,
}

impl<T: Display> Shape for Point<T> {
    fn to_string(&self) -> String {
        format!("[{},{}]", self.x, self.y)
    }
}

struct Circle<T> {
    center: Point<T>,
    radius: T,
}

impl<T: Display> Shape for Circle<T> {
    fn to_string(&self) -> String {
        format!("[center:{},radius:{}]", self.center.to_string(), self.radius)
    }
}

fn print(shape: Box<dyn Shape>) {
    println!("{}", shape.to_string());
}

fn main() {
    let point = Box::new(Point { x: 2, y: 3 });
    let circle = Box::new(Circle {
        center: Point { x: 2, y: 3 },
        radius: 1,
    });

    let mut shapes = Vec::<Box<dyn Shape>>::new();
    shapes.push(point);
    shapes.push(circle);
    for shape in &shapes{
        println!("{}", shape.to_string());
    }
    for shape in shapes.iter() {
        println!("{}", shape.to_string());
    }
}
