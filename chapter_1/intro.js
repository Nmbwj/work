// Example of printing
console.log("df");

// Example of closure 
function makeAdder(x) {
  return function (y) {
    return x + y;
  };
}

const add5 = makeAdder(5);
const add10 = makeAdder(10);

console.log(add5(2)); // 7
console.log(add10(2)); // 12

function mult(factor){
    return number => number * factor;
    
}
let twice = mult(5);
console.log(twice(10));


