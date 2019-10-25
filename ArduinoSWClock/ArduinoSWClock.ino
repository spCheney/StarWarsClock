class Set {
    virtual int set(byte inc, byte dec, byte next, int state) = 0;      //inc = increments the current state by one
};                                                                      //dec = decrements the current state by one
                                                                        //next = moves on to the next state, ex hour to minute to month to day...
                                                                        //state = current state of the variable we are setting

class Time : public Set {
  int set(byte inc, byte dec, byte next, int state) {
    int hour = state / 100;             //the state is currently in the format with hour as 3rd and 4th digits
    int minute = state - hour;          //and minutes as the 1st and 2nd digits
    
    int i = 0;            //we have to set the minutes and hours so we are going to go through this process twice
    while (i < 2) {
      if(next == HIGH) {
        i += 1;
      }
      else if(inc == HIGH) {
        if(i == 0) {
          if(hour > 24) {
            hour = 1;
          }
          else {
            hour += 1;
          }
        }
        else {
          if(minute >= 60) {
            minute = 0;
          }
          else {
            minute += 1;
          }
        }
      }
      else if(dec == HIGH) {
        if(i == 0) {
          if(hour <= 0) {
            hour = 24;
          }
          else {
            hour -= 1;
          }
        }
        else {
          if(minute <= 0) {
            minute = 59;
          }
          else {
            minute -= 1;
          }
        }
      }
    }
    return ((hour * 100) + minute);
  }
};

class Date : public Set {
  int set(byte inc, byte dec, byte next, int state) {
    int month = state / 1000000;                  //state is in the format with the months in the 7th and 8th digits
    int day = (state - month) / 10000;            //days in the 5th and 6th digit
    int year = state - month - day;               //and years in the 1st through 4th digit
    int maxDays = maxDaysOfMonth(month, year);
    
    int i = 0;
    while (i < 3) {
      if(next == HIGH) {
        i += 1;
      }
      else if(inc == HIGH) {
        if(i == 0) {
          if(month > 12) {
            month = 1;
          }
          else {
            month += 1;
          }
        }
        else if(i == 1) {
          if(day > maxDays) {
            day = 0;
          }
          else {
            day += 1;
          }
        }
        else {
          year += 1;
        }
      }
      else if(dec == HIGH) {
        if(i == 0) {
          if(month == 1)
          {
            month = 12;
          }
          else {
            month -= 1;
          }
        }
        else if(i == 1) {
          if(day == 1) {
            day = maxDays;
          }
          else {
            day -= 1;
          }
        }
        else {
          year -= 1;
        }
      }
    }
    return (month * 1000000) + (day * 10000) + year;
  }

  //calculates the max amount of days in a given month
  int maxDaysOfMonth(int month, int year) {
    switch (month) {
      case 2:
        if(checkForLeapYear(year)) {
          return 29;
        }
        else {
          return 28;
        }
      case 4:
      case 6:
      case 9:
      case 11:
        return 30;
      default:
        return 31;
    }
  }

  //checks if a year is a leap year
  bool checkForLeapYear(int year) {
    if(year % 400 == 0) {
      return true;
    }
    else if(year % 100 == 0) {
      return false;
    }
    else if(year % 4 == 0) {
      return true;
    }
    else {
      return false;
    }
  }
};

int minuteHasPassed(int prevTime) {
  int newTime = prevTime + 1;
  bool timeChecked = false;
  int valueToCheck = 100;
  int maxValue = 60;
  while(!timeChecked) {
    if((newTime % valueToCheck) > maxValue) {
      newTime += valueToCheck;
    }

    valueToCheck *= 100;
    switch (valueToCheck) {
      case (10000):
        maxValue = 24;
        break;
      case (1000000):
        maxValue = 
    }
  }

  return newTime;
}


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
