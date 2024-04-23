
/* import the Script module, to reduce space I intaintional removed it*/
let SCRIPTS = require('./SCRIPT.js'); 
const dayjs = require('dayjs');
function map(array, transform){
	let mapped = [];
	for (let element of array){
		mapped.push(transform(element));
		}
	return mapped;
}
let rtlScripts = SCRIPTS.filter(s=>s.direction == "rtl");
console.log(dayjs().format('YYYY MM-DDTHH:mm:ss'));
console.log(map(rtlScripts, s=>s.name));
