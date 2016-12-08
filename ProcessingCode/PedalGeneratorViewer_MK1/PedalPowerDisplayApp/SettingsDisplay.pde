public class SettingsDisplay{
 
  ControlP5 cp5;
  Button[] whichSerialPortButtons;
  Button[] playerSelectButtons ;
  SerialInterface si;
  PFont settingsFont = createFont("BEBAS___", height / 40);
  ArrayList<PowerDisplay> pedalDisplays;
  int[] colorCycler;
  PedalConstants colorDefs;
  ArrayList<Button> allButtons;
  Textlabel comPortLabel;
  Textlabel selectedLabel;
  boolean hasActiveCOMPort = false;
  
  
  public SettingsDisplay(ControlP5 theCp5In, SerialInterface siIn, ArrayList<PowerDisplay> pedalDisplaysIn)
  {
    colorDefs = new PedalConstants();
     cp5 = theCp5In;
     si = siIn;
     pedalDisplays = pedalDisplaysIn;
     initControls();
     placeControls();
     initBehaviours();
     initAllButtonsArray();
     colorCycler = new int[] {0,0,0,0};
     selectedLabel = cp5.addLabel("selectedCOMPORTLabel");
     selectedLabel.setFont(createFont("BEBAS___", height / 32));
     selectedLabel.setText("< selected");
     selectedLabel.hide();
  }
  
  public void show(){
     for (Button b : allButtons)
     {
       b.setVisible(true);
     }
     
     if (comPortLabel != null){
       comPortLabel.setVisible(true);
     }
     
     if (hasActiveCOMPort){
       selectedLabel.setVisible(true);
     }     
  }
  
  public void hide(){
    for (Button b : allButtons)
    {
      b.setVisible(false);    
    }
    
    if (comPortLabel != null){
      comPortLabel.setVisible(false);
    }
    
    selectedLabel.setVisible(false);
    
  }
  
  public void renderOnScreen()
  {
    
  }
  
  public void initControls(){
    
    whichSerialPortButtons = new Button[si.getCOMPortList().length];
    for (byte b = 0; b < si.getCOMPortList().length; b++ ){
      whichSerialPortButtons[b] = cp5.addButton(si.getCOMPortList()[b])
        .setSize(width / 4, PedalConstants.BUTTON_HEIGHT*2)
        .setFont(settingsFont)
        ;
    }
    
    if (whichSerialPortButtons.length == 0){
     comPortLabel = cp5.addLabel("No COM Port Found.").setPosition(width/4, height/2);
    }    
    
    playerSelectButtons = new Button[PedalConstants.numDisplays];
    for (byte b = 0; b < playerSelectButtons.length; b++)
    {
      playerSelectButtons[b] = cp5.addButton("Player " + (b+1) + " colour" );
      playerSelectButtons[b].setSize(width/4, height/16);
      playerSelectButtons[b].setFont(settingsFont);
      CColor tempCol = new CColor();
      tempCol.setBackground(PedalConstants.allCols[b]);
      tempCol.setCaptionLabel(0);
      playerSelectButtons[b].setColor(tempCol);
    }   
  }
  
  public void placeControls()
  {
    for (byte b = 0; b < whichSerialPortButtons.length; b++)
    {
      whichSerialPortButtons[b].setPosition(width / 32, (height / 16) + (b*whichSerialPortButtons[b].getHeight()*1.25f)); 
    }
    
    int standardOffsetX = width/4;
    int standardOffsetY = height/16;
    int yPosPSB = height/16;
    if (whichSerialPortButtons.length > 0){    
      yPosPSB = (int)whichSerialPortButtons[0].getPosition()[1]; 
    }
    
    playerSelectButtons[0].setPosition((width / 2), yPosPSB);
    playerSelectButtons[1].setPosition((width / 2) + standardOffsetX, yPosPSB);
    playerSelectButtons[2].setPosition((width / 2), yPosPSB + standardOffsetY);
    playerSelectButtons[3].setPosition((width / 2) + standardOffsetX, yPosPSB + standardOffsetY);    
  }  


  public void initBehaviours()
  {
    for (byte b = 0; b < playerSelectButtons.length; b++){
      final byte whichPlayer = b;
      playerSelectButtons[b].addCallback(new CallbackListener(){
         public void controlEvent(CallbackEvent ce)
         {
           if (ce.getAction() ==  ControlP5.ACTION_PRESS){
             colorCycler[whichPlayer] ++;
             colorCycler[whichPlayer] %= 4;
             pedalDisplays.get(whichPlayer).setBackColor(PedalConstants.allCols[colorCycler[whichPlayer]], PedalConstants.dimCols[colorCycler[whichPlayer]]);
             CColor col = new CColor();
             col.setBackground(PedalConstants.allCols[colorCycler[whichPlayer]]);
             col.setForeground(PedalConstants.allCols[colorCycler[whichPlayer]]);
             playerSelectButtons[whichPlayer].setColor(col);
             col = null;
           }
         }
      });
    }
    
    int indexSerial = 0;
    for (final Button b : whichSerialPortButtons){
      final int indexSerialFinal = indexSerial;
      b.addCallback(new CallbackListener(){
        public void controlEvent(CallbackEvent ce){          
          if (ce.getAction() == ControlP5.ACTION_PRESS){
            si.setCOMPort(si.getCOMPortList()[indexSerialFinal]);
            // selected label goes here:
            hasActiveCOMPort = true;
            selectedLabel.show();
            selectedLabel.setPosition(b.getPosition()[0] + b.getWidth(), b.getPosition()[1] + b.getHeight()/4);
          }
        }
        });
      indexSerial++;
    }
  }

  public void initAllButtonsArray()
  {
   allButtons = new ArrayList<Button>();
   
   for (Button b : playerSelectButtons){
    allButtons.add(b); 
   }
   
   for (Button b : whichSerialPortButtons){
    allButtons.add(b); 
   }
  }

}