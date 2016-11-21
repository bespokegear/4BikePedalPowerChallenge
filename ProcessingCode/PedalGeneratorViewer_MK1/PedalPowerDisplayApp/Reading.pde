public class Reading
{
   float[] powers;
   long timeStamp;
   
   public Reading(float[] powersIn, long timeStampIn)
   {
      powers = new float[powersIn.length];
      for (int i = 0; i < powers.length; i++){
         powers[i] = powersIn[i]; 
      }
      timeStamp = timeStampIn;
   }
   
   public String toCSVLine()
   {
    String toReturn = "";
    for (int i = 0; i < powers.length; i++){
      toReturn += "" + powers[i]; 
      toReturn += ",";  
    }
    toReturn += "" + timeStamp;
    return toReturn;    
   }
}