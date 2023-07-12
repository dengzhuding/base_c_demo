/**
 * @brief 
 * 
  浮点数的表示类似于科学记数法 1000000000(数字), 1.0 X 10⁹(科学记数法), 1.0e9(指数记数法)
  C 语言中的浮点类型有:
    float  至少6位有效数字(指必须表示33.333333的前6位数字，而不是精确到小数点后6位)，且取值范围至少是10﹣³⁷ ~ 10﹢³⁷ 占用32位(8位用于指数的值和符号,24位用于非指数部分(尾数或有效数)及其符号)
    double(双精度)  与float最小取值范围相同，但至少表示10位有效数字   占用64位，多出的32位用来表示有效数(高精度),或者指数部分(范围扩大)
    long double C只保证long double类型至少与double类型的精度相同

    
 */

#include<stdio.h>
#include<math.h>

int main(void) {
  // 声明
  float noah, jonah;
  double trouble;
  float planck = 6.63e-34;
  long double gnp;

  /* 浮点型常量 -1.56E+12  2.84e-3
    正号可以省略，可以没有小数点: 2E5,可以没有指数: 12.2,但不能同时省略(122变成整型了)
    可以省略小数部分(3.E16)或者整型部分(.12E-1),但不能同时省略两者(.E16无效)
    默认情况下，编译器假定浮点型常量是double类型的精度(1.1)，在浮点数后面加上f或F后缀可覆盖默认设置，看作float类型,如2.3f;使用l或L成为long double类型
  */
  .8E-5;
  100.;
  // .E16; // 无效
  
  // C99(并非所有编译器都支持C99这一特性) 新增十六进制表示浮点型常量 - 0x或0X作为前缀，p或P代替e和E,用2的幂代替10的幂(即，p记数法)
  0xa.1fp10; // 表示(10+1/16+15/256)×1024 = 10364.0

  /*
  %f - 打印十进制记数法的float和double类型浮点数
  %e - 打印指数记数法的浮点数
  %a - 打印指数记数法（十六进制的浮点数）
  打印long double类型用%Lf,%Le或%La转换说明
  */
  float aboat = 32000.0;
  double abet = 2.14e9;
  long double dip = 5.32e-5;
  printf("%f can be written %e\n", aboat, aboat); // 32000.000000  3.200000e+04
  printf("And it's %a in hexadecimal, powers of 2 notation\n", aboat); // 0x1.f4p+14
  printf("%f can be written %e\n", abet, abet); // 2140000000.000000  2.140000e+09
  printf("%Lf can be written %Le\n", dip, dip); // 0.000053  5.320000e-05

  float f_a = 3333.333333123456789f; // (float)(3333.333252F) - 精度缺失(小数点后10位)
  double f_b = 3333.333333123456789; // (double)(3333.333333123456669) - 精度缺失(小数点后15位)
  long double f_c = 3333.333333123456789L; // (long double)(3333.3333331234567L) - (小数点后13位)
  printf("十进制:%f  %f  %Lf\n", f_a, f_b, f_c); //  3333.333252  3333.333333  3333.333333
  printf("十进制.8:%.8f  %.8f  %.8Lf\n", f_a, f_b, f_c); // 3333.33325195  3333.33333312  3333.33333312
  printf("指数记数法:%e  %e  %Le\n", f_a, f_b, f_c); // 3.333333e+03  3.333333e+03  3.333333e+03
  printf("十六进制指数记数法:%a  %a  %La\n", f_a, f_b, f_c); // 0x1.a0aaaap+11  0x1.a0aaaaaa39fd7p+11  0xd.05555551cfeba1ep+8

  printf("%e \n", 0.1234E1); // 1.234000e+00

  
  // 浮点值的上溢和下溢
  /*
  上溢(overflow)
    当计算导致数字过大，超过当前类型能表达的范围时就会发生上溢，现在会赋值表示无穷大(inf 或 infinity)
  */
  float toobig = 3.4E38 * 100.0f;
  double toobig2 = 3.4E38 * 100.0f;
  printf("toobig: %e  %e\n", toobig, toobig2); // toobig: inf  3.400000e+40
  /*
  下溢(underflow)
    指数已是最小值(float -37)， 计算机只好把位数部分向右移，空出第一个二进制，并丢弃最后一位二进制
    虽然得到了结果，但是在计算过程中却损失了原本末尾有效位上的数字，这种情况叫做下溢
    C语言把损失了类型精度的浮点值称为低于正常的(subnormal)浮点值
    如果除以一个非常大的值，会导致所有的位都为0
  */
  float toosmall = 3.1415926E-37 / 1.0E10;
  printf("toosmall: %e\n", toosmall); // toosmall: 0.000000e+00

  // NaN - not a number
  printf("asin(1.1) = %f\n", asin(1.1)); // asin(1.1) = nan

  // 浮点数舍入错误 - 计算机缺少足够的小数位来完成正确的运算
  float a, b;
  b = 2.0e20 + 1.0;
  a = b - 2.0e20;
  printf("a = %f, b = %f\n", a, b); // error: a = 4008175468544.000000, b = 200000004008175468544.000000
  float c, d;
  d = 2.0e5 + 1.0;
  c = d - 2.0e5;
  printf("c = %f, d = %f\n", c, d); // ok: c = 1.000000, d = 200001.000000

  /**
   * 把一个类型的数值初始化给不同的类型的变量时，
   * 编译器会把值转换成与变量匹配的类型，这将导致部分数据丢弃
   * 
   * 命名约定a(方便一样看出变量类型)：
   * i_xxx - int类型
   * u_xxx - unsigned int 类型
   * s_xxx - short int 
   * us_xxx - unsigned short int
   * 
   * c_xxx - char 
   * f_xxx - float
   * d_xxx - double
   * 等等类似这样的变量命名
   * 
   */
  int i_num = 12.99; // (double)(12.99000000000000021) -> int = 12
  float f_pi = 3.1415926536; // (double)(3.141592653600000062) -> float
  printf("i_num: %d  f_pi: %f\n", i_num, f_pi); // i_num: 12  f_pi: 3.141593

  return 0;
}