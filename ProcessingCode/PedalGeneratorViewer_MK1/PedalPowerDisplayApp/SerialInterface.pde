import processing.serial.*;

public class SerialInterface{
 
  Serial serialObject;
  int lf = 10; // line feed;
  PedalPowerDisplayApp theApp;
  float[] currentPowerReadings;
  long    millisTimeStamp;
  PowerLogger powerLogger;  
  boolean raceRunning;
  
  
  public SerialInterface(PedalPowerDisplayApp theAppIn)
  {
    theApp = theAppIn;
    powerLogger = new PowerLogger();
    if (Serial.list().length > 0)
    {
      serialObject = new Serial(theApp, Serial.list()[0], PedalConstants.baudRate); 
    }
    currentPowerReadings = new float[4];
  }
  
  public void setCOMPort(String channel)
  {
     if (serialObject != null)
     {
      serialObject.stop(); 
     }
     delay(30);
     
     serialObject = new Serial(theApp, channel, PedalConstants.baudRate); 
  }
  
  String[] getCOMPortList()
  {
    return Serial.list(); 
  }
  
  public void checkForIncoming()
  {
    if (serialObject != null){
      String inString = serialObject.readStringUntil(lf);
      if (inString != null){
//        println("Unfiltered Rec:" + inString);
        if (inString.startsWith("a")) // it's probably going to be of interest
        {
          String deciderString = inString.substring(1,inString.length()-1);
          
          int whereIsT = deciderString.indexOf("t");
          if (deciderString.startsWith("START")){
            
            
            if (!raceRunning){
              powerLogger.reset();
              powerLogger.setStartTime(theApp.getDateTimeString());
              System.out.println("Race started...");
            }
          }
          
          else if (deciderString.startsWith("A") && whereIsT != -1 ){
            currentPowerReadings = getPowerReadingsFromString(deciderString);
            int tIndex = deciderString.indexOf("T");
            int tsIndex = deciderString.indexOf("t");
            millisTimeStamp         = (int)tryToParseThis(deciderString,tIndex+1,tsIndex); 
            powerLogger.addLog(currentPowerReadings, millisTimeStamp);
            
            for (int i = 0; i < currentPowerReadings.length; i++){
              theDisplayElements.get(i).setPower(currentPowerReadings[i]);
            }
          }
          
          else if(deciderString.startsWith("END"))
          {
            if (powerLogger != null){ 
              powerLogger.writeToFile();
            }
            raceRunning = false;
          }
          
          else if (deciderString.startsWith("RESULT"))
          {
            System.out.println("Race results are in...");
            float[] finalPowerReadings = getPowerReadingsFromString(deciderString);
            int maxIndex = 0;
            float maxVal = 0;
            for (byte b = 0; b < finalPowerReadings.length; b++){
              if (finalPowerReadings[b] > maxVal){
                maxVal = finalPowerReadings[b];
                maxIndex = b;
              }
            }
            System.out.println("Player " + (maxIndex+1) +  " was winner");
            for (int i = 0; i < finalPowerReadings.length; i++){
              if (maxIndex == i){
               theDisplayElements.get(i).setWinnerState(true); 
              }
              else{
                theDisplayElements.get(i).setWinnerState(false);
              }
              theDisplayElements.get(i).setPower(finalPowerReadings[i]);
            }            
          }
          else if (deciderString.startsWith("RESET")){
           for (PowerDisplay pd : theApp.theDisplayElements){
              pd.reset();
              pd.tl.setText("");
            } 
          }
        }
      }
    }
  }
  
  private int tryToParseThis(String toParse, int startIndex, int endIndex)
  {
    int toReturn = 0;
    if (startIndex >= 0 && endIndex >0)
    {
      String intString = "";
      try {
        intString = toParse.substring(startIndex, endIndex);
        toReturn = Integer.parseInt(intString);   
      }
      catch (NumberFormatException exc){
       System.err.print("ERR while parsing:");
       System.err.println("" + intString);
      }
      catch (IndexOutOfBoundsException e){
        System.err.println("ERR: indexes wrong");
      }
    }
    return toReturn;
  }  
  
  public void setGUIElementsFromReading(Reading thisReading)
  {
    for (int i = 0; i < thisReading.powers.length; i++){
      theDisplayElements.get(i).setPower(thisReading.powers[i]);
    }
  }
  
  public float[] getPowerReadingsFromString(String stringIn){
    float[] toReturn = new float[4];    
    int aIndex = stringIn.indexOf("A");
    int bIndex = stringIn.indexOf("B");
    int cIndex = stringIn.indexOf("C");
    int dIndex = stringIn.indexOf("D");
    int tIndex = stringIn.indexOf("T");   
    toReturn[0] =      tryToParseThis(stringIn,aIndex+1,bIndex)/100f;
    toReturn[1] =      tryToParseThis(stringIn,bIndex+1,cIndex)/100f;
    toReturn[2] =      tryToParseThis(stringIn,cIndex+1,dIndex)/100f;
    toReturn[3] =      tryToParseThis(stringIn,dIndex+1,dIndex+6)/100f;
    return toReturn;
  }
}