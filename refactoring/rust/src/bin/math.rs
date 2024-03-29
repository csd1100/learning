use rust::math::math::{add, div};
use anyhow::{Ok, Result};

fn main() -> Result<()> {
    let a = 12;
    let b = 23;
    println!("{} + {} = {}", a, b, add(a, b)?);
    let c = 400;
    let d = 200;
    println!("{} / {} = {}", c, d, div(c, d)?);
    return Ok(());
}
