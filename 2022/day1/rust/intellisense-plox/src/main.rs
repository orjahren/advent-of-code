use std::fs;

fn main() {
    //let content = fs::read_to_string("../../../small").expect("Skulle ha kunnet lese filen..");
    let content = fs::read_to_string("../../../input").expect("Skulle ha kunnet lese filen..");

    let mut arr: Vec<u32> = Vec::new();

    let mut i = 0;
    let mut endret_forrige = true;

    for line in content.lines() {
        if line == "" {
            i = i + 1;
            endret_forrige = true;
        } else {
            if endret_forrige {
                arr.push(0);
                endret_forrige = false;
            }
            arr[i] = arr[i] + line.parse::<u32>().unwrap();
        }
    }

    arr.sort();

    let max = arr.pop().unwrap();
    let pen = arr.pop().unwrap();
    let tredje = arr.pop().unwrap();
    let part2_res = max + pen + tredje;
    print!("Part 1: {max} \n");
    print!("Part 2: {part2_res}\n");
}
