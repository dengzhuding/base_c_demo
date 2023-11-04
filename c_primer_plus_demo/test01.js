const rl = require("readline").createInterface({ input: process.stdin });
var iter = rl[Symbol.asyncIterator]();
const readline = async () => (await iter.next()).value;

// 判断素数
let isPrime = function (num) {
    if (num <= 3) {
        return num > 0;
    }
    if (num % 2 == 0 || num % 3 == 0) {
        return false;
    }
    for (let i = 5; i * i < num; i++) {
        if (num % i == 0 || num % (i + 1) == 0) {
            return false;
        }
    }
    return true;
};

void (async function () {
    // Write your code here
    let lenStr = await readline();
    let arrStr = await readline();
    let arr = arrStr.split(" ");
    let count = 0;
    let arr1 = [];
    let arr2 = [];
    let link = []; // 记录arr2匹配到的arr1下标
    let state = []; // 记录arr2是否已经被连接

    let r = [];
    for (let i = 0; i < arr.length; i++) {
        let num = parseInt(arr[i]);
        num % 2 == 0 ? arr1.push(num) : arr2.push(num);
    }
    for (let i = 0; i < arr1.length; i++) {
        r[i] = [];
        for (let j = 0; j < arr2.length; j++) {
            r[i][j] = isPrime(arr1[i] + arr2[j]); // 是否能相加为素数
        }
    }
    let match = function(i) {
        for (let j = 0; j < arr2.length; j++) {
            if(r[i][j] && state[j] === undefined) {
                state[j] = true;
                if(link[j] === undefined || match(link[j])) {
                    link[j] = i;
                    return true;
                }
            }
        }
        return false;
    }
    
    for (let i = 0; i < arr1.length; i++) {
        state = []; // 重置访问状态
        if (match(i)) {
            count++;
        };
    }
    console.log(count);
})();
