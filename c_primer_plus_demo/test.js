const rl = require("readline").createInterface({ input: process.stdin });
var iter = rl[Symbol.asyncIterator]();
const readline = async () => (await iter.next()).value;

void async function () {
    // Write your code here
    let s = new Set();
    let flag = 0;
    while(line = await readline()){
        if (flag == 0) {
            flag = 1;
            continue;
        }
        s.add(line);
    }
    let arr = Array.from(s);
    let outArr = arr.sort();
    for (let item of outArr) {console.log(item)}
}()
