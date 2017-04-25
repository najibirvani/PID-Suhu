int sensor = A0;
int suhu;
float tempSuhu, target_suhu = 50.0;
float a,b,c;
float current_error, previous_error1 = 0, previous_error2 = 0;
float Kp = 101.021, Ki = 2.3065, Kd = 42.3718, Ts=2.5;
int pwm, previous_pwm = 0, pwm_out;

void setup() {
  // put your setup code here, to run once:
  analogReference(INTERNAL);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  suhu = analogRead(sensor);
  tempSuhu = suhu/9.31;
  Serial.print(tempSuhu);Serial.print('\t');Serial.println(target_suhu);

  current_error = target_suhu-tempSuhu;
  a = Kp + Ki*Ts/2 + Kd/Ts;
  b = -Kp + Ki*Ts/2 - 2*Kd/Ts;
  c = Kd/Ts;
  pwm = previous_pwm + a*current_error + b*previous_error1 + c*previous_error2;
  
  if (pwm>255)pwm=255;
  if (pwm<0)pwm=0;

  pwm_out = map(pwm,0,255,255,0);
  analogWrite(11, pwm_out);
  
  previous_pwm = pwm;
  previous_error2 = previous_error1;
  previous_error1 = current_error;

  delay(2500);
}
