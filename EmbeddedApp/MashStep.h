

#define STEP_INI  0
#define STEP_RUN  1
#define STEP_WAIT 2
#define STEP_DONE 3

class MashStep {
  
  private:
    int curTime;
    int progTime;
    int progTemp;
    
  public:
    void start(int curTemp);
    int updateState();
    
};
