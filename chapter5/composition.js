
/* import the Script module, to reduce space I intaintional removed it*/


function average(array){
	return array.reduce((a,b)=> a+b) /array.length;
}

console.log(Math.round(average(SCRIPTS.filter(s=>s.living).map(s=>s.year))));

console.log(Math.round(average(SCRIPTS.filter(s=>!s.living).map(s=>s.year))));
