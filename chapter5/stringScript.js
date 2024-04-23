
/* import the Script module, to reduce space I intaintional removed it*/
let SCRIPTS = require('./SCRIPT.js'); 


function characterScript(code){
	for (script of SCRIPTS){
		if(script.ranges.some(([from,to])=>{
			return code >= from && code < to;
		})){
			return script;
		}
	}
	return null;
}
//console.log(characterScript(65));
/*
let horseShoe = "🐴👟";
console.log(horseShoe.length);
console.log(horseShoe[0]);
console.log(horseShoe.charCodeAt(0));
console.log(horseShoe.codePointAt(0));
*/
/*
let roseDragon = "🌹🐉";
for (let char of roseDragon){
	console.log(char);
}
*/
function countBy(items, groupName) {
let counts = [];
for (let item of items) {
let name = groupName(item);
let known = counts.findIndex(c => c.name == name);
if (known == -1) {
counts.push({name, count: 1});
} else {
counts[known].count++;
}
}
return counts;
}

function textScripts(text) {
let scripts = countBy(text, char => {
let script = characterScript(char.codePointAt(0));
return script ? script.name : "none";
}).filter(({name}) => name != "none");
let total = scripts.reduce((n, {count}) => n + count, 0);
if (total == 0) return "No scripts found";
return scripts.map(({name, count}) => {
return `${Math.round(count * 100 / total)}% ${name}`;
}).join(", ");
}
console.log(textScripts(' 英国的狗说 "woof", 俄罗斯的狗说 "тяв" 🌹'));
