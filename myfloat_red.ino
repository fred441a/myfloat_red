/*
  Low level precision floating point lib
  Author: Henrik Schiøler

*/

// low precision floating pt type
typedef struct myfloat
{
  signed char mantissa;
  signed char exponent;
} myfloat_type;

// convert from double to low precision type
void doub2mydouble(double arg, myfloat_type *res)
{
  int exponent;
  double temp;

  exponent = ceil(log(abs(arg)) / log(2)); // base 2 logarithm
  temp = arg * pow(2, 7 - exponent);
  res->mantissa = (signed char)temp;
  res->exponent = exponent - 7;
}

// convert from low precision type to double
double myfloat2double(myfloat_type *arg1)
{
  double res = (double)(arg1->mantissa) * pow(2, arg1->exponent);
  return res;
}

// multiply to low precision types
void mult_float(myfloat_type *arg1, myfloat_type *arg2, myfloat_type *result)
{
  int temp;
  unsigned char sign;

  sign = 0x80 & ((unsigned char)arg1->mantissa ^ (unsigned char)arg2->mantissa); // find sign of result

  char i = 0;
  temp = (int)(arg1->mantissa) * (int)(arg2->mantissa);

  temp = temp & 0x7f00; // take away sign from product

  while (abs(temp) > 128)
  {
    i++;
    temp = temp >> 1;
  }

  result->mantissa = (unsigned char)temp;

  result->mantissa = result->mantissa | sign; // add recorded sign

  result->exponent = arg1->exponent + arg2->exponent + i;
}

void setup()
{
  /*
  //opgave 1-6

  Serial.begin(9600);
  double temp;
  double da[100];
  myfloat_type mda[100];
  double avrageSum = 0.0;
  for (int i = 0; i <= 99; i++)
  {
    temp = (double)random(-500000,500000)/100000.0;
    da[i] = temp;
    doub2mydouble(temp, &mda[i]);
    mult_float(&mda[i],&mda[i],&mda[i]);
    avrageSum += abs(myfloat2double(&mda[i])-da[i])/abs(da[i]);
  }
  Serial.println((avrageSum/100.0), 10);

// opgave 7-10

  double a = 1.001;
  unsigned long tid = micros();

  for(int i = 0; i <=99;i++){
    da[i] = a;
  }
  Serial.println(micros()-tid);


  myfloat_type f1;
  doub2mydouble(a,&f1);
  myfloat_type f;
  tid = micros();
  for(int i = 0; i<=99;i++){
    mult_float(&f1,&mda[i],&f); memcpy(&f1,&f,2);
  }
  Serial.println(micros()-tid);
*/
  Serial.begin(9600);

  unsigned long tid = micros();
  double sinus = sin(10);
  Serial.println(sinus);
  Serial.println(micros() - tid,10);
  
}

void loop()
{
}
