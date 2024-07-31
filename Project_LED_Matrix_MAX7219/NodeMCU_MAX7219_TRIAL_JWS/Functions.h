void getTime(){ 
  timeClient.update();
  Epoch_Time = timeClient.getEpochTime()+ 1;
  Serial.println(Epoch_Time);
  delay(500);
  if( Epoch_Time >= 1357041600) { 
     setTime(Epoch_Time);
  }
}

void GetDateTime() {
//Uncomment for Debug
//Serial.println( String(_day) + "-" + String(_month) + "-" + String(_year));
//Serial.println( String(_hour24) + ":" + String(_minute) + ":" + String(_second));

  _day=day();
  _month=month();
  _year=year();
  _hour24=hour();
  _minute=minute();
  _second=second();
  _dtw=weekday();

  hr24=_hour24;
  
  if (hr24>12) { _hour12=hr24-12; }
  else if (hr24==0) { _hour12=12; }
  else { _hour12=hr24; }

  if (hr24<12) { st="AM"; }
  else { st="PM"; } 
}

void HitungJadwalSholat() {

  /*
    CALCULATION METHOD
    ------------------
    Jafari,   // Ithna Ashari
    Karachi,  // University of Islamic Sciences, Karachi
    ISNA,     // Islamic Society of North America (ISNA)
    MWL,      // Muslim World League (MWL)
    Makkah,   // Umm al-Qura, Makkah
    Egypt,    // Egyptian General Authority of Survey
    Custom,   // Custom Setting
    JURISTIC
    --------
    Shafii,    // Shafii (standard)
    Hanafi,    // Hanafi
    ADJUSTING METHOD
    ----------------
    None,        // No adjustment
    MidNight,   // middle of night
    OneSeventh, // 1/7th of night
    AngleBased, // angle/60th of night
    TIME IDS
    --------
    Fajr,
    Sunrise,
    Dhuhr,
    Asr,
    Sunset,
    Maghrib,
    Isha
  */
  
  int tahun = year();
  int bulan = month();
  int tanggal = day();
  float latitude = -7.058037;
  float longitude = 110.433432;
  int zonawaktu = 7;
  
  set_calc_method(Karachi);
  set_asr_method(Shafii);
  set_high_lats_adjust_method(AngleBased);
  set_fajr_angle(20);
  set_isha_angle(18);  

  get_prayer_times(tahun, bulan, tanggal, latitude, longitude, zonawaktu, times);
}

void brightSet(){
  if ( (_hour24 >= 0 && _hour24 <= 7) || (_hour24 >=17 && _hour24 <= 23)){ sendCmdAll(CMD_INTENSITY, 2); }
  
  else { sendCmdAll(CMD_INTENSITY, 5); }
}

void TampilJadwalSholat() {
  static uint32_t pM;
  uint32_t cM = millis();
  
  char sholat[7];
  char jam[5];
  char TimeName[][8] = {"SUBUH","TERBIT","DZUHR","ASHAR","TRBNM","MAGRB","ISYA"};
  int hours, minutes;
  int ihti = 2;

  if (cM - pM >= 0) {
    pM = cM;
    clr();
    
//    if (i == 1) {i = 2;} // Abaikan Terbit
    if (ijadwal == 4) {ijadwal = 5;} // Abaikan Terbenam

    get_float_time_parts(times[ijadwal], hours, minutes);
    minutes = minutes + ihti;

    if (minutes >= 60) {
      minutes = minutes - 60;
      hours ++;
    }

    char *sholat = TimeName[ijadwal];
    sprintf(jam,"%02d:%02d", hours, minutes);     
    Disp.setFont(verdanav2);
    JadwalAnim(sholat, jam);
//    textCenter(-1, sholat); 
//    textCenter(7, jam);
     
//    ijadwal++;

    if (ijadwal > 6) {
      get_float_time_parts(times[0], hours, minutes);
      minutes = minutes + ihti;
      if (minutes < 11) {
        minutes = 60 - minutes;
        hours --;
      } else {
        minutes = minutes - 10 ;
      }
      sprintf(jam,"%02d:%02d", hours, minutes);
      Disp.drawRect(0,0,32,15,0,0);
      Disp.setFont(verdanav2);
      JadwalAnim("IMSAK", jam);
//      textCenter(-1, "IMSAK"); 
//      textCenter(7, jam); 
      
      if (ijadwal > 7) {
        ijadwal = 0;
        clr();
        tmpinfo = 0;
      }
    }   
  }
}

void scrolling_date(){
  teks = String(String(nameoftheday[_dtw-1]) + ", " +String(_day) + "-" + String(month_name[_month-1]) + "-" + String(_year) + " ");
  
  printStringWithShift(teks,40);
  delay(10);
  printStringWithShift("      ",40);
  delay(10);
  tmpinfo = 0;
}

