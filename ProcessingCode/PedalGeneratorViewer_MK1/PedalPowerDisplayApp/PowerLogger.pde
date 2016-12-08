public class PowerLogger
{
  ArrayList<Reading> theReadings;
  PrintWriter        theOutputWriter;
  String             startTimeDateString;
  
  public PowerLogger()
  {
    theReadings = new ArrayList<Reading>();
  }
  
  public void addLog(float[] powersIn, long timeStampIn)
  {
    theReadings.add(new Reading(powersIn, timeStampIn));
  }
  
  public void reset(){
    theReadings.clear();
  }
  
  public void writeToFile()
  {
    System.out.println("Writing to file at:" +  startTimeDateString);
    if (startTimeDateString == null){
     startTimeDateString = getDateTimeString(); 
    }
    theOutputWriter = createWriter(startTimeDateString + ".csv");
   // TODO: write it to a file.
   if (theReadings != null){
     for (Reading s : theReadings)
     {
       theOutputWriter.println(s.toCSVLine());  
     }
   }
   
   theOutputWriter.flush();
   theOutputWriter.close();
   
  }
  
  public void setStartTime(String startTimeDateIn){
    startTimeDateString = startTimeDateIn;
  }
}