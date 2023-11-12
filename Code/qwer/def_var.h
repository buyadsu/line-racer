
int PID = 0, I, Error = 0, lastError = 0;

// Encoder 
int leftCounter = 0;
int rightCounter = 0;

/*************************************************************************
* Global variables
*************************************************************************/
bool enableMotor = false;
bool enableEDF = false;
bool serialSensor = false;

/* Serial */
int incomingByte;



bool start = false;

short state = 0;

bool Timer = false;
unsigned char lineCount = 0;
unsigned long decreasingSpeed = 4000;
unsigned long previousTime = 0;
uint16_t position;
int pposition;