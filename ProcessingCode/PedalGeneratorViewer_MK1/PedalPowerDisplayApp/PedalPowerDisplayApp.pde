// TODONE: default colour select buttons
// TODONE: finish power displays - little watts indicator.
// TODONE: resize buttons.
// TODONE: get rid of decimals for display, but still store them
// TODONE: add try-catch when selecting com port  
          //(this was supposed to be for if starting the program with no com port enumerated)
          // now just checks whether a com port exists.
// TODONE: check line.startswith and line.ends with - ignore that line if NFE
// TODONE: indicate which com port is selected. (draw a line / triangle)
// TODONE: dim the losers colour on finish.
// TODONE: deal with restarts more elegantly.
        // implement a reset function that is called when race is started.


/*
 Reinnovation Pedal power display 
 Tom Grover, 24/09/2016
  
   external files required:  
   1 - font file - located in data folder   
   
   TIME LOGS:
     Start 1649
     Fin   1715
     (26 mins)     
     ___
     Start 2159
     Fin   2220
     (21 mins)
     (RT:47) 
     ___
     Start  1944
     Finish 2103
     (79 mins)
     (RT:126min)
     ___
     start 1213
     finish 1305
     (52 mins)
     (RT:178mins)
     ___
     start 1330
     fin 1455
     (85mins)
     (258mins)
     ___
     start 1200
     finish 1315
     (75mins)
     (333mins )
     ---
     start 1330
     finish 1415 
     (378 minutes)
     
     --- 
     start 1922
     fin 1942
      
     --- 
     start 1144
     fin   1250
     
     --
     start 1430
     fin   1530
     
*/



import controlP5.*;
import processing.serial.*;

// Global variables:
ControlP5 cp5;
Button showPowerButton;
Button showSettingsButton;
Button[] allMainButtons;

ArrayList<PowerDisplay> theDisplayElements;
SettingsDisplay settingsDisp;
boolean displayMode = PedalConstants.pedalDisplay;
long lastFrameMouseMove;
SerialInterface theDataProvider;

void setup(){
  //colorDefs = new PedalConstants();
  System.out.println("Starting pedal generator at time: " + getDateTimeString());
  cp5 = new ControlP5(this);
  cp5.setFont(createFont("BEBAS___", height / 32));
  theDataProvider = new SerialInterface(this);
  
  
  initDisplayElements();
  initButtons();
  settingsDisp = new SettingsDisplay(cp5, theDataProvider, theDisplayElements);  
  fullScreen();
  //size(600, 480);
  
  frameRate(20); // eases load on CPU - drawing at 60fps is intensive
  
  settingsDisp.hide();
  for (PowerDisplay pd : theDisplayElements){
     pd.show(); 
  }
   
}

void draw(){
  background(PedalConstants.backgroundCol);
  if (frameCount - lastFrameMouseMove  < 60){ // under two seconds
    showMainButtons();
  }
  else{ //  over two seconds
     hideMainButtons();
  }
  
  theDataProvider.checkForIncoming();
  
  if (displayMode == PedalConstants.pedalDisplay){
    for (PowerDisplay pd : theDisplayElements)
    {
      pd.renderOnScreen();
    }
  }
}

public void initButtons()
{
  showPowerButton = cp5.addButton("showPowerButton")
    .setCaptionLabel("Power Display")
    ;
  
  showSettingsButton = cp5.addButton("whoSettingsButton")
    .setCaptionLabel("SETTINGS")
    ;
    
   allMainButtons = new Button[2];
   allMainButtons[0] = showPowerButton;
   allMainButtons[1] = showSettingsButton;
   
   for (Button b : allMainButtons){
    b.setBroadcast(false)
      .setSize((int)(PedalConstants.BUTTON_WIDTH*2.5f), PedalConstants.BUTTON_HEIGHT)
      ;
   }
   
   showPowerButton.setPosition(width/16,0)
     ;
     
   showSettingsButton.setPosition(showPowerButton.getWidth()+ showPowerButton.getPosition()[0] + PedalConstants.MARGIN, 0);
    
   showPowerButton.addCallback(new CallbackListener(){
       public void controlEvent (CallbackEvent ce)
       {
         if (ce.getAction() ==  ControlP5.ACTION_PRESS){
             displayMode = PedalConstants.pedalDisplay;
             
             for (PowerDisplay pd : theDisplayElements)
             {
                pd.show(); 
             }
             
             settingsDisp.hide();
         }
       }
   });
   
   showSettingsButton.addCallback(new CallbackListener(){
       public void controlEvent (CallbackEvent ce)
       {
         if (ce.getAction() ==  ControlP5.ACTION_PRESS){
           displayMode = PedalConstants.settingsDisplay;
           
           for (PowerDisplay pd : theDisplayElements)
             {
                pd.hide(); 
             }
           
           settingsDisp.show();
         }
       }
   }); 
}

public void showMainButtons()
{
   for (Button b : allMainButtons){
    b.setVisible(true); 
   }
}

public void hideMainButtons(){
  for (Button b : allMainButtons){
    b.setVisible(false); 
   }
}

public void mouseMoved()
{
  lastFrameMouseMove = frameCount;
}

public void initDisplayElements()
{
  theDisplayElements = new ArrayList<PowerDisplay>();
  for (int i = 0; i < PedalConstants.numDisplays; i++)
  {
    theDisplayElements.add(new PowerDisplay(cp5,i));
  }
  
  theDisplayElements.get(0).setPosition(0, 0, width/2, height/2);
  theDisplayElements.get(0).setBackColor(PedalConstants.allCols[0], PedalConstants.dimCols[0]);
  
  theDisplayElements.get(1).setPosition(width/2, 0, width/2, height/2);
  theDisplayElements.get(1).setBackColor(PedalConstants.allCols[1], PedalConstants.dimCols[1]);
  
  theDisplayElements.get(2).setPosition(0, height/2, width/2, height/2);
  theDisplayElements.get(2).setBackColor(PedalConstants.allCols[2], PedalConstants.dimCols[2]);
  
  theDisplayElements.get(3).setPosition(width/2, height/2, width/2, height/2);
  theDisplayElements.get(3).setBackColor(PedalConstants.allCols[3], PedalConstants.dimCols[3]); 
}

public String getDateTimeString()
{
 String toReturn = "";
 toReturn += year();
 toReturn += "_";
 toReturn += month();
 toReturn += "_";
 toReturn += day();
 toReturn += "_";
 toReturn += hour();
 toReturn += "_";
 toReturn += minute();
 toReturn += "_";
 toReturn += second();
 return toReturn;
}