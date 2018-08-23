

#define  ON  true
#define OFF false
#define NBR_SEG 5

// pour un ardurino un long fait 32 bit
typedef struct  s_light_pack
{
  long  beg;
  long  period;
  long  offset;
  long  nbr_seg;
  long  lst_pt[NBR_SEG * 2];
  long  end;
}   t_segments;


void    pin_test(int tick)
{
  digitalWrite(13, HIGH);
  delay(tick);
  digitalWrite(13, LOW);
  delay(tick);
}


void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  digitalWrite(13, LOW);
}


  byte  buf[256];
  
void serialEvent()
{
  int i;
  int pack_size;

  pack_size = sizeof(t_segments);
  for(i = 0;i < pack_size && Serial.available(); i++)
  {
    buf[i] = Serial.read();
  }
  
    pin_test((i == pack_size) ? 1000 : 100);
}

void loop() {
  // put your main code here, to run repeatedly:

}