void showAnimClock(){
  if (_second %2 == 0) { dots = !dots; }
  if (_second == 25)   { tmpinfo = 2; }
  
  byte digPos[4]={1,8,17,25};
  int digHt = 12;
  int num = 4; 
  int i;
  if(del==0) {
    del = digHt;
    for(i=0; i<num; i++) digold[i] = dig[i];
    dig[0] = h/10 ? h/10 : 10;
    dig[1] = h%10;
    dig[2] = m/10;
    dig[3] = m%10;
    for(i=0; i<num; i++)  digtrans[i] = (dig[i]==digold[i]) ? 0 : digHt;
  } else
    del--;
  
  clr();
  for(i=0; i<num; i++) {
    if(digtrans[i]==0) {
      dy=0;
      showDigit(dig[i], digPos[i], dig6x8);
    } else {
      dy = digHt-digtrans[i];
      showDigit(digold[i], digPos[i], dig6x8);
      dy = -digtrans[i];
      showDigit(dig[i], digPos[i], dig6x8);
      digtrans[i]--;
    }
  }
  dy=0;
  setCol(15,dots ? B00100100 : 0);
  refreshAll();
 delay(30);
}

void AlarmSholat() {  
  int hours, minutes, seconds;

//---------------------------------------Imsak----------------------------------------------//
  get_float_time_parts(times[0], hours, minutes);
  minutes = minutes + ihti;
  if (minutes < 10) {
    minutes = 60 - minutes;
    hours --;
  } else {
    minutes = minutes - 10 ;
  }
  if (_hour24 == hours && _minute == minutes) {
    tipealarm = 0;
    detikbeep = 0;
    clr();
    tmpinfo = 3;
  }

//---------------------------------------Subuh----------------------------------------------//
  get_float_time_parts(times[0], hours, minutes);
  minutes = minutes + ihti;
  if (minutes >= 60) {
    minutes = minutes - 60;
    hours ++;
  }
  if (_hour24 == hours && _minute == minutes) {
    tipealarm = 1;
    detikbeep = 0;
    clr();
    tmpinfo = 3;
  }

//---------------------------------------Dzuhur----------------------------------------------//
  get_float_time_parts(times[2], hours, minutes);
  minutes = minutes + ihti;
  if (minutes >= 60) {
    minutes = minutes - 60;
    hours ++;
  }
  if (_hour24 == hours && _minute == minutes &&  _second == 0 && _dtw != 5) {
    tipealarm = 2;
    detikbeep = 0;
    clr();
    tmpinfo = 3;
  } 
  else if (_hour24 == hours && _minute == minutes && _second == 0 && _dtw == 5) {
    tipealarm = 3;
    detikbeep = 0;
    clr();
    tmpinfo = 3;
  }

//---------------------------------------Ashar----------------------------------------------//
  get_float_time_parts(times[3], hours, minutes);
  minutes = minutes + ihti;
  if (minutes >= 60) {
    minutes = minutes - 60;
    hours ++;
  }
  if (_hour24 == hours && _minute == minutes && _second == 0) {
    tipealarm = 4;
    detikbeep = 0;
    clr();
    tmpinfo = 3;
  }
  
//--------------------------------------Maghrib----------------------------------------------//
  get_float_time_parts(times[5], hours, minutes);
  minutes = minutes + ihti;
  if (minutes >= 60) {
    minutes = minutes - 60;
    hours ++;
  }
  if (_hour24 == hours && _minute == minutes && _second == 0) {
    tipealarm = 5;
    detikbeep = 0;
    clr();
    tmpinfo = 3;
  }

//----------------------------------------Isya-----------------------------------------------//
  get_float_time_parts(times[6], hours, minutes);
  minutes = minutes + ihti;
  if (minutes >= 60) {
    minutes = minutes - 60;
    hours ++;
  }
  if (_hour24 == hours && _minute == minutes && _second == 0) {
    tipealarm = 6;
    detikbeep = 0;
    clr();
    tmpinfo = 3;
  }  
}

void TampilAdzan() {
  BunyiBeep(2,30);

  static uint32_t pM;
  uint32_t cM = millis();
  static uint16_t det;
  int hours, minutes;
  
  if (beep){
    if (tipealarm == 0) {
      printStringWithShift("IMSAK",1);
    }
    
    if (tipealarm == 1) {
      printStringWithShift("SUBUH",1);
    }
    
    if (tipealarm == 2) {
      printStringWithShift("DZUHR",1);
    }
    
    if (tipealarm == 3) {
      printStringWithShift("JUMAT",1);
    }
    
    if (tipealarm == 4) {
      printStringWithShift("ASHAR",1);
    }
    
    if (tipealarm == 5) {
      printStringWithShift("MAGHRB",1);
    } 
    
    if (tipealarm == 6) {
      printStringWithShift("ISYA",1);
    }  
  }else { clr(); }
  

  if (cM-pM >= 1000) {
    det++;
    if (tipealarm == 0 or tipealarm == 1 or tipealarm == 2 or tipealarm == 3 or tipealarm == 4 or tipealarm == 5 or tipealarm == 6) {
      if (det == 30) {
        clr();
        det = 0;
        detikbeep = 0;
        tmpinfo = 0;
      } 
    }
    pM = cM;
  }  
}

void tampilinfo() {
  switch(tmpinfo) {
    case 0 :
      clr();
      noTone(buzzer);
      showAnimClock();
      break;

    case 1 :
      scrolling_date();
      break;

    case 2 :
      TampilJadwalSholat();
      break;

    case 3 :
      TampilAdzan();
  }
}
