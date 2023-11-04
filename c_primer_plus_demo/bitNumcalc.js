function calcNum(num) { // return num * num-1 *...*1 = 
  // return num === Math.pow(2,left) + num%2
  if (num === 1) {
      return num;
  }
  let sumArr = [];
  let tempSum = 1;
  for (let i = num; i > 0; i--) {
      if (Number.isSafeInteger(tempSum * i)) {
          tempSum*=i;
      } else {
          sumArr.push(tempSum);
          tempSum = 1;
      }
  }
  if (sumArr.length === 0) {
      return tempSum.toString();
  }
  // sum = sumArr[0]*sumArr[1]*...*sumArr[sumArr.length - 1]
  let sumStr = sumArr[0];
  for (let i = 1, len = sumArr.length; i < len; i++) {
      sumStr = multStr(sumStr, sumArr[i]);
  }
  return sumStr; // return string 
}

function showCur(str) {
  console.log('当前：' + str);
}

// 十进制字符串乘法运算
function multStr(a, b) {
  if (!a || !b) {
      return '';
  }
  if (typeof a == 'number') {
      a = a.toString();
  }
  if (typeof b == 'number') {
      b = b.toString();
  }
  let i = a.length;
  let lenB = b.length;
  let sumTempStr = a;
  for (let k = lenB - 1; k > 0; k--) {
      let cur2 = b.charAt(k);
      cur2 = cur2.padEnd(lenB - k, '0');
      let temp = sumTempStr;
      // 打印当前计算值
      let preTime = Date.now();
      while(cur2 != 0) {
          sumTempStr = addDStr(sumTempStr, temp); // 这里执行太久阻塞了主进程
          if (globalThis.stop === true) { // 设置window.stop = true中断，没用还是阻塞
              showCur(sumTempStr);
              throw new Error('用户自行中断');  
          }
          let curTime = Date.now()
          if (curTime - preTime > 2000) {
              preTime = curTime;
              showCur(sumTempStr); // 进来这里可断点，然后设置window.stop = true
          }
          cur2--;
      }
  }
  return sumTempStr;
}
// 十进制字符串加法运算 
function addDStr(a, b) {
  if (typeof a == 'number') {
      a = a.toString();
  }
  if (typeof b == 'number') {
      b = b.toString();
  }
  // throw new Error();
  let i = a.length;
  let j = b.length;
  if (i === 1 && a === '0') {
      return b;
  }
  if (j === 1 && b === '0') {
      return a;
  }
  let up = 0;
  let res = [];
  // console.log(i,j);
  while (i > 0 || j > 0) {
      let cur1 = parseInt(a.charAt(i - 1));
      let cur2 = parseInt(b.charAt(j - 1));
      if (!cur1) {
          cur1 = 0;
      }
      if (!cur2) {
          cur2 = 0;
      }
      let temp = cur1 + cur2 + up;
      if (temp > 9) {
          up = 1;
          temp -= 10;
      } else {
          up = 0;
      }
      i--;
      j--;
      res.unshift(temp); // 入栈
  }
  if (up !== 0) {
      res.unshift(up); // 多余的进位
  }
  let retStr = res.join('');
  return retStr;
}
// test 
calcNum(100); // 理想输出 字符串数值 '464....'