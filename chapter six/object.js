let ages = new Map();
ages.set("boris",39);
console.log(`${ages.has("boris")}`);
console.log(`${ages.get("boris")}`);
console.log(`${ages.has("toString")}`);

let kudo = {
    bulaus: 723,
    marken: 2545
};

let mudo = Object.create(null);
mudo.bulaus=535;
console.log(`${kudo["bulaus"]}`);
console.log(`${mudo["bulaus"]}`);
