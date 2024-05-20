Struktura projektu:

CliFacade



CarDatabase
int nextId;
map<int, CarData> database; //pomyśleć jak zaznaczyć zmianę stanu z dostępnego na sold


CarData
int year, price, increment;
int priceDropCount;
std::string model;
static int firstTimer, laterTimer;
TimerService& timerService;

void updatePrice();


TimerService
void registerNewTimer();
void secondPassed();


Timer
int duration;
chrono cośtam start;



Clock
void end();
void pause();