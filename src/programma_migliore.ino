#define numled 9 //numero di led da controllare. Vanno collegati a partire dal pin n°2
#define letture 300 //è il numero di valori di campionamento raccolti dal microfono per fare la media (forse 300 rallentano un po' troppo)
#define minimal 250 //è il valore zero, cioè il rumore di fondo. Si aggira sempre intorno a questa cifra

void displayer(float value); //inizializzo il sottoprogramma che controlla i led. Necessita di un valore che gli venga passato.
void controller();
int sensy=0;
void setup()
{
    Serial.begin(9600);
    for(int i=2; i<2+numled; i++) //inizializzo tutti i pin che controllano i led
      pinMode(i, OUTPUT);
    pinMode(12, INPUT);
}

void loop()
{
    controller();
    float media=0;
    for(int i=0; i<letture; i++)  //fa le letture di campionamento da microfono
    {
      media+=abs(analogRead(A0)-minimal)/letture;
    }
  //  Serial.println(media);
 /*   media*=1023;
    media/=512;
    media*=9; */
    displayer(media);  //comanda i led (void a seguire)
}

void displayer(float value)
{
    for(int i=2; i<numled+sensy; i++) //a seconda di quale valore assume la media (difficilmente supera 450. . .) accende i led...
    {                             // è il primo metodo efficace che mi è venuto in mente, però non è male...
        if(value>=minimal/(numled+sensy))
        {
            digitalWrite(i, HIGH);
            value-=minimal/(numled);
        }
        else
        {
            digitalWrite(i, LOW);
        }
    }
    delay(25);
}

void controller()
{
    int total=0;
    for(int i=0; i<50; i++)
        if(digitalRead(12)==HIGH)
            total++;
    if(total>0)
    {
        sensy++;
        if(sensy>=10)
            sensy=0;
        for(int i=2; i<sensy+2; i++)
            digitalWrite(i, HIGH);
        delay(1000);
        for(int i=2; i<sensy+2; i++)
            digitalWrite(i, LOW);
    }
        Serial.println(sensy);
}
