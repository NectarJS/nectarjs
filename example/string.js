var a = 'Hi, it\'s ';
var b = "NectarJS !";
var c = a + b;
console.log("a = Hi, it's ");
console.log("b = NectarJS !");
console.log("c = a + b: " + c);
console.log('Typeof c: ' + typeof c);
console.log("Length: " + c.length);
console.log("c.split(',')[0]: " + c.split(',')[0]); // output: Hi
console.log("c.indexOf('NectarJS'): " + c.indexOf("NectarJS"));
console.log("c.slice(3): " + c.slice(3));
console.log("c.slice(9, 17): " + c.slice(9, 17));
console.log("c.replace('Hi', 'Hello'): " + c.replace('Hi', 'Hello'));