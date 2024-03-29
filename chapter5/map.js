
/* import the Script module, to reduce space I intaintional removed it*/


function map(array, transform){
	let mapped = [];
	for (let element of array){
		mapped.push(transform(element));
		}
	return mapped;
}
let rtlScripts = SCRIPTS.filter(s=>s.direction == "rtl");
console.log(map(rtlScripts, s=>s.name));
