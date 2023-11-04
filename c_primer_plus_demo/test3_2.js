const rl = require("readline").createInterface({ input: process.stdin });
var iter = rl[Symbol.asyncIterator]();
const readline = async () => (await iter.next()).value;

void async function () {
    // Write your code here
    let flag = 0;
    let m,n;
    let arr = []
    // 输入
    try {
        while(line = await readline()){
            if (flag == 0) {
                let temp = line.split(',');
                if (temp.length == 2) {
                    m = temp[0];
                    n = temp[1];
                    if (m < 3 || m > 10 || n < 3 || n > 100) {
                        throw new Error();
                    }
                }
                flag = 1;
                continue;
            }
            let temp2 = line.split(',');
            if (temp2.findIndex(item => item > 10 || item < 1) >= 0) {
                throw new Error();
            }
            arr.push(temp2);
        }
    } catch(e) {
        console.log(-1);
    }
    let sortArr = [];
    for(let i = 0; i < n; i++) {
        sortArr[i] = [i+1, i, 0]; // 编号，对应的列序号,分数
    }
    // 统计总分
    for(let i = 0; i < n; i++) { // 运动员
        let count = 0; //总分
        for(let j = 0; j < m; j++) { //裁判
            let num = sortArr[j, i];
            count = count + parseInt(num);
        }
        sortArr[i][3] = count;
    }
    // 排序
    let returnArr = sortArr.sort((a, b) => {
        if (a[3] - b[3] != 0) {
            return b - a;
        } else {
            return 0;
        }
    })
    // 输出
    console.log(m, n, arr, sortArr,returnArr);

}()
