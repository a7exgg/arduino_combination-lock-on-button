/* Кодовый замок на кнопках.
    В схеме присутствуют три кнопки, зеленый, красный и желтый светодиоды. 
    После запуска программы горит желтый светодиод. Пользователю необходимо нажать три кнопки в правильной
    комбинации. 
    Если кнопки нажаты правильно, загорается зеленый светодиод. 
    Если кнопки нажаты неправильно ­ красный светодиод делает пять коротких импульсов. 

    Для устранения дребезга больших кнопок применяется millis() и 200 мс задержки.
*/

#define butt1 2                 //  pin2 для кнопки 1
#define butt2 3                 //  pin3 для кнопки 2
#define butt3 4                 //  pin4 для кнопки 3
#define ledR 8                  //  pin8 для светодиода красного
#define ledY 9                  //  pin9 для светодиода желтого
#define ledG 10                 //  pin10 для светодиода зеленого

boolean butt1_status = false;   //  статус нажатия кнопки 1
boolean butt2_status = false;   //  статус нажатия кнопки 2
boolean butt3_status = false;   //  статус нажатия кнопки 3

boolean butt1_flag = false;
boolean butt2_flag = false;
boolean butt3_flag = false;

unsigned long last_press;       //  переменная для устранения "дребезга"

byte myArr[3];                  //  массив из трёх элементов для хранения текущих значений
byte controlArr[] = {3, 1, 2};  //  массив для хранения контрольных значений

void setup() {
  Serial.begin(9600);
  pinMode(butt1, INPUT_PULLUP);
  pinMode(butt2, INPUT_PULLUP);
  pinMode(butt3, INPUT_PULLUP);
  pinMode(ledR, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ledG, OUTPUT);
  wait();
}

void loop() {
  //  инвертируем нажатия на логические "1" из-за INPUT_PULLUP:
  butt1_status = !digitalRead(butt1);
  butt2_status = !digitalRead(butt2);
  butt3_status = !digitalRead(butt3);

  if (butt1_status == true && millis() - last_press > 200) {  //  если первая кнопка нажата, то
    last_press = millis();
    checkArr1(1);                                             //  вызываем функцию checkArr и кладем в неё 1
  }
  if (butt2_status == true && millis() - last_press > 200) {  //  если вторая кнопка нажата, то
    last_press = millis();
    checkArr1(2);
  }
  if (butt3_status == true && millis() - last_press > 200) {  //  если третья кнопка нажата, то
    last_press = millis();
    checkArr1(3);
  }

}

//  Функции для проверки массивов:
void checkArr1(byte button) {   //  проверяем элемент
  if (myArr[0] != 0) {          //  если элемент занят, то пробуем положить в следующий
    checkArr2(button);
  } else if (myArr[0] == 0) {
    myArr[0] = button;          //  если элемент массива свободен, то заносим в него
  }
}
void checkArr2(byte button) {
  if (myArr[1] != 0) {
    checkArr3(button);
  } else if ((myArr[1] == 0)) {
    myArr[1] = button;
  }
}
void checkArr3(byte button) {
  if (myArr[2] == 0) {
    myArr[2] = button;
    finalCode();                //  запустить финальную процедуру проверки
  }
}
void finalCode() {
  if ((myArr[0] == controlArr[0]) && (myArr[1] == controlArr[1]) && (myArr[2] == controlArr[2])) { // если все ок, то
    correct();                      //  включаем правильный ввод
    delay(2000);
    cleaner();                      //  чистим массив
    wait();                         //  обнулить
  } else {
    incorrect();                    //  включаем неправильный ввод
    cleaner();
    wait();
  }
}

//  Идентификация ожидания:
void wait() {
  digitalWrite(ledG, LOW);
  digitalWrite(ledR, LOW);
  digitalWrite(ledY, HIGH);
}
//  Идентификация правильного ввода:
void correct() {
  digitalWrite(ledY, LOW);
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, HIGH);
}
//  Идентификация неправильного ввода:
void incorrect() {
  digitalWrite(ledY, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledR, HIGH);
  delay(200);
  digitalWrite(ledR, LOW);
  delay(200);
  digitalWrite(ledR, HIGH);
  delay(200);
  digitalWrite(ledR, LOW);
  delay(200);
  digitalWrite(ledR, HIGH);
  delay(200);
  digitalWrite(ledR, LOW);
  delay(200);
  digitalWrite(ledR, HIGH);
  delay(200);
  digitalWrite(ledR, LOW);
  delay(200);
  digitalWrite(ledR, HIGH);
  delay(200);
  digitalWrite(ledR, LOW);
}
// Для чистки массива:
void cleaner() {
  for (byte i = 0; i < 3; i++) { 
    myArr[i] = 0;
  }
}
