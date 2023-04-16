class Mode {
private:
  int mode = 0;
  void (*onChanged)();
public:
  Mode(void (*changed)()) {
    onChanged = changed;
  }

  String getModeString(){
    switch (mode) {
      case -4 : return "-1/4";
      case -3 : return "-1/3";
      case -2 : return "-1/2";
      case -1 : return "-1/1";
      case 0 : return "1/1";
      case 1 : return "1/2";
      case 2 : return "1/3";
      case 3 : return "1/4";
      case 4 : return "1/5";
      default : return "1/1";
    }

  };

  int getModeDivider(){
  switch (mode) {
      case -4 : return -4;
      case -3 : return -3;
      case -2 : return -2;
      case -1 : return -1;
      case 0 : return 1;
      case 1 : return 2;
      case 2 : return 3;
      case 3 : return 4;
      case 4 : return 5;
      default : return 1/1;
    }
  };

  void setMode(int newMode) {
    if (mode != newMode) {
      mode = newMode;
      onChanged();
    }
  };
};