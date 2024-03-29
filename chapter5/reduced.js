
/* import the Script module, to reduce space I intaintional removed it*/


function reduce(array, combine, start){
	let current = start;
	for (element of array){
		current = combine(current, element);
	}
	return current;
}
function characterCount(script){
	return script.ranges.reduce((count,[from,to])=>{
		return count + (to-from);
	},0);
}
let script = SCRIPTS.reduce((a,b)=> {
	return characterCount(a)<characterCount(b)?b:a;});
console.log(`${console.log(script)} \nand the number of character is: ${characterCount(script)}`);
