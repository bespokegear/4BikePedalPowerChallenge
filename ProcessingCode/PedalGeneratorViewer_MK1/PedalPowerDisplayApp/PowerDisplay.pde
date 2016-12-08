class PowerDisplay{
   
  int theColor;
  int theDimColor;
  int theSelectedColor;
  float currentPower;
  ControlP5 theDisplayCp5;
  int positionX, positionY, sizeX, sizeY;
  int id;
  public Textlabel tl; 
  boolean hasWon = false;
  Textlabel wattsIndicator;
  int numDisplays;
  
  
  public PowerDisplay(ControlP5 theCp5In, int id)
  {
    theDisplayCp5 = theCp5In;   
    tl = theDisplayCp5.addTextlabel("" + id)
         .setText ("---")
         .setColor(0)
    ;
  }
  
  public void show()
  {
    tl.setVisible(true);  
    wattsIndicator.setVisible(true);
  }
  
  public void hide()
  {
    tl.setVisible(false); 
    wattsIndicator.setVisible(false);
  }
  
  public void setPosition( int positionXIn, int positionYIn, int sizeXIn, int sizeYIn)
  {
    positionX = positionXIn;
    positionY = positionYIn;
    sizeX = sizeXIn;
    sizeY = sizeYIn;
    reset();
    
    wattsIndicator = cp5.addLabel("" + positionX + positionY).setColor(0);
    wattsIndicator.setText("w");
    wattsIndicator.setFont(createFont("BEBAS___", height / 16));
    wattsIndicator.setPosition(positionX + 3*sizeX/4, positionY + 4*sizeY/7);
  }
  
  public void setBackColor(int theColorIn, int theDimColorIn)
  {
    theColor = theColorIn;
    theDimColor = theDimColorIn;
    theSelectedColor = theColor;
  }
  
  public void dimBackground(){
    theSelectedColor = theDimColor;
  }
  
  public void resetColor(){
    theSelectedColor = theColor;
  }
  
  public void renderOnScreen()
  {
    if (hasWon){
      int framesFlashPeriod = 30;
      int modulusFrames = frameCount % framesFlashPeriod;
      if (modulusFrames > framesFlashPeriod/2){
        fill(255);
      }
    else{
        fill(theDimColor);
      }
    }
    else{
      fill(theSelectedColor);
    }
    rect(positionX, positionY, sizeX, sizeY );
  }
  
  public void setPower(float thePower){
    int numWatts = (int)thePower;
    tl.setText("" + numWatts);
  }
  
  public void reset()
  {
   hasWon = false;
   theSelectedColor = theColor; 
   tl.setPosition(positionX + sizeX/4, positionY + (sizeY / 2));
   tl.setFont(createFont("BEBAS___", height / 4));
   tl.getValueLabel().alignX(ControlP5.LEFT);
   tl.getValueLabel().alignY(ControlP5.TOP_OUTSIDE);
   tl.getValueLabel().setPaddingY(-height/8);
  }
  
  public void setWinnerState(boolean isWinnerIn){
    hasWon = isWinnerIn;
    if (isWinnerIn){
      System.out.println("Setting winner:");
    }
    else {
       tl.setFont(createFont("BEBAS___", height / 12)); 
       dimBackground();
    }
  }
  
}