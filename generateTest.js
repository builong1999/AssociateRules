
const fs = require('fs');

path = "input6.txt"
const NumProduct = 1E4;
const transaction = 1E3;
var listProduct = []
const t = [];

for (var j = 0; j < NumProduct; j++) {
    t.push(j + 1)
}
listProduct.push(t.join(','))

for (var i = 0; i < transaction; i++) {
    var temp = []
    for (var j = 0; j < NumProduct; j++) {
        var random_boolean = Math.random() >= 0.5;
        if (random_boolean) {
            temp.push(1)
        }
        else {
            temp.push(0);
        }
    }
    listProduct.push(temp.join(','))
    temp = []
}

listProduct = listProduct.join("\n");
fs.appendFileSync(path, listProduct,err=>{});